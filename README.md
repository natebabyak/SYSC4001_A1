# SYSC 4001 Assignment 1

Part II - Design and Implementation of an Interrupts Simulator

## Usage

### Getting Started

#### 1. Clone the repository

```sh
git clone https://github.com/natebabyak/SYSC4001_A1.git
```

#### 2. Compile the project

```sh
source build.sh
```

#### 3. Run the simulation

```sh
./bin/interrupts input_files/trace.txt vector_table.txt device_table.txt
```

#### 4. Check the results

```sh
cat execution.txt
```

### Running Simulations

#### 1. Run simulations with varying context times

```sh
mkdir -p output_files

sed -i "10s/.*/#define SAVE_RESTORE_CONTEXT_TIME 10/" interrupts.cpp
sed -i "11s/.*/#define ISR_ACTIVITY_TIME 40/" interrupts.cpp

for context in 10 20 30; do
    sed -i "10s/.*/#define SAVE_RESTORE_CONTEXT_TIME $context/" interrupts.cpp

    source build.sh;

    for ((trace=1; trace<=5; trace++)); do
        ./bin/interrupts input_files/trace_${trace}.txt vector_table.txt device_table.txt
        mv execution.txt output_files/execution_context_${context}_${trace}.txt
    done
done

sed -i "10s/.*/#define SAVE_RESTORE_CONTEXT_TIME 10/" interrupts.cpp
```

#### 2. Run simulations with varying activity times

```sh
mkdir -p output_files

sed -i "10s/.*/#define SAVE_RESTORE_CONTEXT_TIME 10/" interrupts.cpp
sed -i "11s/.*/#define ISR_ACTIVITY_TIME 40/" interrupts.cpp

for activity in 40 120 200; do
    sed -i "11s/.*/#define ISR_ACTIVITY_TIME $activity/" interrupts.cpp

    source build.sh;

    for ((trace=1; trace<=5; trace++)); do
        ./bin/interrupts input_files/trace_${trace}.txt vector_table.txt device_table.txt
        mv execution.txt output_files/execution_activity_${activity}_${trace}.txt
    done
done

sed -i "11s/.*/#define ISR_ACTIVITY_TIME 40/" interrupts.cpp
```
