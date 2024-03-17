echo "\nFor int_1 trace and configuration: 10"
bunzip2 -kc ../traces/int_1.bz2 | ./predictor --gshare:13
echo "\nFor int_2 trace and configuration: 10"
bunzip2 -kc ../traces/int_2.bz2 | ./predictor --gshare:13
echo "\nFor fp_1 trace and configuration: 10"
bunzip2 -kc ../traces/fp_1.bz2 | ./predictor --gshare:13
echo "\nFor fp_2 trace and configuration: 10"
bunzip2 -kc ../traces/fp_2.bz2 | ./predictor --gshare:13
echo "\nFor mm_1 trace and configuration: 10"
bunzip2 -kc ../traces/mm_1.bz2 | ./predictor --gshare:13
echo "\nFor mm_2 trace and configuration: 10"
bunzip2 -kc ../traces/mm_2.bz2 | ./predictor --gshare:13