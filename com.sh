#!/bin/bash 
gcc -c -g asd.c -o asd.o -I./flexNet/include/ -lev
gcc -c -g my_list.c -o my_list.o
ar cr liblicense.so asd.o my_list.o
rm *.o -rf




