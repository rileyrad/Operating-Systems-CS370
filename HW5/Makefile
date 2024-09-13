# C++ Makefile for HW5
#
# Replace the LastName-FirstName in the package section with
# your actual first and last name.

CXX=gcc
CXXFLAGS=-std=c11 -g -Wall -I.

all: Scheduler.c 
	$(CXX) $(CXXFLAGS) -o Scheduler Scheduler.c
		
clean:
	rm -f Scheduler *.o *.zip
	
package:
	zip Radici-Riley-HW5.zip README.txt Makefile Scheduler.c