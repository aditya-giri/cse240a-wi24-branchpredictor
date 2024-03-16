#! /bin/bash

for var in "$@"
do
    echo "\nFor int_1 trace and configuration: $var"
    bunzip2 -kc ../traces/int_1.bz2 | ./predictor --custom:$var
done

echo "\nint_1 is done, now running for int_2\n"

for var in "$@"
do
    echo "\nFor int_2 trace and configuration: $var"
    bunzip2 -kc ../traces/int_2.bz2 | ./predictor --custom:$var
done

echo "\nint_2 is done, now running for mm_1\n"

for var in "$@"
do
    echo "\nFor mm_1 trace and configuration: $var"
    bunzip2 -kc ../traces/mm_1.bz2 | ./predictor --custom:$var
done

echo "\nmm_1 is done, now running for mm_2\n"

for var in "$@"
do
    echo "\nFor mm_2 trace and configuration: $var"
    bunzip2 -kc ../traces/mm_2.bz2 | ./predictor --custom:$var
done

echo "\nmm_2 is done, now running for fp_1\n"

for var in "$@"
do
    echo "\nFor fp_1 trace and configuration: $var"
    bunzip2 -kc ../traces/fp_1.bz2 | ./predictor --custom:$var
done

echo "\nfp_1 is done, now running for fp_2\n"

for var in "$@"
do
    echo "\nFor fp_2 trace and configuration: $var"
    bunzip2 -kc ../traces/fp_2.bz2 | ./predictor --custom:$var
done