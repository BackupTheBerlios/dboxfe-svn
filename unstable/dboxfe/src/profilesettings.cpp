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
    profileConfiguration.mixer.insert( "rate", spinnBoxPrebuffer->value() );
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
    for ( int a = 0; a < lwAutoexec->count(); a++ ) {

      qApp->processEvents();

      QListWidgetItem *item = lwAutoexec->item( a );
      profileConfiguration.autoexec.append( item->text() );
    }

    // Inernet page
    for ( int b = 0;  b < twSerial->topLevelItemCount(); b ++ ) {

      qApp->processEvents();

      QTreeWidgetItem *item = twSerial->topLevelItem( b );
      profileConfiguration.serial.insert( item->text( 0 ), item->text( 1 ) );
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

    DBoxFE::configBaseInstance()->writeConfiguration( profFile, profileConfiguration );

    QDialog::accept();
  }

  void ProfileSettings::setDefaultConfiguration() {

    profileConfiguration.clear();
    profileConfiguration = DBoxFE::configBaseInstance()->readConfiguration( QString::fromUtf8( ":/default/default.conf" ) );

    if ( !profileConfiguration.isEmpty() ) {

      // intial default settings

    }
  }

  void ProfileSettings::loadConfiguration() {

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
    checkBoxSDLUseScanCode->setChecked( profileConfiguration.sdl.value( "usescancodes"  ).toBool() );
    comboBoxIndex = comboBoxSDLOutout->findText( profileConfiguration.sdl.value( "output" ).toString(), Qt::MatchExactly );
    comboBoxSDLOutout->setCurrentIndex( comboBoxIndex );
    
    comboBoxIndex = comboBoxSDLFocusUnfocus->findText( profileConfiguration.sdl.value( "priority" ).toString(), Qt::MatchExactly );
    if( comboBoxIndex < 0 ) {

      QString priority = "normal,normal";
      priority = profileConfiguration.sdl.value( "priority" ).toString();
      if( priority.startsWith( "\"" ) && priority.endsWith( "\"" ) ) {

        priority = priority.replace( "\"", "" );
      }
      comboBoxIndex = comboBoxSDLFocusUnfocus->findText( priority, Qt::MatchExactly );
    }
    comboBoxSDLFocusUnfocus->setCurrentIndex( comboBoxIndex );

    comboBoxIndex = comboBoxSDLWindowWightHigh->findText( profileConfiguration.sdl.value( "windowresolution" ).toString(), Qt::MatchExactly );
    comboBoxSDLWindowWightHigh->setCurrentIndex( comboBoxIndex );
    comboBoxIndex = comboBoxSDLFullWightHigh->findText( profileConfiguration.sdl.value( "fullresolution" ).toString(), Qt::MatchExactly );
    comboBoxSDLFullWightHigh->setCurrentIndex( comboBoxIndex );
    lcdSDLSensitivity->display( profileConfiguration.sdl.value( "sensitivity").toInt() );

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
    spinnBoxPrebuffer->setValue( profileConfiguration.mixer.value( "rate" ).toInt() );    
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

    //profileConfiguration.mdi.value( "mpu401", comboBoxMDIMPU->currentText() );
    //profileConfiguration.mdi.value( "device", comboBoxMDIDevice->currentText() );
    //profileConfiguration.mdi.value( "config", lineEditMDIConfig->text() );

    // Autoexec page
    foreach( QString autoexec, profileConfiguration.autoexec ) {

      qApp->processEvents();

      QListWidgetItem *item = new QListWidgetItem( lwAutoexec );
      item->setText( autoexec );
    }

    // Inernet page
    QMap< QString, QVariant >::const_iterator serial = profileConfiguration.serial.constBegin();
    while( serial != profileConfiguration.serial.constEnd() ) {

      qApp->processEvents();

      QTreeWidgetItem *item = new QTreeWidgetItem( twSerial );
      item->setText( 0, serial.key() );
      item->setText( 1, serial.value().toString() );

      ++serial;
    }

    //profileConfiguration.ipx.value( "ipx", checkBoxIPX->setChecked(  ) );

    //// DOS page
    //profileConfiguration.dosbox.value( "language", lineEditLanguage->text() );
    //profileConfiguration.dosbox.value( "machine", comboBoxMachine->currentText() );
    //profileConfiguration.dosbox.value( "captures", comboBoxCaptures->currentText() );
    //profileConfiguration.dosbox.value( "memsize", comboBoxMemsize->currentText() );

    //profileConfiguration.dos.value( "xms", checkBoxXMS->setChecked(  ) );
    //profileConfiguration.dos.value( "ems", checkBoxEMS->setChecked(  ) );
    //profileConfiguration.dos.value( "umb", checkBoxUMB->setChecked(  ) );
    //profileConfiguration.dos.value( "keyboardlayout", comboBoxKeyboardLayout->currentText() );

    //profileConfiguration.joystick.value( "timed", checkBoxTimed->setChecked(  ) );
    //profileConfiguration.joystick.value( "autofire", checkBoxAutofire->setChecked(  ) );
    //profileConfiguration.joystick.value( "swap34", checkBoxSwap34->setChecked(  ) );
    //profileConfiguration.joystick.value( "buttonwrap", checkBoxButtonWrap->setChecked(  ) );
    //profileConfiguration.joystick.value( "joysticktype", comboBoxJoystickType->currentText() );
  }

  void ProfileSettings::closeWidget() {

    profileConfiguration.clear();
    reject();
  }
}
