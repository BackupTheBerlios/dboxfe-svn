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

#include <gamewizard.h>
#include <importexportpage.h>

#include <QtCore>
#include <QtGui>

namespace asaal {

  ImportExportPage::ImportExportPage( QWidget *parent ) : QWizardPage( parent ) {

    setupUi( this );
    setTitle( tr( "Import / Export" ) );
    setSubTitle( tr( "Please select an option and select your profiles from list which profiles you want to import and/or export." ) );

    registerField( "dfendDirectory", lineEditDFendDirectory );
    registerField( "dboxfeDirectory", lineEditDboxFeDirectory );

    connect( btnDFend, SIGNAL( clicked() ), this, SLOT( chooseDfendDirectory() ) );
    connect( btnDboxFe, SIGNAL( clicked() ), this, SLOT( chooseDboxFeDirectory() ) );
    connect( btnMarkAll, SIGNAL( clicked() ), this, SLOT( markAllProfiles() ) );
    connect( btnUnmarkAll, SIGNAL( clicked() ), this, SLOT( unmarkAllProfiles() ) );
  }

  int ImportExportPage::nextId() const {

    return -1;
  }

  void ImportExportPage::accept() {

    QString dfendDirectory = field( "dfendDirectory" ).toString();
    QString dboxfeDirectory = field( "dboxfeDirectory" ).toString();

    if (( dfendDirectory.isNull() || dfendDirectory.isEmpty() ) ) {
      QMessageBox::warning( 0, "Game Assistant", tr( "D-Fend directory can't be empty." ) );
      return;
    }

    if (( dboxfeDirectory.isNull() || dboxfeDirectory.isEmpty() ) ) {
      QMessageBox::warning( 0, "Game Assistant", tr( "DBoxFE directory can't be empty." ) );
      return;
    }
      
    if( profileList.size() >= 1 ) {
      QMap< QString, QString >::const_iterator proIt = profileList.begin();
      bool import = rbtnImport->isChecked();

      if( import ) {    
        while( proIt != profileList.end() ) {

          qApp->processEvents();

          QString profileName = proIt.key();
          QString profilePath = proIt.value();

          importDfendProfiles( profilePath, profileName );

          proIt++;
        }

      } else {
        while( proIt != profileList.end() ) {

          qApp->processEvents();

          QString profileName = proIt.key();
          QString profilePath = proIt.value();

          exportDboxFeProfile( profilePath, profileName );

          proIt++;
        }
      }
    }

    qApp->quit();
  }

