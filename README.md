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
./bin/interrupts trace.txt vector_table.txt device_table.txt
```

#### 4. Check the results

```sh
cat execution.txt
```

### Running simulations

#### trace.txt

```sh
source build.sh; ./bin/interrupts trace.txt vector_table.txt device_table.txt; cat execution.txt
```

#### trace_1.txt

```sh
source build.sh; ./bin/interrupts testcases/trace_1.txt vector_table.txt device_table.txt; cat execution.txt
```

#### trace_2.txt

```sh
source build.sh; ./bin/interrupts testcases/trace_2.txt vector_table.txt device_table.txt; cat execution.txt
```

#### trace_3.txt

```sh
source build.sh; ./bin/interrupts testcases/trace_3.txt vector_table.txt device_table.txt; cat execution.txt
```

#### trace_4.txt

```sh
source build.sh; ./bin/interrupts testcases/trace_4.txt vector_table.txt device_table.txt; cat execution.txt
```

#### trace_5.txt

```sh
source build.sh; ./bin/interrupts testcases/trace_5.txt vector_table.txt device_table.txt; cat execution.txt
```

### Python

#### 1. Create virtual environment

```sh
python -m venv venv
```

#### 2. Activate virtual environment

```sh
venv/scripts/activate
```

#### 3. Run `main.py` script

```sh
python main.py
```
