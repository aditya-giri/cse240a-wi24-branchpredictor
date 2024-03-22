#!/bin/bash

# Define output file
output_file="../../report/gshare_results.txt"
> "$output_file"
# List of trace files
traces=("int_1.bz2" "int_2.bz2" "fp_1.bz2" "fp_2.bz2" "mm_1.bz2" "mm_2.bz2")

# List of gshare configurations
gshare_configs=(9 10 11 12 13 14 15 16 17 18 19 20)

echo "Evaluating Gshare predictor on all traces..."

# Loop through trace files
for trace in "${traces[@]}"; do
    echo "$trace:" >> "$output_file"
    # Loop through gshare configurations
    for config in "${gshare_configs[@]}"; do
        echo "Gshare_$config:" >> "$output_file"
        # Run the command with the current trace file and gshare configuration
        bunzip2 -kc "../../traces/$trace" | ../predictor --gshare:$config >> "$output_file"
    done
    echo "======" >> "$output_file"
done
echo "Execution completed. Output written to $output_file."