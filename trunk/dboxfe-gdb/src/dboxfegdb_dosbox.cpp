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
#include "dboxfegdb_dosbox.h"
#include "dboxfegdb_sql.h"

#include <XMLPreferences.h>

#include <QtGui>
#include <QtCore>

GameDosBoxDialog::GameDosBoxDialog( QDialog *parent, Qt::WFlags flags ) : QDialog( parent, flags )
{
	setupUi( this );

	gd_sql = new GameDatabaseSql( this );

	XMLPreferences xmlPreferences( "DBoxFE - GDB", "Alexander Saal" );
	xmlPreferences.load( QDir::homePath() + "/.dboxfe-gdb/dboxfegdb.xml" );

	database = xmlPreferences.getString( "Database", "DatabaseFile" );	

	gd_sql->createConnection( database );

	connect( btnAccept, SIGNAL ( clicked() ), this, SLOT ( select() ) );
	connect( btnCancel, SIGNAL ( clicked() ), this, SLOT ( cancel() ) );

	connect( lineEditSearch, SIGNAL( textChanged( const QString & ) ), this, SLOT( lineEditSearchTextChanged( const QString & ) ) );
	connect( comboBoxDosboxVersion, SIGNAL ( currentIndexChanged( const QString & ) ), this, SLOT ( comboBoxDosboxVersionCurrentIndexChanged( const QString & ) ) );
	connect( treeWidgetDosboxGames, SIGNAL ( itemClicked( QTreeWidgetItem *, int ) ), this, SLOT ( treeWidgetDosboxGamesItemClicked( QTreeWidgetItem *, int ) ) );

	QDesktopWidget *desktop = qApp->desktop();
	const QRect rect = desktop->availableGeometry ( desktop->primaryScreen() );
	int left = ( rect.width() - width() ) / 2;
	int top = ( rect.height() - height() ) / 2;
	setGeometry ( left, top, width(), height() );

	getDosboxVersion();
}

GameDosBoxDialog::~GameDosBoxDialog()
{}

void GameDosBoxDialog::comboBoxDosboxVersionCurrentIndexChanged( const QString &item )
{
	if( !item.isNull() || !item.isEmpty() )
		gd_sql->selectDosBoxGames( item, treeWidgetDosboxGames );

	comboBoxSearch->clear();

	if( treeWidgetDosboxGames->columnCount() >= 1 )
	{
		for( int i = 0; i < treeWidgetDosboxGames->columnCount(); i++ )
		{
			comboBoxSearch->addItem( treeWidgetDosboxGames->headerItem()->text( i ) );
		}

		if( comboBoxSearch->count() >= 0 )
			comboBoxSearch->setCurrentIndex( 0 );
		else
			comboBoxSearch->setCurrentIndex( -1 );
	}

}

void GameDosBoxDialog::treeWidgetDosboxGamesItemClicked( QTreeWidgetItem *item, int col )
{
	treeWidgetDosboxGames->setSelectionMode( QAbstractItemView::SingleSelection );

	if( col == 0 )
	{
		for( int a = 0; a < treeWidgetDosboxGames->topLevelItemCount(); a++ )
		{
			qApp->processEvents();
			treeWidgetDosboxGames->topLevelItem( a )->setSelected( false );
		}

		lineEditGames->setText( item->text( col ) );
	}
}

void GameDosBoxDialog::lineEditSearchTextChanged( const QString &txt )
{
	treeWidgetDosboxGames->setSelectionMode( QAbstractItemView::MultiSelection );

	if( comboBoxSearch->currentIndex() <= -1 )
	{
		QMessageBox::information( this, "Gamedatabase", tr("Please select a column for search.") );
		return;
	}

	if( txt.isNull() || txt.isEmpty() )
		return;

	for( int a = 0; a < treeWidgetDosboxGames->topLevelItemCount(); a++ )
	{
		qApp->processEvents();
		treeWidgetDosboxGames->topLevelItem( a )->setSelected( false );
	}

	QList<QTreeWidgetItem *> search( treeWidgetDosboxGames->findItems( txt, Qt::MatchCaseSensitive | Qt::MatchContains, comboBoxSearch->currentIndex() ) );
	if( !search.isEmpty() && !(search.size() <= 0) )
	{
		for( int i = 0; i < search.size(); i++ )
		{
			QTreeWidgetItem *item = search.value( i );
			item->setSelected( true );
		}
	}		
}

void GameDosBoxDialog::getDosboxVersion()
{
	comboBoxDosboxVersion->clear();
	comboBoxDosboxVersion->addItem( "" );

	dosboxVersionList = gd_sql->selectDosBoxVersion();
	if( dosboxVersionList.isEmpty() || dosboxVersionList.size() <= 0 )
	{
		QMessageBox::critical( this, tr( "Gamedatabase" ), tr( "No dosbox version in the database." ) );
		return;
	}

	for( int i = 0; i < dosboxVersionList.size(); i++ )
	{
		comboBoxDosboxVersion->addItem( dosboxVersionList.value( i ) );
	}
}

void GameDosBoxDialog::select()
{
	QDialog::accept();
}

void GameDosBoxDialog::cancel()
{
	QDialog::reject();
}
