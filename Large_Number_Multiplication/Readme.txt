

Source Files:

prog1.c-> For single thread

prog2.c-> For multi thread

Input Files:

a.txt
b.txt

Output Files

c1.txt -> For single thread
c2.txt -> For multi thread


create_input.c -> File for creating input files of desired size

Out files

p1.out -> For single thread
p2.out -> For multi thread

time.sh file for seeing lapse time

Execution steps:

For executing prog1.c and prog2.c

gcc prog1.c/prog2.c -lpthread -o p1.out
./p1.out

gcc prog2.c -lpthread -o p2.out
./p2.out


After running prog2.c, it will ask for number of threads. Enter a number between 1 and 100


For running the files together and seeing the lapse time, run the below command

./time.sh

The program has been tested for input files containing upto 10000 digits.