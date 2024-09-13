README
======

This package includes the following files.

|-- Coordinator.c [This is the coordinator program which uses fork() execlp() and wait() to produce four processes]
|-- Checker.c [The program that the four processes from coordinator will use]
|-- Makefile [A Makefile which carries out the operations make all and make clean]
|-- README.txt [This file]

To compile:
    make all

To run:
    ./Coordinator <divisor> <dividend_1> <dividend_2> <dividend_3> <dividend_4>

For example;
     ./Coordinator 3 3 20 49 102

