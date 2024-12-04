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

echo "2 threads,4 threads,8 threads,16 threads,32 threads" > csv/philosophe_tas.csv
for ((i=1; i<=iterations; i++)); do
    real_time=""
    for thread in "${threads[@]}"; do
        time_value=$( (time -p ./bin/philosophe_tas -n $thread) 2>&1 | grep real | awk '{print $2}')
        real_time+="$time_value,"
    done
    # Remove the last comma
    real_time=${real_time%?}
    echo "$real_time" >> csv/philosophe_tas.csv
done

echo "2 threads,4 threads,8 threads,16 threads,32 threads" > csv/philosophe_tatas.csv
for ((i=1; i<=iterations; i++)); do
    real_time=""
    for thread in "${threads[@]}"; do
        time_value=$( (time -p ./bin/philosophe_tatas -n $thread) 2>&1 | grep real | awk '{print $2}')
        real_time+="$time_value,"
    done
    # Remove the last comma
    real_time=${real_time%?}
    echo "$real_time" >> csv/philosophe_tatas.csv
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

echo "2 threads,4 threads,8 threads,16 threads,32 threads" > csv/prodcons_tas.csv
for ((i=1; i<=iterations; i++)); do
    real_time=""
    for thread in "${threads[@]}"; do
        p=$(($thread/2))
        c=$(($thread/2))
        time_value=$( (time -p ./bin/prodcons_tas -p $p -c $c) 2>&1 | grep real | awk '{print $2}')
        real_time+="$time_value,"
    done
    # Remove the last comma
    real_time=${real_time%?}
    echo "$real_time" >> csv/prodcons_tas.csv
done

echo "2 threads,4 threads,8 threads,16 threads,32 threads" > csv/prodcons_tatas.csv
for ((i=1; i<=iterations; i++)); do
    real_time=""
    for thread in "${threads[@]}"; do
        p=$(($thread/2))
        c=$(($thread/2))
        time_value=$( (time -p ./bin/prodcons_tatas -p $p -c $c) 2>&1 | grep real | awk '{print $2}')
        real_time+="$time_value,"
    done
    # Remove the last comma
    real_time=${real_time%?}
    echo "$real_time" >> csv/prodcons_tatas.csv
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

echo "2 threads,4 threads,8 threads,16 threads,32 threads" > csv/readerwriter_tas.csv
for ((i=1; i<=iterations; i++)); do
    real_time=""
    for thread in "${threads[@]}"; do
        r=$(($thread/2))
        w=$(($thread/2))
        time_value=$( (time -p ./bin/readerwriter_tas -r $r -w $w) 2>&1 | grep real | awk '{print $2}')
        real_time+="$time_value,"
    done
    # Remove the last comma
    real_time=${real_time%?}
    echo "$real_time" >> csv/readerwriter_tas.csv
done

echo "2 threads,4 threads,8 threads,16 threads,32 threads" > csv/readerwriter_tatas.csv
for ((i=1; i<=iterations; i++)); do
    real_time=""
    for thread in "${threads[@]}"; do
        r=$(($thread/2))
        w=$(($thread/2))
        time_value=$( (time -p ./bin/readerwriter_tatas -r $r -w $w) 2>&1 | grep real | awk '{print $2}')
        real_time+="$time_value,"
    done
    # Remove the last comma
    real_time=${real_time%?}
    echo "$real_time" >> csv/readerwriter_tatas.csv
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
cat csv/philosophe_tas.csv
cat csv/philosophe_tatas.csv


cat csv/prodcons.csv
cat csv/prodcons_tas.csv
cat csv/prodcons_tatas.csv

cat csv/readerwriter.csv
cat csv/readerwriter_tas.csv
cat csv/readerwriter_tatas.csv


cat csv/test_and_set_perf.csv
cat csv/test_and_test_and_set_perf.csv