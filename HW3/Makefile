#list of files 
C_SRCS = Coordinator.c Checker.c 
C_OBJS = Coordinator.o Checker.o 

#C_HEADERS 
OBJS = ${C_OBJS} 
EXE1 = Coordinator
EXE2 = Checker

#compiler and loader commands and flags 
GCC = gcc 
GCC_FLAGS = -std=c11 -g -Wall -c -I. 
LD_FLAGS = -std=c11 -g -Wall -I. 

#compile .c files to .o files 
.c.o: 
	$(GCC) $(GCC_FLAGS) $< 

#target is the executable 
all: Coordinator Checker 
Coordinator: Coordinator.o 
	$(GCC) $(LD_FLAGS) Coordinator.o -o $(EXE1) 

Checker: Checker.o 
	$(GCC) $(LD_FLAGS) Checker.o -o $(EXE2) 

#recomplile c objects if headers change 
$(C_OBJS): ${C_HEADERS} 

#clean up directory 
clean: 
	rm -f *.o *- $(EXE1) $(EXE2) 

package: 
	zip -r Riley-Radici-HW3.zip Coordinator.c Checker.c Makefile README.txt
