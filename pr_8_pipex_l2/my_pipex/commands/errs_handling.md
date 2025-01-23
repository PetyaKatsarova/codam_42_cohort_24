** 1 file not exists  ✅ Test passed: Outputs match.**
======================================================

./pipex luck cat wc outf
luck: No such file or directory

 < luck cat | wc > outf
zsh: no such file or directory: luck

--------------------------------

** 2 not read permissions ✅ Test passed: Outputs match.**
===========================================================

./pipex lucky.txt 'cat' wc outfile
lucky.txt: Permission denied

< lucky.txt 'cat' | wc > outfile
zsh: permission denied: lucky.txt

-----------------------------------

** 2.5 empty str s command 1, command 2 or both ** ✅ Test passed: Outputs match.**
===================================================

./pipex lucky.txt "usr/bash/" '' outfile // nth happens

< lucky.txt "" | '' > outfile
zsh: permission denied: 
zsh: permission denied: 
---------------------------------------------------

** 3 handle empty file **
./pipex /dev/null "ls" "wc -l" outfile
< /dev/null ls | wc -l > outfile





 



** 3 f not exist + empty str + empty str ❌ Test failed: Outputs differ." **
==============================================================================

./pipex lucky '' "" outfile
lucky: No such file or directory

==== DESIRED ===============
< lucky '' | "" > outfile
zsh: no such file or directory: lucky
zsh: permission denied: 

------------------------------------
** 4 empty str as command: first, second or both 


-----------------------------------------------

** 5 no read perm. + command="" **


-------------------------------