#!/bin/bash

# Define the executables and the number of threads
executables=("philosophe" "prodcons" "readerwriter")
threads=(2 4 8 16 32)
iterations=5

# Function to run the executable with the given number of threads and capture the execution time
run_executable() {
    local executable=$1
    local thread=$2
    local time=$(./$executable $thread) # Assuming the executable prints the execution time
    echo $time
}

# Loop through each executable
for executable in "${executables[@]}"; do
    # Create a CSV file for the executable
    csv_file="${executable}.csv"
    echo "Threads,2,4,8,16,32" > $csv_file

    # Loop through the number of iterations
    for ((i=1; i<=iterations; i++)); do
        row="$i"
        # Loop through each thread count
        for thread in "${threads[@]}"; do
            time=$(run_executable $executable $thread)
            row="$row,$time"
        done
        echo $row >> $csv_file
    done
done