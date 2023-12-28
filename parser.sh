#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file_path>"
    exit 1
fi

# Extract the file path from the command line argument
file_path=$1

# Construct the command with the provided file path
command="od -c -A d -t x2z --endian=big -v $file_path | cut -c 9- | tr -d '[:space:]'

# Run the command
eval $command