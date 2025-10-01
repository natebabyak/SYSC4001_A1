import os

path = 'output_files'


def main():
    overhead_time = 0
    program_time = 0

    for file in os.scandir(path):
        with open(file, "r") as f:
            lines = f.readlines()

            for line in lines:
                values = line.split()

                if values[2] == "CPU burst":
                    overhead_time += int(values[1])
                else:
                    program_time += int(values[1])


if __name__ == "__main__":
    main()
