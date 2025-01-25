#!/bin/bash

# Define test input and output files
INPUT_FILE="texts/test_input.txt"
OUTPUT_FILE="texts/test_output.txt"
SHELL_OUTPUT="texts/shell_output.txt"

# Create a test input file
# echo -e "apple\nbanana\ncat\ndog\nexample\nfish\n" > $INPUT_FILE
echo -e "I remember that wonderful instant:
You appeared before me,
Like a fleeting vision,
Like a spirit of pure beauty.

In the anguish of hopeless sadness,
In the worries of noisy bustle,
Your tender voice lingered in my heart,
Your dear features came to me in dreams.

The years passed. The storm's wild gusts
Dispersed my earlier dreams,
And I forgot your tender voice,
Your heavenly features.

In the solitude, in the darkness of confinement,
My days quietly dragged along,
Without divinity, without inspiration,
Without tears, without life, without love.

My soul awoke from its torpor,
And you appeared again,
Like a fleeting vision,
Like a spirit of pure beauty.

And my heart beat in rapture,
And once again revived,
Divinity, inspiration,
Life, tears, and love.
\n" > $INPUT_FILE

# Run the tests
run_test() {
    local description="$1"
    local cmd1="$2"
    local cmd2="$3"
    local output_file="$4"

    echo "Running: $description"

    ./pipex "$INPUT_FILE" "$cmd1" "$cmd2" "$output_file"
    bash -c "< $INPUT_FILE $cmd1 | $cmd2 > $SHELL_OUTPUT"

    echo "Output from pipex ($output_file):"
    cat "$output_file"
    echo

    echo "Output from shell execution ($SHELL_OUTPUT):"
    cat "$SHELL_OUTPUT"
    echo

    # Compare the outputs
    if diff "$output_file" "$SHELL_OUTPUT" > /dev/null; then
        echo "✅ Test passed: Outputs match."
    else
        echo "❌ Test failed: Outputs differ."
        echo "Diff:"
        diff "$output_file" "$SHELL_OUTPUT"
    fi
    echo "-----------------------------------------"
}

# Clean up old files
rm -f $OUTPUT_FILE $SHELL_OUTPUT

# Test cases
run_test "sed s/p/P/g | cat" "sed s/p/P/g" "cat" $OUTPUT_FILE

run_test "ls -l | wc -l" "ls -l" "wc -l" $OUTPUT_FILE
run_test "grep a | wc -w" "grep a" "wc -w" $OUTPUT_FILE
run_test "sort | head -n 3" "sort" "head -n 3" $OUTPUT_FILE
run_test "man -k atoi | cat" "man -k atoi" "cat" $OUTPUT_FILE
run_test "tr a-z A-Z | wc" "tr a-z A-Z" "wc -l" $OUTPUT_FILE
run_test "rev | wc -c" "rev" "wc -c" $OUTPUT_FILE
run_test "./run_script.sh | wc" "./run_script.sh" "wc" $OUTPUT_FILE
# ./pipex lucky.txt 'sed s/And/But/' 'grep But' outfile_pip.txt

run_test "'sed s/And/But/' 'grep But'" 'sed s/And/BLA/' 'grep BLA' $OUTPUT_FILE
run_test "sed s/And/BUT/g | grep But" "sed s/And/BUT/g" "grep BUT" $OUTPUT_FILE

# Clean up
rm -f $INPUT_FILE $OUTPUT_FILE $SHELL_OUTPUT
