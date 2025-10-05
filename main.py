import os

OUTPUT_DIR = "output_files"


def main():
    if not os.path.isdir(OUTPUT_DIR):
        raise FileNotFoundError

    for entry in os.scandir(OUTPUT_DIR):
        file_name = entry.name.split("_")

        [_, variable, value, trace_num] = file_name

        with open(entry, "r") as file:
            lines = file.readlines()

            for line in lines:
                [time, duration, activity] = line.split()

                if values[2] == "CPU burst":
                    overhead_time += int(values[1])
                else:
                    program_time += int(values[1])


if __name__ == "__main__":
    main()