  void ImportExportPage::chooseDfendDirectory() {

    QString dfendFolder = QFileDialog::getExistingDirectory( this, tr( "Open D-Fend folder" ), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    if ( !dfendFolder.isEmpty() ) {
      lineEditDFendDirectory->setText( dfendFolder );
    }

    QDir dfendProfileFolder( dfendFolder + "/Confs" );
    if ( !dfendProfileFolder.exists() ) {
      QMessageBox::warning( 0, "Game Assistant", tr( "This is not a D-Fend Reloaded directory." ) );
      return;
    }


    if ( rbtnImport->isChecked() ) {

      profileList.clear();

      QApplication::setOverrideCursor( Qt::WaitCursor );

      treeWidgetImportExport->headerItem()->setText( 0, "D-Fend Profiles" );
      QTreeWidgetItem *dfendProf;
      QFileInfo fi;
      const QFileInfoList fil = dfendProfileFolder.entryInfoList( QDir::Files, QDir::Name );
      QListIterator< QFileInfo > it( fil );
      QStringList lst;

      while ( it.hasNext() ) {
        qApp->processEvents();

        fi = it.next();

        if ( fi.fileName() == "." || fi.fileName() == ".." ) {
          ;
        } else {

          if ( fi.isFile() && fi.isReadable() && fi.fileName().endsWith( ".prof" ) ) {

            dfendProf = new QTreeWidgetItem( treeWidgetImportExport );
            treeWidgetImportExport->setItemWidget( dfendProf, 0, new QCheckBox( fi.baseName() ) );
            QCheckBox *checkBox = ( QCheckBox* )treeWidgetImportExport->itemWidget( dfendProf, 0 );

            if ( checkBox ) {
              checkBox->setCheckState( Qt::Checked );
            }

            profileList.insert( fi.baseName(), fi.absolutePath() );
          }
        }
      }

      QApplication::restoreOverrideCursor();
    }
  }

  void ImportExportPage::chooseDboxFeDirectory() {

    QString dboxfeFolder = QFileDialog::getExistingDirectory( this, tr( "Open DBoxFE folder" ), QDir::homePath() + "/.dboxfe", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    QFileInfo dboxfeProfile( dboxfeFolder + "/profile/profile.xml" );
    if ( !dboxfeProfile.exists() ) {
      QMessageBox::warning( 0, "Game Assistant", tr( "This is not a DBoxFE directory." ) );
      return;
    }

    if ( !dboxfeFolder.isEmpty() ) {
      lineEditDboxFeDirectory->setText( dboxfeFolder );
    }

    if ( rbtnExport->isChecked() ) {

      profileList.clear();

      QApplication::setOverrideCursor( Qt::WaitCursor );

      QDir dboxfeProfDir( dboxfeFolder );
      treeWidgetImportExport->headerItem()->setText( 0, "DBoxFE Profiles" );
      QTreeWidgetItem *dboxfeProf;
      QFileInfo fi;
      const QFileInfoList fil = dboxfeProfDir.entryInfoList( QDir::Files, QDir::Name );
      QListIterator< QFileInfo > it( fil );
      QStringList lst;

      while ( it.hasNext() ) {
        qApp->processEvents();

        fi = it.next();

        if ( fi.fileName() == "." || fi.fileName() == ".." ) {
          ;
        } else {

          if ( fi.isFile() && fi.isReadable() && fi.fileName().endsWith( ".conf" ) ) {

            dboxfeProf = new QTreeWidgetItem( treeWidgetImportExport );
            treeWidgetImportExport->setItemWidget( dboxfeProf, 0, new QCheckBox( fi.baseName() ) );
            QCheckBox *checkBox = ( QCheckBox* )treeWidgetImportExport->itemWidget( dboxfeProf, 0 );

            if ( checkBox ) {
              checkBox->setCheckState( Qt::Checked );
            }

            profileList.insert( fi.baseName(), fi.absolutePath() );
          }
        }
      }

      QApplication::restoreOverrideCursor();
    }
  }


  void ImportExportPage::markAllProfiles() {

    QApplication::setOverrideCursor( Qt::WaitCursor );

    for ( int a = 0; a < treeWidgetImportExport->topLevelItemCount(); a++ ) {

      qApp->processEvents();

      QTreeWidgetItem *item = treeWidgetImportExport->topLevelItem( a );
      QCheckBox *checkBox = ( QCheckBox* )treeWidgetImportExport->itemWidget( item, 0 );

      if ( checkBox ) {

        if ( checkBox->checkState() != Qt::Checked ) {

          checkBox->setCheckState( Qt::Checked );
        }
      }
    }

    QApplication::restoreOverrideCursor();
  }

  void ImportExportPage::unmarkAllProfiles() {

    QApplication::setOverrideCursor( Qt::WaitCursor );

    for ( int a = 0; a < treeWidgetImportExport->topLevelItemCount(); a++ ) {

      qApp->processEvents();

      QTreeWidgetItem *item = treeWidgetImportExport->topLevelItem( a );
      QCheckBox *checkBox = ( QCheckBox* )treeWidgetImportExport->itemWidget( item, 0 );

      if ( checkBox ) {

        if ( checkBox->checkState() == Qt::Checked ) {

          checkBox->setCheckState( Qt::Unchecked );
        }
      }
    }

    QApplication::restoreOverrideCursor();
  }

  void ImportExportPage::importDfendProfiles( const QString &path, const QString &name ) {
  }

  void ImportExportPage::exportDboxFeProfile( const QString &path, const QString &name ) {
  }
}
