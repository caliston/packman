/*********************************************************************
* Copyright 2009 Alan Buckley
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
 * InstallCommand.h
 *
 *  Created on: 25-Mar-2009
 *      Author: alanb
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "tbx/command.h"

class MainWindow;
class IRWindow;

/**
 * Command to install current item
 */
class InstallCommand : public tbx::Command
{
private:
	MainWindow *_main;
	IRWindow *_install;
public:
	enum {COMMAND_ID = 1}; // ID in resources

	InstallCommand(MainWindow *main) : _main(main), _install(0) {}
	virtual ~InstallCommand() {}

	virtual void execute();
};

/**
 * Command to remove current item
 */
class RemoveCommand : public tbx::Command
{
private:
	MainWindow *_main;
	IRWindow *_remove;
public:
	enum {COMMAND_ID = 2}; // ID in resources

	RemoveCommand(MainWindow *main) : _main(main), _remove(0) {}
	virtual ~RemoveCommand() {}

	virtual void execute();
};

/**
 * Command to commit the current install or remove
 */
class CommitCommand : public tbx::Command
{
public:
	virtual void execute();
};

/**
 * Command to update the list of packages
 */
class UpdateListCommand : public tbx::Command
{
public:
	enum {COMMAND_ID = 3}; // ID in resources

	virtual void execute();
};

#endif /* COMMANDS_H_ */
