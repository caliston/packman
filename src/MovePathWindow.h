/*********************************************************************
* Copyright 2012 Alan Buckley
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
 * MovePathWindow.h
 *
 *  Created on: 19 Aprn 2012
 *      Author: alanb
 */

#ifndef MOVEPATHWINDOW_H_
#define MOVEPATHWINDOW_H_

#include "tbx/command.h"
#include "tbx/window.h"
#include "tbx/displayfield.h"
#include "tbx/slider.h"
#include "tbx/actionbutton.h"
#include "MovePath.h"

class MovePathWindow : public tbx::Command
{
	tbx::Window _window;
	tbx::DisplayField _status_text;
	tbx::Slider _progress;
	tbx::ActionButton _cancel;
	tbx::CommandMethod<MovePathWindow> _do_cancel;
	tbx::ActionButton _faster;
	tbx::CommandMethod<MovePathWindow> _do_faster;

	MovePath _move_path;
	MovePath::State _last_state;

	bool _can_cancel;
	bool _run_faster;

public:
	MovePathWindow(const std::string &logical_path, const std::string &to_path);
	virtual void execute();

private:
	void cancel();
	void close();
	void show_warning();
	void show_error();
	void faster();

	std::string warning_text();
	std::string error_text();
};

#endif /* MOVEPATHWINDOW_H_ */
