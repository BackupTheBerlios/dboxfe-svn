/*
*   Copyright (C) 2007 by Alexander Saal <alex.saal@gmx.de>
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

#ifndef DBOXFEGDB_TEMPLATE_NEW_H
#define DBOXFEGDB_TEMPLATE_NEW_H

#include "ui_dboxfegdb_template_new.h"

#include <QtCore>
#include <QtGui>

class GameTemplateNewDialog : public QDialog, public Ui::GameTemplateDialogNew
{
	Q_OBJECT

	public:
		GameTemplateNewDialog( QDialog *parent, Qt::WFlags flags = 0 );
		~GameTemplateNewDialog();

	private slots:
		void ok();
		void cancel();

	private:
		QDialog *object;
};


#endif // DBOXFEGDB_TEMPLATE_NEW_H