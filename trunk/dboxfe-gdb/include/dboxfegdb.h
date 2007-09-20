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

#ifndef DBOXFEGDB_H
#define DBOXFEGDB_H

#include "dboxfegdb_sql.h"
#include "dboxfegdb_template.h"
#include "dboxfegdb_xml.h"

#include <QtGui>
#include <QtCore>

#include "ui_dboxfegdb.h"

class GameDatabaseDialog : public QDialog, public Ui::GameDatabaseDialog
{
	Q_OBJECT

	public:
		GameDatabaseDialog( QDialog *parent = 0, Qt::WFlags flags = 0 );
		~GameDatabaseDialog();
		
	private slots:
		void addGame();		
		void updateGame();
		void deleteGame();
		
		void chooseGame();
		void chooseExec();
		
		void save();
		void cancel();

	private:
		GameTemplate *gd_template;
		GameDatabaseSql *gd_sql;
		GameDatabaseXml *gd_xml;

	protected:
		void closeEvent ( QCloseEvent *e );
	
};

#endif // DBOXFEGDB_H