/*
*   Copyright (C) 2004/05/06 by Alexander Saal <alex.saal@gmx.de>
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

#ifndef DBOXFE_GAMESETTINGS_H
#define DBOXFE_GAMESETTINGS_H

#include <QtGui>
#include <QtCore>

#include "ui_gamesettings.h"

class DBoxFE_GameSettings : public QWidget
{
        Q_OBJECT

    public:
        DBoxFE_GameSettings( QWidget *parent = 0, Qt::WFlags flags = 0 );
        ~DBoxFE_GameSettings();

        Ui::DBoxFE_GameSettings ui;

    private slots:
        void slotAdd();
        void slotRemove();
        void slotChange();
        void slotPreview();
        void slotSave();
        void slotImage();

    protected:
        void closeEvent( QCloseEvent *e );
};

#endif // DBOXFE_GAMESETTINGS_H
