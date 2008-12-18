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
 *   the Free Software Foundation; either version 3 of the License, or     *
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
#include <games.h>
#include <profilesettings.h>

#include <QtGui>
#include <QtCore>

namespace asaal {

  ProfileSettings::ProfileSettings( QWidget *parent, Qt::WFlags flags ) : QDialog( parent, flags ) {

    setupUi( this );

    btnAutoexecUpdate->setEnabled( false );

    /* ProfileSettings connections */
    connect( btnSave, SIGNAL( clicked() ), this, SLOT( saveConfiguration() ) );
    connect( btnDefault, SIGNAL( clicked() ), this, SLOT( setDefaultConfiguration() ) );
    connect( btnAbort, SIGNAL( clicked() ), this, SLOT( closeWidget() ) );

    /* Autoexec page connections */
    connect( comboBoxAutoexecMountOption, SIGNAL( currentIndexChanged( int ) ), this, SLOT( comboBoxAutoexecIndexChanged( int ) ) );
    connect( comboBoxAutoexecImageFormat, SIGNAL( currentIndexChanged( int ) ), this, SLOT( comboBoxAutoexecImageFormatIndexChanged( int ) ) );
    connect( btnAutoexecDrive, SIGNAL( clicked() ), this, SLOT( autoexecDrive() ) );
    connect( btnAutoexecAdd, SIGNAL( clicked() ), this, SLOT( autoexecAdd() ) );
    connect( btnAutoexecRemove, SIGNAL( clicked() ), this, SLOT( autoexecRemove() ) );
    connect( btnAutoexecUpdate, SIGNAL( clicked() ), this, SLOT( autoexecUpdate() ) );

    connect( btnGame, SIGNAL( clicked() ), this, SLOT( addGame() ) );
    connect( btnAutoexecUp, SIGNAL( clicked() ), this, SLOT( autoexecMoveUp() ) );
    connect( btnAutoexecDown, SIGNAL( clicked() ), this, SLOT( autoexecMoveDown() ) );

    /* Internet page connections */
    connect( comboBoxDSOption, SIGNAL( currentIndexChanged( int ) ), this, SLOT( comboBoxSerialIndexChanged( int ) ) );
    connect( btnSerialAdd, SIGNAL( clicked() ), this, SLOT( serialAdd() ) );
    connect( btnSerialRemove, SIGNAL( clicked() ), this, SLOT( serialRemove() ) );

    /* DOS page connections */
    connect( btnLanguage, SIGNAL( clicked() ), this, SLOT( openLanguageFile() ) );
    connect( comboBoxKeyboardLayout, SIGNAL( currentIndexChanged( int ) ), this, SLOT( comboBoxKeyboardLayoutIndexChanged( int ) ) );

    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );
  }

  ProfileSettings::~ProfileSettings() {}

  void ProfileSettings::closeEvent( QCloseEvent *e ) {

    e->accept();

    profileConfiguration.clear();
  }

  void ProfileSettings::comboBoxSerialIndexChanged( int index ) {

    switch ( index ) {

      case 0:               // diasabled
        groupBoxSerialOption->setEnabled( false );
        break;

      case 1:               // dummy
        groupBoxSerialOption->setEnabled( false );
        break;

      case 2:               // modem
        groupBoxSerialOption->setEnabled( true );
        labelDSRealPort->setEnabled( true );
        comboBoxDSRealPort->setEnabled( true );
        labelDSIrq->setEnabled( true );
        lineEditDSIrq->setEnabled( true );
        labelDSDefaultBps->setEnabled( true );
        lineEditDSBps->setEnabled( true );
        labelDSByteSize->setEnabled( true );
        comboBoxDSByteSize->setEnabled( true );
        labelDSStopBit->setEnabled( true );
        comboBoxDSStopBit->setEnabled( true );
        labelDSParity->setEnabled( true );
        comboBoxDSParity->setEnabled( true );
        labelDSComPort->setEnabled( false );
        comboBoxDSComPort->setEnabled( false );
        break;

      case 3:               // directserial
        groupBoxSerialOption->setEnabled( true );
        labelDSRealPort->setEnabled( true );
        comboBoxDSRealPort->setEnabled( true );
        labelDSIrq->setEnabled( true );
        lineEditDSIrq->setEnabled( true );
        labelDSDefaultBps->setEnabled( true );
        lineEditDSBps->setEnabled( true );
        labelDSByteSize->setEnabled( true );
        comboBoxDSByteSize->setEnabled( true );
        labelDSStopBit->setEnabled( true );
        comboBoxDSStopBit->setEnabled( true );
        labelDSParity->setEnabled( true );
        comboBoxDSParity->setEnabled( true );
        labelDSComPort->setEnabled( false );
        comboBoxDSComPort->setEnabled( false );
        break;
    }
  }

  void ProfileSettings::comboBoxAutoexecIndexChanged( int index ) {

    switch ( index ) {

      case 0:               // Default
        labelAutoexecCDDVDROMOption->setEnabled( false );
        comboBoxAutoexecCDDVDROMOption->setEnabled( false );

        labelAutoexecImageTyp->setEnabled( false );
        comboBoxAutoexecImageTyp->setEnabled( false );

        labelAutoexecImageFormat->setEnabled( false );
        comboBoxAutoexecImageFormat->setEnabled( false );

        labelAutoexecImageSize->setEnabled( false );
        lineEditImageSize->setEnabled( false );

        labelAutoexecImageHddMode->setEnabled( false );
        comboBoxAutoexecImageHddMode->setEnabled( false );
        break;

      case 1:               // CD/DVD ROM
        labelAutoexecCDDVDROMOption->setEnabled( true );
        comboBoxAutoexecCDDVDROMOption->setEnabled( true );

        labelAutoexecImageTyp->setEnabled( false );
        comboBoxAutoexecImageTyp->setEnabled( false );

        labelAutoexecImageFormat->setEnabled( false );
        comboBoxAutoexecImageFormat->setEnabled( false );

        labelAutoexecImageSize->setEnabled( false );
        lineEditImageSize->setEnabled( false );

        labelAutoexecImageHddMode->setEnabled( false );
        comboBoxAutoexecImageHddMode->setEnabled( false );
        break;

      case 2:               // Floppy
        labelAutoexecCDDVDROMOption->setEnabled( false );
        comboBoxAutoexecCDDVDROMOption->setEnabled( false );

        labelAutoexecImageTyp->setEnabled( false );
        comboBoxAutoexecImageTyp->setEnabled( false );

        labelAutoexecImageFormat->setEnabled( false );
        comboBoxAutoexecImageFormat->setEnabled( false );

        labelAutoexecImageSize->setEnabled( false );
        lineEditImageSize->setEnabled( false );

        labelAutoexecImageHddMode->setEnabled( false );
        comboBoxAutoexecImageHddMode->setEnabled( false );
        break;

      case 3:               // Image
        labelAutoexecCDDVDROMOption->setEnabled( false );
        comboBoxAutoexecCDDVDROMOption->setEnabled( false );

        labelAutoexecImageTyp->setEnabled( true );
        comboBoxAutoexecImageTyp->setEnabled( true );

        labelAutoexecImageFormat->setEnabled( true );
        comboBoxAutoexecImageFormat->setEnabled( true );

        labelAutoexecImageSize->setEnabled( false );
        lineEditImageSize->setEnabled( false );

        labelAutoexecImageHddMode->setEnabled( false );
        comboBoxAutoexecImageHddMode->setEnabled( false );
        break;
    }
  }

  void ProfileSettings::comboBoxAutoexecImageFormatIndexChanged( int index ) {

    switch ( index ) {

      case 0:               // iso
        labelAutoexecImageSize->setEnabled( false );
        lineEditImageSize->setEnabled( false );

        labelAutoexecImageHddMode->setEnabled( false );
        comboBoxAutoexecImageHddMode->setEnabled( false );
        break;

      case 1:               // fat
        labelAutoexecImageSize->setEnabled( false );
        lineEditImageSize->setEnabled( false );

        labelAutoexecImageHddMode->setEnabled( false );
        comboBoxAutoexecImageHddMode->setEnabled( false );
        break;

      case 2:               // none
        labelAutoexecImageSize->setEnabled( true );
        lineEditImageSize->setEnabled( true );

        labelAutoexecImageHddMode->setEnabled( true );
        comboBoxAutoexecImageHddMode->setEnabled( true );
        break;
    }
  }

  void ProfileSettings::comboBoxKeyboardLayoutIndexChanged( int index ) {

    labelKeyboardLayoutInfo->setText( tr( "No keyboardlayot" ) );

    switch ( index ) {

      case 0:
        labelKeyboardLayoutInfo->setText( tr( "No keyboardlayot" ) );     /* none  */
        break;

      case 1:
        labelKeyboardLayoutInfo->setText( tr( "Bulgaria" ) );      /* BG  */
        break;

      case 2:
        labelKeyboardLayoutInfo->setText( tr( "Czech Republic" ) );     /* CZ243 */
        break;

      case 3:
        labelKeyboardLayoutInfo->setText( tr( "France" ) );       /* FR  */
        break;

      case 4:
        labelKeyboardLayoutInfo->setText( tr( "Greece" ) );       /* GK  */
        break;

      case 5:
        labelKeyboardLayoutInfo->setText( tr( "Germany" ) );      /* GR  */
        break;

      case 6:
        labelKeyboardLayoutInfo->setText( tr( "Croatia" ) );      /* HR  */
        break;

      case 7:
        labelKeyboardLayoutInfo->setText( tr( "Hungary" ) );      /* HU  */
        break;

      case 8:
        labelKeyboardLayoutInfo->setText( tr( "Italy" ) );       /* IT  */
        break;

      case 9:
        labelKeyboardLayoutInfo->setText( tr( "Netherlands" ) );     /* NL  */
        break;

      case 10:
        labelKeyboardLayoutInfo->setText( tr( "Norway" ) );      /* NO  */
        break;

      case 11:
        labelKeyboardLayoutInfo->setText( tr( "Poland" ) );      /* PL  */
        break;

      case 12:
        labelKeyboardLayoutInfo->setText( tr( "Russian Federation" ) );   /* RU  */
        break;

      case 13:
        labelKeyboardLayoutInfo->setText( tr( "Slovakia" ) );      /* SK  */
        break;

      case 14:
        labelKeyboardLayoutInfo->setText( tr( "Spain" ) );       /* SP  */
        break;

      case 15:
        labelKeyboardLayoutInfo->setText( tr( "Finland" ) );      /* SU  */
        break;

      case 16:
        labelKeyboardLayoutInfo->setText( tr( "Sweden" ) );      /* SV  */
        break;
    }
  }

  void ProfileSettings::autoexecDrive() {

    QString autoDrive = QString( "" );

    if ( comboBoxAutoexecMountOption->currentIndex() == 3 ) {

      autoDrive = QFileDialog::getOpenFileName( this, tr( "Open image file" ), QDir::homePath(),  "ISO (*.iso);;CUE (*.cue);;BIN (*.bin)" );
    } else {

      autoDrive = QFileDialog::getExistingDirectory( this, tr( "Open directory for mount in dosbox" ), QDir::homePath() );
    }

    if ( autoDrive.isEmpty() )
      return;

    lineEditDrives->setText( autoDrive );
  }

  void ProfileSettings::autoexecUpdate() {
  }

  void ProfileSettings::autoexecRemove() {

    QTreeWidgetItem * item = treeWidgetAutoexec->currentItem();

    if ( item == NULL ) {
      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No entry was selected." ) );
      return;
    }

    delete item;
  }

  void ProfileSettings::autoexecAdd() {

    QList<QTreeWidgetItem *> it( treeWidgetAutoexec->findItems( comboBoxDrive->currentText().toLower(), Qt::MatchExactly, 0 ) );

    for ( int a = 0; a < it.size(); a++ ) {
      QTreeWidgetItem *item;
      item = it.value( a );

      if ( item->text( 0 ) == comboBoxDrive->currentText().toLower() ) {

        QMessageBox::information( this, tr( "DBoxFE" ), tr( "Can not add the same drive '%1' to the list." ).arg( comboBoxDrive->currentText().toLower() ) );
        return;
      }
    }

    QString addStr;

    QTreeWidgetItem *autoexecItem = new QTreeWidgetItem();

    if ( lineEditDrives->text().isEmpty() ) {
      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No file/directory was choosed." ) );
      return ;
    } else {
      switch ( comboBoxAutoexecMountOption->currentIndex() ) {

        case 0:               // Default

          if ( checkBoxLabelCDDVD->isChecked() ) {
            if ( !lineEditDeviceLabel->text().isEmpty() ) {

              addStr = "mount " + comboBoxDrive->currentText().toLower() + " " + lineEditDrives->text() + " -label " + lineEditDeviceLabel->text();
              autoexecItem->setText( 0, comboBoxDrive->currentText().toLower() );
              autoexecItem->setText( 1, lineEditDrives->text() );
              autoexecItem->setText( 2, lineEditDeviceLabel->text() );
              autoexecItem->setText( 5, addStr );
            } else {

              QMessageBox::information( this, tr( "DBoxFE" ), tr( "Please enter a valid name for label." ) );
              return ;
            }
          } else {

            lineEditDeviceLabel->setText( "" );
            addStr = "mount " + comboBoxDrive->currentText().toLower() + " " + lineEditDrives->text();

            autoexecItem->setText( 0, comboBoxDrive->currentText().toLower() );
            autoexecItem->setText( 1, lineEditDrives->text() );
            autoexecItem->setText( 5, addStr );
          }

          break;

        case 1:               // CD/DVD

          switch ( comboBoxAutoexecCDDVDROMOption->currentIndex() ) {

            case 0:             // Windows 2000/XP/Linux

              if ( checkBoxLabelCDDVD->isChecked() ) {
                if ( !lineEditDeviceLabel->text().isEmpty() ) {

                  addStr = "mount " + comboBoxDrive->currentText().toLower() + " " + lineEditDrives->text() + " -t cdrom -usecd 0 -ioctl -label " + lineEditDeviceLabel->text();
                  autoexecItem->setText( 0, comboBoxDrive->currentText().toLower() );
                  autoexecItem->setText( 1, lineEditDrives->text() );
                  autoexecItem->setText( 2, lineEditDeviceLabel->text() );
                  autoexecItem->setText( 5, addStr );
                } else {

                  QMessageBox::information( this, tr( "DBoxFE" ), tr( "Please enter a valid name for label." ) );
                  return ;
                }
              } else {

                lineEditDeviceLabel->setText( "" );
                addStr = "mount " + comboBoxDrive->currentText().toLower() + " " + lineEditDrives->text() + " -t cdrom -usecd 0 -ioctl";
                autoexecItem->setText( 0, comboBoxDrive->currentText().toLower() );
                autoexecItem->setText( 1, lineEditDrives->text() );
                autoexecItem->setText( 5, addStr );
              }

              break;

            case 1:             // Windows 98

              if ( checkBoxLabelCDDVD->isChecked() ) {
                if ( !lineEditDeviceLabel->text().isEmpty() ) {

                  addStr = "mount " + comboBoxDrive->currentText().toLower() + " " + lineEditDrives->text() + " -t cdrom -usecd 0 -aspi -label " + lineEditDeviceLabel->text();
                  autoexecItem->setText( 0, comboBoxDrive->currentText().toLower() );
                  autoexecItem->setText( 1, lineEditDrives->text() );
                  autoexecItem->setText( 2, lineEditDeviceLabel->text() );
                  autoexecItem->setText( 5, addStr );
                } else {

                  QMessageBox::information( this, tr( "DBoxFE" ), tr( "Please enter a valid name for label." ) );
                  return ;
                }
              } else {

                lineEditDeviceLabel->setText( "" );
                addStr = "mount " + comboBoxDrive->currentText().toLower() + " " + lineEditDrives->text() + " -t cdrom -usecd 0 -aspi";
                autoexecItem->setText( 0, comboBoxDrive->currentText().toLower() );
                autoexecItem->setText( 1, lineEditDrives->text() );
                autoexecItem->setText( 5, addStr );
              }

              break;
          }

          break;

        case 2:               // Floppy

          if ( checkBoxLabelCDDVD->isChecked() ) {
            if ( !lineEditDeviceLabel->text().isEmpty() ) {

              addStr = "mount " + comboBoxDrive->currentText().toLower() + " " + lineEditDrives->text() + " -t floppy -label " + lineEditDeviceLabel->text();
              autoexecItem->setText( 0, comboBoxDrive->currentText().toLower() );
              autoexecItem->setText( 1, lineEditDrives->text() );
              autoexecItem->setText( 2, lineEditDeviceLabel->text() );
              autoexecItem->setText( 5, addStr );
            } else {

              QMessageBox::information( this, tr( "DBoxFE" ), tr( "Please enter a valid name for label." ) );
              return ;
            }
          } else {

            lineEditDeviceLabel->setText( "" );
            addStr = "mount " + comboBoxDrive->currentText().toLower() + " " + lineEditDrives->text() + " -t floppy";
            autoexecItem->setText( 0, comboBoxDrive->currentText().toLower() );
            autoexecItem->setText( 1, lineEditDrives->text() );
            autoexecItem->setText( 5, addStr );
          }

          break;

        case 3:               // Image

          switch ( comboBoxAutoexecImageTyp->currentIndex() ) {

            case 0: // floppy

              switch ( comboBoxAutoexecImageFormat->currentIndex() ) {

                case 0: // iso
                  addStr = "imgmount " + comboBoxDrive->currentText().toLower() + " " + lineEditDrives->text() + " -t iso";
                  autoexecItem->setText( 0, comboBoxDrive->currentText().toLower() );
                  autoexecItem->setText( 1, lineEditDrives->text() );
                  autoexecItem->setText( 5, addStr );
                  break;

                case 1: // fat
                  addStr = "imgmount " + comboBoxDrive->currentText().toLower() + " " + lineEditDrives->text() + " -t fat";
                  autoexecItem->setText( 0, comboBoxDrive->currentText().toLower() );
                  autoexecItem->setText( 1, lineEditDrives->text() );
                  autoexecItem->setText( 5, addStr );
                  break;

                case 2: // none
                  QMessageBox::information( this, tr( "DBoxFE" ), tr( "Not used by floppy!" ) );
                  return;
              }

              break;

            case 1: // iso
              break;

            case 2: // hdd
              break;
          }

          break;
      }
    }

    if ( checkBoxSwitchDir->isChecked() ) {

      autoexecItem->setText( 3, "true" );
      checkBoxSwitchDir->setChecked( false );
    } else {

      autoexecItem->setText( 3, "false" );
    }

    treeWidgetAutoexec->addTopLevelItem( autoexecItem );

    addStr = "";
  }

  void ProfileSettings::autoexecMoveUp() {

    QTreeWidgetItem *item = treeWidgetAutoexec->currentItem();

    if ( item == NULL ) {
      return;
    }

    int index = treeWidgetAutoexec->indexOfTopLevelItem( item );

    if ( index <= 0 ) {
      return;
    }

    treeWidgetAutoexec->insertTopLevelItem( index - 1, treeWidgetAutoexec->takeTopLevelItem( index ) );

    treeWidgetAutoexec->setCurrentItem( item );
  }

  void ProfileSettings::autoexecMoveDown() {

    QTreeWidgetItem *item = treeWidgetAutoexec->currentItem();

    if ( item == NULL ) {
      return;
    }

    int index = treeWidgetAutoexec->indexOfTopLevelItem( item );

    if (( index + 1 ) >= treeWidgetAutoexec->topLevelItemCount() ) {
      return;
    }

    treeWidgetAutoexec->insertTopLevelItem( index + 1, treeWidgetAutoexec->takeTopLevelItem( index ) );

    treeWidgetAutoexec->setCurrentItem( item );
  }

  void ProfileSettings::addGame() {

    Games *games = new Games();

    QApplication::setOverrideCursor( Qt::WaitCursor );
    games->initalGames();
    QApplication::restoreOverrideCursor();

    if ( games->exec() == QDialog::Accepted ) {

      QTreeWidgetItem *autoexecItem = treeWidgetAutoexec->currentItem();

      if ( autoexecItem ) {
        autoexecItem->setText( 4, games->executable() );
      } else {

        QMessageBox::information( this, tr( "DBoxFE" ), tr( "You must select a autoexec entry from list to add a game!" ) );
        return;
      }
    }

    games = 0;

    delete games;
  }

  void ProfileSettings::serialRemove() {

    QTreeWidgetItem * item = treeWidgetSerial->currentItem();

    if ( item == NULL ) {
      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No serial was selected." ) );
      return;
    }

    delete item;
  }

  void ProfileSettings::serialAdd() {

    // Check if the item available in the list then show a message and exit function
    QList<QTreeWidgetItem *> it( treeWidgetSerial->findItems( comboBoxDSSerial->currentText(), Qt::MatchExactly, 0 ) );

    for ( int a = 0; a < it.size(); ++a ) {
      QTreeWidgetItem *sItem;
      sItem = it.value( a );

      if ( sItem->text( a ) == comboBoxDSSerial->currentText() ) {
        QMessageBox::information( this, tr( "DBoxFE" ), tr( "Can not add the same serial '%1' port to the list." ).arg( sItem->text( a ) ) );
        return;
      }
    }

    // Check if the list count higher as 4 then show message and exit function
    if ( treeWidgetSerial->topLevelItemCount() >= 4 ) {
      QMessageBox::information( this, tr( "DBoxFE" ), tr( "Can not add 5 serialports to the list, maximal 4 are allow." ) );
      return;
    }

    QTreeWidgetItem *item = new QTreeWidgetItem( treeWidgetSerial );

    item->setText( 0, comboBoxDSSerial->currentText() );

    QString serialOption;

    switch ( comboBoxDSOption->currentIndex() ) {

      case 0:               // diasabled
        item->setText( 1, comboBoxDSOption->currentText() );
        break;

      case 1:               // dummy
        item->setText( 1, comboBoxDSOption->currentText() );
        break;

      case 2:               // modem
        serialOption = comboBoxDSOption->currentText() + " " +
                       "listenport:" + lineEditDSListenPort->text() + " " +
                       "realport:" + comboBoxDSRealPort->currentText() + " " +
                       "startbps:" + lineEditDSBps->text() + " " +
                       "parity:" + comboBoxDSParity->currentText() + " " +
                       "bytesize:" + comboBoxDSByteSize->currentText() + " " +
                       "stopbits:" + comboBoxDSStopBit->currentText() + " " +
                       "irq:" + lineEditDSIrq->text();

        item->setText( 1, serialOption );
        break;

      case 3:               // directserial
        serialOption = comboBoxDSOption->currentText() + " " +
                       "realport:" + comboBoxDSRealPort->currentText() + " " +
                       "startbps:" + lineEditDSBps->text() + " " +
                       "parity:" + comboBoxDSParity->currentText() + " " +
                       "bytesize:" + comboBoxDSByteSize->currentText() + " " +
                       "stopbits:" + comboBoxDSStopBit->currentText() + " " +
                       "irq:" + lineEditDSIrq->text();

        item->setText( 1, serialOption );
        break;
    }

  }

  void ProfileSettings::openLanguageFile() {
  }

  void ProfileSettings::saveConfiguration() {

    QApplication::setOverrideCursor( Qt::WaitCursor );

    qApp->processEvents();

    profileConfiguration.clear();

    // Graphic  page
    profileConfiguration.sdl.insert( "fullscreen", checkBoxSDLFullScreen->isChecked() );
    profileConfiguration.sdl.insert( "fulldouble", checkBoxSDLFullDouble->isChecked() );
    profileConfiguration.sdl.insert( "waitonerror", checkBoxSDLWaitOnError->isChecked() );
    profileConfiguration.sdl.insert( "autolock", checkBoxSDLAutolock->isChecked() );
    profileConfiguration.sdl.insert( "usescancodes", checkBoxSDLUseScanCode->isChecked() );
    profileConfiguration.sdl.insert( "output", comboBoxSDLOutout->currentText() );
    profileConfiguration.sdl.insert( "priority", comboBoxSDLFocusUnfocus->currentText().replace( "\"", "" ) );
    profileConfiguration.sdl.insert( "windowresolution", comboBoxSDLWindowWightHigh->currentText() );
    profileConfiguration.sdl.insert( "fullresolution", comboBoxSDLFullWightHigh->currentText() );
    profileConfiguration.sdl.insert( "sensitivity", lcdSDLSensitivity->intValue() );

    profileConfiguration.render.insert( "scaler", comboBoxRenderScaler->currentText() );
    profileConfiguration.render.insert( "frameskip", lcdRenderFrameScip->intValue() );
    profileConfiguration.render.insert( "aspect", checkBoxRenderAspect->isChecked() );

    profileConfiguration.cpu.insert( "core", comboBoxCPUCore->currentText() );
    profileConfiguration.cpu.insert( "cycleup", comboBoxCPUCycleUp->currentText() );
    profileConfiguration.cpu.insert( "cycles", comboBoxCPUCycles->currentText() );
    profileConfiguration.cpu.insert( "cycledown", comboBoxCPUCycleDown->currentText() );

    // Sound page
    profileConfiguration.mixer.insert( "rate", comboBoxMixerRate->currentText() );
    profileConfiguration.mixer.insert( "blocksize", comboBoxMixerBlockSize->currentText() );
    profileConfiguration.mixer.insert( "prebuffer", spinnBoxPrebuffer->value() );
    profileConfiguration.mixer.insert( "nosound", checkBoxMixerNoSound->isChecked() );

    profileConfiguration.sblaster.insert( "sbtype", comboBoxSBType->currentText() );
    profileConfiguration.sblaster.insert( "sbbase", comboBoxSBBase->currentText() );
    profileConfiguration.sblaster.insert( "irq", comboBoxSBIRQ->currentText() );
    profileConfiguration.sblaster.insert( "dma", comboBoxSBDMA->currentText() );
    profileConfiguration.sblaster.insert( "oplmode", comboBoxSBOplMode->currentText() );
    profileConfiguration.sblaster.insert( "hdma", comboBoxSBHDMA->currentText() );
    profileConfiguration.sblaster.insert( "oplrate", comboBoxSBOPLRate->currentText() );
    profileConfiguration.sblaster.insert( "mixer", checkBoxSBMixer->isChecked() );

    profileConfiguration.gus.insert( "gus", checkBoxGUS->isChecked() );
    profileConfiguration.gus.insert( "gusrate", comboBoxGUSRate->currentText() );
    profileConfiguration.gus.insert( "gusbase", comboBoxGUSBase->currentText() );
    profileConfiguration.gus.insert( "irq1", comboBoxGUSIrq_1->currentText() );
    profileConfiguration.gus.insert( "irq2", comboBoxGUSIrq_2->currentText() );
    profileConfiguration.gus.insert( "dma1", comboBoxGUSDMA_1->currentText() );
    profileConfiguration.gus.insert( "dma2", comboBoxGUSDMA_2->currentText() );
    profileConfiguration.gus.insert( "ultradir", lineEditGUSUltraDir->text() );

    profileConfiguration.speaker.insert( "pcspeaker", comboBoxSpeaker->currentText() );
    profileConfiguration.speaker.insert( "pcrate", comboBoxSpeakerRate->currentText() );
    profileConfiguration.speaker.insert( "tandy", comboBoxSpeakerTandy->currentText() );
    profileConfiguration.speaker.insert( "tandyrate", comboBoxSpeakerTandyRate->currentText() );
    profileConfiguration.speaker.insert( "disney", checkBoxDisney->isChecked() );

    profileConfiguration.mdi.insert( "mpu401", comboBoxMDIMPU->currentText() );
    profileConfiguration.mdi.insert( "device", comboBoxMDIDevice->currentText() );
    profileConfiguration.mdi.insert( "config", lineEditMDIConfig->text() );

    // Autoexec page
    for ( int a = 0; a < treeWidgetAutoexec->topLevelItemCount(); a++ ) {

      qApp->processEvents();

      QTreeWidgetItem *item = treeWidgetAutoexec->topLevelItem( a );
      profileConfiguration.autoexec.append( item->text( 5 ) );

      if ( item->text( 3 ) == "true" ) {

        profileConfiguration.autoexec.append( item->text( 0 ) + ":" );
      }

      if ( !item->text( 4 ).isNull() || !item->text( 4 ).isEmpty() ) {

        profileConfiguration.autoexec.append( item->text( 4 ) );
      }
    }

    // Inernet page
    // Now we are check this list for more then one entry
    bool serialFound1 = false;
    bool serialFound2 = false;
    bool serialFound3 = false;
    bool serialFound4 = false;

    for ( int b = 0;  b < treeWidgetSerial->topLevelItemCount(); b++ ) {

      qApp->processEvents();

      QTreeWidgetItem *item = treeWidgetSerial->topLevelItem( b );

      if ( item->text( 0 ) == "serial1" ) {

        serialFound1 = true;
        profileConfiguration.serial.insert( item->text( 0 ), item->text( 1 ) );
      } else if ( item->text( 0 ) == "serial2" ) {

        serialFound2 = true;
        profileConfiguration.serial.insert( item->text( 0 ), item->text( 1 ) );
      } else if ( item->text( 0 ) == "serial3" ) {

        serialFound3 = true;
        profileConfiguration.serial.insert( item->text( 0 ), item->text( 1 ) );
      } else if ( item->text( 0 ) == "serial4" ) {

        serialFound4 = true;
        profileConfiguration.serial.insert( item->text( 0 ), item->text( 1 ) );
      }
    }

    if ( !serialFound1 && serialFound2 && serialFound3 && serialFound4 ) {

      profileConfiguration.serial.insert( "serial1", "dummy" );
    } else if ( serialFound1 && !serialFound2 && serialFound3 && serialFound4 ) {

      profileConfiguration.serial.insert( "serial2", "dummy" );
    } else if ( serialFound1 && serialFound2 && !serialFound3 && serialFound4 ) {

      profileConfiguration.serial.insert( "serial3", "disabled" );
    } else if ( serialFound1 && serialFound2 && serialFound3 && !serialFound4 ) {

      profileConfiguration.serial.insert( "serial4", "disabled" );
    } else if ( serialFound1 && !serialFound2 && !serialFound3 && !serialFound4 ) {

      profileConfiguration.serial.insert( "serial2", "dummy" );
      profileConfiguration.serial.insert( "serial3", "disabled" );
      profileConfiguration.serial.insert( "serial4", "disabled" );
    } else if ( serialFound1 && serialFound2 && !serialFound3 && !serialFound4 ) {

      profileConfiguration.serial.insert( "serial3", "disabled" );
      profileConfiguration.serial.insert( "serial4", "disabled" );
    } else if ( !serialFound1 && !serialFound2 && serialFound3 && serialFound4 ) {

      profileConfiguration.serial.insert( "serial1", "dummy" );
      profileConfiguration.serial.insert( "serial2", "dummy" );
    } else if ( !serialFound1 && !serialFound2 && !serialFound3 && serialFound4 ) {

      profileConfiguration.serial.insert( "serial1", "dummy" );
      profileConfiguration.serial.insert( "serial2", "dummy" );
      profileConfiguration.serial.insert( "serial3", "disbaled" );
    } else if ( !serialFound1 && !serialFound2 && !serialFound3 && !serialFound4 ) {

      profileConfiguration.serial.insert( "serial1", "dummy" );
      profileConfiguration.serial.insert( "serial2", "dummy" );
      profileConfiguration.serial.insert( "serial3", "disbaled" );
      profileConfiguration.serial.insert( "serial4", "disbaled" );
    } else if ( !serialFound1 && serialFound2 && !serialFound3 && !serialFound4 ) {

      profileConfiguration.serial.insert( "serial1", "dummy" );
      profileConfiguration.serial.insert( "serial3", "disbaled" );
      profileConfiguration.serial.insert( "serial4", "disabled" );
    } else if ( !serialFound1 && serialFound2 && serialFound3 && !serialFound4 ) {

      profileConfiguration.serial.insert( "serial1", "dummy" );
      profileConfiguration.serial.insert( "serial4", "disabled" );
    } else if ( serialFound1 && !serialFound2 && serialFound3 && !serialFound4 ) {

      profileConfiguration.serial.insert( "serial2", "dummy" );
      profileConfiguration.serial.insert( "serial4", "disabled" );
    } else if ( serialFound1 && !serialFound2 && !serialFound3 && serialFound4 ) {

      profileConfiguration.serial.insert( "serial2", "dummy" );
      profileConfiguration.serial.insert( "serial3", "disabled" );
    } else if ( !serialFound1 && serialFound2 && !serialFound3 && serialFound4 ) {

      profileConfiguration.serial.insert( "serial1", "dummy" );
      profileConfiguration.serial.insert( "serial3", "disabled" );
    } else if ( !serialFound1 && !serialFound2 && serialFound3 && !serialFound4 ) {

      profileConfiguration.serial.insert( "serial1", "dummy" );
      profileConfiguration.serial.insert( "serial2", "dummy" );
      profileConfiguration.serial.insert( "serial4", "disbaled" );
    }

    profileConfiguration.ipx = QVariant( checkBoxIPX->isChecked() ).toString();

    // DOS page
    profileConfiguration.dosbox.insert( "language", lineEditLanguage->text() );
    profileConfiguration.dosbox.insert( "machine", comboBoxMachine->currentText() );
    profileConfiguration.dosbox.insert( "captures", comboBoxCaptures->currentText() );
    profileConfiguration.dosbox.insert( "memsize", comboBoxMemsize->currentText() );

    profileConfiguration.dos.insert( "xms", checkBoxXMS->isChecked() );
    profileConfiguration.dos.insert( "ems", checkBoxEMS->isChecked() );
    profileConfiguration.dos.insert( "umb", checkBoxUMB->isChecked() );
    profileConfiguration.dos.insert( "keyboardlayout", comboBoxKeyboardLayout->currentText() );

    profileConfiguration.joystick.insert( "timed", checkBoxTimed->isChecked() );
    profileConfiguration.joystick.insert( "autofire", checkBoxAutofire->isChecked() );
    profileConfiguration.joystick.insert( "swap34", checkBoxSwap34->isChecked() );
    profileConfiguration.joystick.insert( "buttonwrap", checkBoxButtonWrap->isChecked() );
    profileConfiguration.joystick.insert( "joysticktype", comboBoxJoystickType->currentText() );

    qApp->processEvents();

    DBoxFE::configBaseInstance()->writeConfiguration( profFile, profileConfiguration );

    QApplication::restoreOverrideCursor();

    QDialog::accept();
  }

  void ProfileSettings::setDefaultConfiguration() {

    int messageResult = QMessageBox::question( this, tr( "DBoxFE" ), tr( "Are you sure that you would like to use\nthe default preferences for this game\nprofile?" ), QMessageBox::Yes, QMessageBox::No );

    switch ( messageResult ) {

      case QMessageBox::Yes:

        profileConfiguration.clear();
        profileConfiguration = DBoxFE::configBaseInstance()->readConfiguration( QString::fromUtf8( ":/default/default.conf" ) );

        if ( !profileConfiguration.isEmpty() ) {

          loadConfiguration();
        }

        break;
    }
  }

  void ProfileSettings::loadConfiguration() {

    QApplication::setOverrideCursor( Qt::WaitCursor );

    qApp->processEvents();

    profileConfiguration.clear();
    profileConfiguration = DBoxFE::configBaseInstance()->readConfiguration( profFile );

    if ( profileConfiguration.isEmpty() ) {

      profileConfiguration = DBoxFE::configBaseInstance()->readConfiguration( QString::fromUtf8( ":/default/default.conf" ) );
    }

    int comboBoxIndex = 0;

    qApp->processEvents();

    // Graphic  page
    checkBoxSDLFullScreen->setChecked( profileConfiguration.sdl.value( "fullscreen" ).toBool() );
    checkBoxSDLFullDouble->setChecked( profileConfiguration.sdl.value( "fulldouble" ).toBool() );
    checkBoxSDLWaitOnError->setChecked( profileConfiguration.sdl.value( "waitonerror" ).toBool() );
    checkBoxSDLAutolock->setChecked( profileConfiguration.sdl.value( "autolock" ).toBool() );
    checkBoxSDLUseScanCode->setChecked( profileConfiguration.sdl.value( "usescancodes" ).toBool() );
    comboBoxIndex = comboBoxSDLOutout->findText( profileConfiguration.sdl.value( "output" ).toString(), Qt::MatchExactly );
    comboBoxSDLOutout->setCurrentIndex( comboBoxIndex );

    comboBoxIndex = comboBoxSDLFocusUnfocus->findText( profileConfiguration.sdl.value( "priority" ).toString(), Qt::MatchExactly );

    if ( comboBoxIndex < 0 ) {

      QString priority = QString( "" );
      priority = profileConfiguration.sdl.value( "priority" ).toString();

      if ( priority.isNull() || priority.isEmpty() ) {
        priority = "\"normal,normal\"";
      }

      if ( priority.startsWith( "\"" ) && priority.endsWith( "\"" ) ) {

        priority = priority.replace( "\"", "" );
      }

      comboBoxIndex = comboBoxSDLFocusUnfocus->findText( priority, Qt::MatchExactly );
    }

    comboBoxSDLFocusUnfocus->setCurrentIndex( comboBoxIndex );

    comboBoxIndex = comboBoxSDLWindowWightHigh->findText( profileConfiguration.sdl.value( "windowresolution" ).toString(), Qt::MatchExactly );
    comboBoxSDLWindowWightHigh->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxSDLFullWightHigh->findText( profileConfiguration.sdl.value( "fullresolution" ).toString(), Qt::MatchExactly );
    comboBoxSDLFullWightHigh->setCurrentIndex( comboBoxIndex );
    lcdSDLSensitivity->display( profileConfiguration.sdl.value( "sensitivity" ).toInt() );

    comboBoxIndex = comboBoxRenderScaler->findText( profileConfiguration.render.value( "scaler" ).toString(), Qt::MatchExactly );
    comboBoxRenderScaler->setCurrentIndex( comboBoxIndex );
    lcdRenderFrameScip->display( profileConfiguration.render.value( "frameskip" ).toInt() );
    checkBoxRenderAspect->setChecked( profileConfiguration.render.value( "aspect" ).toBool() );

    comboBoxIndex = comboBoxCPUCore->findText( profileConfiguration.cpu.value( "core" ).toString(), Qt::MatchExactly );
    comboBoxCPUCore->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxCPUCycleUp->findText( profileConfiguration.cpu.value( "cycleup" ).toString(), Qt::MatchExactly );
    comboBoxCPUCycleUp->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxCPUCycles->findText( profileConfiguration.cpu.value( "cycles" ).toString(), Qt::MatchExactly );
    comboBoxCPUCycles->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxCPUCycleDown->findText( profileConfiguration.cpu.value( "cycledown" ).toString(), Qt::MatchExactly );
    comboBoxCPUCycleDown->setCurrentIndex( comboBoxIndex );

    // Sound page
    comboBoxIndex = comboBoxMixerRate->findText( profileConfiguration.mixer.value( "rate" ).toString(), Qt::MatchExactly );
    comboBoxMixerRate->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxMixerBlockSize->findText( profileConfiguration.mixer.value( "blocksize" ).toString(), Qt::MatchExactly );
    comboBoxMixerBlockSize->setCurrentIndex( comboBoxIndex );
    spinnBoxPrebuffer->setValue( profileConfiguration.mixer.value( "prebuffer" ).toInt() );
    checkBoxMixerNoSound->setChecked( profileConfiguration.mixer.value( "nosound" ).toBool() );

    comboBoxIndex = comboBoxSBType->findText( profileConfiguration.sblaster.value( "sbtype" ).toString(), Qt::MatchExactly );
    comboBoxSBType->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxSBBase->findText( profileConfiguration.sblaster.value( "sbbase" ).toString(), Qt::MatchExactly );
    comboBoxSBBase->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxSBIRQ->findText( profileConfiguration.sblaster.value( "irq" ).toString(), Qt::MatchExactly );
    comboBoxSBIRQ->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxSBDMA->findText( profileConfiguration.sblaster.value( "dma" ).toString(), Qt::MatchExactly );
    comboBoxSBDMA->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxSBOplMode->findText( profileConfiguration.sblaster.value( "oplmode" ).toString(), Qt::MatchExactly );
    comboBoxSBOplMode->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxSBHDMA->findText( profileConfiguration.sblaster.value( "hdma" ).toString(), Qt::MatchExactly );
    comboBoxSBHDMA->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxSBOPLRate->findText( profileConfiguration.sblaster.value( "oplrate" ).toString(), Qt::MatchExactly );
    comboBoxSBOPLRate->setCurrentIndex( comboBoxIndex );
    checkBoxSBMixer->setChecked( profileConfiguration.sblaster.value( "mixer" ).toBool() );

    checkBoxGUS->setChecked( profileConfiguration.gus.value( "gus" ).toBool() );
    comboBoxIndex = comboBoxGUSRate->findText( profileConfiguration.gus.value( "gusrate" ).toString(), Qt::MatchExactly );
    comboBoxGUSRate->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxGUSBase->findText( profileConfiguration.gus.value( "gusbase" ).toString(), Qt::MatchExactly );
    comboBoxGUSBase->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxGUSIrq_1->findText( profileConfiguration.gus.value( "irq1" ).toString(), Qt::MatchExactly );
    comboBoxGUSIrq_1->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxGUSIrq_2->findText( profileConfiguration.gus.value( "irq2" ).toString(), Qt::MatchExactly );
    comboBoxGUSIrq_2->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxGUSDMA_1->findText( profileConfiguration.gus.value( "dma1" ).toString(), Qt::MatchExactly );
    comboBoxGUSDMA_1->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxGUSDMA_2->findText( profileConfiguration.gus.value( "dma2" ).toString(), Qt::MatchExactly );
    comboBoxGUSDMA_2->setCurrentIndex( comboBoxIndex );
    lineEditGUSUltraDir->setText( profileConfiguration.gus.value( "ultradir" ).toString() );

    comboBoxIndex = comboBoxSpeaker->findText( profileConfiguration.speaker.value( "pcspeaker" ).toString(), Qt::MatchExactly );
    comboBoxSpeaker->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxSpeakerRate->findText( profileConfiguration.speaker.value( "pcrate" ).toString(), Qt::MatchExactly );
    comboBoxSpeakerRate->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxSpeakerTandy->findText( profileConfiguration.speaker.value( "tandy" ).toString(), Qt::MatchExactly );
    comboBoxSpeakerTandy->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxSpeakerTandyRate->findText( profileConfiguration.speaker.value( "tandyrate" ).toString(), Qt::MatchExactly );
    comboBoxSpeakerTandyRate->setCurrentIndex( comboBoxIndex );
    checkBoxDisney->setChecked( profileConfiguration.speaker.value( "disney" ).toBool() );

    comboBoxIndex = comboBoxMDIMPU->findText( profileConfiguration.mdi.value( "mpu401" ).toString(), Qt::MatchExactly );
    comboBoxMDIMPU->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxMDIDevice->findText( profileConfiguration.mdi.value( "device" ).toString(), Qt::MatchExactly );
    comboBoxMDIDevice->setCurrentIndex( comboBoxIndex );
    lineEditMDIConfig->setText( profileConfiguration.mdi.value( "config" ).toString() );

    // Autoexec page
    treeWidgetAutoexec->clear();
    QTreeWidgetItem *item = new QTreeWidgetItem();
    foreach( QString autoexec, profileConfiguration.autoexec ) {

      qApp->processEvents();

      if( autoexec.toLower().startsWith( "mount" ) ) {

        QStringList mountList = autoexec.split( " " );
        item->setText( 0, mountList.value( 1 ) );
        item->setText( 1, mountList.value( 2 ) );
        item->setText( 2, mountList.value( mountList.size() - 1 ) );
        item->setText( 5, autoexec );

      } else if( autoexec.toLower().contains( "bat" ) || autoexec.toLower().contains( "exe" ) || autoexec.toLower().contains( "com" )) {
        item->setText( 4, autoexec );

      } else if( autoexec.toLower().contains( ":" ) ) {

        QStringList mountList = autoexec.split( ":" );
        if( mountList.count() >= 1 ) {

          if( mountList.value( 0 ).startsWith( autoexec.left( 0 ) ) ) {
            item->setText( 3, "true" );
          } else {
            item->setText( 3, "false" );
          }
        }        
      }
    }
    treeWidgetAutoexec->addTopLevelItem( item );

    // Inernet page
    treeWidgetSerial->clear();
    QMap< QString, QVariant >::const_iterator serial = profileConfiguration.serial.constBegin();

    while ( serial != profileConfiguration.serial.constEnd() ) {

      qApp->processEvents();

      QTreeWidgetItem *item = new QTreeWidgetItem( treeWidgetSerial );
      item->setText( 0, serial.key() );
      item->setText( 1, serial.value().toString() );

      ++serial;
    }

    checkBoxIPX->setChecked( profileConfiguration.ipx == "true" ? true : false );

    // DOS page
    lineEditLanguage->setText( profileConfiguration.dosbox.value( "language" ).toString() );
    comboBoxIndex = comboBoxMachine->findText( profileConfiguration.dosbox.value( "machine" ).toString(), Qt::MatchExactly );
    comboBoxMachine->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxCaptures->findText( profileConfiguration.dosbox.value( "captures" ).toString(), Qt::MatchExactly );
    comboBoxCaptures->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxMemsize->findText( profileConfiguration.dosbox.value( "memsize" ).toString(), Qt::MatchExactly );
    comboBoxMemsize->setCurrentIndex( comboBoxIndex );

    checkBoxXMS->setChecked( profileConfiguration.dos.value( "xms" ).toBool() );
    checkBoxEMS->setChecked( profileConfiguration.dos.value( "ems" ).toBool() );
    checkBoxUMB->setChecked( profileConfiguration.dos.value( "umb" ).toBool() );
    comboBoxIndex = comboBoxKeyboardLayout->findText( profileConfiguration.dos.value( "keyboardlayout" ).toString(), Qt::MatchExactly );
    comboBoxKeyboardLayout->setCurrentIndex( comboBoxIndex );

    checkBoxTimed->setChecked( profileConfiguration.joystick.value( "timed" ).toBool() );
    checkBoxAutofire->setChecked( profileConfiguration.joystick.value( "autofire" ).toBool() );
    checkBoxSwap34->setChecked( profileConfiguration.joystick.value( "swap34" ).toBool() );
    checkBoxButtonWrap->setChecked( profileConfiguration.joystick.value( "buttonwrap" ).toBool() );
    comboBoxIndex = comboBoxJoystickType->findText( profileConfiguration.joystick.value( "joysticktype" ).toString(), Qt::MatchExactly );
    comboBoxJoystickType->setCurrentIndex( comboBoxIndex );

    QApplication::restoreOverrideCursor();
  }

  void ProfileSettings::closeWidget() {

    profileConfiguration.clear();
    reject();
  }
}
