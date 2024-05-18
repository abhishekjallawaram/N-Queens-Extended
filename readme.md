# Knights and Queens Problem Solver

This project implements various optimization algorithms to solve the Knights and Queens problem on an N x M board with Q queens and K knights. The goal is to place all queens and knights on the board such that the number of conflicts is minimized.

## Problem Description

Given an N x M board, Q queens, and K knights, the objective is to place all the queens and knights on the board to minimize conflicts. Conflicts are counted as follows:
1. A knight attacks another knight.
2. A knight attacks a queen.
3. A queen attacks another queen.

Queens attacking knights are not counted as conflicts.

## Algorithms Used

1. Simple Hill Climbing (HC)
2. Simulated Annealing (SA)
3. Memory-Based Simple Hill Climbing
4. CSP (Constraint Satisfaction Problem)
5. Genetic Algorithm

## Goal

The program writes the solution to the specified file. The output includes the board with `K` for knights, `Q` for queens, and `E` for empty positions, followed by the number of conflicts. Example:

```
KKEQK
KQEEE
EEEEQ
EEQEK
QKEEE
0
```


## Environment Setup

### Prerequisites

To run and test the code, you need to have the following installed on your macOS:

- **Xcode Command Line Tools**: This includes the GCC compiler. You can install it by running:
  
```
xcode-select --install
```

- **Visual Studio Code**: A code editor for running and debugging C++ code. You can download it from [here](https://code.visualstudio.com/).

### Setup Instructions

1. **Clone the Repository**:
   ```
   git clone <repository_url> && cd <repository_name>
   ```

2. **Open the Project in Visual Studio Code**:
   ```
   code .
   ```

## Compilation and Execution

### Compilation

To compile the code, open a terminal in VS Code and run the following command:
```
g++ -std=c++14 -o main MainApplication.cpp BoardHelper.cpp SimpleHillClimbing.cpp SimulatedAnnealing.cpp MemoryBasedSimpleHillClimbing.cpp CSPSolver.cpp GeneticAlgorithm.cpp
```
### Execution

After successful compilation, you can run the program with the required arguments:

`./main N M Q K tmax fileName methodName`

- **N**: Number of rows in the board
- **M**: Number of columns in the board
- **Q**: Number of queens
- **K**: Number of knights
- **tmax**: Maximum allowed time (in seconds) for the algorithm
- **fileName**: Output file to save the results
- **methodName**: The name of the method to use (e.g., `hc` for Simple Hill Climbing, `sa` for Simulated Annealing, `mhc` for Memory-Based Simple Hill Climbing, `csp` for CSP (Constraint Satisfaction Problem), `ga` for Genetic Algorithm)

### Example

To run the Simple Hill Climbing algorithm on an 8x8 board with 2 queens and 3 knights, with a time limit of 1000 seconds, and save the output to `output.txt`, use:

```
./main 8 8 2 3 1000 output.txt hc
```

## Code Structure

- **BoardHelper.h/cpp**: Contains utility functions for creating the board, placing queens and knights, and calculating attacks.
- **HillClimbing.h**: Abstract base class for different hill climbing algorithms.
- **SimpleHillClimbing.h/cpp**: Implements the Simple Hill Climbing algorithm.
- **SimulatedAnnealing.h/cpp**: Implements the Simulated Annealing algorithm.
- **MemoryBasedSimpleHillClimbing.h/cpp**: Implements the Memory-Based Simple Hill Climbing algorithm.
- **CSPSolver.h/cpp**: Implements the Constraint Satisfaction Problem Solver.
- **GeneticAlgorithm.h/cpp**: Implements the Genetic Algorithm Solver.
- **MainApplication.cpp**: Contains the main function, argument parsing, and execution logic.


## Running the Tests

A Bash script (run_tests.sh) is provided to run the algorithms with different configurations. The script can run tests for all methods or a specific method.

### Running for All Methods

To run the tests for all methods, execute the script without any arguments:

```
./run_tests.sh
```


### Running for a Specific Method

To run the tests for a specific method, provide the method name as an argument. For example, to run the tests for the Simple Hill Climbing method (hc), use:

```
./run_tests.sh hc
```


### Valid Methods

- `hc`: Simple Hill Climbing
- `sa`: Simulated Annealing
- `mhc`: Memory-Based Hill Climbing
- `csp`: Constraint Satisfaction Problem Solver
- `ga`: Genetic Algorithm Solver

## Script Details

The `run_tests.sh` script runs the algorithms for various board configurations and saves the output in the `outputs` directory.

### Parameters

The script uses the following parameters for testing:

- `N_values`: Array of board sizes (rows)
- `M_values`: Array of board sizes (columns)
- `Q_values`: Array of numbers of queens
- `K_values`: Array of numbers of knights
- `tmax`: Maximum time for the algorithm to run (in seconds)

### Output

The output files are saved in the `outputs` directory with the following naming convention:
```
{method}-{N}-{M}-{Q}-{K}-{tmax}.txt
```


## Example

To run the tests for the Simulated Annealing method:

```
./run_tests.sh sa
```

This will produce output files in the `outputs` directory, such as:

```
outputs/sa-8-8-8-0-120.txt
outputs/sa-10-10-10-0-120.txt
```


Each output file contains the final board configuration, the total number of attacks, and the elapsed time.

## Additional Information

- **Debugging**: Use the built-in debugger in Visual Studio Code to step through the code and inspect variables.
- **Logging**: Add print statements or use a logging library to log intermediate results for debugging purposes.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
