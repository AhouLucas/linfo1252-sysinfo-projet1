#!/bin/bash

threads=(2 4 8 16 32)
iterations=5


# philosophe
echo "2 threads,4 threads,8 threads,16 threads,32 threads" > csv/philosophe.csv
for ((i=1; i<=iterations; i++)); do
    real_time=""
    for thread in "${threads[@]}"; do
        time_value=$( (time -p ./bin/philosophe -n $thread) 2>&1 | grep real | awk '{print $2}')
        real_time+="$time_value,"
    done
    # Remove the last comma
    real_time=${real_time%?}
    echo "$real_time" >> csv/philosophe.csv
done

# prodcons
echo "2 threads,4 threads,8 threads,16 threads,32 threads" > csv/prodcons.csv
for ((i=1; i<=iterations; i++)); do
    real_time=""
    for thread in "${threads[@]}"; do
        p=$(($thread/2))
        c=$(($thread/2))
        time_value=$( (time -p ./bin/prodcons -p $p -c $c) 2>&1 | grep real | awk '{print $2}')
        real_time+="$time_value,"
    done
    # Remove the last comma
    real_time=${real_time%?}
    echo "$real_time" >> csv/prodcons.csv
done

# readerwriter
echo "2 threads,4 threads,8 threads,16 threads,32 threads" > csv/readerwriter.csv
for ((i=1; i<=iterations; i++)); do
    real_time=""
    for thread in "${threads[@]}"; do
        r=$(($thread/2))
        w=$(($thread/2))
        time_value=$( (time -p ./bin/readerwriter -r $r -w $w) 2>&1 | grep real | awk '{print $2}')
        real_time+="$time_value,"
    done
    # Remove the last comma
    real_time=${real_time%?}
    echo "$real_time" >> csv/readerwriter.csv
done

# test_and_set_perf
echo "1 threads,2 threads,4 threads,8 threads,16 threads,32 threads" > csv/test_and_set_perf.csv
for ((i=1; i<=iterations; i++)); do
    real_time=""
    for thread in {1,2,4,8,16,32}; do
        time_value=$( (time -p ./bin/test_and_set_perf -n $thread) 2>&1 | grep real | awk '{print $2}')
        real_time+="$time_value,"
    done
    # Remove the last comma
    real_time=${real_time%?}
    echo "$real_time" >> csv/test_and_set_perf.csv
done

# test_and_test_and_set_perf
echo "1 threads,2 threads,4 threads,8 threads,16 threads,32 threads" > csv/test_and_test_and_set_perf.csv
for ((i=1; i<=iterations; i++)); do
    real_time=""
    for thread in {1,2,4,8,16,32}; do
        time_value=$( (time -p ./bin/test_and_test_and_set_perf -n $thread) 2>&1 | grep real | awk '{print $2}')
        real_time+="$time_value,"
    done
    # Remove the last comma
    real_time=${real_time%?}
    echo "$real_time" >> csv/test_and_test_and_set_perf.csv
done

# write the csv to stdout
cat csv/philosophe.csv
cat csv/prodcons.csv
cat csv/readerwriter.csv
cat csv/test_and_set_perf.csv
cat csv/test_and_test_and_set_perf.csv