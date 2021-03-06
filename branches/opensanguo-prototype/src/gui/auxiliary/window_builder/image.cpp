/* $Id: image.cpp 37554 2009-08-08 20:22:56Z mordante $ */
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

#include "gui/auxiliary/window_builder/image.hpp"

#include "config.hpp"
#include "gui/auxiliary/log.hpp"
#include "gui/widgets/image.hpp"

namespace gui2 {

namespace implementation {

tbuilder_image::tbuilder_image(const config& cfg)
	: tbuilder_control(cfg)
{
}

twidget* tbuilder_image::build() const
{
	timage* widget = new timage();

	init_control(widget);

	DBG_GUI_G << "Window builder: placed image '"
		<< id << "' with defintion '"
		<< definition << "'.\n";

	return widget;
}

} // namespace implementation

} // namespace gui2

/*WIKI_MACRO
 * @start_macro = image_description
 *
 *        An image shows a static image.
 * @end_macro
 */

/*WIKI
 * @page = GUIWidgetInstanceWML
 * @order = 2_image
 *
 * == Image ==
 *
 * @macro = image_description
 *
 * An image has no extra fields.
 */

