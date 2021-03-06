/*********************************************************************
* Copyright 2009-2012 Alan Buckley
*
* This file is part of PackMan.
*
* PackMan is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PackMan is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PackMan. If not, see <http://www.gnu.org/licenses/>.
*
*****************************************************************************/
/*
 * AppSaveAs.cc
 *
 *  Created on: 29-Jul-2009
 *      Author: alanb
 */

#include "AppSaveAs.h"
#include "AppsWindow.h"
#include "CreateStub.h"

#include "tbx/objectdelete.h"
#include "tbx/hourglass.h"
#include "tbx/messagewindow.h"
#include "tbx/fileraction.h"
#include "tbx/stringutils.h"

#include <stdexcept>


/**
 * Set up listeners to set up and do the save
 */
AppSaveAs::AppSaveAs(tbx::Object obj) : _saveas(obj)
{
	_saveas.add_about_to_be_shown_listener(this);
	_saveas.set_save_to_file_handler(this);
}

AppSaveAs::~AppSaveAs()
{
}

/**
 * Setup dialog for show
 */
void AppSaveAs::about_to_be_shown(tbx::AboutToBeShownEvent &event)
{
	AppsWindow *apps_window = AppsWindow::from_window(event.id_block().ancestor_object());
	int id = event.id_block().parent_component().id();
	_save_type = SaveType(id - 1);

	switch(_save_type)
	{
	case STUB: _saveas.title("Create Stub"); break;
	case LINK: _saveas.title("Create link"); break;
	case COPY: _saveas.title("Copy application"); break;
	}

	// Menu item id specifies type of save
	_source_path = apps_window->selected_app_path();
	_saveas.file_name(_source_path.leaf_name());
}

/**
 * Do actual save
 */
void AppSaveAs::saveas_save_to_file(tbx::SaveAs saveas, bool selection, std::string filename)
{
	tbx::Hourglass hg;

	switch(_save_type)
	{
	case COPY: // Copy file
		try
		{
			tbx::Path target(filename);
			if (target.leaf_name() != _source_path.leaf_name())
			{
				// Non multi-tasking copy need if leaf name changes
				_source_path.copy(filename, tbx::Path::COPY_RECURSE);
			} else
			{
				// Use FilerAction to get a multi-tasking copy
				tbx::FilerAction fa(_source_path);
				fa.copy(target.parent(), tbx::FilerAction::VERBOSE);
			}
		} catch(std::runtime_error &e)
		{
			std::string msg("Unable to start filer copy\n");
			msg += e.what();
			tbx::show_message(msg, "PackMan", "warning");
		}
		break;

	case STUB: // Create an application stub
		create_application_stub(_source_path, filename);
		break;

	case LINK: // Create a link
		create_application_link(_source_path, filename);
		break;
	}

	_saveas.file_save_completed(true, filename);
}
