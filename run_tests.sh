#!/bin/bash

# Parameters
methods=("hc" "sa" "mhc" "csp" "ga")
N_values=(8 8 8 10 10 10 15 15 15 20 20 20 30)
M_values=(8 8 8 10 10 10 15 15 15 20 20 20 30)
Q_values=(8 0 8 10 0 10 15 0 15 20 0 20 30)
K_values=(0 8 8 0 10 10 0 15 15 0 20 20 0)
tmax=120

# Create output directory if it doesn't exist
mkdir -p outputs

# Check if a specific method is provided
if [ $# -eq 1 ]; then
  specific_method=$1
  if [[ ! " ${methods[@]} " =~ " ${specific_method} " ]]; then
    echo "Invalid method: ${specific_method}. Valid methods are: ${methods[@]}"
    exit 1
  fi
  methods=($specific_method)
fi

# Run for each combination
for method in "${methods[@]}"; do
  for i in "${!N_values[@]}"; do
    N=${N_values[$i]}
    M=${M_values[$i]}
    Q=${Q_values[$i]}
    K=${K_values[$i]}
    output_file="outputs/${method}-${N}-${M}-${Q}-${K}-${tmax}.txt"
    ./main $N $M $Q $K $tmax $output_file $method
  done
done
