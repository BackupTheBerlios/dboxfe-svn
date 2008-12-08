/***************************************************************************
 *   Copyright (C) 2004-2008 by Alexander Saal                             *
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

#include <dboxfe.h>
#include <profilesettings.h>

#include <QtGui>
#include <QtCore>

namespace asaal {

  ProfileSettings::ProfileSettings( QWidget *parent, Qt::WFlags flags ) : QDialog( parent, flags ) {

    setupUi( this );

    connect( btnSave, SIGNAL( clicked() ), this, SLOT( saveConfiguration() ) );
    connect( btnDefault, SIGNAL( clicked() ), this, SLOT( setDefaultConfiguration() ) );
    connect( btnAbort, SIGNAL( clicked() ), this, SLOT( closeWidget() ) );
  }

  ProfileSettings::~ProfileSettings() {}

  void ProfileSettings::closeEvent( QCloseEvent *e ) {
  }

  void ProfileSettings::comboBoxSerialIndexChanged( int index ) {
  }

  void ProfileSettings::comboBoxAutoexecIndexChanged( int index ) {
  }

  void ProfileSettings::comboBoxAutoexecImageFormatIndexChanged( int index ) {
  }

  void ProfileSettings::comboBoxKeyboardLayoutIndexChanged( int index ) {
  }

  void ProfileSettings::autoexecDrive() {
  }

  void ProfileSettings::autoexecUpdate() {
  }

  void ProfileSettings::autoexecRemove() {
  }

  void ProfileSettings::autoexecAdd() {
  }

  void ProfileSettings::serialRemove() {
  }

  void ProfileSettings::serialAdd() {
  }

  void ProfileSettings::openLanguageFile() {
  }

  void ProfileSettings::saveConfiguration() {

    if ( !profileConfiguration.isEmpty() ) {

      DBoxFE::configBaseInstance()->writeConfiguration( profFile, profileConfiguration );
    }

    accept();
  }

  void ProfileSettings::setDefaultConfiguration() {

    profileConfiguration.clear();
    profileConfiguration = DBoxFE::configBaseInstance()->readConfiguration( QString::fromUtf8( ":/default/default.conf" ) );

    if ( !profileConfiguration.isEmpty() ) {

      // intial default settings

    }
  }

  void ProfileSettings::loadConfiguration() {

    profileConfiguration.clear();
    profileConfiguration = DBoxFE::configBaseInstance()->readConfiguration( profFile );

    if ( profileConfiguration.isEmpty() ) {

      profileConfiguration = DBoxFE::configBaseInstance()->readConfiguration( QString::fromUtf8( ":/default/default.conf" ) );
    }

    // initial settings
    

  }

  void ProfileSettings::closeWidget() {

    profileConfiguration.clear();
    reject();
  }
}
