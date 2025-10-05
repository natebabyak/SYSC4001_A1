/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */

#include <interrupts.hpp>

#define SAVE_RESTORE_CONTEXT_TIME 10
#define ISR_ACTIVITY_TIME 40

int main(int argc, char **argv)
{
    // vectors is a C++ std::vector of strings that contain the address of the ISR
    // delays  is a C++ std::vector of ints that contain the delays of each device
    // the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;     //!< string to store single line of trace file
    std::string execution; //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/

    int current_time = 0;

    auto log = [&](int duration, std::string activity)
    {
        execution += std::to_string(current_time) + ", " + std::to_string(duration) + ", " + activity + '\n';
        current_time += duration;
    };

    auto handle_cpu = [&](int duration) {
        log(duration, "CPU burst");
    };

    auto handle_syscall = [&](int device)
    {
        auto [exec, curr] = intr_boilerplate(current_time, device, SAVE_RESTORE_CONTEXT_TIME, vectors);
        execution += exec;
        current_time = curr;

        int remaining_time = delays[device];

        if (remaining_time >= ISR_ACTIVITY_TIME) {
            log(ISR_ACTIVITY_TIME, "SYSCALL: run the ISR (device driver)");
            remaining_time -= ISR_ACTIVITY_TIME;
        } else if (remaining_time > 0) {
            log(remaining_time, "SYSCALL: run the ISR (device driver)");
            remaining_time = 0;
        }

        if (remaining_time >= ISR_ACTIVITY_TIME) {
            log(ISR_ACTIVITY_TIME, "transfer data from device to memory");
            remaining_time -= ISR_ACTIVITY_TIME;
        } else if (remaining_time > 0) {
            log(remaining_time, "transfer data from device to memory");
            remaining_time = 0;
        }

        if (remaining_time > 0) {
            log(remaining_time, "check for errors");
            remaining_time = 0;
        }

        log(1, "IRET");
    };

    auto handle_end_io = [&](int device)
    {
        auto [exec, curr] = intr_boilerplate(current_time, device, SAVE_RESTORE_CONTEXT_TIME, vectors);
        execution += exec;
        current_time = curr;

        int remaining_time = delays[device];

        if (remaining_time >= ISR_ACTIVITY_TIME) {
            log(ISR_ACTIVITY_TIME, "ENDIO: run the ISR (device driver)");
            remaining_time -= ISR_ACTIVITY_TIME;
        } else if (remaining_time > 0) {
            log(remaining_time, "ENDIO: run the ISR (device driver)");
            remaining_time = 0;
        }

        if (remaining_time > 0) {
            log(remaining_time, "check device status");
            remaining_time = 0;
        }
        
        log(1, "IRET");
    };

    /******************************************************************/

    // parse each line of the input trace file
    while (std::getline(input_file, trace))
    {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/

        if (activity == "CPU")
        {
            handle_cpu(duration_intr);
        }
        else if (activity == "SYSCALL")
        {
            handle_syscall(duration_intr);
        }
        else if (activity == "END_IO")
        {
            handle_end_io(duration_intr);
        }

        /************************************************************************/
    }

    input_file.close();

    write_output(execution);

    return 0;
}