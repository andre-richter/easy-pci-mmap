/*
 * -*- coding: utf-8 -*-
 *
 *
 * (c) 2016 by the author(s)
 *
 * Author(s):
 *    Andre Richter, andre.richter@tum.de
 */

#include "utility.hpp"

std::string utility::get_pci_dbdf(uint32_t vendor, uint32_t device,
				  unsigned int func_num)
{
	DIR *dir;
	std::string err = std::string();

        if ((dir = opendir("/sys/bus/pci/devices")) == nullptr) {
	        pr_errno();
		return err;
        }

	// iterate over all PCIe devices
	struct dirent *d;
	std::ifstream ifstr;
	std::string bdf_found;
	while ((d = readdir(dir)) != nullptr) {

		// only consider actual device folders, not ./ and ../
		if (strstr(d->d_name, "0000:") != nullptr) {
			bdf_found = std::string(d->d_name);

			// Continue only if the function number matches
			if ((unsigned int)(bdf_found.back() - '0') != func_num)
				continue;

			std::string path("/sys/bus/pci/devices/" + bdf_found);

			// read vendor id
			ifstr.open(path + "/vendor");
		        std::string tmp((std::istreambuf_iterator<char>(ifstr)),
					std::istreambuf_iterator<char>());
			ifstr.close();

			// check if vendor id is correct
			if (std::stoul(tmp, nullptr, 16) == vendor) {

				// read device id
				ifstr.open(path + "/device");
				std::string tmp((std::istreambuf_iterator<char>(ifstr)),
						std::istreambuf_iterator<char>());
				ifstr.close();

				// check if device also fits
			        if (std::stoul(tmp, nullptr, 16) == device)
				        return bdf_found;
			}
		}
	}
	pr_err_msg("BDF not found for 0x" << std::setbase(16)
		   << vendor << ":0x" << device
		   << " Func" << func_num);

	return err;
}
