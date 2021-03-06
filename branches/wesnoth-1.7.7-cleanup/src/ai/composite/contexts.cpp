/* $Id: contexts.cpp 37383 2009-08-01 14:17:15Z crab $ */
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
 * Helper functions for the object which operates in the context of AI for specific side
 * This is part of AI interface
 * @file ai/composite/contexts.cpp
 */

#include "contexts.hpp"

// =======================================================================
namespace ai {

ai_context::ai_context()
{
}


ai_context::~ai_context()
{
}


ai_context_proxy::ai_context_proxy()
	: target_()
{
}


ai_context_proxy::~ai_context_proxy()
{
}


rca_context::rca_context()
{
}


rca_context::~rca_context()
{
}


rca_context_proxy::rca_context_proxy()
	: target_()
{
}


rca_context_proxy::~rca_context_proxy()
{
}

} //end of namespace ai
