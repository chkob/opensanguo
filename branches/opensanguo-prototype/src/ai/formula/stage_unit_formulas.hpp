/* $Id: stage_unit_formulas.hpp 37682 2009-08-11 20:42:22Z crab $ */
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
 * @file ai/formula/stage_unit_formulas.hpp
 * Stage which executes unit formulas
 * */


#ifndef AI_FORMULA_STAGE_UNIT_FORMULAS_HPP_INCLUDED
#define AI_FORMULA_STAGE_UNIT_FORMULAS_HPP_INCLUDED

#include "../composite/stage.hpp"


#ifdef _MSC_VER
#pragma warning(push)
//silence "inherits via dominance" warnings
#pragma warning(disable:4250)
#endif

namespace ai {

class formula_ai;

class stage_unit_formulas: public stage {
public:
        stage_unit_formulas( ai_context &context, const config &cfg, formula_ai &fai );

        virtual ~stage_unit_formulas();

        bool do_play_stage();

        void on_create();

        config to_config() const;

private:
        const config &cfg_;
	formula_ai &fai_;

};

} //end of namespace ai

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
