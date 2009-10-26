/* $Id: engine_default.cpp 37964 2009-08-20 08:56:20Z crab $ */
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
 * CPP AI Support engine - creating specific ai components from config
 * @file ai/composite/engine_default.cpp
 */

#include "ai.hpp"
#include "engine_default.hpp"
#include "rca.hpp"
#include "../../foreach.hpp"
#include "../../log.hpp"

namespace ai {

static lg::log_domain log_ai_composite_engine_cpp("ai/composite/engine/cpp");
#define DBG_AI_COMPOSITE_ENGINE_CPP LOG_STREAM(debug, log_ai_composite_engine_cpp)
#define LOG_AI_COMPOSITE_ENGINE_CPP LOG_STREAM(info, log_ai_composite_engine_cpp)
#define ERR_AI_COMPOSITE_ENGINE_CPP LOG_STREAM(err, log_ai_composite_engine_cpp)

engine_cpp::engine_cpp( readonly_context &context, const config &cfg )
	: engine(context,cfg)
{
}

engine_cpp::~engine_cpp()
{
}


void engine_cpp::do_parse_aspect_from_config( const config &cfg, const std::string &id, std::back_insert_iterator<std::vector< aspect_ptr > > b )
{
	const std::string aspect_factory_key = id+"*"+cfg["name"];//@note: hack which combines aspect id and name to get the std::string key of the aspect factory
	aspect_factory::factory_map::iterator f = aspect_factory::get_list().find(aspect_factory_key);
	if (f == aspect_factory::get_list().end()){
		ERR_AI_COMPOSITE_ENGINE_CPP << "side "<<ai_.get_side()<< " : UNKNOWN aspect["<<aspect_factory_key<<"]" << std::endl;
		DBG_AI_COMPOSITE_ENGINE_CPP << "config snippet contains: " << std::endl << cfg << std::endl;
		return;
	}
	aspect_ptr new_aspect = f->second->get_new_instance(ai_,cfg,id);
	if (!new_aspect) {
		ERR_AI_COMPOSITE_ENGINE_CPP << "side "<<ai_.get_side()<< " : UNABLE TO CREATE aspect, key=["<<aspect_factory_key<<"]"<< std::endl;
		DBG_AI_COMPOSITE_ENGINE_CPP << "config snippet contains: " << std::endl << cfg << std::endl;
		return;
	}
	*b = new_aspect;
}


void engine_cpp::do_parse_candidate_action_from_config( rca_context &context, const config &cfg, std::back_insert_iterator<std::vector< candidate_action_ptr > > b ){
	candidate_action_factory::factory_map::iterator f = candidate_action_factory::get_list().find(cfg["name"]);
	if (f == candidate_action_factory::get_list().end()){
		ERR_AI_COMPOSITE_ENGINE_CPP << "side "<<ai_.get_side()<< " : UNKNOWN candidate_action["<<cfg["name"]<<"]"<< std::endl;
		DBG_AI_COMPOSITE_ENGINE_CPP << "config snippet contains: " << std::endl << cfg << std::endl;
		return;
	}
	candidate_action_ptr new_candidate_action = f->second->get_new_instance(context,cfg);
	if (!new_candidate_action) {
		ERR_AI_COMPOSITE_ENGINE_CPP << "side "<<ai_.get_side()<< " : UNABLE TO CREATE candidate_action["<<cfg["name"]<<"]"<< std::endl;
		DBG_AI_COMPOSITE_ENGINE_CPP << "config snippet contains: " << std::endl << cfg << std::endl;
		return;
	}
	*b = new_candidate_action;

}

void engine_cpp::do_parse_stage_from_config( ai_context &context, const config &cfg, std::back_insert_iterator<std::vector< stage_ptr > > b )
{
	stage_factory::factory_map::iterator f = stage_factory::get_list().find(cfg["name"]);
	if (f == stage_factory::get_list().end()){
		ERR_AI_COMPOSITE_ENGINE_CPP << "side "<<ai_.get_side()<< " : UNKNOWN stage["<<cfg["name"]<<"]"<< std::endl;
		DBG_AI_COMPOSITE_ENGINE_CPP << "config snippet contains: " << std::endl << cfg << std::endl;
		return;
	}
	stage_ptr new_stage = f->second->get_new_instance(context,cfg);
	if (!new_stage) {
		ERR_AI_COMPOSITE_ENGINE_CPP << "side "<<ai_.get_side()<< " : UNABLE TO CREATE stage["<<cfg["name"]<<"]"<< std::endl;
		DBG_AI_COMPOSITE_ENGINE_CPP << "config snippet contains: " << std::endl << cfg << std::endl;
		return;
	}
	*b = new_stage;
}


void engine_cpp::do_parse_goal_from_config(const config &cfg, std::back_insert_iterator<std::vector< goal_ptr > > b )
{
	goal_factory::factory_map::iterator f = goal_factory::get_list().find(cfg["name"]);
	if (f == goal_factory::get_list().end()){
		ERR_AI_COMPOSITE_ENGINE_CPP << "side "<<ai_.get_side()<< " : UNKNOWN goal["<<cfg["name"]<<"]"<< std::endl;
		DBG_AI_COMPOSITE_ENGINE_CPP << "config snippet contains: " << std::endl << cfg << std::endl;
		return;
	}
	goal_ptr new_goal = f->second->get_new_instance(ai_,cfg);
	if (!new_goal) {
		ERR_AI_COMPOSITE_ENGINE_CPP << "side "<<ai_.get_side()<< " : UNABLE TO CREATE goal["<<cfg["name"]<<"]"<< std::endl;
		DBG_AI_COMPOSITE_ENGINE_CPP << "config snippet contains: " << std::endl << cfg << std::endl;
		return;
	}
	*b = new_goal;
}


std::string engine_cpp::get_name() const
{
	return "cpp";
}

} //end of namespace ai