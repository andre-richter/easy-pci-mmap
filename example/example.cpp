/*
 * -*- coding: utf-8 -*-
 *
 *
 * (c) 2016 by the author(s)
 *
 * Author(s):
 *    Andre Richter, andre.richter@tum.de
 */

#include "pci_mmap.hpp"

#define VENDOR   0x8086
#define DEVICE   0x8c26
#define FUNCTION 0
#define BAR      0

#define BAR_OFFSET 0x8

int main(int argc, char *argv[])
{
	pci_mmap dev(VENDOR, DEVICE, FUNCTION, BAR);

	std::cout << "Domain:Bus:Device:Function: "
		  << dev.dbdf() << std::endl

		  << "sysfs file:                 "
		  << dev.sysfs_bar_file() << std::endl

		  << "BAR size:                   0x"
		  << std::hex << dev.bar_size() << std::endl

		  << "read from BAR at offset:    0x"
		  << std::hex << BAR_OFFSET << std::endl

		  << "value:                      0x"
		  << std::hex << dev.read64(BAR_OFFSET) << std::endl;
}
