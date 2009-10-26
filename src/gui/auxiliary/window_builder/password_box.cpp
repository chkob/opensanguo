/* $Id: password_box.cpp 36317 2009-06-21 11:15:39Z mordante $ */
/*
   Copyright (C) 2008 - 2009 by Mark de Wever <koraq@xs4all.nl>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2
   or at your option any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

#define GETTEXT_DOMAIN "wesnoth-lib"

#include "gui/auxiliary/window_builder/password_box.hpp"

#include "config.hpp"
#include "gui/auxiliary/log.hpp"
#include "gui/widgets/password_box.hpp"


namespace gui2 {

namespace implementation {

tbuilder_password_box::tbuilder_password_box(const config& cfg)
	: tbuilder_control(cfg)
	, history_(cfg["history"])
{
}

twidget* tbuilder_password_box::build() const
{
	tpassword_box* widget = new tpassword_box();

	init_control(widget);

	// A textbox doesn't have a label but a text
	widget->set_value(label);

	if (!history_.empty()) {
		widget->set_history(history_);
	}

	DBG_GUI_G << "Window builder: placed password box '"
		<< id << "' with defintion '"
		<< definition << "'.\n";

	return widget;
}

} // namespace implementation

} // namespace gui2

/*WIKI
 * @page = GUIWidgetInstanceWML
 * @order = 2_password_box
 *
 * == Password box ==
 *
 * @start_table = config
 *     label (tstring = "")            The initial text of the text box.
 *     history (string = "")           The name of the history for the text
 *                                     box. A history saves the data entered
 *                                     in a text box between the games. With
 *                                     the up and down arrow it can be
 *                                     accessed. To create a new history item
 *                                     just add a new unique name for this
 *                                     field and the engine will handle the
 *                                     rest.
 * @end_table
 */

