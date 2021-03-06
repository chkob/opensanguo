/* $Id: scrollbar_panel.cpp 36579 2009-07-04 14:56:03Z mordante $ */
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

#include "gui/auxiliary/window_builder/scrollbar_panel.hpp"

#include "config.hpp"
#include "gettext.hpp"
#include "gui/auxiliary/log.hpp"
#include "gui/auxiliary/window_builder/helper.hpp"
#include "gui/widgets/scrollbar_panel.hpp"
#include "wml_exception.hpp"

namespace gui2 {

namespace implementation {

tbuilder_scrollbar_panel::tbuilder_scrollbar_panel(const config& cfg)
	: tbuilder_control(cfg)
	, vertical_scrollbar_mode(
			get_scrollbar_mode(cfg["vertical_scrollbar_mode"]))
	, horizontal_scrollbar_mode(
			get_scrollbar_mode(cfg["horizontal_scrollbar_mode"]))
	, grid(NULL)
{
	const config &definition = cfg.child("definition");

	VALIDATE(definition, _("No list defined."));
	grid = new tbuilder_grid(definition);
	assert(grid);
}

twidget* tbuilder_scrollbar_panel::build() const
{
	tscrollbar_panel *widget = new tscrollbar_panel();

	init_control(widget);

	widget->set_vertical_scrollbar_mode(vertical_scrollbar_mode);
	widget->set_horizontal_scrollbar_mode(horizontal_scrollbar_mode);

	DBG_GUI_G << "Window builder: placed scrollbar_panel '"
			<< id << "' with defintion '"
			<< definition << "'.\n";

	boost::intrusive_ptr<
			const tscrollbar_panel_definition::tresolution> conf =
				boost::dynamic_pointer_cast
					<const tscrollbar_panel_definition::tresolution>
						(widget->config());
	assert(conf);


	widget->init_grid(conf->grid);
	widget->finalize_setup();

	/*** Fill the content grid. ***/
	tgrid* content_grid = widget->content_grid();
	assert(content_grid);

	const unsigned rows = grid->rows;
	const unsigned cols = grid->cols;

	content_grid->set_rows_cols(rows, cols);

	for(unsigned x = 0; x < rows; ++x) {
		content_grid->set_row_grow_factor(x, grid->row_grow_factor[x]);
		for(unsigned y = 0; y < cols; ++y) {

			if(x == 0) {
				content_grid->set_col_grow_factor(y
						, grid->col_grow_factor[y]);
			}

			twidget* widget = grid->widgets[x * cols + y]->build();
			content_grid->set_child(widget
					, x
					, y
					, grid->flags[x * cols + y]
					, grid->border_size[x * cols + y]);
		}
	}

	return widget;
}

} // namespace implementation

} // namespace gui2

/*WIKI
 * @page = GUIWidgetInstanceWML
 * @order = 2_scrollbar_panel
 *
 * == Scrollbar panel ==
 *
 * Instance of a scrollbar_panel.
 *
 * List with the scrollbar_panel specific variables:
 * @start_table = config
 *     vertical_scrollbar_mode (scrollbar_mode = auto | initial_auto)
 *                                     Determines whether or not to show the
 *                                     scrollbar. The default of initial_auto
 *                                     is used when --new-widgets is used.
 *                                     In the future the default will be
 *                                     auto.
 *     horizontal_scrollbar_mode (scrollbar_mode = auto | initial_auto)
 *                                     Determines whether or not to show the
 *                                     scrollbar. The default of initial_auto
 *                                     is used when --new-widgets is used.
 *                                     In the future the default will be
 *                                     initial_auto.
 *
 *     definition (section)            This defines how a scrollbar_panel item
 *                                     looks. It must contain the grid
 *                                     definition for 1 row of the list.
 *
 * @end_table
 */

