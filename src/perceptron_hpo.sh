#!/bin/bash

# Define output file
output_file="../report/perceptron_hpo.txt"
> "$output_file"
# List of trace files
traces=("int_1.bz2" "int_2.bz2" "fp_1.bz2" "fp_2.bz2" "mm_1.bz2" "mm_2.bz2")

# Loop through trace files
echo "Starting HPO of perceptron...."

for trace in "${traces[@]}"; do
    # Loop through x values such that param ranges from 14 to 100
    for ((x=6; x<=44; x+=2)); do
        # Calculate param based on the formula
        param=$(echo "scale=2; 1.93 * $x + 14" | bc)
        
        # Run the command with the current trace file and parameter
        output=$(bunzip2 -kc "../traces/$trace" | ./predictor --custom$param | grep "Misprediction Rate:" | awk -v trace="$trace" -v param="$param" '{print trace "," param "," $3}')
        
        # Append output to the output file
        echo "$output" >> "$output_file"
    done
done

echo "Execution completed. Output appended to $output_file."
