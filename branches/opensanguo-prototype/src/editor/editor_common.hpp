/* $Id: editor_common.hpp 37545 2009-08-08 11:14:58Z ilor $ */
/*
   Copyright (C) 2008 - 2009 by Tomasz Sniatowski <kailoran@gmail.com>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2
   or at your option any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

/**
 * @file editor_common.hpp
 * Main (common) editor header. Contains forward declarations for most classes,
 * logging macro definitions and base exception declarations
 */

#ifndef EDITOR_EDITOR_COMMON_HPP_INCLUDED
#define EDITOR_EDITOR_COMMON_HPP_INCLUDED

#include "../log.hpp"
#include <stdexcept>

extern lg::log_domain log_editor;
#define DBG_ED LOG_STREAM_INDENT(debug, log_editor)
#define LOG_ED LOG_STREAM_INDENT(info, log_editor)
#define WRN_ED LOG_STREAM_INDENT(warn, log_editor)
#define ERR_ED LOG_STREAM_INDENT(err, log_editor)
#define SCOPE_ED log_scope2(log_editor, __func__)

class display;
class gamemap;

namespace editor {

struct editor_exception : public std::exception
{
	editor_exception(const std::string& msg)
	: msg(msg)
	{
	}
	~editor_exception() throw() {}
	const char* what() const throw() { return msg.c_str(); }
	const std::string msg;
};

struct editor_logic_exception : public editor_exception
{
	editor_logic_exception(const std::string& msg)
	: editor_exception(msg)
	{
	}
};

// forward declarations
class brush;
class editor_action;
class editor_controller;
class editor_display;
class editor_map;
class editor_mouse_handler;
class map_context;
class map_fragment;
class mouse_action;

} //end namespace editor

#endif
