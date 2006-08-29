/*
*   Copyright (C) 2004 - 06 by Alexander Saal <alex.saal@gmx.de>
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

#include "dboxfe.h"
#include "dboxfe_base.h"
#include "dboxfe_gamesettings.h"

// Qt 4 Header
#include <QtCore>
#include <QtGui>
#include <QtNetwork>

DBoxFE_GameFile::DBoxFE_GameFile( QWidget *parent, Qt::WFlags flags )
        : QWidget( parent, flags )
{
    ui.setupUi( this );

    m_http = new QHttp( this );
    connect( m_http, SIGNAL( dataReadProgress( int, int  ) ), this, SLOT( httpDataReadProgress( int, int ) ) );
    connect( m_http, SIGNAL( requestFinished( int, bool ) ), this, SLOT( httpRequestFinished( int, bool ) ) );
    connect( m_http, SIGNAL( responseHeaderReceived( const QHttpResponseHeader & ) ), this, SLOT( readResponseHeader( const QHttpResponseHeader & ) ) );

    // center the wiget on desktop screen
    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );

}

DBoxFE_GameFile::~DBoxFE_GameFile()
{
    delete m_http;
    delete m_file;
}

void DBoxFE_GameFile::closeEvent( QCloseEvent *e )
{
}

void DBoxFE_GameFile::loadGameFile( const QString &urlPath )
{
    QUrl url( urlPath );
    QFileInfo fileInfo( url.path() );
    QString fileName;
    fileName = QDir::homePath();
    fileName.append( "/.dboxfe/profile/" + fileInfo.fileName() );

    if ( QFile::exists( fileName ) ) {
        QFile::remove( fileName );
    }

    m_file = new QFile( fileName );

    if ( !m_file->open( QIODevice::WriteOnly ) ) {
        QMessageBox::information( this, dbfe->winTitle(), tr( "Unable to update the file %1: %2." ).arg( fileName ).arg( m_file->errorString() ) );
        delete m_file;
        m_file = 0;
        return ;
    }

    m_http->setHost( url.host(), url.port() != -1 ? url.port() : 80 );
    if ( !url.userName().isEmpty() )
        m_http->setUser( url.userName(), url.password() );

    httpRequestAborted = false;
    httpGetId = m_http->get( url.path(), m_file );
}

void DBoxFE_GameFile::parseGameFile( const QString &file, DBoxFE_GameSettings *dbfe_gs )
{
 		 DB_BASE db_base;
 		 ui.pBarParseStatus->setValue( 0 );
 		 db_base.readGameDb( file, ui.pBarParseStatus, dbfe_gs->ui_gs.twGameSettings );
}

void DBoxFE_GameFile::httpDataReadProgress( int done, int total  )
{
 		 ui.pBarParseStatus->setMaximum( total );
 		 ui.pBarParseStatus->setValue( done );
 		 
 		 if( ui.pBarParseStatus->value() == ui.pBarParseStatus->maximum() ) {
		 		 ui.pBarParseStatus->setValue( 0 );
 		 }
}
				
void DBoxFE_GameFile::httpRequestFinished( int requestId, bool error )
{
    if ( httpRequestAborted ) {
        if ( m_file ) {
            m_file->close();
            m_file->remove();
            delete m_file;
            m_file = 0;
        }

        return ;
    }

    if ( requestId != httpGetId )
        return ;

    m_file->flush();
    m_file->close();

    if ( error ) {
        m_file->remove();
        QMessageBox::information( this, dbfe->winTitle(), tr( "Download failed: %1." ).arg( m_http->errorString() ) );
    }

    delete m_file;
    m_file = 0;
}

void DBoxFE_GameFile::readResponseHeader( const QHttpResponseHeader &responseHeader )
{
    if ( responseHeader.statusCode() != 200 ) {
        QMessageBox::information( this, dbfe->winTitle(), tr( "Download failed: %1." ).arg( responseHeader.reasonPhrase() ) );
        httpRequestAborted = true;
        m_http->abort();
        return ;
    }
}
