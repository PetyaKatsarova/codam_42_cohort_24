awk '{count++} END {print count}'
is a script written in awk, a text processing tool, to count the number of lines in a given input file or stream.

{count++}:

This action is executed for each line in the input.
count++ increments the variable count for every line.
awk initializes variables (like count) to 0 by default.
END {print count}:
The END block runs after all lines in the input have been processed.
It prints the value of count, which contains the total number of lines.


** To fix: **
'awk "{count++} END {printf "count: %i" , count}"'
needs to rmv initial ''(first last), keeps the rest, but initial are not used

---------------------------------------- WORKS ------------------------------------------------
< texts/infile.txt sed "s/And/But/" | awk '{count++} END {print count}' > outfile_pipe.txt // works
./pipex texts/infile.txt 'sed "s/And/But/"' 'awk '"'"'{count++} END {print count}'"'"'' outfile.txt
-----------------------------------------------------------------------------

--------------------------- works ------------------------------------
< texts/infile.txt sed "s/And/But/" | awk "{count++} END {print count}" > outfile.txt
./pipex texts/infile.txt 'sed "s/And/But/"' 'awk "{count++} END {print count}"' outfile.txt


---------------- ERR TO FIX ----------------------- esc: \" ------------------------
< texts/infile.txt sed "s/And/But/" | awk "{count++} END {printf \"count: %i\" , count}" > outfile.txt
./pipex texts/infile.txt 'sed "s/And/But/"' 'awk "{count++} END {printf \"count: %i\" , count}"' outfile.txt
-----------------------------------------------------------

------------------ similar outcome: ok-ish --------------------------------
< texts/infile.txt sed "s/And/But/" | awk "{count++} END {printf "count: %i" , count}" > outfile.txt
./pipex texts/infile.txt 'sed "s/And/But/"' 'awk "{count++} END {printf "count: %i" , count}"' outfile.txt
-----------------------------------------------------------------------------

---------------------- err to fix: multiple quotes -------------------------------
 < texts/infile.txt sed "s/And/But/" | awk '{count++} END {printf "count: %i", count}' > outfile.txt
 ./pipex texts/infile.txt 'sed "s/And/But/"' 'awk '"'"'{count++} END {printf "count: %i", count}'"'"'' outfile.txt
 texts/infile.txt sed "s/And/But/" | awk '{count++} END {printf "count: %i", count}' > outfile.txt
 ---------------------------------------------------------------------------------------------

./pipex texts/infile.txt 'sed "s/And/But/"' 'awk "{count++} END {printf 'count: %i', count}'"' outfile.txt

-------------------- works -------------------------------------------------
< texts/infile.txt ./scripts/script.sh | wc > outfile_shell.txt
./pipex texts/infile.txt ./scripts/script.sh wc outfile.txt
-----------------------------------------------------------------

