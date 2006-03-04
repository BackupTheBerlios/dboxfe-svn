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

#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include <QtGui/QListWidgetItem>

DB_BASE::DB_BASE()
{}

// read gameprofile ini
void DB_BASE::readGPIni( const QString &gpIni, QListWidget* lw )
{
  QStringList sList;

  QSettings settGP( gpIni, QSettings::IniFormat );

  int size = settGP.beginReadArray("Profile");

  for (int i = 0; i < size; ++i)
  {
    settGP.setArrayIndex(i);
    sList.append( settGP.value("Name").toString() );
  }

  settGP.endArray();
  lw->clear();
  lw->addItems( sList );
}

// save gameprofile ini
void DB_BASE::saveGPIni( const QString &gpIni, QListWidget* lw  )
{
  QSettings settGP( gpIni, QSettings::IniFormat );
  QStringList sList;

  for( int a = 0; a < lw->count(); ++a )
  {
    sList.append( lw->item( a )->text() );
  }

  settGP.beginWriteArray( "Profile" );

  for( int x = 0; x < sList.count(); ++x )
  {
    settGP.setArrayIndex( x );
    settGP.setValue( "Name", sList.value( x ) );
  }

  settGP.endArray();
  settGP.sync();
}

void DB_BASE::readDBConf( const QString &dbconf )
{
}

void DB_BASE::saveDBConf( const QString &dbconf )
{
}

// start dosbox with parameters and return output in QStringList ...
QStringList DB_BASE::start( const QString& bin, const QString &param, const QString &conf )
{
  QByteArray m_result;
  dBox = new QProcess();

  m_param.append( param );
  m_param.append( conf );

  dBox->start( bin, m_param );
  
  while( dBox->waitForReadyRead() )
      m_result += dBox->readAll();
  
  m_out.append( m_result );
  m_param.clear();
  
  return m_out;
}
