/* $Id: formula_debugger_fwd.hpp 37911 2009-08-17 15:06:13Z crab $ */
/*
   Copyright (C) 2009 by Yurii Chernyi <terraninfo@terraninfo.net>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2
   or at your option any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

/**
 * @file formula_debugger_fwd.hpp
 * Formula AI debugger, forward
 *
 */


#ifndef FORMULA_DEBUGGER_FWD_HPP_INCLUDED
#define FORMULA_DEBUGGER_FWD_HPP_INCLUDED

#include "global.hpp"
#include "variant.hpp"

#include <boost/shared_ptr.hpp>
#include <deque>


class variant;

namespace game_logic {

class formula_debugger;
class debug_info;
class formula_expression;
class formula;
class formula_callable;

class base_breakpoint;

typedef boost::shared_ptr<base_breakpoint> breakpoint_ptr;

formula_debugger* add_debug_info(formula_debugger *fdb, int arg_number, const char *f_name);

variant evaluate_arg_callback(formula_debugger &fdb, const formula_expression &expression, const formula_callable &variables);

variant evaluate_formula_callback(formula_debugger &fdb, const formula &f, const formula_callable &variables);

variant evaluate_formula_callback(formula_debugger &fdb, const formula &f);


} // end of namespace game_logic

#endif
