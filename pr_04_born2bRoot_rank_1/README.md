 You only have to turn in a signature.txt file at the root of your repository. You
must paste in it the signature of your machine’s virtual disk.

Since it is a matter of setting up a server, you will install the
minimum of services. For this reason, a graphical interface is of no
use here. It is therefore forbidden to install X.org or any other
equivalent graphics server. Otherwise, your grade will be 0.
You must choose as an operating system either the latest stable version of Debian (no
testing/unstable), or the latest stable version of Rocky. Debian is highly recommended
if you are new to system administration

AppArmor
for Debian must be running at startup
==============================================
need to know:
1. diff aptitude and apt, SELinux or AppArmor is, need to know abt the OS used
2. SSH on p. 4242, ot possible ot connect using SSH s root.
undestand theory of how ssh works
3. config with UFW and only p 4242 open in ur v.machine: must be active on launch
4. hostname must be my login n ending wiht 42(pekatsar42)
-- implement strong pwd policy: 
 a.) expire every 30 days
 b.) min num of days allowed b4 modification of pwd set to 2
 c.) usr recieve wanring msg 7 days b4 their pwd expires
 d.) pwd must be min 10 chars long, Uppercase, lowercae letters and a num. 
 e.) must not contain more than 3 consecutive identical chars
 f.) must not include the name of the usr
 !! g.) The following rule does not apply to the root password: The password must have
at least 7 characters that are not part of the former password.
h.) room pwd must comply with the rest
     After setting up your configuration files, you will have to change
all the passwords of the accounts present on the virtual machine,
including the root account.

p.7 sudo TODO!!

5. install and config sudo with strict rules
6. in addition to root usr, another usr pekatsar should be present, belonging to user42 and sudo groups
--- during defence will create a new usr and assign to a group
===============================================
submit the singature of ur machine's virtual disk.
