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

#ifndef DBOXFEGDB_DOSBOX_H
#define DBOXFEGDB_DOSBOX_H

#include "ui_dboxfegdb_dosbox.h"
#include "dboxfegdb_sql.h"

#include <QtGui>
#include <QtCore>


class GameDosBoxDialog : public QDialog, public Ui::DosboxGamesDialog
{
	Q_OBJECT

	public:
		GameDosBoxDialog( QDialog *parent = 0, Qt::WFlags flags = 0 );
		~GameDosBoxDialog();

	private slots:
		void comboBoxDosboxVersionCurrentIndexChanged( const QString & );
		void treeWidgetDosboxGamesItemClicked( QTreeWidgetItem *, int );
		void lineEditSearchTextChanged( const QString & );

		void getDosboxVersion();		

		void select();
		void cancel();

	private:
		GameDatabaseSql *gd_sql;
		QString database;
		QStringList dosboxVersionList;
};

#endif // DBOXFEGDB_H
