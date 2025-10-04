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

    auto log = [&](int duration, std::string event)
    {
        execution += std::to_string(current_time) + ", " + std::to_string(duration) + ", " + event + '\n';
        current_time += duration;
    };

    auto handleSyscall = [&](int intr_num)
    {
        std::pair<std::string, int> res =  intr_boilerplate(current_time, intr_num, SAVE_RESTORE_CONTEXT_TIME, vectors);

        execution += res.first;
        current_time = res.second;

        log(1, "switch to kernel mode");

        log(SAVE_RESTORE_CONTEXT_TIME, "context saved");

        log(1, "find vector " + std::to_string(intr_num) + " in memory position " + std::to_string(intr_num * 2));

        log(1, "obtain ISR address");

        log(ISR_ACTIVITY_TIME, "call device driver");

        log(1, "IRET");
    };

    auto handleEndIo = [&](int device)
    {
        log(delays[device], "end of I/O " + std::to_string(device) + ": interrupt");

        log(1, "switch to kernel mode");

        log(SAVE_RESTORE_CONTEXT_TIME, "context saved");

        log(1, "find vector " + std::to_string(device) + " in memory position " + std::to_string(device * 2));

        log(1, "obtain ISR address");

        log(ISR_ACTIVITY_TIME, "call device driver");

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
            log(duration_intr, "CPU burst");
        }
        else if (activity == "SYSCALL")
        {
            handleSyscall(duration_intr);
        }
        else if (activity == "END_IO")
        {
            handleEndIo(duration_intr);
        }

        /************************************************************************/
    }

    input_file.close();

    write_output(execution);

    return 0;
}