echo "\nFor int_1 trace and configuration: 10"
bunzip2 -kc ../traces/int_1.bz2 | ./predictor --tournament:10:11:11
echo "\nFor int_2 trace and configuration: 10"
bunzip2 -kc ../traces/int_2.bz2 | ./predictor --tournament:10:11:11
echo "\nFor fp_1 trace and configuration: 10"
bunzip2 -kc ../traces/fp_1.bz2 | ./predictor --tournament:10:11:11
echo "\nFor fp_2 trace and configuration: 10"
bunzip2 -kc ../traces/fp_2.bz2 | ./predictor --tournament:10:11:11
echo "\nFor mm_1 trace and configuration: 10"
bunzip2 -kc ../traces/mm_1.bz2 | ./predictor --tournament:10:11:11
echo "\nFor mm_2 trace and configuration: 10"
bunzip2 -kc ../traces/mm_2.bz2 | ./predictor --tournament:10:11:11