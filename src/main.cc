/*********************************************************************
* Copyright 2009-2011 Alan Buckley
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
 * main.cc
 *
 *  Created on: 18-Mar-2009
 *      Author: alanb
 */

#include "tbx/application.h"
#include "tbx/iconbar.h"
#include "tbx/command.h"
#include "tbx/reporterror.h"
#include "tbx/autocreate.h"
#include "tbx/matchlifetime.h"
#include "tbx/showhelp.h"

#include "Packages.h"
#include "MainWindow.h"
#include "PackageLoader.h"
#include "Commands.h"
#include "MainMenu.h"
#include "PackageMenu.h"
#include "InfoWindow.h"
#include "AppsWindow.h"
#include "AppsMenu.h"
#include "AppSaveAs.h"
#include "AppMoveTo.h"
#include "CopyrightWindow.h"
#include "SearchWindow.h"
#include "InstallWindow.h"
#include "CacheWindow.h"

/**
 * Show the main packman window if it's not already shown
 */
class ShowMainWindowCommand : public tbx::Command
{
public:
	virtual void execute()
	{
		if (Packages::instance()->ensure_package_base())
		{
			new MainWindow();
		} else
		{
			new InstallWindow();
		}
	}
};

/**
 * Show the main window with the "Installed" filter selected
 */
class ShowInstalledCommand : public tbx::Command
{
public:
	virtual void execute()
	{
		if (Packages::instance()->ensure_package_base())
		{
			MainWindow *main = new MainWindow();
			main->set_filter("Installed");
		} else
		{
			new InstallWindow();
		}
	}
};

/**
 * Entry point for program
 */
int main(int argc, char *argv[])
{
	tbx::Application packman("<PackMan$Dir>");
	tbx::Iconbar iconbar("IconbarIcon");
	tbx::ShowHelp show_help;

	// Attach auto created objects to C++ classes to handle them
	packman.set_autocreate_listener("MainMenu", new tbx::AutoCreateClass<MainMenu>() );
	packman.set_autocreate_listener("PackageMenu", new tbx::AutoCreateClass<PackageMenu>() );
	packman.set_autocreate_listener("Info", new tbx::AutoCreateClass<InfoWindow>() );
	packman.set_autocreate_listener("Cache", new tbx::AutoCreateClassOnce<CacheWindow>());

	// Commands that can be run from anywhere
	packman.add_command(HELP_COMMAND_ID, &show_help);
	packman.add_command(UpgradeAllCommand::COMMAND_ID, new UpgradeAllCommand());
	packman.add_command(UpdateListCommand::COMMAND_ID, new UpdateListCommand());

	// Windows that probably won't be used as often so create on demand
	tbx::MatchLifetime<AppsWindow> mlt_apps("Apps");
	tbx::MatchLifetime<AppsMenu> mlt_apps_menu("AppsMenu");
	tbx::MatchLifetime<AppSaveAs> mlt_app_save_as("AppSaveAs");
	tbx::MatchLifetime<AppMoveTo> mlt_app_move_to("AppMoveTo");
	tbx::MatchLifetime<CopyrightWindow> mlt_copyright("Copyright");
	tbx::MatchLifetime<SearchWindow> mlt_search("Search");

	iconbar.add_select_command(new ShowMainWindowCommand());
	iconbar.add_adjust_command(new ShowInstalledCommand());
	iconbar.add_loader(new PackageLoader());
	iconbar.menu().add_command(ShowSourcesWindowCommand::COMMAND_ID, new ShowSourcesWindowCommand());
	iconbar.menu().add_command(ShowPathsWindowCommand::COMMAND_ID, new ShowPathsWindowCommand());
	iconbar.menu().add_command(ShowBackupWindowCommand::COMMAND_ID, new ShowBackupWindowCommand());

	iconbar.show();
	packman.run();

	return 0;
}
