/***************************************************************************
 *   Copyright (C) 2004-2008 by Alexander Saal                             *
 *   alex.saal@gmx.de                                                      *
 *                                                                          *
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
#include <dboxfe.h>

#include <preference.h>

#include <QtGui>
#include <QtCore>

namespace asaal {

  Preference::Preference( QWidget *parent ) : QDialog( parent ) {

    setupUi( this );

    connect( btnDosboxBinary, SIGNAL( clicked() ), this, SLOT( chooseDosbox() ) );
    connect( btnOk, SIGNAL( clicked() ), this, SLOT( save() ) );

    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );

    configBase = DBoxFE::configBaseInstance();
    loadSettings( configBase->readSettings() );
  }

  Preference::~Preference() {

    configBase = 0;
  }

  void Preference::closeEvent( QCloseEvent *event ) {

    event->accept();
  }

  /*
   * Save DBoxFE configuration
   */
  void Preference::save() {

    if ( dosboxBinary.isNull() || dosboxBinary.isEmpty() ) {

      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No dosbox binary was selected!" ) );
      return;
    }

    dboxfeConfig.clear();

    dboxfeConfig.dosboxBinary = dosboxBinary;
    dboxfeConfig.dosboxVersion = dosboxVersion;
    dboxfeConfig.profiles = configBase->readProfiles();
    dboxfeConfig.winHide = checkBoxWindowsHide->isChecked();
    dboxfeConfig.keyMapper = checkBoxStartKeyMapper->isChecked();

    configBase->writeSettings( dboxfeConfig );

    configBase = 0;
    delete configBase;

    QDialog::accept();
  }

  /*
   * Choose dosbox binary and check this version
   */
  void Preference::chooseDosbox() {

    dosboxBinary = QFileDialog::getOpenFileName( this, tr( "Open dosbox binary" ), QDir::rootPath(), tr( "DOSBox (dosbox dosox.exe)" ) );

    if ( dosboxBinary.isNull() || dosboxBinary.isEmpty() ) {

      return;
    }

    qApp->processEvents();

    parameters.clear();

    dosbox = 0;
    dosbox = new QProcess( this );

#ifdef Q_OS_WIN32

    QFileInfo dosboxBin( dosboxBinary );

    parameters.append( "-noconsole" );
    parameters.append( "-version" );

    dosbox->setWorkingDirectory( QDir::homePath() + "/.dboxfe" );
    dosbox->start( dosboxBinary, parameters );

    while ( dosbox->waitForFinished() ) {
      QFile dboxOutFile( dosbox->workingDirectory() + "/stdout.txt" );

      if ( !dboxOutFile.open( QFile::ReadOnly | QFile::Text ) ) {
        QMessageBox::information( this, winTitle(), tr( "Can not read " ) + dboxOutFile.fileName() );
        dosboxVersion = QString( "" );
        dosbox->close();
        delete dosbox;
        return;
      }

      QTextStream t( &dboxOutFile );

      dosboxVersion = t.readAll();
      QStringList dVersion = dosboxVersion.split( " " );
      dosboxVersion = dVersion.value( 2 ).replace( ",", "" );

      if ( QString( dosboxVersion.simplified() ).trimmed().isEmpty() ) {

        QMessageBox::information( this, tr( "DBoxFE" ), tr( "This is not a valid dosbox binary." ) );
        dosboxVersion = QString( "" );
        dosbox->close();
        delete dosbox;
        return;
      }

      if ( QString( dosboxVersion.simplified() ).trimmed() >= "0.70" ) {

        lineEditDosboxBinary->setText( dosboxBinary );
        lineEditDosboxVersion->setText( QString( tr( "DOSBox Version:  " ) + dosboxVersion ) );
        dosboxVersion = dVersion;
      } else {

        QMessageBox::information( this, tr( "DBoxFE" ), tr( "Wrong dosbox version %1, i need 0.7x or higher." ).arg( QString( dosboxVersion.simplified() ).trimmed() ) );
        dosboxVersion = QString( "" );
        dosbox->close();
        delete dosbox;
        return;
      }
    }

    dosbox->close();

    delete dosbox;

#else
    parameters.append( "-version" );
    dosbox->start( dosboxBinary, parameters );

    while ( dosbox->waitForFinished() ) {
      dosboxVersion = dosbox->readAll();
      QStringList dVersion = dosboxVersion.split( " " );
      dosboxVersion = dVersion.value( 2 ).replace( ",", "" );

      if ( QString( dosboxVersion.simplified() ).trimmed().isEmpty() ) {

        QMessageBox::information( this, tr( "DBoxFE" ), tr( "This is not a valid dosbox binary." ) );
        dosboxVersion = QString();
        dosbox->close();
        delete dosbox;
        return;
      }

      if ( QString( dosboxVersion.simplified() ).trimmed() >= "0.70" ) {

        lineEditDosboxBinary->setText( dosboxBinary );
        lineEditDosboxVersion->setText( QString( tr( "DOSBox Version:  " ) + dosboxVersion ) );
        dosboxVersion = dosboxVersion;
      } else {

        QMessageBox::information( this, tr( "DBoxFE" ), tr( "Wrong dosbox version %1, i need 0.7x or higher." ).arg( QString( dosboxVersion.simplified() ).trimmed() ) );
        dosboxVersion = QString( "" );
        dosbox->close();
        delete dosbox;
        return;
      }
    }

    dosbox->close();

    delete dosbox;

#endif

  }

  /*
   * Load DBoxFE configuration
   */
  void Preference::loadSettings( const DBoxFE_Configuration &dboxfeConfig ) {

    qApp->processEvents();

    if ( dboxfeConfig.isEmpty() ) {

      return;
    }

    lineEditDosboxBinary->setText( dboxfeConfig.dosboxBinary );
    lineEditDosboxVersion->setText( QString( tr( "DOSBox Version: %1" ).arg( dboxfeConfig.dosboxVersion ) ) );

    checkBoxWindowsHide->setChecked( dboxfeConfig.winHide );
    checkBoxStartKeyMapper->setChecked( dboxfeConfig.keyMapper );
  }
}
