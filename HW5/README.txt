README
======

This package includes the following files.

|-- Scheduler.c [The program written in C. Reads in a .csv file, turns it into a 
                data structure, and makes three copies for each of the following 
                scheduling algorithms: FCFS (Non-preemptive), SJF (Preemptive),
                Priority (Preemptive)]
|-- Makefile [A Makefile which carries out the operations all, clean, and package]
|-- README.txt [This file]

To compile:
    make all

To run:
    ./Scheduler <Name of CSV file>


