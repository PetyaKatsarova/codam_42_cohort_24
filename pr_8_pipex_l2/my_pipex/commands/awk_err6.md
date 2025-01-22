awk '{count++} END {print count}'
is a script written in awk, a text processing tool, to count the number of lines in a given input file or stream.

{count++}:

This action is executed for each line in the input.
count++ increments the variable count for every line.
awk initializes variables (like count) to 0 by default.
END {print count}:
The END block runs after all lines in the input have been processed.
It prints the value of count, which contains the total number of lines.


----------------------------------------------------------------------------------------
< texts/infile.txt sed "s/And/But/" | awk '{count++} END {print count}' > outfile_pipe.txt // works
./pipex texts/infile.txt 'sed "s/And/But/"' 'awk '"'"'{count++} END {print count}'"'"'' outfile.txt


-----------------------------------------------------------------------------


"< texts/infile.txt sed "s/And/But/" | awk "{count++} END {print count}" > outfile.txt", pipex: "./pipex texts/
./pipex infile.txt 'sed "s/And/But/"' 'awk "{count++} END {print count}"' outfile.txt"


"< texts/infile.txt sed "s/And/But/" | awk "{count++} END {printf \"count: %i\" , count}" > outfile.txt", pipex: "./pipex texts/infile.txt 'sed "s/And/But/"' 'awk "{count++} END {printf \"count: %i\" , count}"' outfile.txt


 "< texts/infile.txt sed "s/And/But/" | awk '{count++} END {printf "count: %i", count}' > outfile.txt", pipex: "./pipex texts/infile.txt 'sed "s/And/But/"' 'awk '"'"'{count++} END {printf "count: %i", count}'"'"'' outfile.txt


 < texts/infile.txt ./script.sh | wc > outfile.txt", pipex: "./pipex texts/infile.txt ./script.sh wc outfile.txt

