```
Lab Assignment 1

1.	Display Calendar of year 2025.
student@admins-iMac-4 ~ % cal
    January 2025      
Su Mo Tu We Th Fr Sa  
          1  2  3  4  
 5  6  7  8  9 10 11  
12 13 14 15 16 17 18  
19 20 21 22 23 24 25  
26 27 28 29 30 31                
student@admins-iMac-4 ~ %        

2. Display the system’s date.
student@admins-iMac-4 ~ % date
Tue Jan 21 12:22:42 IST 2025
student@admins-iMac-4 ~ % 

3. Count the number of lines in the /etc/passwd file.
student@admins-iMac-4 ~ % wc -l /etc/passwd
     120 /etc/passwd
student@admins-iMac-4 ~ % 

4. Find out who else is on the system.
tudent@admins-iMac-4 ~ % who
student  console  Jan 20 14:03 
student  ttys000  Jan 21 12:08 
student@admins-iMac-4 ~ % 

5. Direct the output of the man pages for the date command to a file named mydate.
student@admins-iMac-4 ~ % man date > mydate

6. Create a subdirectory called mydir.
student@admins-iMac-4 ~ % mkdir mydir

7. Move the file mydate into the new subdirectory.
student@admins-iMac-4 ~ % mv mydate mydir/

8. Go to the subdirectory mydir and copy the file mydate to a new file called ourdate
student@admins-iMac-4 ~ % cd mydir
student@admins-iMac-4 mydir % cp mydate ourdate

9. List the contents of mydir.
student@admins-iMac-4 mydir % cd ..
student@admins-iMac-4 ~ % ls mydir
mydate	ourdate

10. Do a long listing on the file ourdate and note the permissions.
student@admins-iMac-4 ~ % ls -l ourdate
-rw-r--r--  1 student  staff  12418 Jan 20 13:12 ourdate

11. Display the name of the current directory starting from the root.
student@admins-iMac-4 ~ % pwd
/Users/student

12. Move the files in the directory mydir back to your home directory.
       student@admins-iMac-4 mydir % mv mydate ourdate /Users/student/                             

13. Display the first 5 lines of mydate.
student@admins-iMac-4 ~ % head mydate
DATE(1)                   BSD General Commands Manual                  DATE(1)
NAME
     date -- display or set date and time
SYNOPSIS
     date [-jRu] [-r seconds | filename] [-v [+|-]val[ymwdHMS]] ...
          [+output_fmt]
     date [-jnu] [[[mm]dd]HH]MM[[cc]yy][.ss]
student@admins-iMac-4 ~ % 

14. Display the last 8 lines of mydate.
student@admins-iMac-4 ~ % tail -n 8  mydate
     The date utility is expected to be compatible with IEEE Std 1003.2
     (``POSIX.2'').  The -d, -f, -j, -n, -r, -t, and -v options are all exten-
     sions to the standard.
HISTORY
     A date command appeared in Version 1 AT&T UNIX.
BSD                               May 7, 2015  

15. Remove the directory mydir.
student@admins-iMac-4 ~ % rmdir mydir

16. Redirect the output of the long listing of files to a file named list.
student@admins-iMac-4 ~ % ls -l > list

17. Select any 5 capitals of states in India and enter them in a file named capitals1. Choose 5 more capitals and enter them in a file named capitals2. Choose 5 more capitals and enter them in a file named capitals3. Concatenate all 3 files and redirect the output to a file named capitals.
student@admins-iMac-4 ~ % cat > capitals1 
Mumbai
Chennai
Haidrabad
Delhi 
Banglore
student@admins-iMac-4 ~ % cat >  capitals2
Bhopal
Ahemadabad
Guwahati 
Patna
Chandigarh
student@admins-iMac-4 ~ % cat > capitals3
Kolkata
Jaipur
Kochi
Thiruvanthapuram
Lucknow
student@admins-iMac-4 ~ % cat capitals1 capitals2 capitals3 > capitals

18. Concatenate the file capitals2 at the end of file capitals.
student@admins-iMac-4 ~ % cat capitals2 >> capitals
student@admins-iMac-4 ~ % cat capitals
Mumbai
Chennai
Haidrabad
Delhi 
Banglore
Bhopal
Ahemadabad
Guwahati
Patna
Chandigarh
Kolkata
Jaipur
Kochi
Thiruvanthapuram
Lucknow
Bhopal
Ahemadabad
Guwahati
Patna
Chandigarh

19. Give read and write permissions to all users for the file capitals.
student@admins-iMac-4 ~ % chmod a+rw capitals
student@admins-iMac-4 ~ % ls -l capitals
-rw-rw-rw-  1 student  staff  175 Jan 21 13:28 capitals

20. Give read permissions only to the owner of the file capitals. Open the file, make some changes and try to save it. What happens ?
student@admins-iMac-4 ~ % chmod u-w capitals
student@admins-iMac-4 ~ % cat capitals
Mumbai
Chennai
Haidrabad
Delhi 
Banglore
Bhopal
Ahemadabad
Guwahati
Patna
Chandigarh
Kolkata
Jaipur
Kochi
Thiruvanthapuram
Lucknow
Bhopal
Ahemadabad
Guwahati
Patna
Chandigarh
student@admins-iMac-4 ~ % cat >> capitals 
zsh: permission denied: capitals

21. Create an alias to concatenate the 3 files capitals1, capitals2, capitals3 and redirect the output to a file named capitals. Activate the alias and make it run.

student@admins-iMac-4 ~ % alias al_cap='cat capitals1 capitals2 capitals3 > capitals' 
student@admins-iMac-4 ~ % al_cap
student@admins-iMac-4 ~ % cat capitals
Mumbai
Chennai
Haidrabad
Delhi 
Banglore
Bhopal
Ahemadabad
Guwahati
Patna
Chandigarh
Kolkata
Jaipur
Kochi
Thiruvanthapuram
Lucknow
student@admins-iMac-4 ~ % 

22. Find out the number of times the string “the” appears in the file mydate.
student@admins-iMac-4 ~ % grep -o "the" mydate | wc -l
     154

23. Find out the line numbers on which the string “date” exists in mydate.
student@admins-iMac-4 ~ % grep -n "date" mydate
5:     date -- display or set date and time
16:     date and time.  Otherwise, depending on the options specified, date will
17:     set the date and time or print it in a user-defined way.
19:     The date utility displays the date and time read from the kernel clock.
20:     When used to set the date and time, both the kernel clock and the hard-
21:     ware clock are updated.
23:     Only the superuser may set the date, and if the system securelevel (see
37:     -j      Do not try to set the date.  This allows you to use the -f flag
38:             in addition to the + option to convert one date format to
46:     -R      Use RFC 2822 date and time output format. This is equivalent to
51:             Print the date and time represented by seconds, where seconds is
57:             Print the date and time of the last modification of filename.
64:     -u      Display or set the date in UTC (Coordinated Universal) time.
66:     -v      Adjust (i.e., take the current date and display the result of the
67:             adjustment; not actually set the date) the second, minute, hour,
69:             preceded with a plus or minus sign, the date is adjusted forwards

24. Print all lines of mydate except those that have the letter “i” in them.
student@admins-iMac-4 ~ % grep -v "i" mydate
DATE(1)                   BSD General Commands Manual                  DATE(1)
NAME
SYNOPSIS
          [+output_fmt]
     date [-jnu] [[[mm]dd]HH]MM[[cc]yy][.ss]
DESCRIPTION
     ware clock are updated.
     than 1 second.
             another.
             the ``C'' locale .
     -r seconds
             hex.
             the current one.
             adjustment means that the clock goes forward at 01:00 to 02:00,
             essary to reach October 29, 2:30.
     ``+%+''.
                   year.
           dd      Day, a number from 1 to 31.
           HH      Hour, a number from 0 to 23.
                   leap seconds).
ENVIRONMENT
FILES
EXIT STATUS
EXAMPLES
     The command:
           date "+DATE: %Y-%m-%d%nTIME: %H:%M:%S"
           DATE: 1987-11-21
           TIME: 13:36:16
           date -v1m -v+1y
           Sun Jan  4 04:15:24 GMT 1998

25. List the words of 4 letters from the file mydate.

yash@yash-VirtualBox:~$ grep -o -w "\w\{4\}" mydate
DATE
User
DATE
NAME
date
date
time
date
date
date
time
With
with
date
time
long
date
time
date
warn
file
like
date
once
each
line
8601
date
time
8601
date
date
only
date
time
2006
date
time
5322
2006
0600
3339
date
time
3339
date
date
time
2006
FILE
last
time
FILE

26. List 5 states in north east India in a file mystates. List their corresponding capitals in a file mycapitals. Use the paste command to join the 2 files.
student@admins-iMac-4 ~ % cat > mystates
Arunachal Pradesh
Mizoram
Nagaland
Aasam 
Meghalay
student@admins-iMac-4 ~ % cat > mycapitals
Itanagar
Aizawl
Shillong
Dispur
Kohima
student@admins-iMac-4 ~ % paste mystates mycapitals
Arunachal Pradesh	Itanagar
Mizoram	Aizawl
Nagaland	Shillong
Aasam 	Dispur
Meghalay	Kohima

27. Use the cut command to print the 1 st and 3 rd columns of the /etc/passwd file for all students in this class.

student@admins-iMac-4 ~ % cut -d: -f 1,3 /etc/passwd
##
# User Database
# 
# Note that this file is consulted directly only when the system is running
# in single-user mode.  At other times this information is provided by
# Open Directory.
#
# See the opendirectoryd(8) man page for additional information about
# Open Directory.
##
nobody:-2
root:0
daemon:1
_uucp:4
_taskgated:13
_networkd:24
_installassistant:25
_lp:26
_postfix:27
_scsd:31
_ces:32
_appstore:33
_mcxalr:54
_appleevents:55
_geod:56
_devdocs:59
_sandbox:60
_mdnsresponder:65
_ard:67
_www:70
_eppc:71
_cvs:72
_svn:73
_mysql:74
_sshd:75
_qtss:76
_cyrus:77
_mailman:78
_appserver:79
_clamav:82
_amavisd:83
_jabber:84
_appowner:87
_windowserver:88
_spotlight:89
_tokend:91
_securityagent:92
_calendar:93
_teamsserver:94
_update_sharing:95
_installer:96
_atsserver:97
_ftp:98
_unknown:99
_softwareupdate:200
_coreaudiod:202
_screensaver:203
_locationd:205
_trustevaluationagent:208
_timezone:210
_lda:211
_cvmsroot:212
_usbmuxd:213
_dovecot:214
_dpaudio:215
_postgres:216
_krbtgt:217
_kadmin_admin:218
_kadmin_changepw:219
_devicemgr:220
_webauthserver:221
_netbios:222
_warmd:224
_dovenull:227
_netstatistics:228
_avbdeviced:229
_krb_krbtgt:230
_krb_kadmin:231
_krb_changepw:232
_krb_kerberos:233
_krb_anonymous:234
_assetcache:235
_coremediaiod:236
_launchservicesd:239
_iconservices:240
28. Count the number of people logged in and also trap the users in a file using the tee command.
student@admins-iMac-4 ~ % who | tee users.txt | wc -l
       2

29. Convert the contents of mystates into uppercase.
student@admins-iMac-4 ~ % tr 'a-z' 'A-Z' < mystates
ARUNACHAL PRADESH
MIZORAM
NAGALAND
AASAM 
MEGHALAY

30. Create any two files & display the common values between them.
yash@yash-VirtualBox:~$ cat > file1
OS 
CN
DS 
yash@yash-VirtualBox:~$ cat > file2
ML
AI
CN
yash@yash-VirtualBox:~$ sort file1 > file11
yash@yash-VirtualBox:~$ sort file2 > file22
yash@yash-VirtualBox:~$ comm file11 file22
	AI
		CN
DS
	ML
OS 





Lab Assignment 2


1.	Write shell script to execute command ls, date, pwd repetitively.
yash@yash-VirtualBox:~$ nano f1.sh
  GNU nano 7.2                                              f1.sh                                                       
ls
date
pwd
yash@yash-VirtualBox:~$ bash f1.sh
Btech	 Documents  Music     snap	 Student2  Student5  Student8	    SY	       TY
Btech11  Downloads  Pictures  Student1	 Student3  Student6  Student9	    SYTY       ufile
Desktop  f1.sh	    Public    Student11  Student4  Student7  Student_Names  Templates  Videos
Fri Jan 31 12:01:31 AM IST 2025
/home/yash

2.	Write a shell script to assign value to the variable?
Display value with $ and without $.
yash@yash-VirtualBox:~$ nano f2.sh
  GNU nano 7.2                                              f2.sh                                                       
num1=1
num2=2
echo "num1 is $num1"
echo "num2 is $num2"
echo "num1 is num1"
echo "num2 is num2"
yash@yash-VirtualBox:~$ bash f2.sh
num1 is 1
num2 is 2
num1 is num1
num2 is num2

3.	Variables are untyped in Shell Script.
Write a shell script to show variables are untyped.
yash@yash-VirtualBox:~$ nano f3.sh
  GNU nano 7.2                                              f3.sh                                                       
var1=10
var2=10.5
var3=VIT
var4="SY B DIV"
echo "var1 = $var1"
echo "var2 = $var2"
echo "var3 = $var3"
echo "var4 = $var4"
yash@yash-VirtualBox:~$ bash f3.sh
var1 = 10
var2 = 10.5
var3 = VIT
var4 = SY B DIV

4.	Write a shell script to accept numbers from user. (Keyboard)
yash@yash-VirtualBox:~$ nano f4.sh
  GNU nano 7.2                                              f4.sh                                                       
echo "Enter 5 Numbers: "

read num1
read num2
read num3
read num4
read num5

echo "Entered Numbers are "
echo "$num1, $num2, $num3, $num4, $num5"

yash@yash-VirtualBox:~$ bash f4.sh
Enter 5 Numbers: 
1
2
3
4
5
Entered Numbers are 
1, 2, 3, 4, 5

5.	Write a shell script to accept numbers from command line arguments.
yash@yash-VirtualBox:~$ nano f5.sh
  GNU nano 7.2                                              f5.sh                                                       
echo "Entered Numbers are $1, $2, $3"
yash@yash-VirtualBox:~$ bash f5.sh 10 20 30 
Entered Numbers are 10, 20, 30

6.	Write a shell script to show the contents of environmental variables SHELL,PATH,HOME. 
yash@yash-VirtualBox:~$ nano f6.sh
  GNU nano 7.2                          f6.sh                                   
echo "path is $PATH"
echo "shell is $SHELL"
echo "home is $HOME"
yash@yash-VirtualBox:~$ bash f6.sh
path is /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin
shell is /bin/bash
home is /home/yash

7.	Write a shell script to create two files. Accept file names from user. 
yash@yash-VirtualBox:~$ nano f7.sh
  GNU nano 7.2                          f7.sh                                   
echo "Enter the name for the first file:"
read file1
echo "Enter the name for the second file:"
read file2
touch "$file1"
touch "$file2"
echo "Files '$file1' and '$file2' have been created."
yash@yash-VirtualBox:~$ bash f7.sh
Enter the name for the first file:
File_1
Enter the name for the second file:
File_2
Files 'File_1' and 'File_2' have been created.

8.	Write a shell script to create two directories. Accept directories name from Command line.
yash@yash-VirtualBox:~$ nano f8.sh
  GNU nano 7.2                          f8.sh                                   
dir1=$1
dir2=$2
mkdir "$dir1"
mkdir "$dir2"
echo "Directories '$dir1' and '$dir2' have been created."
yash@yash-VirtualBox:~$ bash f8.sh R1 R2
Directories 'R1' and 'R2' have been created.

9.	Write a shell script to copy file content of one file to another file. Accept files names from command line argument.
 yash@yash-VirtualBox:~$ nano f9.sh
   GNU nano 7.2                          f9.sh                                   
file1=$1
file2=$2
echo "This is some content inside $file1." > "$file1"
cp "$file1" "$file2"
echo "Content of '$file1' has been copied to '$file2'."
yash@yash-VirtualBox:~$ bash f9.sh Yash_File_1 Yash_File_2
Content of 'Yash_File_1' has been copied to 'Yash_File_2'.

10.	Write a shell script to rename the file name. Accept old filename and new filename from command line argument. 
yash@yash-VirtualBox:~$ nano f10.sh
  GNU nano 7.2                         f10.sh                                   
old_name=$1
new_name=$2
mv "$old_name" "$new_name"
echo "File '$old_name' has been renamed to '$new_name'."
yash@yash-VirtualBox:~$ bash f10.sh Yash_File_1  fname_new
File 'Yash_File_1' has been renamed to 'fname_new'.

11.	Write a shell script to perform arithmetic operation of integer data.
yash@yash-VirtualBox:~$ nano f11.sh
  GNU nano 7.2                         f11.sh                                   
echo "Enter first integer:"
read num1
echo "Enter second integer:"
read num2
sum=$((num1 + num2))
difference=$((num1 - num2))
product=$((num1 * num2))
quotient=$((num1 / num2))
echo "Sum: $sum"
echo "Difference: $difference"
echo "Product: $product"
echo "Quotient: $quotient"
yash@yash-VirtualBox:~$ bash f11.sh
Enter first integer:
4
Enter second integer:
2
Sum: 6
Difference: 2
Product: 8
Quotient: 2

12.	Write a shell script to perform arithmetic operation of float  data.
yash@yash-VirtualBox:~$ nano f12.sh
      GNU nano 7.2                         f12.sh                                   
echo "Enter first float number:"
read num1
echo "Enter second float number:"
read num2
sum=$(echo "$num1 + $num2" | bc)
difference=$(echo "$num1 - $num2" | bc)
product=$(echo "$num1 * $num2" | bc)
quotient=$(echo "scale=2; $num1 / $num2" | bc)
echo "Sum: $sum"
echo "Difference: $difference"
echo "Product: $product"
echo "Quotient: $quotient"
yash@yash-VirtualBox:~$ bash f12.sh
Enter first float number:
10.5
Enter second float number:
3.6
Sum: 14.1
Difference: 6.9
Product: 37.8
Quotient: 2.91












Lab Assignment 3


1. Write a shell script to check number entered by the user is greater than 10.

student@admins-iMac ~ % nano s1.sh
  GNU nano 7.2                             s1.sh                                       
  GNU nano 2.0.6                                               File: s1.sh                                                                                                   
echo "Enter Number: "
read num1

if [ $num1 -gt 10 ]
then
echo "$num1 is greater than 10."
else
echo "$num1 is not greater than 10"
fi

student@admins-iMac ~ % bash s1.sh
Enter Number: 
2
2 is not greater than 10
student@admins-iMac ~ % bash s1.sh
Enter Number: 
12
12 is greater than 10.


2. Write a shell script to check if a file exists. If not, then create it.

student@admins-iMac ~ % nano s2.sh
  GNU nano 7.2                             s2.sh                                       
no 2.0.6                                               File: s2.sh                                                                                                  
echo "Enter the name of file: "
read file

if [ -f $file ]
then
echo "File exists"
else
echo "File does not exists"
fi

student@admins-iMac ~ % ls
8Puzzle.java	Downloads	Pictures	f1		f3.sh		filescount.sh	myfile.txt	q1.sh		s2.sh
Applications	Library		Public		f1.sh		f4.sh		list.txt	name.txt	q2.sh
Desktop		Movies		armstrong.sh	f1.sh.save	f5.sh		mydate		ourdate		q3.sh
Documents	Music		char_count.sh	f2.sh		f6.sh		mydir		prob1.sh	s1.sh

student@admins-iMac ~ % bash s2.sh
Enter the name of file: 
name.txt
File exists

student@admins-iMac ~ % bash s2.sh  
Enter the name of file: 
yourname.txt
File does not exists

3. Write a shell script that takes two command line arguments. Check whether the name passed as first argument is of a directory or not. If not ,create directory using name passed as second argument. 

student@admins-iMac ~ % nano s3.sh  G
  GNU nano 7.2                             s3.sh                                                                                File: s3.sh                                                                                 
dir1=$1
dir2=$2

if [ -d $dir1 ]
then
echo "$dir1 is present"
else
mkdir "$dir2"
echo "$dir2 is made"
fi

student@admins-iMac ~ % pwd
/Users/student
student@admins-iMac ~ % bash s3.sh /Users/student Y1
/Users/student is present
student@admins-iMac ~ % bash s3.sh Y1 Y2            
Y2 is made

4. Write a shell script which checks the total arguments passed. If the argument count is greater than 5, then display message “Too many arguments”

yash@yash-VirtualBox:~$ nano s4.sh

  GNU nano 7.2                             s4.sh                                       
if [ $# -gt 5 ]
then
echo "too many arguements"
else
echo "$# arguements are passed"
fi

yash@yash-VirtualBox:~$ bash s4.sh 1 2 3 4 
4 arguements are passed
yash@yash-VirtualBox:~$ bash s4.sh 1 2 3 4 5 6 7
too many arguments

5. Write a shell script to check arguments passed at command line is whether of a file or directory.

student@admins-iMac ~ % nano s5.sh
  GNU nano 7.2                             s5.sh                                       
GNU nano 2.0.6                                               File: s5.sh                                                                                                   
arg=$1

if [ -f $arg ]
then
echo "$arg is file"
elif [ -d $arg ]
then
echo "$arg is directory"
fi

student@admins-iMac ~ % bash s5.sh name.txt      
name.txt is file
student@admins-iMac ~ % bash s5.sh /Users/student
/Users/student is directory

6. Write a shell script to read a month name from the user. Check if the name entered is either August or October.

student@admins-iMac ~ % nano s6.sha
  GNU nano 7.2                             s6.sh                                       no 2.0.6                                               File: s6.sh                                                                                 
echo "Enter Month Name: "
read mon

if [ $mon =  August ]
then
echo "Month is August"
elif [ $mon = October ]
then
echo "Month is October"
else
echo "Month is neither August nor October"
fi

student@admins-iMac ~ % bash s6.sh
Enter Month Name: 
August
Month is August
student@admins-iMac ~ % bash s6.sh
Enter Month Name: 
October
Month is October
student@admins-iMac ~ % bash s6.sh
Enter Month Name: 
May
Month is neither August nor October

7. Write a shell script to check whether file or directory exists.
yash@yash-VirtualBox:~$ nano s7.sh

  GNU nano 7.2                             s7.sh *                                     
echo "Enter the name: "
read arg

if [ -f $arg ] 
then
echo "$arg is file and exists"

elif [ -d $arg ] 
then
echo "$arg is directory and exists"

else
echo "$arg does not exist"
fi

yash@yash-VirtualBox:~$ ls
Btech      f11.sh  f5.sh   File_2     R2         Student2  Student8       TY
Btech11    f12.sh  f6.sh   fname_new  s4.sh      Student3  Student9       ufile
Desktop    f1.sh   f7.sh   Music      s7.sh      Student4  Student_Names  Videos
Documents  f2.sh   f8.sh   Pictures   snap       Student5  SY             Yash_File_2
Downloads  f3.sh   f9.sh   Public     Student1   Student6  SYTY
f10.sh     f4.sh   File_1  R1         Student11  Student7  Templates
yash@yash-VirtualBox:~$ bash s7.sh
Enter the name: 
Desktop
Desktop is directory and exists
yash@yash-VirtualBox:~$ bash s7.sh
Enter the name: 
Btech
Btech is file and exists
yash@yash-VirtualBox:~$ bash s7.sh
Enter the name: 
Pokemon
Pokemon does not exist

8. Write a shell script to check whether file is exists and file is readable.

student@admins-iMac ~ % nano s8.sh
  GNU nano 7.2                             s8.sh                                       

echo "Enter File Name: "
read file

if [ -f $file ] && [ -r $file ]
then
echo "File exists and is readable as well"
elif [ -f $file ]
then
echo "File exists but is not readable"
else
echo "File does not exist"
fi

student@admins-iMac ~ % bash s8.sh
Enter File Name: 
name.txt
File exists and is readable as well

student@admins-iMac ~ % chmod 000 name.txt
student@admins-iMac ~ % bash s8.sh        
Enter File Name: 
name.txt
File exists but is not readable

student@admins-iMac ~ % bash s8.sh
Enter File Name: 
ok.txt
File does not exist

9. Write a shell script to check if the present month is August   or not. Use date command to get present month.U 

student@admins-iMac ~ % nano s9.sh
  GNU nano 7.2                             s9.sh                                       
nano 2.0.6                                               File: s9.sh                                                                                                  
x=$(date +"%m")

if [ $x = "August" ]
then
echo "Present month is August"
else
echo "Present month is not August"
fi

student@admins-iMac ~ % bash s9.sh
Present month is not August

10. Write a shell script to check if the current user is root or regular user.

yash@yash-VirtualBox:~$ nano s10.sh
  GNU nano 7.2                             s10.sh *                                    
if [ "$(id -u)" -eq 0 ] 
then
    echo "The current user is the root user."
else
    echo "The current user is the regular user."
fi
yash@yash-VirtualBox:~$ bash s10.sh
The current user is the regular user.

11. Write a shell script to check the total arguments passed at command line. If the arguments are more than 3 then list the argument else print “type more next time”
yash@yash-VirtualBox:~$ nano s11.sh
  GNU nano 7.2                         s11.sh                                   
if [ $# -gt 3 ]; then
    echo "Arguments passed: $@"
else
    echo "Type more next time"
fi

yash@yash-VirtualBox:~$ bash s11.sh 1 2
Type more next time
yash@yash-VirtualBox:~$ bash s11.sh 1 2 3 4
Arguments passed: 1 2 3 4









Lab Assignment 4


1.	Write a shell script to create three files.

student@admins-iMac ~ % nano m1.sh
  GNU nano 2.0.6                 File: m1.sh                                         
for x in file1 file2 file3
do
touch $x
echo "File is Created"
done

student@admins-iMac ~ % bash m1.sh
File is Created
File is Created
File is Created

2.	Write a shell script to print date and time 10 times, once after each second.


student@admins-iMac ~ % nano m2.sh
  GNU nano 2.0.6                 File: m2.sh                               Modified  
for (( i=0; i<10; i++))
do 
date
done

student@admins-iMac ~ % bash m2.sh      
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025

3.	Write a shell script to create five directories. Accept the name of directories from command line.


student@admins-iMac ~ % nano m3.sh

  GNU nano 2.0.6                File: m3.sh                                         
mkdir1=$1
mkdir2=$2
mkdir3=$3
mkdir4=$4
mkdir5=$5
for x in $*
do
  mkdir $x
  echo "Directory is created"
done


student@admins-iMac ~ % bash m3.sh d1 d2 d3 d4 d5
Directory is created
Directory is created
Directory is created
Directory is created
Directory is created

4.	Write a shell script to print long list of all file’s names passed at command line.
yash@yash-VirtualBox:~/OS$ nano f1.sh
  GNU nano 7.2                                                                     f1.sh                                                                               
for file in "$@"
do
    if [ -e "$file" ]
    then
    ls "$file" 
    else
    echo "Error: $file does not exist."
  fi
done

yash@yash-VirtualBox:~/OS$ bash f1.sh s1.sh s4.sh
s1.sh
s4.sh
yash@yash-VirtualBox:~/OS$ ls
f1.sh  s1.sh  s2.sh  s3.sh  s4.sh

5.	Write a shell script to count the number of file names passed at command line.

yash@yash-VirtualBox:~/OS$ nano f2.sh
  GNU nano 7.2                                                                   f2.sh                                                                               
count=$#
echo "Number of files passed: $count"

yash@yash-VirtualBox:~/OS$ bash f2.sh s1.sh s4.sh s3.sh f1.sh
Number of files passed: 4

6.	Write a shell script to accept and display array. As-sume array consist 5 number.
yash@yash-VirtualBox:~/OS$ nano f3.sh
  GNU nano 7.2                                                                     f3.sh *                                                                             
echo "Enter 5 numbers"
for (( i=0; i<5; i++ ))
do
read a[i]
done

echo "Entered array is: "
for (( i=0; i<5; i++ ))
do
echo "${a[i]}"
done

yash@yash-VirtualBox:~/OS$ bash f3.sh
Enter 5 numbers
10
45
64
75
23
Entered array is: 
10
45
64
75
23

7.	Write Shell script to find out even and odd numbers from accepted array. Assume Array consists of 5 numbers. Also accept arrays from users.

yash@yash-VirtualBox:~/OS$ nano f4.sh
  GNU nano 7.2                                                                     f4.sh                                                                               
echo "Enter 5 numbers:"
for (( i=0; i<5; i++ ))
do
  read arr[i] 
done

echo "Even numbers:"
for (( i=0; i<5; i++ ))
do
  if (( arr[i] % 2 == 0 )); then
    echo "${arr[i]}"
  fi
done

echo "Odd numbers:"
for (( i=0; i<5; i++ ))
do
  if (( arr[i] % 2 != 0 )); then
    echo "${arr[i]}"
  fi
done
yash@yash-VirtualBox:~/OS$ bash f4.sh
Enter 5 numbers:
78
43
100
21
85
Even numbers:
78
100
Odd numbers:
43
21
85

8.	Write shell script to find out the reverse number of a given number. 
yash@yash-VirtualBox:~/OS$ nano f5.sh
  GNU nano 7.2                                                                     f5.sh *                                                                             
echo "Enter a number:"
read num

reverse=0

while [ $num -gt 0 ]
do
  remainder=$(( num % 10 ))    
  reverse=$(( reverse * 10 + remainder )) 
  num=$(( num / 10 ))           
done

echo "Reversed number: $reverse"

yash@yash-VirtualBox:~/OS$ bash f5.sh
Enter a number:
560946
Reversed number: 649065

9.	Write Shell script to sort array numbers ascending and descending order. Assume Array consists of 5 numbers. Also accept arrays from users. 	
yash@yash-VirtualBox:~/OS$ nano f6.sh
GNU nano 7.2                                                                     f6.sh                                                                               
echo "Enter 5 numbers:"
for (( i=0; i<5; i++ ))
do
  read arr[i] 
done

echo "Choose Sorting Order:"
echo "1) Ascending Order"
echo "2) Descending Order"
read choice

case $choice in    
for (( j=0; j<5-i-1; j++ ))
      do
        if (( arr[j] > arr[j+1] ))
         then
         temp=${arr[j]}
          arr[j]=${arr[j+1]}
          arr[j+1]=$temp
        fi
      done
    done
    echo "Sorted in Ascending Order: ${arr[*]}"
   ;;

  2) for (( i=0; i<5; i++ ))
    do
      for (( j=0; j<5-i-1; j++ ))
      do
        if (( arr[j] < arr[j+1] ))
          then
          temp=${arr[j]}
          arr[j]=${arr[j+1]}
          arr[j+1]=$temp
        fi
      done
    done
    echo "Sorted in Descending Order: ${arr[*]}"
    ;;

  *) 
    echo "Invalid choice! Please enter 1 or 2."
esac

yash@yash-VirtualBox:~/OS$ bash f6.sh
Enter 5 numbers:
7              
96
46
25
99
Choose Sorting Order:
1) Ascending Order
2) Descending Order
1
Sorted in Ascending Order: 7 25 46 96 99
yash@yash-VirtualBox:~/OS$ bash f6.sh
Enter 5 numbers:
58 
34
90
12
59
Choose Sorting Order:
1) Ascending Order
2) Descending Order
2
Sorted in Descending Order: 90 59 58 34 12


10.	Write Shell script to find out smallest number and largest number of given arrays. Assume Array consists of 5 numbers. Also accept arrays from users.
yash@yash-VirtualBox:~/OS$ nano f7.sh
  GNU nano 7.2                                                                     f7.sh                                                                               
echo "Enter 5 numbers:"
for (( i=0; i<5; i++ ))
do
  read arr[i]
done

min=${arr[0]}
max=${arr[0]}

for (( i=1; i<5; i++ ))
do
  if (( arr[i] < min ))
  then
    min=${arr[i]}
  fi

  if (( arr[i] > max ))
  then
    max=${arr[i]}
  fi
done

echo "Smallest Number: $min"
echo "Largest Number: $max"

yash@yash-VirtualBox:~/OS$ bash f7.sh
Enter 5 numbers:
87  
45
36
9
13
Smallest Number: 9
Largest Number: 87












Tutorial 2


1. Create Student record text file as “Student1” for given input student details.
yash@yash-VirtualBox:~$ cat > Student1
PRN Number | Student Name | Year | Division | Roll No | Email Id | Gender
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
11910490 | KOLPE SAKET PRADIP | BTech | CS-B | 16 | saket.kolpe19@vit.edu | Male
12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C | 28 | gaurav.pawar20@vit.edu | Male
11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D | 2 | varun.ringnekar19@vit.edu | Male
11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D | 9 | harsh.satdeve19@vit.edu | Male
11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D | 7 | SAMARTH.GAWANDE19@vit.edu | Male
11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D | 13 | kirtish.surangalikar19@vit.edu | Male
11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 | 11 | pradyumn.patil19@vit.edu | Male
2. Find out Btech student from “Student1” file and save the content into “Btech” file.
yash@yash-VirtualBox:~$ grep -i "btech" Student1 > Btech
yash@yash-VirtualBox:~$ cat Btech
11910490 | KOLPE SAKET PRADIP | BTech | CS-B | 16 | saket.kolpe19@vit.edu | Male
12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C | 28 | gaurav.pawar20@vit.edu | Male
11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D | 2 | varun.ringnekar19@vit.edu | Male
11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D | 9 | harsh.satdeve19@vit.edu | Male
11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D | 7 | SAMARTH.GAWANDE19@vit.edu | Male
11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D | 13 | kirtish.surangalikar19@vit.edu | Male
11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 | 11 | pradyumn.patil19@vit.edu | Male
3. Find out TY student from “Student1” file and save the content into “TY” file
yash@yash-VirtualBox:~$ grep -i "ty" Student1 > TY
yash@yash-VirtualBox:~$ cat TY
12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
4. Find out SY student from “Student1” file and save the content into “SY” file.
yash@yash-VirtualBox:~$ grep -i "sy" Student1 > SY
yash@yash-VirtualBox:~$ cat SY
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
5.Combine SY and TY students from “Student1” file and save the content into “SYTY” file.
yash@yash-VirtualBox:~$ cat SY TY > SYTY
yash@yash-VirtualBox:~$ cat SYTY
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
6. Sort the file based on Roll No. and save content into “Student2” file.
yash@yash-VirtualBox:~$ sort -t'|' -k5,5n Student1 > Student2
yash@yash-VirtualBox:~$ cat Student2

PRN Number | Student Name | Year | Division | Roll No | Email Id | Gender
11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D | 2 | varun.ringnekar19@vit.edu | Male
11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D | 7 | SAMARTH.GAWANDE19@vit.edu | Male
11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D | 9 | harsh.satdeve19@vit.edu | Male
11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 | 11 | pradyumn.patil19@vit.edu | Male
11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D | 13 | kirtish.surangalikar19@vit.edu | Male
11910490 | KOLPE SAKET PRADIP | BTech | CS-B | 16 | saket.kolpe19@vit.edu | Male
12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C | 28 | gaurav.pawar20@vit.edu | Male
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
7. Compare “Student1” file with “Btech” file and save content into “Student2” file.
yash@yash-VirtualBox:~$ cmp Student1 Btech > Student2
yash@yash-VirtualBox:~$ cat Student2
Student1 Btech differ: byte 1, line 1
8. Find out PRN NO, Student Name, Year and Division field data from “Student1” file. And save into “Student3” file.
yash@yash-VirtualBox:~$ awk -F'|' '{print $1 "|" $2 "|" $3 "|" $4}' Student1 > Student3
yash@yash-VirtualBox:~$ cat Student3
PRN Number | Student Name | Year | Division 
12110382 | INGLE AKASH SWARUP | SY | CS-B 
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B 
12111284 | JOSHI PRANAV JAYANT | SY | CS-B 
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B 
12010017 | Pavan Kumar Sanjay | TY | CS-C 
12010870 | PAWAR OMKAR VIKAS | TY | CS-C 
12011408 | PRANITA PRASHANT MASKE | TY | CS-C 
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C 
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C 
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C 
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C 
12120033 | MUKTA PATIL | TY | CS-C 
11910490 | KOLPE SAKET PRADIP | BTech | CS-B 
12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C 
11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D 
11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D 
11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D 
11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D 
11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 
9. Find out Roll No., Email Id and Gender field date from “Student1” file and save into “Student4” file.
yash@yash-VirtualBox:~$ awk -F'|' '{print $5 "|" $6 "|" $7}' Student1 > Student4
yash@yash-VirtualBox:~$ cat Student4
 Roll No | Email Id | Gender
 32 | akash.ingle21@vit.edu | Male
 40 | atharva.jayappa21@vit.edu | Male
 43 | pranav.joshi21@vit.edu | Male
 56 | ojas.ketkar211@vit.edu | Male
 26 | pavan.sanjay20@vit.edu | Male
 28 | omkar.pawar20@vit.edu | Male
 41 | pranita.maske20@vit.edu | Female
 55 | akash.bhagwat21@vit.edu | Male
 62 | udayan.gaikwad21@vit.edu | Male
 64 | saniya.inamadar21@vit.edu | Female
 69 | shreyas.kapse21@vit.edu | Male
 72 | patil.mukta21@vit.edu | Male
 16 | saket.kolpe19@vit.edu | Male
 28 | gaurav.pawar20@vit.edu | Male
 2 | varun.ringnekar19@vit.edu | Male
 9 | harsh.satdeve19@vit.edu | Male
 7 | SAMARTH.GAWANDE19@vit.edu | Male
 13 | kirtish.surangalikar19@vit.edu | Male
 11 | pradyumn.patil19@vit.edu | Male└─$ cat Student4
10. Combine “Student3” and “Student4” file and save content into “Student5” file.
yash@yash-VirtualBox:~$ cat Student3 Student4 > Student5
yash@yash-VirtualBox:~$ cat Student5
PRN Number | Student Name | Year | Division 
12110382 | INGLE AKASH SWARUP | SY | CS-B 
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B 
12111284 | JOSHI PRANAV JAYANT | SY | CS-B 
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B 
12010017 | Pavan Kumar Sanjay | TY | CS-C 
12010870 | PAWAR OMKAR VIKAS | TY | CS-C 
12011408 | PRANITA PRASHANT MASKE | TY | CS-C 
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C 
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C 
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C 
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C 
12120033 | MUKTA PATIL | TY | CS-C 
11910490 | KOLPE SAKET PRADIP | BTech | CS-B 
12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C 
11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D 
11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D 
11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D 
11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D 
11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 
|||
 Roll No | Email Id | Gender
 32 | akash.ingle21@vit.edu | Male
 40 | atharva.jayappa21@vit.edu | Male
 43 | pranav.joshi21@vit.edu | Male
 56 | ojas.ketkar211@vit.edu | Male
 26 | pavan.sanjay20@vit.edu | Male
 28 | omkar.pawar20@vit.edu | Male
 41 | pranita.maske20@vit.edu | Female
 55 | akash.bhagwat21@vit.edu | Male
 62 | udayan.gaikwad21@vit.edu | Male
 64 | saniya.inamadar21@vit.edu | Female
 69 | shreyas.kapse21@vit.edu | Male
 72 | patil.mukta21@vit.edu | Male
 16 | saket.kolpe19@vit.edu | Male
 28 | gaurav.pawar20@vit.edu | Male
 2 | varun.ringnekar19@vit.edu | Male
 9 | harsh.satdeve19@vit.edu | Male
 7 | SAMARTH.GAWANDE19@vit.edu | Male
 13 | kirtish.surangalikar19@vit.edu | Male
 11 | pradyumn.patil19@vit.edu | Male
11. Convert “Student1” content into Uppercase Letter and save into “Student6” file.
yash@yash-VirtualBox:~$ tr 'a-z' 'A-Z' < Student1 > Student6
yash@yash-VirtualBox:~$ cat Student6
PRN NUMBER | STUDENT NAME | YEAR | DIVISION | ROLL NO | EMAIL ID | GENDER
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | AKASH.INGLE21@VIT.EDU | MALE
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | ATHARVA.JAYAPPA21@VIT.EDU | MALE
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | PRANAV.JOSHI21@VIT.EDU | MALE
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | OJAS.KETKAR211@VIT.EDU | MALE
12010017 | PAVAN KUMAR SANJAY | TY | CS-C | 26 | PAVAN.SANJAY20@VIT.EDU | MALE
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | OMKAR.PAWAR20@VIT.EDU | MALE
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | PRANITA.MASKE20@VIT.EDU | FEMALE
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | AKASH.BHAGWAT21@VIT.EDU | MALE
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | UDAYAN.GAIKWAD21@VIT.EDU | MALE
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | SANIYA.INAMADAR21@VIT.EDU | FEMALE
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | SHREYAS.KAPSE21@VIT.EDU | MALE
12120033 | MUKTA PATIL | TY | CS-C | 72 | PATIL.MUKTA21@VIT.EDU | MALE
11910490 | KOLPE SAKET PRADIP | BTECH | CS-B | 16 | SAKET.KOLPE19@VIT.EDU | MALE
12020233 | PAWAR GAURAV PRABHAKAR | BTECH | CS-C | 28 | GAURAV.PAWAR20@VIT.EDU | MALE
11910590 | RINGNEKAR VARUN DEEPAK | BTECH | CS-D | 2 | VARUN.RINGNEKAR19@VIT.EDU | MALE
11910541 | SATDEVE HARSH SHAILESH | BTECH | CS-D | 9 | HARSH.SATDEVE19@VIT.EDU | MALE
11910157 | SAMARTH GAJANAN GAWANDE | BTECH | CS-D | 7 | SAMARTH.GAWANDE19@VIT.EDU | MALE
11911020 | SURANGALIKAR KIRTISH NITIN | BTECH | CS-D | 13 | KIRTISH.SURANGALIKAR19@VIT.EDU | MALE
11911229 | PATIL PRADYUMN NARENDRA | BTECH | CS-C-3 | 11 | PRADYUMN.PATIL19@VIT.EDU | MALE
12.  Compare “Student1” and “BTech” file and save content into “Student7” file.
yash@yash-VirtualBox:~$ cmp Student1 Btech > Student7
yash@yash-VirtualBox:~$ cat Student7
Student1 Btech differ: byte 1, line 1
13. Find out difference between “Student1” and “Btech” file and Save into “Student 8” file.
yash@yash-VirtualBox:~$ diff Student1 Btech > Student8
yash@yash-VirtualBox:~$ cat Student8
1,13d0
< PRN Number | Student Name | Year | Division | Roll No | Email Id | Gender
< 12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
< 12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
< 12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
< 12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
< 12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
< 12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
< 12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
< 12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
< 12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
< 12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
< 12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
< 12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
21d7
< 
14.  Find out common between “Student1” and “Btech” file and save content into “Student9” file.
yash@yash-VirtualBox:~$ sort Student1 > Student11
yash@yash-VirtualBox:~$ sort Btech > Btech11
yash@yash-VirtualBox:~$ comm Student11 Btech11 > Student9
yash@yash-VirtualBox:~$ cat Student9

		11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D | 7 | SAMARTH.GAWANDE19@vit.edu | Male
		11910490 | KOLPE SAKET PRADIP | BTech | CS-B | 16 | saket.kolpe19@vit.edu | Male
		11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D | 9 | harsh.satdeve19@vit.edu | Male
		11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D | 2 | varun.ringnekar19@vit.edu | Male
		11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D | 13 | kirtish.surangalikar19@vit.edu | Male
		11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 | 11 | pradyumn.patil19@vit.edu | Male
12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
		12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C | 28 | gaurav.pawar20@vit.edu | Male
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
PRN Number | Student Name | Year | Division | Roll No | Email Id | Gender
15. Remove user and group of “SY” file read and write permission file.
yash@yash-VirtualBox:~$ ls -l SY
-rw-rw-r-- 1 yash yash 324 Jan 30 21:53 SY
yash@yash-VirtualBox:~$ chmod ug-rw SY
yash@yash-VirtualBox:~$ ls -l SY
-------r-- 1 yash yash 324 Jan 30 21:53 SY
16. Assign read, write, execute permission to user and others of “SY” file.
yash@yash-VirtualBox:~$ chmod 707 SY
yash@yash-VirtualBox:~$ ls -l SY
-rwx---rwx 1 yash yash 324 Jan 30 21:53 SY
17. Display count of male students from “Student1” file.
yash@yash-VirtualBox:~$ grep -c 'Male' Student1 
17
18. Find out Name of student field data from “Student1” file and redirect output to count  Number of students in “Student1” file.
yash@yash-VirtualBox:~$ awk -F'|' '{print $2}' Student1 | wc -l
20
19. Find out file and directory in current path and trap this output in userfile as “ufile”.Also Display count of number of directories and files in current path.
yash@yash-VirtualBox:~$ ls -l > ufile
yash@yash-VirtualBox:~$ ls -l | grep -v '^d' | wc -l
18
yash@yash-VirtualBox:~$ ls -l | grep '^d' | wc -l
9


So, the number of files is 18 and the directories are 9. 






Tutorial 3


1.	Write a shell script to display files in current directory /output of date command /present working directory. Accept choice from user. (Use case statement) .
student@admins-iMac ~ % nano y1.sh
  GNU nano 2.0.6                 File: y1.sh                                         
echo "Enter choice, 1: Display Files in Current Directory, 2: Output of Date Command$
read choice
case $choice in
1) ls;;
2) date;;
3) pwd;;
*) echo "Wrong Input"
esac

student@admins-iMac ~ % bash y1.sh
Enter choice, 1: Display Files in Current Directory, 2: Output of Date Command, 3: Present Working Directory 
1
41		Y2		f1.sh		mydir		s5.sh
8Puzzle.java	a.sh		f1.sh.save	myfile.txt	s6.sh
Applications	aa		f2.sh		name.txt	s8.sh
Desktop		ap.sh		f3.sh		ourdate		s9.sh
Documents	armstrong.sh	f4.sh		prob1.sh	stud.sh
Downloads	array.sh	f5.sh		q1.sh		student.sh
Library		bb		f6.sh		q2.sh		unique.sh
Movies		cc		filescount.sh	q3.sh		ved.txt
Music		char_count.sh	kadane.sh	s1.sh		y1.sh
Pictures	diagonal.sh	list.txt	s2.sh		y2.sh
Public		f1		mydate		s3.sh
student@admins-iMac ~ % bash y1.sh
Enter choice, 1: Display Files in Current Directory, 2: Output of Date Command, 3: Present Working Directory 
2
Tue Feb 11 12:34:21 IST 2025
student@admins-iMac ~ % bash y1.sh
Enter choice, 1: Display Files in Current Directory, 2: Output of Date Command, 3: Present Working Directory 
3
/Users/student
student@admins-iMac ~ % bash y1.sh
Enter choice, 1: Display Files in Current Directory, 2: Output of Date Command, 3: Present Working Directory 
5
Wrong Input

2.	Write a shell script to perform arithmetic operation. Accept choice from user. (Use case statement).
student@admins-iMac ~ % nano y2.sh
  GNU nano 2.0.6                 File: y2.sh                                         
echo "Enter Two Numbers: "
read num1
read num2
echo "Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division"
read choice
case $choice in
1) add=$[ num1 + num2 ]
echo "Addition is $add";;
2) sub=$[ num1 - num2 ]
echo "Subtraction is $sub";;
3) mul=$[ num1 * num2 ]
echo "Multiplication is $mul";;
4) div=$[ num1 / num2 ]
echo "Division is $div";;
*) echo "Wrong Input"
esac

student@admins-iMac ~ % bash y2.sh
Enter Two Numbers: 
10  
5
Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division
1
Addition is 15
student@admins-iMac ~ % bash y2.sh
Enter Two Numbers: 
10
5
Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division
2
Subtraction is 5
student@admins-iMac ~ % bash y2.sh
Enter Two Numbers: 
10
5
Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division
3
Multiplication is 50
student@admins-iMac ~ % bash y2.sh
Enter Two Numbers: 
10
5
Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division
4
Division is 2
student@admins-iMac ~ % bash y2.sh
Enter Two Numbers: 
10
5
Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division
5
Wrong Input

3.	Write a shell script to identify entered key is Uppercase/Lowercase /Number /Punctuation. (Use case statement).
student@admins-iMac ~ % nano y3.sh
  GNU nano 2.0.6                 File: y3.sh                                         
echo "Enter a Key: "
read key
case $key in
[A-Z]) echo "Entered key is Uppercase";;
[a-z]) echo "Entered key is Lowercase";;
[0-9]) echo "Entered key is Number";;
[[:punct:]]) echo "Entered key is Punctuation";;
*) echo "Invalid key"
esac

student@admins-iMac ~ % bash y3.sh
Enter a Key: 
Y
Entered key is Uppercase
student@admins-iMac ~ % bash y3.sh
Enter a Key: 
g
Entered key is Lowercase
student@admins-iMac ~ % bash y3.sh
Enter a Key: 
9
Entered key is Number
student@admins-iMac ~ % bash y3.sh
Enter a Key: 
$
Entered key is Punctuation












Tutorial 4


1.	Write a shell script to enter a name & 3 subject marks of a student & calculate total & percentage & print First class, second class, pass class & fail.
yash@yash-VirtualBox:~/OS$ nano s1.sh
GNU nano 7.2                                                                     s1.sh                                                                               
echo "Enter the name of student: "
read name
echo "Enter the names of three subjects: "
read sub1 sub2 sub3
echo "Enter the marks of three subjects respectively: "
read m1 m2 m3

total=$(($m1 + $m2 + $m3))
per=$(echo "scale=2; $total / 3" | bc)

echo "Total is $total"
echo "Percentage is $per"
echo "The result is: "

if [ $total -gt 270 ] 
then
echo "First Class"
elif [ $total -gt 240 ]
then
echo "Second Class"
elif [ $total -gt 120 ]
then
echo "Pass Class"
else
echo "Fail"
fi

yash@yash-VirtualBox:~/OS$ bash s1.sh
Enter the name of student: 
Yash
Enter the names of three subjects: 
OS MAM CGVR
Enter the marks of three subjects respectively: 
91 67 80
Name is Yash
OS=91, MAM=67, CGVR=80
Total is 238
Percentage is 79.33
The result is: 
Pass Class

2.	Write Shell program to convert given number from decimal to binary and binary to decimal.
yash@yash-VirtualBox:~/OS$ nano s2.sh
  GNU nano 7.2                                                                     s2.sh                                                                               
echo "Enter a choice, 1. Decimal to Binary, 2. Binary to Decimal"
read choice

case $choice in
1) echo "Enter Decimal Number"
read deci

while [ $deci -gt 0 ]
do
  remainder=$(( deci % 2 ))  
  bin="$remainder$bin"    
  deci=$(( deci / 2 ))    
done
echo "Binary: $bin";;

2) echo "Enter Binary Number"
read bin
power=1

while [ -n "$bin" ]
do
  digit=${bin: -1} 
  deci=$(( deci + digit * power ))  
  power=$(( power * 2 ))
  bin=${bin:0:-1}  
done
echo "Decimal: $deci";;

*) echo "Wrong Choice"
esac

yash@yash-VirtualBox:~/OS$ bash s2.sh
Enter a choice, 1. Decimal to Binary, 2. Binary to Decimal
1
Enter Decimal Number
12
Binary: 1100
yash@yash-VirtualBox:~/OS$ bash s2.sh
Enter a choice, 1. Decimal to Binary, 2. Binary to Decimal
2
Enter Binary Number
1001
Decimal: 9
yash@yash-VirtualBox:~/OS$ bash s2.sh
Enter a choice, 1. Decimal to Binary, 2. Binary to Decimal
4
Wrong Choice

3.	Write a shell script that print the smallest digit of a given number.
yash@yash-VirtualBox:~/OS$ nano s3.sh
  GNU nano 7.2                                                                     s3.sh                                                                               
echo "Enter a number:"
read num

min_digit=9

while [ "$num" -gt 0 ]
do
  digit=$(( num % 10 ))  
  if [ "$digit" -lt "$min_digit" ]
  then
  min_digit=$digit  
  fi

  num=$(( num / 10 )) 
done

echo "Smallest digit: $min_digit"

yash@yash-VirtualBox:~/OS$ bash s3.sh 
Enter a number:
40973
Smallest digit: 0

4.	Write a shell program for printing Fibonacci Series.
yash@yash-VirtualBox:~/OS$ nano s4.sh
 GNU nano 7.2                                                                     s4.sh                                                                               
echo "Enter the number of terms:"
read n

a=0
b=1

echo "Fibonacci Series:"

for (( i=0; i<n; i++ ))
do
  echo -n "$a "  
  temp=$(( a + b ))  
  a=$b  
  b=$temp
done

echo  

yash@yash-VirtualBox:~/OS$ bash s4.sh
Enter the number of terms:
11
Fibonacci Series:
0 1 1 2 3 5 8 13 21 34 55 

````
