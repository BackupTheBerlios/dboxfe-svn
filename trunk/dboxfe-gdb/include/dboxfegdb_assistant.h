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

#ifndef DBOXFEGDB_ASSISTANT_H
#define DBOXFEGDB_ASSISTANT_H

#include "ui_dboxfegdb_assistant.h"

#include "dboxfegdb_sql.h"
#include "dboxfegdb_xml.h"

#include <QtGui>
#include <QtCore>
#include <QtNetwork>


class GameDatabaseAssistant : public QDialog, public Ui::GameDatabaseAssistantDialog
{	
	Q_OBJECT

	public:
		GameDatabaseAssistant( QDialog *parent = 0, Qt::WFlags flags = 0 );
		~GameDatabaseAssistant();

	public slots:
		void next();
		void back();
		void finish();
		void help();

		void generateNewOrUseDatabase();

		void writeXmlSetting( const QString &xml );
		void writeLogFile( const QString &log );

		void importIntoDatabase( const QString &db );		

	private:
		bool downloadDosboxXml( const QString &xml );
		
		GameDatabaseSql *gd_sql;
		GameDatabaseXml *gd_xml;
		
		QHttp *m_http;
		QFile *m_file;
		
		QString fileNameDatabase, fileNameXml;
		QMap< QString, QMap<QString, QString> > dosboxGameList;

		int httpGetId;
		bool httpRequestAborted;
		int page;

	private slots:
		void httpRequestFinished( int requestId, bool error );
		void readResponseHeader( const QHttpResponseHeader &responseHeader );
		void readDataReadProgress( int bytesRead, int totalBytes );
		void done( bool error );

	protected:
		void closeEvent ( QCloseEvent *e );
};

#endif // DBOXFEGDB_ASSISTANT_H
