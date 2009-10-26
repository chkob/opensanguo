/* $Id: action_base.hpp 33081 2009-02-24 19:10:53Z ilor $ */
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
 * @file action_base.hpp
 * Base class for editor actions
 *
 * An action is constructed in response to a user command, then executed on
 * the map. An undo action is returned by default via pointer, caller-owned).
 * It is possible to call an action without creating the undo action.
 * Actions report failure via exceptions.
 * Code that only deals with actions polymorphically should only need to
 * include this header file.
 */

#ifndef EDITOR2_ACTION_BASE_HPP_INCLUDED
#define EDITOR2_ACTION_BASE_HPP_INCLUDED



#include "editor_common.hpp"

#include <string>


namespace editor2 {

/**
 * Base class for all editor actions. An editor_action object
 * encapsulates the action to be performed on a map, in separation
 * from the user interface or display, and provides a way of reversing
 * its affects by creating an "undo" action.  All the actions can be
 * processed via this base class' virtual functions.
 */
class editor_action
{
	public:
		editor_action();
		virtual ~editor_action();

		/**
		 * Perform the action, returning an undo action that,
		 * when performed, shall reverse any effects of this
		 * action.  The undo action object is owned by the
		 * caller. Default behaviour is to create a whole-map
		 * undo, call the perform_without_undo function and
		 * return the undo object.
		 */
		virtual editor_action* perform(map_context&) const;

		/**
		 * Perform the action without creating an undo action.
		 */
		virtual void perform_without_undo(map_context&) const = 0;

		/**
		 * @return the actual number of actions contained within
		 */
		virtual int action_count() const;

		/**
		 * A textual description of the action. For use
		 * e.g. in the undo menu, to have a "Undo: Fill with
		 * Grassland" item rather than just "Undo". Should be
		 * overriden by derived Actions, defaults to a debug
		 * message.
		 */
		virtual std::string get_description();

		/**
		 * Debugging aid. Return an unique identifier of this Action.
		 */
		int get_id() const { return id_; }

		/**
		 * Debugging aid. Return number of existing instances of Actions.
		 */
		static int get_instance_count() { return instance_count_; }

	private:
		static int next_id_;
		static int instance_count_;
		const int id_;
};


//TODO: add messages etc
struct editor_action_exception : public editor_exception
{
	editor_action_exception(const std::string& msg)
	: editor_exception(msg)
	{
	}
};

//thrown instead of a "todo" debug message
struct editor_action_not_implemented : public editor_action_exception
{
	editor_action_not_implemented();
};

//used when e.g. passed parameters are invalid
struct editor_action_creation_fail : public editor_action_exception
{
	editor_action_creation_fail();
};

} //end namespace editor2

#endif