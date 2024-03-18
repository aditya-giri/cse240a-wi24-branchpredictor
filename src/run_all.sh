make clean
make
echo "Begin"
echo "int_1:" >> res.txt
echo "Gshare:" >> res.txt
bunzip2 -kc ../traces/int_1.bz2 | ./predictor --gshare:13 >> res.txt
echo "Tournament:" >> res.txt
bunzip2 -kc ../traces/int_1.bz2 | ./predictor --tournament:9:10:10 >> res.txt
echo "Custom:" >> res.txt
bunzip2 -kc ../traces/int_1.bz2 | ./predictor --custom >> res.txt
echo "======" >> res.txt
echo "int_2:" >> res.txt
echo "Gshare:" >> res.txt
bunzip2 -kc ../traces/int_2.bz2 | ./predictor --gshare:13 >> res.txt
echo "Tournament:" >> res.txt
bunzip2 -kc ../traces/int_2.bz2 | ./predictor --tournament:9:10:10 >> res.txt
echo "Custom:" >> res.txt
bunzip2 -kc ../traces/int_2.bz2 | ./predictor --custom >> res.txt
echo "======" >> res.txt
echo "fp_1:" >> res.txt
echo "Gshare:" >> res.txt
bunzip2 -kc ../traces/fp_1.bz2 | ./predictor --gshare:13 >> res.txt
echo "Tournament:" >> res.txt
bunzip2 -kc ../traces/fp_1.bz2 | ./predictor --tournament:9:10:10 >> res.txt
echo "Custom:" >> res.txt
bunzip2 -kc ../traces/fp_1.bz2 | ./predictor --custom >> res.txt
echo "======" >> res.txt
echo "fp_2:" >> res.txt
echo "Gshare:" >> res.txt
bunzip2 -kc ../traces/fp_2.bz2 | ./predictor --gshare:13 >> res.txt
echo "Tournament:" >> res.txt
bunzip2 -kc ../traces/fp_2.bz2 | ./predictor --tournament:9:10:10 >> res.txt
echo "Custom:" >> res.txt
bunzip2 -kc ../traces/fp_2.bz2 | ./predictor --custom >> res.txt
echo "======" >> res.txt
echo "mm_1:" >> res.txt
echo "Gshare:" >> res.txt
bunzip2 -kc ../traces/mm_1.bz2 | ./predictor --gshare:13 >> res.txt
echo "Tournament:" >> res.txt
bunzip2 -kc ../traces/mm_1.bz2 | ./predictor --tournament:9:10:10 >> res.txt
echo "Custom:" >> res.txt
bunzip2 -kc ../traces/mm_1.bz2 | ./predictor --custom >> res.txt
echo "======" >> res.txt
echo "mm_2:" >> res.txt
echo "Gshare:" >> res.txt
bunzip2 -kc ../traces/mm_2.bz2 | ./predictor --gshare:13 >> res.txt
echo "Tournament:" >> res.txt
bunzip2 -kc ../traces/mm_2.bz2 | ./predictor --tournament:9:10:10 >> res.txt
echo "Custom:" >> res.txt
bunzip2 -kc ../traces/mm_2.bz2 | ./predictor --custom >> res.txt
echo "======" >> res.txt
echo "DONE"
