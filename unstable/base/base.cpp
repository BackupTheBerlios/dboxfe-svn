/***************************************************************************
 *   Copyright (C) 2008 by Alexander Saal                                  *
 *   alex.saal@gmx.de                                                      *
 *                                                                         *
 *   File: ${filename}.${extension}                                        *
 *   Desc: ${description}                                                  *
 *                                                                         *
 *   This file is part of DBoxFE - DOSBox Front End                        *
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

#include <base.h>
#include <xmlpreferences.h>

#include <QtCore>

namespace asaal {

  ConfigBase::ConfigBase( QObject *parent ) : QObject( parent ) {

    m_Parent = parent;
  }

  ConfigBase::~ConfigBase() {
  }

  Configuration ConfigBase::readConfiguration( const QString &profile ) {

    clearSettings();
    QFile configFile( profile );

    if ( !configFile.exists() ) {
      m_Configuration.clear();
      return m_Configuration;
    }

    QSettings readConf( profile, QSettings::IniFormat );

    return m_Configuration;
  }

  Configuration ConfigBase::convertConfiguration( const QString &profile ) {

    clearSettings();
    QFile configFile( profile );

    if ( !configFile.exists() ) {
      m_Configuration.clear();
      return m_Configuration;
    }

    QSettings readConf( profile, QSettings::IniFormat );

    return m_Configuration;
  }

  void ConfigBase::writeConfiguration( const QString &profile, const Configuration &config ) {

    if ( config.isEmpty() ) {
      return;
    }
  }

}