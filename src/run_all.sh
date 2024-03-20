#!/bin/bash

# Define output file
output_file="../report/combined_results.txt"
> "$output_file"
# List of trace files
traces=("int_1.bz2" "int_2.bz2" "fp_1.bz2" "fp_2.bz2" "mm_1.bz2" "mm_2.bz2")

# List of predictor types
predictors=("Gshare" "Tournament" "Custom")

echo "Evaluating all predictors on all traces..."

# Loop through trace files
for trace in "${traces[@]}"; do
    echo "$trace:" >> "$output_file"
    # Loop through predictor types
    for predictor in "${predictors[@]}"; do
        echo "$predictor:" >> "$output_file"
        # Run the command with the current trace file and predictor type
        if [ "$predictor" == "Gshare" ]; then
            bunzip2 -kc "../traces/$trace" | ./predictor --gshare:13 >> "$output_file"
        elif [ "$predictor" == "Tournament" ]; then
            bunzip2 -kc "../traces/$trace" | ./predictor --tournament:9:10:10 >> "$output_file"
        elif [ "$predictor" == "Custom" ]; then
            bunzip2 -kc "../traces/$trace" | ./predictor --custom37 >> "$output_file"
        fi
    done
    echo "======" >> "$output_file"
done
echo "Execution completed. Output written to $output_file."
