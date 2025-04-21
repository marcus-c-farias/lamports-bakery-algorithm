all: liblamport_mutex.so program program_lamport #run_programs clean

liblamport_mutex.so: lamport_mutex.o
	gcc -shared lamport_mutex.o -o liblamport_mutex.so

lamport_mutex.o: lamport_mutex.c
	gcc -fPIC -c lamport_mutex.c -o lamport_mutex.o

program: program.c 
	gcc program.c -o program

program_lamport: program_lamport.c liblamport_mutex.so
	gcc program_lamport.c -L. -llamport_mutex -o program_lamport

run_program: program
	time ./program

run_program_lamport: program_lamport
	time sh -c "LD_LIBRARY_PATH=. ./program_lamport"

run_programs: run_program run_program_lamport

clean:
	rm -f *.o *.so program program_lamport