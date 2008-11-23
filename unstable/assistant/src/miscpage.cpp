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

#include <gamewizard.h>
#include <miscpage.h>

#include <QtCore>
#include <QtGui>

namespace asaal {

  MiscPage::MiscPage( QWidget *parent ) : QWizardPage( parent ) {

    setupUi( this );
    setTitle( tr( "Misc. option" ) );
    setSubTitle( tr( "Specify basic information about the misc. for selected game." ) );

    registerField( "autoexec", listWidgetAutoexec );
    registerField( "language", lineEditDosBoxLanguage );

    registerField( "machine", comboBoxDosBoxMachine );
    registerField( "captures", comboBoxDosBoxCapture );
    registerField( "memsize", comboBoxDosBoxMemSize );
    registerField( "xms", checkBoxDosXMS );
    registerField( "ems", checkBoxDosEMS );
    registerField( "umb", checkBoxDosUMB );
    registerField( "keyboardlayout", comboBoxDosKeyboardLayout );
    registerField( "timed", checkBoxJoystickTimed );
    registerField( "autofire", checkBoxJoystickAutofire );
    registerField( "swap34", checkBoxJoystickSwap34 );
    registerField( "buttonwrap", checkBoxJoystickButtonWrap );
    registerField( "joysticktype", comboBoxJoystickType );

  }

  int MiscPage::nextId() const {

    return GameWizard::PAGE_FINSH;
  }

  QVariant MiscPage::fieldWidgetValue( const QString &fieldName ) {

    if ( fieldName.isNull() || fieldName.isEmpty() ) {

      return QVariant();
    }

    QStringList autoexec;

    if ( fieldName == "machine" ) {
    } else if ( fieldName == "captures" ) {

    } else if ( fieldName == "memsize" ) {

    } else if ( fieldName == "keyboardlayout" ) {

    } else if ( fieldName == "autoexec" ) {

      for ( int a = 0; a < listWidgetAutoexec->topLevelItemCount(); a++ ) {
        autoexec.append( listWidgetAutoexec->topLevelItem( a ) );
      }

      return QVariant( autoexec );
    }

    return QVariant();
  }
}
