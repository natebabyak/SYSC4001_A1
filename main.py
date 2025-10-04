import os

INPUT_DIR = "input_files/testcases"
OUTPUT_DIR = "output_files"

SAVE_RESTORE_CONTEXT_TIMES = [10, 20, 30]
ISR_ACTIVITY_TIMES = [40, 80, 120, 160, 200]


def main():
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

    overhead_time = 0
    program_time = 0

    return

    for entry in os.scandir(path):
        with open(entry, "r") as file:
            lines = file.readlines()

            for line in lines:
                values = line.split()

                if values[2] == "CPU burst":
                    overhead_time += int(values[1])
                else:
                    program_time += int(values[1])


if __name__ == "__main__":
    main()
