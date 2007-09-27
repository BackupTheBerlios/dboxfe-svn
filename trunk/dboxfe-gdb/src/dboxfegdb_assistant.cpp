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

#include "dboxfegdb_assistant.h"

#include "dboxfegdb_sql.h"
#include "dboxfegdb_xml.h"

#include <XMLPreferences.h>

#include <QtGui>
#include <QtCore>
#include <QtNetwork>

GameDatabaseAssistant::GameDatabaseAssistant( QDialog *parent, Qt::WFlags flags ) : QDialog( parent, flags )
{
	setupUi( this );

	gd_sql = new GameDatabaseSql( this );
	gd_xml = new GameDatabaseXml( this );

	page = 0;

	m_http = new QHttp ( this );
	connect ( m_http, SIGNAL( requestFinished( int, bool ) ), this, SLOT( httpRequestFinished( int, bool ) ) );
	connect ( m_http, SIGNAL( responseHeaderReceived( const QHttpResponseHeader & ) ), this, SLOT( readResponseHeader( const QHttpResponseHeader & ) ) );

	connect( btnNext, SIGNAL( clicked() ), this, SLOT( next() ) );
	connect( btnBack, SIGNAL( clicked() ), this, SLOT( back() ) );
	connect( btnFinish, SIGNAL( clicked() ), this, SLOT( finish() ) );
	connect( btnHelp, SIGNAL( clicked() ), this, SLOT( help() ) );

	QDesktopWidget *desktop = qApp->desktop();
	const QRect rect = desktop->availableGeometry ( desktop->primaryScreen() );
	int left = ( rect.width() - width() ) / 2;
	int top = ( rect.height() - height() ) / 2;
	setGeometry ( left, top, width(), height() );
}

GameDatabaseAssistant::~GameDatabaseAssistant()
{
	delete m_http;
	delete m_file;
}

void GameDatabaseAssistant::closeEvent ( QCloseEvent *e )
{}

void GameDatabaseAssistant::next()
{
	btnBack->setEnabled ( true );
	stackedWidgetGameDatabase->setCurrentIndex( ++page );

	if( page >= 3 )
	{
		btnNext->setEnabled( false );
		btnFinish->setEnabled( true );
		page = 3;
	}
}

void GameDatabaseAssistant::back()
{
	if( page == 1 )
		btnBack->setEnabled ( false );

	if( page <= 3 )
	{
		btnNext->setEnabled( true );
		btnFinish->setEnabled( false );
	}

	stackedWidgetGameDatabase->setCurrentIndex ( --page );
}

void GameDatabaseAssistant::finish()
{
	downloadDosboxXml();
	QDialog::accept();
}

void GameDatabaseAssistant::help()
{}

void GameDatabaseAssistant::writeXmlSetting( const QString &xml )
{}

void GameDatabaseAssistant::writeLogFile( const QString &log )
{}

void GameDatabaseAssistant::importIntoDatabase( const QString &db )
{}

bool GameDatabaseAssistant::downloadDosboxXml()
{
	QUrl url ( "http://dosbox.sourceforge.net/game_database.xml" );
	QFileInfo fileInfo ( url.path() );
	QString fileName;
	fileName = QDir::homePath();
	fileName.append( "/.dboxfe-gdb/" + fileInfo.fileName() );

	if( QFile::exists( fileName ) )
		QFile::remove( fileName );

	m_file = new QFile( fileName );

	if ( !m_file->open( QIODevice::WriteOnly ) )
	{
		QMessageBox::information ( this, tr( "Gamedatabase - Assistant" ), tr ( "Unable to update the file %1: %2." ).arg ( fileName ).arg ( m_file->errorString() ) );
		delete m_file;
		m_file = 0;
		return false;
	}

	m_http->setHost ( url.host(), url.port() != -1 ? url.port() : 80 );
	if ( !url.userName().isEmpty() )
		m_http->setUser ( url.userName(), url.password() );

	httpRequestAborted = false;
	httpGetId = m_http->get( url.path(), m_file );
	return true;
}

void GameDatabaseAssistant::httpRequestFinished( int requestId, bool error )
{
	if( httpRequestAborted )
	{
		if ( m_file )
		{
			m_file->close();
			m_file->remove();
			delete m_file;
			m_file = 0;
		}

		return;
	}

	if( requestId != httpGetId )
		return;

	m_file->flush();
	m_file->close();

	if( error )
	{
		m_file->remove();
		QMessageBox::information ( this, tr( "Gamedatabase - Assistant" ), tr ( "Download failed: %1." ).arg ( m_http->errorString() ) );
	}

	delete m_file;
	m_file = 0;
}

void GameDatabaseAssistant::readResponseHeader( const QHttpResponseHeader &responseHeader )
{
	if( responseHeader.statusCode() != 200 )
	{
		QMessageBox::information ( this, tr( "Gamedatabase - Assistant" ), tr ( "Download failed: %1." ).arg ( responseHeader.reasonPhrase() ) );
		httpRequestAborted = true;
		m_http->abort();
		return;
	}
}
