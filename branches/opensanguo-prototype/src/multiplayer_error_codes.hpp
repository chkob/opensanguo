/* $Id: multiplayer_error_codes.hpp 33560 2009-03-11 18:43:11Z baufo $ */
/*
   Copyright (C) 2009 by Thomas Baumhauer <thomas.baumhauer@NOSPAMgmail.com>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2
   or at your option any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

/**
 * @file  multiplayer_error_codes.hpp
 * Define the errors the server may send during the login procedure
 */

#ifndef MULTIPLAYER_ERROR_CODES_HPP_INCLUDED
#define MULTIPLAYER_ERROR_CODES_HPP_INCLUDED

#define MP_MUST_LOGIN					"100"
#define MP_NAME_TAKEN_ERROR				"101"
#define MP_INVALID_CHARS_IN_NAME_ERROR			"102"
#define MP_NAME_TOO_LONG_ERROR				"103"
#define MP_NAME_RESERVED_ERROR				"104"
#define MP_NAME_UNREGISTERED_ERROR			"105"

#define MP_PASSWORD_REQUEST				"200"
#define MP_PASSWORD_REQUEST_FOR_LOGGED_IN_NAME		"201"
#define MP_NO_SEED_ERROR				"202"
#define MP_INCORRECT_PASSWORD_ERROR			"203"

#endif // MULTIPLAYER_ERROR_CODES_HPP_INCLUDES


