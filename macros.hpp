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

#include <iostream>
#include <cerrno>
#include <cstring>

#define ERROR_BODY(message) std::cout << "ERROR:\t" << __FUNCTION__ << ":\t" \
	<< message << std::endl
#define pr_errno() ERROR_BODY(std::strerror(errno))
#define pr_errno_msg(message) ERROR_BODY(std::strerror(errno) << std::endl << message)
#define pr_err_msg(message) ERROR_BODY(message)
