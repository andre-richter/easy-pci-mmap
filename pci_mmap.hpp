/*
 * -*- coding: utf-8 -*-
 *
 *
 * (c) 2016 by the author(s)
 *
 * Author(s):
 *    Andre Richter, andre.richter@tum.de
 */

#pragma once

#include "macros.hpp"
#include "utility.hpp"

#include <unistd.h> 		// getpagesize()
#include <sys/mman.h>		// munmap()
#include <fcntl.h>		// O_ flags
#include <sys/stat.h>


class pci_mmap
{
public:
	pci_mmap(uint32_t vendor, uint32_t device, unsigned int func_num, unsigned int bar_num);
	~pci_mmap();

	uint32_t read32(uint64_t addr) const;
	void write32(uint64_t addr, uint32_t data) const;

	uint64_t read64(uint64_t addr) const;
	void write64(uint64_t addr, uint64_t data) const;

	std::string dbdf() const;
	unsigned int bar_size() const;
	std::string sysfs_bar_file() const;

private:
	bool mmap_bar();

	unsigned int _bar_num;
	std::string _dbdf;
	unsigned int _bar_size;
	std::string _sysfs_bar_file;
	int bar_fd;
        void *bar;
};

inline uint32_t pci_mmap::read32(uint64_t addr) const
{
	return *((volatile uint32_t *)((char *)bar + addr));
}

inline void pci_mmap::write32(uint64_t addr, uint32_t data) const
{
	*((volatile uint32_t *)((char *)bar + addr)) = data;
}

inline uint64_t pci_mmap::read64(uint64_t addr) const
{
	return *((volatile uint64_t *)((char *)bar + addr));
}

inline void pci_mmap::write64(uint64_t addr, uint64_t data) const
{
	*((volatile uint64_t *)((char *)bar + addr)) = data;
}
