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

pci_mmap::pci_mmap(uint32_t vendor, uint32_t device, unsigned int func_num, unsigned int bar_num)
{
	if (bar_num > 5) {
		pr_errno_msg("Invalid BAR number");
		exit(EXIT_FAILURE);
	}
	_bar_num = bar_num;

	_dbdf = utility::get_pci_dbdf(vendor, device, func_num);
	if (_dbdf.empty())
		exit(EXIT_FAILURE);

	if (!(mmap_bar()))
		exit(EXIT_FAILURE);
}

pci_mmap::~pci_mmap()
{
	munmap(bar, getpagesize());
	close(bar_fd);
}

bool pci_mmap::mmap_bar()
{
	_sysfs_bar_file = "/sys/bus/pci/devices/" + _dbdf + "/resource" + std::to_string(_bar_num);

	bar_fd = open(_sysfs_bar_file.c_str(), O_RDWR | O_SYNC);
	if (bar_fd < 0) {
		pr_errno_msg("Maybe execute via sudo?");
		return false;
	}

	struct stat st;
	stat(_sysfs_bar_file.c_str(), &st); // get BAR size through sysfs file size
	_bar_size = st.st_size;

	bar = mmap(0, _bar_size, PROT_READ | PROT_WRITE, MAP_SHARED, bar_fd, 0);
	if (bar == MAP_FAILED) {
		pr_errno();
		close(bar_fd);
		return false;
	}

	return true;
}

std::string pci_mmap::dbdf() const
{
	return _dbdf;
}

unsigned int pci_mmap::bar_size() const
{
	return _bar_size;
}

std::string pci_mmap::sysfs_bar_file() const
{
	return _sysfs_bar_file;
}
