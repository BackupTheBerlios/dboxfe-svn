@echo off
cls

echo ***************************************************************************
echo *   Copyright (C) 2004-2007 by Alexander Saal                             *
echo *   alex.saal@gmx.de                                                      *
echo *                                                                         *
echo *   This program is free software; you can redistribute it and/or modify  *
echo *   it under the terms of the GNU General Public License as published by  *
echo *   the Free Software Foundation; either version 2 of the License, or     *
echo *   (at your option) any later version.                                   *
echo *                                                                         *
echo *   This program is distributed in the hope that it will be useful,       *
echo *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
echo *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
echo *   GNU General Public License for more details.                          *
echo *                                                                         *
echo *   You should have received a copy of the GNU General Public License     *
echo *   along with this program; if not, write to the                         *
echo *   Free Software Foundation, Inc.,                                       *
echo *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
echo ***************************************************************************
echo.

if "%QTDIR%" == "" (
	echo Please set %%QTDIR%% to the Qt source directory.
	goto ERROR
)
) else (
	echo Create Makefile 'dboxfe' ...
	qmake dboxfe.pro >nul
	
	if not exist Makefile (
		echo.
		echo Makefile for 'dboxfe' not found.
		goto ERROR
	)

	echo Create Makefile 'dboxfetray' ...
	cd dboxfetray && qmake dboxfe.pro >nul
	cd ..
	
	if not exist Makefile (
		echo.
		echo Makefile for 'dboxfetray' not found.
		goto ERROR
	)

	goto FINISH	
)

:ERROR
echo.
echo An error occured. Configuration aborted.
echo.

goto LEAVE

:FINISH
echo.
echo Good - your configure finished.
echo.
echo If you use MinGW than use: mingw32-make
echo If you use MSVC++ 2003/2005 than use: nmake
echo.

:LEAVE
