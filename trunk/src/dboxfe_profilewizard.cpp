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

#include "dboxfe.h"
#include "dboxfe_base.h"
#include "dboxfe_profilewizard.h"

#include <QtGui>
#include <QtCore>
#include <QtNetwork>

DBoxFE_ProfileWizard::DBoxFE_ProfileWizard ( QDialog *parent, Qt::WFlags flags )
		: QDialog ( parent, flags )
{

	// setup grafical user interface (gui)
	setupUi ( this );

	page = 0;

	// for download game database file
	m_http = new QHttp ( this );
	connect ( m_http, SIGNAL ( requestFinished ( int, bool ) ), this, SLOT ( httpRequestFinished ( int, bool ) ) );
	connect ( m_http, SIGNAL ( responseHeaderReceived ( const QHttpResponseHeader & ) ), this, SLOT ( readResponseHeader ( const QHttpResponseHeader & ) ) );

	// connection
	connect ( btnBack, SIGNAL ( clicked() ), this, SLOT ( slotBack() ) );
	connect ( btnNext, SIGNAL ( clicked() ), this, SLOT ( slotNext() ) );
	connect ( btnNext, SIGNAL ( clicked() ), this, SLOT ( slotFinish() ) );

	connect ( btnHelp, SIGNAL ( clicked() ), this, SLOT ( slotHelp() ) );
	connect ( btnAbort, SIGNAL ( clicked() ), this, SLOT ( slotAbort() ) );
	connect ( btnSelectDir, SIGNAL ( clicked() ), this, SLOT ( slotSelectDir() ) );
	connect ( btnSearch, SIGNAL ( clicked() ), this, SLOT ( slotSearch() ) );

	// enable button
	btnNext->setEnabled ( true );

	// center the wiget on desktop screen
	QDesktopWidget *desktop = qApp->desktop();
	const QRect rect = desktop->availableGeometry ( desktop->primaryScreen() );
	int left = ( rect.width() - width() ) / 2;
	int top = ( rect.height() - height() ) / 2;
	setGeometry ( left, top, width(), height() );

	downloadFile();
}

DBoxFE_ProfileWizard::~DBoxFE_ProfileWizard()
{
	delete m_http;
	delete m_file;
}

void DBoxFE_ProfileWizard::slotFinish()
{
	DB_BASE gpBase;

	m_gp_file = QDir::homePath();
	m_gp_file.append ( "/.dboxfe/profile/profile.xml" );

	gpList.clear();

	if ( btnNext->text() == tr ( "&Finish" ) )
	{
		lblSaveCfg->setEnabled ( true );

		for ( int a = 0; a < lwGames->topLevelItemCount(); ++a )
		{
			QTreeWidgetItem *item = lwGames->topLevelItem ( a );
			gpList.append ( item->text ( 0 ) );
		}

		lblCreateGP->setEnabled ( true );

		gpBase.createGameProfiles ( m_gp_file, gpList, dbfe, this );

		lblFinish->setEnabled ( true );

		QMessageBox::information ( this, dbfe->winTitle(), tr ( "Please make sure you set the autoexec option for every profile right." ) );
		QDialog::accept();
	}
	else
	{
		btnNext->setText ( tr ( "&Next" ) );
		return ;
	}
}

void DBoxFE_ProfileWizard::slotBack()
{

	if ( page == 1 )
		btnBack->setEnabled ( false );

	if ( page == 0 || page == 1 )
	{
		btnNext->setText ( "&Next" );
	}

	sWidgetGameWizard->setCurrentIndex ( --page );
}

void DBoxFE_ProfileWizard::slotNext()
{

	if ( page == 1 )
	{
		btnNext->setText ( tr ( "&Finish" ) );
	}
	else
	{
		btnNext->setText ( tr ( "&Next" ) );
	}

	btnBack->setEnabled ( true );
	sWidgetGameWizard->setCurrentIndex ( ++page );

	if ( page > 2 )
		page = 2;
}

void DBoxFE_ProfileWizard::slotHelp()
{
	qDebug() << tr ( "Not implemented yet!" );
}

void DBoxFE_ProfileWizard::slotAbort()
{
	QDialog::reject();
}

void DBoxFE_ProfileWizard::slotSelectDir()
{
	QString strDir = QFileDialog::getExistingDirectory ( this, tr ( "Open search directory" ), QDir::homePath() );
	if ( strDir.isEmpty() )
		return ;

	LEDirectory->setText ( strDir );
}

void DBoxFE_ProfileWizard::slotSearch()
{
	DB_BASE base;

	QString path = LEDirectory->text();

	if ( path.isEmpty() )
		return ;

	lwGames->clear();
	base.findGames ( path, lwGames );
}


void DBoxFE_ProfileWizard::httpRequestFinished ( int requestId, bool error )
{
	if ( httpRequestAborted )
	{
		if ( m_file )
		{
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

	if ( error )
	{
		m_file->remove();
		QMessageBox::information ( this, dbfe->winTitle(), tr ( "Download failed: %1." ).arg ( m_http->errorString() ) );
	}

	delete m_file;
	m_file = 0;
}

void DBoxFE_ProfileWizard::readResponseHeader ( const QHttpResponseHeader &responseHeader )
{
	if ( responseHeader.statusCode() != 200 )
	{
		QMessageBox::information ( this, dbfe->winTitle(), tr ( "Download failed: %1." ).arg ( responseHeader.reasonPhrase() ) );
		httpRequestAborted = true;
		m_http->abort();
		return ;
	}
}

void DBoxFE_ProfileWizard::downloadFile()
{
	QUrl url ( "http://chmaster.freeforge.net/update/dboxfe/games.xml" );
	QFileInfo fileInfo ( url.path() );
	QString fileName;
	fileName = QDir::homePath();
	fileName.append ( "/.dboxfe/profile/" + fileInfo.fileName() );

	if ( QFile::exists ( fileName ) )
	{
		QFile::remove
			( fileName );
	}

	m_file = new QFile ( fileName );

	if ( !m_file->open ( QIODevice::WriteOnly ) )
	{
		QMessageBox::information ( this, dbfe->winTitle(), tr ( "Unable to update the file %1: %2." ).arg ( fileName ).arg ( m_file->errorString() ) );
		delete m_file;
		m_file = 0;
		return ;
	}

	m_http->setHost ( url.host(), url.port() != -1 ? url.port() : 80 );
	if ( !url.userName().isEmpty() )
		m_http->setUser ( url.userName(), url.password() );

	httpRequestAborted = false;
	httpGetId = m_http->get ( url.path(), m_file );
}
