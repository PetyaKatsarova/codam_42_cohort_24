* sed: Stream Editor
processes text line-by-line and applies transformations or filters based on patterns and commands.

Key Features of sed
Search and Replace: Modify text using regular expressions.
Delete Lines: Remove specific lines from input.
Insert or Append Text: Add new lines of text.
Substitute Multiple Occurrences: Replace text globally in lines.

Substitute (s):

sed 's/pattern/replacement/' file
Replaces the first occurrence of pattern with replacement in each line.
Add g for global replacement.

echo "cat cat cat" | sed 's/cat/dog/'
dog cat cat

< lucky.txt sed s/b/B/g | cat > test_output.txt
./pipex "sed s/b/B/g" "cat" test_output.txt