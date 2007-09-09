/*
*   Copyright (C) 2004 - 2007 by Alexander Saal <alex.saal@gmx.de>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef DBOXFE_GAMES_H
#define DBOXFE_GAMES_H

#include "ui_games.h"

#include <QtGui>

class DBoxFE_Game : public QDialog, public Ui::DBoxFE_Game
{
		Q_OBJECT

	public:
		DBoxFE_Game ( QDialog *parent = 0, Qt::WFlags flags = 0 );
		~DBoxFE_Game();
};

#endif // DBOXFE_GAMES_H
