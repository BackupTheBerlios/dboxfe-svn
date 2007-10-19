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
#ifndef DBOXFEGDB_TEMPLATE_H
#define DBOXFEGDB_TEMPLATE_H

#include "ui_dboxfegdb_template.h"
#include "dboxfegdb_sql.h"

#include <QtCore>
#include <QtGui>

class GameTemplateDialog : public QDialog, public Ui::GameTemplateDialog
{
	public:
		GameTemplateDialog( QDialog *parent, Qt::WFlags flags = 0 );
		~GameTemplateDialog();

	private slots:
		void comboBoxTemplateCurrentIndexChanged( const QString & );
		void cbxSerialIndexChanged( int );
		void cbxKeyboardLayoutIndexChanged( int );

		void loadTemplate( const QString &templateName );
		void newTemplate();
		void saveTemplate();
		void deleteTemplate();

		void cancel();

		void language();
		void serialAdd();
		void serialRemove();


	private:
		QMap< QString, QMap< QString, QVariant > > settings;
		QMap< QString, QVariant > subSettings;

		QMap< QString, QMap< QString, QVariant > > getSettings();		

		GameDatabaseSql *gd_sql;
		QString database, templateName;
		QDialog *object;
};


#endif // DBOXFEGDB_TEMPLATE_H
