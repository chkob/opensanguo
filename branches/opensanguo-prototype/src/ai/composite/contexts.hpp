
/* $Id: contexts.hpp 38045 2009-08-23 19:30:45Z crab $ */
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
 * @file ai/composite/contexts.hpp
 * Composite AI contexts
 */

#ifndef AI_COMPOSITE_CONTEXTS_HPP_INCLUDED
#define AI_COMPOSITE_CONTEXTS_HPP_INCLUDED

#include "../../global.hpp"

#include "../contexts.hpp"
#include "../default/contexts.hpp"

#include <boost/shared_ptr.hpp>
#include <vector>

#ifdef _MSC_VER
#pragma warning(push)
//silence "inherits via dominance" warnings
#pragma warning(disable:4250)
#endif


//============================================================================
namespace ai {

class ai_context : public virtual default_ai_context {
public:


	/**
	 * Constructor
	 */
	ai_context();


	/**
	 * Destructor
	 */
	virtual ~ai_context();


	/**
	 * Unwrap
	 */
	virtual ai_context& get_ai_context() = 0;


};


class rca_context;
class rca_context : public virtual ai_context {
public:


	/**
	 * Constructor
	 */
	rca_context();


	/**
	 * Destructor
	 */
	virtual ~rca_context();


	/**
	 * Unwrap
	 */
	virtual rca_context& get_rca_context() = 0;
};


class candidate_action_context;
class candidate_action_context : public virtual rca_context {
public:


	/**
	 * Constructor
	 */
	candidate_action_context() {}


	/**
	 * Destructor
	 */
	virtual ~candidate_action_context() {}


	/**
	 * Unwrap
	 */
	virtual candidate_action_context& get_candidate_action_context() = 0;
};

// proxies
class ai_context_proxy : public virtual ai_context, public virtual default_ai_context_proxy {
public:
	ai_context_proxy();


	void init_ai_context_proxy(ai_context &target)
	{
		init_default_ai_context_proxy(target);
		target_ = &target;
	}


	virtual	~ai_context_proxy();


	ai_context& get_ai_context()
	{
		return target_->get_ai_context();
	}


private:
	ai_context *target_;
};


class rca_context_proxy : public virtual rca_context, public virtual ai_context_proxy {
public:
	rca_context_proxy();


	virtual ~rca_context_proxy();


	void init_rca_context_proxy(rca_context &target)
	{
		init_ai_context_proxy(target);
		target_ = &target;
	}


	rca_context& get_rca_context()
	{
		return target_->get_rca_context();
	}


private:
	rca_context *target_;
};


} //end of namespace ai

#ifdef _MSC_VER
#pragma warning(pop)
#endif


#endif