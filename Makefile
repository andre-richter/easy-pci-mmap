# -*- coding: utf-8 -*-
#
#
# (c) 2016 by the author(s)
#
# Author(s):
#    Andre Richter, andre.richter@tum.de
#

# Specify the target file and the install directory
CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -O3
LIB=libperf_iso.a
OBJS = utility.o pci_mmap.o

all: $(LIB)

$(LIB): utility.o pci_mmap.o
	ar rcs $@ $^
	ranlib $@

utility.o: utility.cpp utility.hpp
	$(CC) $(CFLAGS) -c utility.cpp

pci_mmap.o: pci_mmap.cpp pci_mmap.hpp
	$(CC) $(CFLAGS) -c pci_mmap.cpp

clean:
	rm $(LIB) $(OBJS)

.PHONY: all clean
