awk '{count++} END {print count}'
is a script written in awk, a text processing tool, to count the number of lines in a given input file or stream.

{count++}:

This action is executed for each line in the input.
count++ increments the variable count for every line.
awk initializes variables (like count) to 0 by default.
END {print count}:

The END block runs after all lines in the input have been processed.
It prints the value of count, which contains the total number of lines.

ls | awk '{count++} END {print count}'

< lucky.txt awk '{count++} END {print count}' > sundya.md

./pipex lucky.txt "sed c/C/g" "awk '{count++} END {p
rint count}'" sundya_pipe.md

./pipex lucky.txt 'sed "s/And/But/"' 'awk "{count++} END {print count}"' outfile.txt
/usr/bin/sed: -e expression #1, char 1: unknown command: `"'
awk: cmd. line:1: "{count++}
awk: cmd. line:1: ^ unterminated string


Explanation of '\'':
First ' → Marks the beginning of the character literal.
Second \' → Escapes the single quote, so it represents a literal ' character.
Last ' → Marks the end of the character literal.
So '\'' is a way to represent a single quote character (') in C.

./pipex lucky.txt 'sed s/And/But/' 'grep But' outfile_pip.txt

----- pipex fixed ---------------------------
./pipex lucky.txt 'sed "s/And/But/"' 'awk "{count++} END {print count}"' outfile.txt

< lucky.txt 'sed "s/And/But/"' | 'awk "{count++} END {print count}"' > outfile.txt
----------------------------------------------------------

2 more errors to fix:
< lucky.txt sed "s/And/But/" | awk '{count++} END {printf "count: %i", count}' > outfile.txt

./pipex lucky.txt 'sed "s/And/But/"' 'awk '"'"'{count++} END {printf "count: %i", count}'"'"'' outfile_pipe.md

*********** shell: *************
 < lucky.txt 'sed "s/And/But/"' | 'awk '"'"'{coun
t++} END {printf "count: %i", count}'"'"'' > outfile_pipe.md
bash: sed "s/And/But/": No such file or directory
awk '{count++} END {printf "count: %i", count}': command not found
-----------------------
pipex: ***************************
./pipex lucky.txt 'sed "s/And/But/"' 'awk '"'"'{count++} END {printf "count: %i", count}'"'"'' outfile_pipe.md
awk: cmd. line:1: '{count++}
awk: cmd. line:1: ^ invalid char ''' in expression
-------------------------------
< lucky.txt 'sed "s/And/But/"' | 'awk '"'"'{count++} END {printf "count: %i", count}'"'"'' > outfile_pipe.md

error 2:
(7)
< lucky.txt ./run_script.sh | wc > outfile_shell.txt

./pipex lucky.txt ./run_script.sh wc outfile_pipe.txt
