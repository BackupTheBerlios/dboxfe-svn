/***************************************************************************
 *   Copyright (C) 2006 by Alexander Saal                                  *
 *   alex.saal@gmx.de                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "dboxfe.h"
#include "dboxfe_base.h"
#include "XMLPreferences.h"

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

DB_BASE::DB_BASE()
{}

void DB_BASE::readConf( const QString &dbconf, const DBoxFE &dbfe )
{
    QSettings settGP( dbconf, QSettings::IniFormat );
    QStringList sList;

}

void DB_BASE::saveConf( const QString &dbcon, const DBoxFE &dbfe )
{
    QSettings settGP( dbcon, QSettings::IniFormat );

    settGP.setValue( "", "" );

}

void DB_BASE::findGames( const QString &dirName, QListWidget* qlw )
{
    QDir dir( dirName );

    m_file = QDir::homePath();
    m_file.append( "/.dboxfe/profile/games.xml" );

    XMLPreferences games( "DBoxFE", "Alexander Saal" );
    games.setVersion( "v0.1.0" );
    games.load( m_file );

    gameList = games.getStringList( "Games", "Name");

    const QFileInfoList fil = dir.entryInfoList(QDir::Files | QDir::Dirs, QDir::Name);
    QListIterator<QFileInfo> it( fil );
    QStringList lst;

    while ( it.hasNext() )
    {
        fi = it.next();

        if ( fi.fileName() == "." || fi.fileName() == ".." )
            ;
        else
        {
            if ( fi.isDir() && fi.isReadable() )
                findGames( fi.absoluteFilePath(), qlw );
            else
            {
                for( int i = 0; i < gameList.size(); ++i )
                {
                    lst = gameList[i].split(";");
                    if( fi.fileName() == lst.value(1))
                        qlw->addItem( lst.value(0) );
                }
            }
        }
    }
}

/*
 * Create game profiles
 */
void createGameProfiles( const QString &file, const QStringList &gamesList )
{
}

void insertGameInToDb( const QString &name, const QString &executable, QTreeWidget* qtw )
{
    qtw->setColumnCount( qtw->columnCount() );
    
    QTreeWidgetItem *item = new QTreeWidgetItem( qtw );
    item->setText( 0, executable );
    item->setText( 1, name );
    delete item;
}

/*
 * Returns current count of games
 */
int removeGameFromDb( QTreeWidgetItem* qtwItem )
{
    delete qtwItem->parent();
    
    return 0;
}

void saveGameDb( const QString &file, const QStringList &gamesList )
{}

void readGameDb( const QString &file, QTreeWidget* qtw )
{}
