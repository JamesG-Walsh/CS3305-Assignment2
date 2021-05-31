# build an executable named assignment2 from assignment2.c

all: assignment2.c
	 gcc assignment2.c -o assignment2

clean:
	 $(RM) assignment2

run:
	$ ./assignment2 "CS" "3305" " is fun!"

run2:
	$ ./assignment2 "ab" "cd" "ef"
