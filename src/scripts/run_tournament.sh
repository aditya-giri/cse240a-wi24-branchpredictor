#!/bin/bash

# Define output file
output_file="../../report/tournament_results.txt"
> "$output_file"
# List of trace files
traces=("int_1.bz2" "int_2.bz2" "fp_1.bz2" "fp_2.bz2" "mm_1.bz2" "mm_2.bz2")

echo "Evaluating Tournament predictor on all traces..."

# Loop through trace files
for trace in "${traces[@]}"; do
    echo "$trace:" >> "$output_file"
    # Loop through tournament configurations
    for ((i = 5; i <= 20; i++)); do
        config="$i:$((i+1)):$((i+1))"
        echo "Tournament_$config:" >> "$output_file"
        # Run the command with the current trace file and tournament configuration
        bunzip2 -kc "../../traces/$trace" | ../predictor --tournament:$config >> "$output_file"
    done
    echo "======" >> "$output_file"
done
echo "Execution completed. Output written to $output_file."
