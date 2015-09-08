# OS

C implementation of Unix commands and system calls
1) cat - concatenates files and prints on standard output
2) ls - lists the directory contents
3) kill - sends a signal to a process
4) wc - prints newline, word and byte contents for each file
5) ps - lists the current running processes
6) rm - removes files and directories (does not delete if the provided file is a directory.)
7) rm2
./a.out rm file_1 file_2 .... file_n
		:deletes n files without confirmation.
	./a.out rm -i file_1 file_2 .... file_n
		: deletes n files after the user confirms the deletion.
	(doesn't check for directory)
8) rm3
does not delete if the provided file is a directory.
9) rm -r
does not delete the directory. But goes into the directories and deletes non-directory files.

POSIX Thread library:

1) pthread.c - simple implementation of pthread library
