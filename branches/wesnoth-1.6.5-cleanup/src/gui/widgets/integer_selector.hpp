/* $Id: integer_selector.hpp 31858 2009-01-01 10:27:41Z mordante $ */
/*
   copyright (C) 2007 - 2009 by mark de wever <koraq@xs4all.nl>
   part of the battle for wesnoth project http://www.wesnoth.org/

   this program is free software; you can redistribute it and/or modify
   it under the terms of the gnu general public license version 2
   or at your option any later version.
   this program is distributed in the hope that it will be useful,
   but without any warranty.

   see the copying file for more details.
*/

#ifndef GUI_WIDGETS_INTEGER_SELECTOR_HPP_INCLUDED
#define GUI_WIDGETS_INTEGER_SELECTOR_HPP_INCLUDED

namespace gui2 {

/**
 * Small abstract helper class.
 *
 * Parts of the engine inherit this class so we can have generic
 * widgets to select an integer value.
 */
class tinteger_selector_
{
public:
	virtual ~tinteger_selector_() {}

	/** Sets the selected value. */
	virtual void set_value(const int value) = 0;

	/** Gets the selected value. */
	virtual int get_value() const = 0;

	/** Sets the minimum value. */
	virtual void set_minimum_value(const int value) = 0;

	/** Gets the minimum value. */
	virtual int get_minimum_value() const = 0;

	/** Sets the maximum value. */
	virtual void set_maximum_value(const int value) = 0;

	/** Gets the maximum value. */
	virtual int get_maximum_value() const = 0;
};

} // namespace gui2

#endif