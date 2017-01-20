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

#include <stdint.h>		// uint32...
#include <string>
#include <dirent.h>
#include <fstream>		// ifstream
#include <iomanip> 		// setbase()

namespace utility {
	std::string get_pci_dbdf(uint32_t vendor, uint32_t device,
				 unsigned int func_num);
}
