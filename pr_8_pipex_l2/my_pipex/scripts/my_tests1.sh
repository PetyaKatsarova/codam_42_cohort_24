#!/bin/bash

# Define test input and output files
INPUT_FILE="texts/test_input.txt"
OUTPUT_FILE="texts/test_output.txt"
SHELL_OUTPUT="texts/shell_output.txt"

# Create a test input file
echo -e "apple\nbanana\ncat\ndog\nexample\nfish\n" > $INPUT_FILE

# Run the tests
run_test() {
    local description="$1"
    local cmd1="$2"
    local cmd2="$3"
    local output_file="$4"

    echo "Running: $description"

    # Run ./pipex and capture its output
    ./pipex "$INPUT_FILE" "$cmd1" "$cmd2" "$output_file"

    # Run the same commands directly in the shell
    bash -c "< $INPUT_FILE $cmd1 | $cmd2 > $SHELL_OUTPUT"

    # Display the outputs
    echo "Output from pipex ($output_file):"
    cat "$output_file"
    echo

    echo "Output from shell execution ($SHELL_OUTPUT):"
    cat "$SHELL_OUTPUT"
    echo

    echo "-----------------------------------------"
}

# Clean up old files
rm -f $OUTPUT_FILE $SHELL_OUTPUT

run_test "ls -l | wc -l" "ls -l" "wc -l" $OUTPUT_FILE
run_test "grep a | wc -w" "grep a" "wc -w" $OUTPUT_FILE
run_test "sort | head -n 3" "sort" "head -n 3" $OUTPUT_FILE
run_test "pwd --help | cat" "pwd --help" "cat" $OUTPUT_FILE
run_test "tr a-z A-Z | wc" "tr a-z A-Z" "wc -l" $OUTPUT_FILE
run_test "rev | wc -c" "rev" "wc -c" $OUTPUT_FILE
run_test "./run_script.sh | wc" "./run_script.sh" "wc" $OUTPUT_FILE
# ./pipex lucky.txt 'sed s/And/But/' 'grep But' outfile_pip.txt
run_test "'sed s/And/But/' 'grep But'" 'sed s/And/BLA/' 'grep BLA' $OUTPUT_FILE

run_test "sed s/And/BUT/g | grep But" "sed s/And/BUT/g" "grep BUT" $OUTPUT_FILE

run_test "./run_script.sh | wc" "./run_script.sh" "wc" $OUTPUT_FILE

# Clean up
rm -f $INPUT_FILE $OUTPUT_FILE $SHELL_OUTPUT
