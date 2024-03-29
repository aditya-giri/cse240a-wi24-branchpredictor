output_file="../../report/custom_predictor_results.txt"
> "$output_file"
echo "For int_1 trace and configuration:37"
bunzip2 -kc ../../traces/int_1.bz2 | ../predictor --custom37 >> '../../report/custom_predictor_results.txt'
echo "For int_2 trace and configuration:37"
bunzip2 -kc ../../traces/int_2.bz2 | ../predictor --custom37 >> '../../report/custom_predictor_results.txt'
echo "For fp_1 trace and configuration:37"
bunzip2 -kc ../../traces/fp_1.bz2 | ../predictor --custom37 >> '../../report/custom_predictor_results.txt'
echo "For fp_2 trace and configuration:37"
bunzip2 -kc ../../traces/fp_2.bz2 | ../predictor --custom37 >> '../../report/custom_predictor_results.txt'
echo "For mm_1 trace and configuration:37"
bunzip2 -kc ../../traces/mm_1.bz2 | ../predictor --custom37 >> '../../report/custom_predictor_results.txt'
echo "For mm_2 trace and configuration:37"
bunzip2 -kc ../../traces/mm_2.bz2 | ../predictor --custom37 >> '../../report/custom_predictor_results.txt'