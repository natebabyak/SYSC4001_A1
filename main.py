from matplotlib import cm
import matplotlib.pyplot as plt
from collections import defaultdict
import os

OUTPUT_DIR = "output_files"


def compute_overhead_and_work_times(file_name: str) -> tuple[int, int]:
    with open(f"{OUTPUT_DIR}/{file_name}", "r") as file:
        lines = file.readlines()

    overhead_time = 0
    work_time = 0

    for line in lines:
        _, duration, activity = line.strip().split(", ")
        duration = int(duration)

        if activity == "CPU burst":
            work_time += duration
        else:
            overhead_time += duration

    return overhead_time, work_time


def main():
    if not os.path.isdir(OUTPUT_DIR):
        raise FileNotFoundError

    data = []

    for entry in os.scandir(OUTPUT_DIR):
        _, var, val, trace_num = entry.name.split("_")

        overhead_time, work_time = compute_overhead_and_work_times(entry.name)
        total_time = overhead_time + work_time
        overhead_pct = (overhead_time / total_time) * 100

        data.append((var, int(val), int(
            trace_num[:-4]), overhead_time, work_time, total_time, overhead_pct))


if __name__ == "__main__":
    main()
