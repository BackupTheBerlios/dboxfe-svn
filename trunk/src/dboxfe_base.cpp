/*
*   Copyright (C) 2004/05/06 by Alexander Saal <alex.saal@gmx.de>
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

#include "dboxfe.h"
#include "dboxfe_base.h"
#include "dboxfe_profilewizard.h"
#include "dboxfe_gamesettings.h"
#include "XMLPreferences.h"

#include <QtCore>
#include <QtGui>
#include <QtXml>

DB_BASE::DB_BASE()
{}

QString DB_BASE::applicationDir()
{
    return QCoreApplication::applicationDirPath();
}

void DB_BASE::readConf( const QString &dbconf, DBoxFE* dbfe )
{
    QSettings * getConf = new QSettings( dbconf, QSettings::IniFormat );
    getConf->beginGroup( "sdl" );
    dbfe->chkBoxFullScreen->setChecked( getConf->value( "fullscreen" ).toBool() );
    dbfe->chkBoxFullDouble->setChecked( getConf->value( "fulldouble" ).toBool() );
    int fullresolution = dbfe->cbxFullWightHigh->findText( getConf->value( "fullresolution" ).toString() );
    dbfe->cbxFullWightHigh->setCurrentIndex( fullresolution );
    int windowresolution = dbfe->cbxWindowWightHigh->findText( getConf->value( "windowresolution" ).toString() );
    dbfe->cbxWindowWightHigh->setCurrentIndex( windowresolution );
    int priority = dbfe->cbxFocusUnfocus->findText( getConf->value( "priority" ).toString() );
    dbfe->cbxFocusUnfocus->setCurrentIndex( priority );
    int output = dbfe->cbxOutout->findText( getConf->value( "output" ).toString() );
    dbfe->cbxOutout->setCurrentIndex( output );
    dbfe->chkBoxAutolock->setChecked( getConf->value( "autolock" ).toBool() );
    dbfe->chkBoxWaitOnError->setChecked( getConf->value( "waitonerror" ).toBool() );
    dbfe->chkBoxUseScanCode->setChecked( getConf->value( "usescancodes" ).toBool() );
    dbfe->lcdSV->display( getConf->value( "sensitivity" ).toInt() );
    dbfe->sliderSV->setValue( getConf->value( "sensitivity" ).toInt() );
    /*settConf->setValue( "mapperfile", "mapper.txt" );*/
    getConf->endGroup();

    // DOSBox settings
    getConf->beginGroup( "dosbox" );
    dbfe->LELanguage->setText( getConf->value( "language" ).toString() );
    int machine = dbfe->cbxMachine->findText( getConf->value( "machine" ).toString() );
    dbfe->cbxMachine->setCurrentIndex( machine );
    int memsize = dbfe->cbxMemsize->findText( getConf->value( "memsize" ).toString() );
    dbfe->cbxMemsize->setCurrentIndex( memsize );
    int captures = dbfe->cbxCaptures->findText( getConf->value( "captures" ).toString() );
    dbfe->cbxCaptures->setCurrentIndex( captures );
    getConf->endGroup();

    // Render settings
    getConf->beginGroup( "render" );
    dbfe->lcdFS->display( getConf->value( "frameskip" ).toInt() );
    dbfe->sliderFS->setValue( getConf->value( "frameskip" ).toInt() );
    int scaler = dbfe->cbxScaler->findText( getConf->value( "scaler" ).toString() );
    dbfe->cbxScaler->setCurrentIndex( scaler );
    dbfe->chkBoxAspect->setChecked( getConf->value( "aspect" ).toBool() );
    getConf->endGroup();

    // CPU settings
    getConf->beginGroup( "cpu" );
    int core = dbfe->cbxCPUCore->findText( getConf->value( "core" ).toString() );
    dbfe->cbxCPUCore->setCurrentIndex( core );
    int cycles = dbfe->cbxCPUCycles->findText( getConf->value( "cycles" ).toString() );
    dbfe->cbxCPUCycles->setCurrentIndex( cycles );
    int cycleup = dbfe->cbxCPUCycleUp->findText( getConf->value( "cycleup" ).toString() );
    dbfe->cbxCPUCycleUp->setCurrentIndex( cycleup );
    int cycledown = dbfe->cbxCPUCycleDown->findText( getConf->value( "cycledown" ).toString() );
    dbfe->cbxCPUCycleDown->setCurrentIndex( cycledown );
    getConf->endGroup();

    // Mixer settings
    getConf->beginGroup( "mixer" );
    dbfe->chkBoxMixerNoSound->setChecked( getConf->value( "nosound" ).toBool() );
    int rate = dbfe->cbxMixerRate->findText( getConf->value( "rate" ).toString() );
    dbfe->cbxMixerRate->setCurrentIndex( rate );
    int blocksize = dbfe->cbxMixerBlockSize->findText( getConf->value( "blocksize" ).toString() );
    dbfe->cbxMixerBlockSize->setCurrentIndex( blocksize );
    dbfe->spBoxPrebuffer->setValue( getConf->value( "prebuffer" ).toInt() );
    getConf->endGroup();

    // Mdi settings
    getConf->beginGroup( "midi" );
    int mpu = dbfe->cbxMDIMPU->findText( getConf->value( "mpu401" ).toString() );
    dbfe->cbxMDIMPU->setCurrentIndex( mpu );
    int device = dbfe->cbxMDIDevice->findText( getConf->value( "device" ).toString() );
    dbfe->cbxMDIDevice->setCurrentIndex( device );
    dbfe->LEMDIConfig->setText( getConf->value( "config" ).toString() );
    getConf->endGroup();

    // Soundblaster settings
    getConf->beginGroup( "sblaster" );
    int sbtype = dbfe->cbxSBType->findText( getConf->value( "sbtype" ).toString() );
    dbfe->cbxSBType->setCurrentIndex( sbtype );
    int sbbase = dbfe->cbxSBBase->findText( getConf->value( "sbbase" ).toString() );
    dbfe->cbxSBBase->setCurrentIndex( sbbase );
    int irq = dbfe->cbxSBIRQ->findText( getConf->value( "irq" ).toString() );
    dbfe->cbxSBIRQ->setCurrentIndex( irq );
    int dma = dbfe->cbxSBDMA->findText( getConf->value( "dma" ).toString() );
    dbfe->cbxSBDMA->setCurrentIndex( dma );
    int hdma = dbfe->cbxSBHDMA->findText( getConf->value( "hdma" ).toString() );
    dbfe->cbxSBHDMA->setCurrentIndex( hdma );
    int oplrate = dbfe->cbxSBOPLRate->findText( getConf->value( "oplrate" ).toString() );
    dbfe->cbxSBOPLRate->setCurrentIndex( oplrate );
    int oplmode = dbfe->cbxSBOplMode->findText( getConf->value( "oplmode" ).toString() );
    dbfe->cbxSBOplMode->setCurrentIndex( oplmode );
    dbfe->chkBoxSBMixer->setChecked( getConf->value( "mixer" ).toBool() );
    getConf->endGroup();

    // GUS settings
    getConf->beginGroup( "gus" );
    dbfe->chkBoxGUS->setChecked( getConf->value( "gus" ).toBool() );
    int gusrate = dbfe->cbxGUSRate->findText( getConf->value( "gusrate" ).toString() );
    dbfe->cbxGUSRate->setCurrentIndex( gusrate );
    int gusbase = dbfe->cbxGUSBase->findText( getConf->value( "gusbase" ).toString() );
    dbfe->cbxGUSBase->setCurrentIndex( gusbase );
    int irq1 = dbfe->cbxGUSIrq_1->findText( getConf->value( "irq1" ).toString() );
    dbfe->cbxGUSIrq_1->setCurrentIndex( irq1 );
    int irq2 = dbfe->cbxGUSIrq_2->findText( getConf->value( "irq2" ).toString() );
    dbfe->cbxGUSIrq_2->setCurrentIndex( irq2 );
    int dma1 = dbfe->cbxGUSDMA_1->findText( getConf->value( "dma1" ).toString() );
    dbfe->cbxGUSDMA_1->setCurrentIndex( dma1 );
    int dma2 = dbfe->cbxGUSDMA_2->findText( getConf->value( "dma2" ).toString() );
    dbfe->cbxGUSDMA_2->setCurrentIndex( dma2 );
    dbfe->LEGUSUltraDir->setText( getConf->value( "ultradir" ).toString() );
    getConf->endGroup();

    // PC Speaker settings
    getConf->beginGroup( "speaker" );
    if ( getConf->value( "pcspeaker" ).toString() == "true" )
        dbfe->cbxSpeaker->setCurrentIndex( 0 );
    else
        dbfe->cbxSpeaker->setCurrentIndex( 1 );

    int pcrate = dbfe->cbxSpeakerRate->findText( getConf->value( "pcrate" ).toString() );
    dbfe->cbxSpeakerRate->setCurrentIndex( pcrate );
    int tandy = dbfe->cbxSpeakerTandy->findText( getConf->value( "tandy" ).toString() );
    dbfe->cbxSpeakerTandy->setCurrentIndex( tandy );
    int tandyrate = dbfe->cbxSpeakerTandyRate->findText( getConf->value( "tandyrate" ).toString() );
    dbfe->cbxSpeakerTandyRate->setCurrentIndex( tandyrate );
    dbfe->chkBoxDisney->setChecked( getConf->value( "disney" ).toBool() );
    getConf->endGroup();

    // BIOS settings
    getConf->beginGroup( "bios" );
    int joysticktype = dbfe->cbxJoystickType->findText( getConf->value( "joysticktype" ).toString() );
    dbfe->cbxJoystickType->setCurrentIndex( joysticktype );
    getConf->endGroup();

    // Serial settings
    getConf->beginGroup( "serial" );
    dbfe->twSerial->clear();
    QTreeWidgetItem *serial1 = new QTreeWidgetItem( dbfe->twSerial );
    serial1->setText( 0, "serial1" );
    serial1->setText( 1, getConf->value( "serial1" ).toString() );
    QTreeWidgetItem *serial2 = new QTreeWidgetItem( dbfe->twSerial );
    serial2->setText( 0, "serial2" );
    serial2->setText( 1, getConf->value( "serial2" ).toString() );
    QTreeWidgetItem *serial3 = new QTreeWidgetItem( dbfe->twSerial );
    serial3->setText( 0, "serial3" );
    serial3->setText( 1, getConf->value( "serial3" ).toString() );
    QTreeWidgetItem *serial4 = new QTreeWidgetItem( dbfe->twSerial );
    serial4->setText( 0, "serial4" );
    serial4->setText( 1, getConf->value( "serial4" ).toString() );
    getConf->endGroup();

    // DOS settings
    getConf->beginGroup( "dos" );
    dbfe->chkBoxXMS->setChecked( getConf->value( "xms" ).toBool() );
    dbfe->chkBoxEMS->setChecked( getConf->value( "ems" ).toBool() );
    int umb = dbfe->cbxUMB->findText( getConf->value( "umb" ).toString() );
    dbfe->cbxUMB->setCurrentIndex( umb );
    getConf->endGroup();

    // IPX settings
    getConf->beginGroup( "ipx" );
    dbfe->chkBoxIPX->setChecked( getConf->value( "ipx" ).toBool() );
    getConf->endGroup();


    // Autoexec settings
    QFile f( dbconf );

    if ( !f.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        delete getConf;
        return ;
    }

    QTextStream in( &f );
    QString line;

    dbfe->lwAutoexec->clear();

    while ( !in.atEnd() ) {
        line = in.readLine();
        if ( line == "[autoexec]" ) {
            while ( !in.atEnd() ) {
                line = in.readLine();
                QListWidgetItem *autoexec = new QListWidgetItem( dbfe->lwAutoexec );
                autoexec->setText( line );

				// if comes after section [autoexec] a another section, then exit method
				if( line != "[autoexec]" ) {
					f.close();
					delete getConf;
					return;
				}					
            }
        }
    }

    f.close();
    delete getConf;
}

void DB_BASE::saveConf( const QString &dbconf, DBoxFE* dbfe )
{
    QSettings * settConf = new QSettings( dbconf, QSettings::IniFormat );
    // SDL settings
    settConf->beginGroup( "sdl" );
    settConf->setValue( "fullscreen", dbfe->chkBoxFullScreen->isChecked() );
    settConf->setValue( "fulldouble", dbfe->chkBoxFullDouble->isChecked() );

    settConf->setValue( "fullresolution", dbfe->cbxFullWightHigh->currentText() );
    settConf->setValue( "windowresolution", dbfe->cbxWindowWightHigh->currentText() );

    settConf->setValue( "output", dbfe->cbxOutout->currentText() );
    settConf->setValue( "autolock", dbfe->chkBoxAutolock->isChecked() );
    settConf->setValue( "sensitivity", dbfe->lcdSV->intValue() );
    settConf->setValue( "waitonerror", dbfe->chkBoxWaitOnError->isChecked() );
    settConf->setValue( "priority", dbfe->cbxFocusUnfocus->currentText() );
    settConf->setValue( "mapperfile", "mapper.txt" );
    settConf->setValue( "usescancodes", dbfe->chkBoxUseScanCode->isChecked() );
    settConf->endGroup();

    // DOSBox settings
    settConf->beginGroup( "dosbox" );
    settConf->setValue( "language", dbfe->LELanguage->text() );
    settConf->setValue( "machine", dbfe->cbxMachine->currentText() );
    settConf->setValue( "memsize", dbfe->cbxMemsize->currentText() );
    settConf->setValue( "captures", dbfe->cbxCaptures->currentText() );
    settConf->endGroup();

    // Render settings
    settConf->beginGroup( "render" );
    settConf->setValue( "frameskip", dbfe->lcdFS->intValue() );
    settConf->setValue( "scaler", dbfe->cbxScaler->currentText() );
    settConf->setValue( "aspect", dbfe->chkBoxAspect->isChecked() );
    settConf->endGroup();

    // CPU settings
    settConf->beginGroup( "cpu" );
    settConf->setValue( "core", dbfe->cbxCPUCore->currentText() );
    settConf->setValue( "cycles", dbfe->cbxCPUCycles->currentText() );
    settConf->setValue( "cycleup", dbfe->cbxCPUCycleUp->currentText() );
    settConf->setValue( "cycledown", dbfe->cbxCPUCycleDown->currentText() );
    settConf->endGroup();

    // Mixer settings
    settConf->beginGroup( "mixer" );
    settConf->setValue( "nosound", dbfe->chkBoxMixerNoSound->isChecked() );
    settConf->setValue( "rate", dbfe->cbxMixerRate->currentText() );
    settConf->setValue( "blocksize", dbfe->cbxMixerBlockSize->currentText() );
    settConf->setValue( "prebuffer", dbfe->spBoxPrebuffer->value() );
    settConf->endGroup();

    // Mdi settings
    settConf->beginGroup( "midi" );
    settConf->setValue( "mpu401", dbfe->cbxMDIMPU->currentText() );
    settConf->setValue( "device", dbfe->cbxMDIDevice->currentText() );
    if ( !dbfe->LEMDIConfig->text().isEmpty() ) {
        settConf->setValue( "config", dbfe->LEMDIConfig->text() );
    } else {
        settConf->setValue( "config", "" );
    }
    settConf->endGroup();

    // Soundblaster settings
    settConf->beginGroup( "sblaster" );
    settConf->setValue( "sbtype", dbfe->cbxSBType->currentText() );
    settConf->setValue( "sbbase", dbfe->cbxSBBase->currentText() );
    settConf->setValue( "irq", dbfe->cbxSBIRQ->currentText() );
    settConf->setValue( "dma", dbfe->cbxSBDMA->currentText() );
    settConf->setValue( "hdma", dbfe->cbxSBHDMA->currentText() );
    settConf->setValue( "mixer", dbfe->chkBoxSBMixer->isChecked() );
    settConf->setValue( "oplrate", dbfe->cbxSBOPLRate->currentText() );
    settConf->setValue( "oplmode", dbfe->cbxSBOplMode->currentText() );
    settConf->endGroup();

    // GUS settings
    settConf->beginGroup( "gus" );
    settConf->setValue( "gus", dbfe->chkBoxGUS->isChecked() );
    settConf->setValue( "gusrate", dbfe->cbxGUSRate->currentText() );
    settConf->setValue( "gusbase", dbfe->cbxGUSBase->currentText() );
    settConf->setValue( "irq1", dbfe->cbxGUSIrq_1->currentText() );
    settConf->setValue( "irq2", dbfe->cbxGUSIrq_2->currentText() );
    settConf->setValue( "dma1", dbfe->cbxGUSDMA_1->currentText() );
    settConf->setValue( "dma2", dbfe->cbxGUSDMA_2->currentText() );
    settConf->setValue( "ultradir", dbfe->LEGUSUltraDir->text() );
    settConf->endGroup();

    // PC Speaker settings
    settConf->beginGroup( "speaker" );
    if ( dbfe->cbxSpeaker->currentText() == "on" )
        settConf->setValue( "pcspeaker", "true" );
    else
        settConf->setValue( "pcspeaker", "false" );

    settConf->setValue( "pcrate", dbfe->cbxSpeakerRate->currentText() );
    settConf->setValue( "tandy", dbfe->cbxSpeakerTandy->currentText() );
    settConf->setValue( "tandyrate", dbfe->cbxSpeakerTandyRate->currentText() );
    settConf->setValue( "disney", dbfe->chkBoxDisney->isChecked() );
    settConf->endGroup();

    // BIOS settings
    settConf->beginGroup( "bios" );
    settConf->setValue( "joysticktype", dbfe->cbxJoystickType->currentText() );
    settConf->endGroup();

    // Serial settings
    settConf->beginGroup( "serial" );
    for ( int i = 0; i < dbfe->twSerial->topLevelItemCount(); i++ ) {
        QTreeWidgetItem *item = dbfe->twSerial->topLevelItem( i );
        settConf->setValue( item->text( 0 ), item->text( 1 ) );
    }

    if ( dbfe->twSerial->topLevelItemCount() <= 0 ) {
        settConf->setValue( "serial1", "dummy" );
        settConf->setValue( "serial2", "dummy" );
        settConf->setValue( "serial3", "disabled" );
        settConf->setValue( "serial4", "disabled" );
    }
    settConf->endGroup();

    // DOS settings
    settConf->beginGroup( "dos" );
    settConf->setValue( "xms", dbfe->chkBoxXMS->isChecked() );
    settConf->setValue( "ems", dbfe->chkBoxEMS->isChecked() );
    settConf->setValue( "umb", dbfe->cbxUMB->currentText() );
    settConf->endGroup();

    // IPX settings
    settConf->beginGroup( "ipx" );
    settConf->setValue( "ipx", dbfe->chkBoxIPX->isChecked() );
    settConf->endGroup();

    settConf->sync();

    // Autoexec settings
    QFile f( dbconf );

    if ( !f.open( QFile::Append | QFile::WriteOnly ) ) {
        delete settConf;
        return ;
    }

    QTextStream t( &f );
    t << "\n[autoexec]\n";

    for ( int q = 0; q < dbfe->lwAutoexec->count(); q++ ) {
        t << dbfe->lwAutoexec->item( q )->text() << "\n";
    }

    t.flush();
    f.close();

    delete settConf;

}

void DB_BASE::defaultSettings( DBoxFE* dbfe )
{
    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [sdl]" );

    dbfe->chkBoxFullScreen->setChecked( false );
    dbfe->chkBoxFullDouble->setChecked( false );
    int fullresolution = dbfe->cbxFullWightHigh->findText( "original" );
    dbfe->cbxFullWightHigh->setCurrentIndex( fullresolution );

    int windowresolution = dbfe->cbxWindowWightHigh->findText( "original" );
    dbfe->cbxWindowWightHigh->setCurrentIndex( windowresolution );

    int priority = dbfe->cbxFocusUnfocus->findText( "higher,normal" );
    dbfe->cbxFocusUnfocus->setCurrentIndex( priority );

    int output = dbfe->cbxOutout->findText( "surface" );
    dbfe->cbxOutout->setCurrentIndex( output );

    dbfe->chkBoxAutolock->setChecked( true );
    dbfe->chkBoxWaitOnError->setChecked( true );
    dbfe->chkBoxUseScanCode->setChecked( true );
    dbfe->lcdSV->display( 100 );
    dbfe->sliderSV->setValue( 100 );

    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [dosbox]" );
    // DOSBox settings
    dbfe->LELanguage->setText( "" );

    int machine = dbfe->cbxMachine->findText( "vga" );
    dbfe->cbxMachine->setCurrentIndex( machine );

    int memsize = dbfe->cbxMemsize->findText( "16" );
    dbfe->cbxMemsize->setCurrentIndex( memsize );

    int captures = dbfe->cbxCaptures->findText( "capture" );
    dbfe->cbxCaptures->setCurrentIndex( captures );


    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [render]" );
    // Render settings
    dbfe->lcdFS->display( 0 );
    dbfe->sliderFS->setValue( 0 );

    int scaler = dbfe->cbxScaler->findText( "normal2x" );
    dbfe->cbxScaler->setCurrentIndex( scaler );

    dbfe->chkBoxAspect->setChecked( false );

    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [cpu]" );
    // CPU settings
    int core = dbfe->cbxCPUCore->findText( "normal" );
    dbfe->cbxCPUCore->setCurrentIndex( core );

    int cycles = dbfe->cbxCPUCycles->findText( "3000" );
    dbfe->cbxCPUCycles->setCurrentIndex( cycles );

    int cycleup = dbfe->cbxCPUCycleUp->findText( "500" );
    dbfe->cbxCPUCycleUp->setCurrentIndex( cycleup );

    int cycledown = dbfe->cbxCPUCycleDown->findText( "20" );
    dbfe->cbxCPUCycleDown->setCurrentIndex( cycledown );


    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [mixer]" );
    // Mixer settings
    dbfe->chkBoxMixerNoSound->setChecked( false );
    int rate = dbfe->cbxMixerRate->findText( "22050" );
    dbfe->cbxMixerRate->setCurrentIndex( rate );
    int blocksize = dbfe->cbxMixerBlockSize->findText( "2048" );
    dbfe->cbxMixerBlockSize->setCurrentIndex( blocksize );
    dbfe->spBoxPrebuffer->setValue( 10 );

    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [mdi]" );
    // Mdi settings
    int mpu = dbfe->cbxMDIMPU->findText( "intelligent" );
    dbfe->cbxMDIMPU->setCurrentIndex( mpu );

    int device = dbfe->cbxMDIDevice->findText( "default" );
    dbfe->cbxMDIDevice->setCurrentIndex( device );

    dbfe->LEMDIConfig->setText( "" );

    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [sblaster]" );
    // Soundblaster settings
    int sbtype = dbfe->cbxSBType->findText( "sb16" );
    dbfe->cbxSBType->setCurrentIndex( sbtype );
    int sbbase = dbfe->cbxSBBase->findText( "220" );
    dbfe->cbxSBBase->setCurrentIndex( sbbase );
    int irq = dbfe->cbxSBIRQ->findText( "7" );
    dbfe->cbxSBIRQ->setCurrentIndex( irq );
    int dma = dbfe->cbxSBDMA->findText( "1" );
    dbfe->cbxSBDMA->setCurrentIndex( dma );
    int hdma = dbfe->cbxSBHDMA->findText( "5" );
    dbfe->cbxSBHDMA->setCurrentIndex( hdma );
    int oplrate = dbfe->cbxSBOPLRate->findText( "22050" );
    dbfe->cbxSBOPLRate->setCurrentIndex( oplrate );
    int oplmode = dbfe->cbxSBOplMode->findText( "auto" );
    dbfe->cbxSBOplMode->setCurrentIndex( oplmode );

    dbfe->chkBoxSBMixer->setChecked( true );


    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [gus]" );
    // GUS settings
    dbfe->chkBoxGUS->setChecked( true );
    int gusrate = dbfe->cbxGUSRate->findText( "22050" );
    dbfe->cbxGUSRate->setCurrentIndex( gusrate );
    int gusbase = dbfe->cbxGUSBase->findText( "240" );
    dbfe->cbxGUSBase->setCurrentIndex( gusbase );
    int irq1 = dbfe->cbxGUSIrq_1->findText( "5" );
    dbfe->cbxGUSIrq_1->setCurrentIndex( irq1 );
    int irq2 = dbfe->cbxGUSIrq_2->findText( "5" );
    dbfe->cbxGUSIrq_2->setCurrentIndex( irq2 );
    int dma1 = dbfe->cbxGUSDMA_1->findText( "3" );
    dbfe->cbxGUSDMA_1->setCurrentIndex( dma1 );
    int dma2 = dbfe->cbxGUSDMA_2->findText( "3" );
    dbfe->cbxGUSDMA_2->setCurrentIndex( dma2 );
    dbfe->LEGUSUltraDir->setText( "C:\\ULTRASND" );


    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [speaker]" );
    // PC Speaker settings
    int pcspeaker = dbfe->cbxSpeaker->findText( "on" );
    dbfe->cbxSpeaker->setCurrentIndex( pcspeaker );
    int pcrate = dbfe->cbxSpeakerRate->findText( "22050" );
    dbfe->cbxSpeakerRate->setCurrentIndex( pcrate );
    int tandy = dbfe->cbxSpeakerTandy->findText( "auto" );
    dbfe->cbxSpeakerTandy->setCurrentIndex( tandy );
    int tandyrate = dbfe->cbxSpeakerTandyRate->findText( "22050" );
    dbfe->cbxSpeakerTandyRate->setCurrentIndex( tandyrate );
    dbfe->chkBoxDisney->setChecked( true );

    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [bios]" );
    // BIOS settings
    int joysticktype = dbfe->cbxJoystickType->findText( "2axis" );
    dbfe->cbxJoystickType->setCurrentIndex( joysticktype );

    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [serial]" );
    // Serial settings
    dbfe->twSerial->clear();
    QTreeWidgetItem *serial1 = new QTreeWidgetItem( dbfe->twSerial );
    serial1->setText( 0, "serial1" );
    serial1->setText( 1, "dummy" );
    QTreeWidgetItem *serial2 = new QTreeWidgetItem( dbfe->twSerial );
    serial2->setText( 0, "serial2" );
    serial2->setText( 1, "dummy" );
    QTreeWidgetItem *serial3 = new QTreeWidgetItem( dbfe->twSerial );
    serial3->setText( 0, "serial3" );
    serial3->setText( 1, "disabled" );
    QTreeWidgetItem *serial4 = new QTreeWidgetItem( dbfe->twSerial );
    serial4->setText( 0, "serial4" );
    serial4->setText( 1, "disabled" );

    qDebug() << QObject::tr( "Set dafault settings, based on dosbox default settings .... [dos]" );
    // DOS settings
    dbfe->chkBoxXMS->setChecked( true );
    dbfe->chkBoxEMS->setChecked( true );
    int umb = dbfe->cbxUMB->findText( "true" );
    dbfe->cbxUMB->setCurrentIndex( umb );
}

void DB_BASE::findGames( const QString &dirName, QTreeWidget* qtw )
{
    QDir dir( dirName );

    m_file = QDir::homePath();
    m_file.append( "/.dboxfe/profile/games.xml" );

    XMLPreferences games( "DBoxFE", "Alexander Saal" );
    games.setVersion( "v0.1.2" );
    games.load( m_file );

    gameList = games.getStringList( "Games", "Name" );

    const QFileInfoList fil = dir.entryInfoList( QDir::Files | QDir::Dirs, QDir::Name );
    QListIterator<QFileInfo> it( fil );
    QStringList lst;

    while ( it.hasNext() ) {
        fi = it.next();

        if ( fi.fileName() == "." || fi.fileName() == ".." )
            ;
        else {
            if ( fi.isDir() && fi.isReadable() )
                findGames( fi.absoluteFilePath(), qtw );
            else {
                for ( int i = 0; i < gameList.size(); ++i ) {
                    lst = gameList[ i ].split( ";" );
                    if ( fi.fileName() == lst.value( 1 ) ) {
                        QTreeWidgetItem * item = new QTreeWidgetItem( qtw );
                        item->setText( 0, lst.value( 0 ) );
                        item->setText( 1, fi.absolutePath() );
                    }
                }
            }
        }
    }
}

/*
 * Create game profiles
 */
void DB_BASE::createGameProfiles( const QString &file, const QStringList &gamesList, DBoxFE* dbfe, DBoxFE_ProfileWizard* dbfe_pw )
{
    /* init settings from mainwindow */
    dbfe->init();

    XMLPreferences settGP( "DBoxFE", "Alexander Saal" );
    settGP.setVersion( dbfe->getAppVersion() );

    settGP.setStringList( "Profile", "Name", gamesList );
    settGP.setString( "DOSBox", "binary", dbfe->LEDbxStabel->text() );
    settGP.setString( "DOSBox", "version", dbfe->LEDbxVersion->text() );
    settGP.setInt( "DBoxFE", "Lng", dbfe->cbxLanguage->currentIndex() );
    settGP.setBool( "DBoxFE", "winHide", dbfe->chkBoxWindowHide->isChecked() );
    settGP.setBool( "DBoxFE", "keyMapper", dbfe->chkBoxStartmapper->isChecked() );
    settGP.save( file );

    QString fileName;

    fileName = ":/default/default.conf";

    QFile readFile( fileName );
    if ( !readFile.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        return ;
    }

    QTextStream in( &readFile );
    QString line = in.readAll();
    readFile.close();
    for ( int x = 0; x < gamesList.size(); ++x ) {
        fileName = "";
        fileName = QDir::homePath();
        fileName.append( "/.dboxfe/" + gamesList.value( x ) + ".conf" );

		createFile = new QFile( fileName );

		if( !createFile->exists() ) {
			if( isDoubleEntry( gamesList.value( x ), dbfe ) )
				return;

			if ( !createFile->open( QIODevice::WriteOnly | QIODevice::Text ) )
				return;

			QTextStream out( createFile );
			out << line;
			out.flush();
		}
		
		createFile->close();
    }
    line = "";
}

/*
 * TODO Load image files from directory
 */
QStringList DB_BASE::loadImage( const QString &imageDirectory )
{
    QDir dir( imageDirectory );
    QStringList lstImages;

    const QFileInfoList fil = dir.entryInfoList( QDir::Files | QDir::Dirs, QDir::Name );
    QListIterator<QFileInfo> it( fil );

    while ( it.hasNext() ) {
        fi = it.next();

        if ( fi.fileName() == "." || fi.fileName() == ".." )
            ;
        else {
            if ( fi.isDir() && fi.isReadable() )
                loadImage( fi.absoluteFilePath() );
            else {
                if ( fi.suffix() == "jpg" ) {
                    lstImages += fi.baseName() + ";" + fi.absoluteFilePath();
				} else if ( fi.suffix() == "jpeg" ) {
                    lstImages += fi.baseName() + ";" + fi.absoluteFilePath();
				} else if ( fi.suffix() == "png" ) {
                    lstImages += fi.baseName() + ";" + fi.absoluteFilePath();
				} else if ( fi.suffix() == "bmp" ) {
                    lstImages += fi.baseName() + ";" + fi.absoluteFilePath();
				} else if ( fi.suffix() == "gif" ) {
                    lstImages += fi.baseName() + ";" + fi.absoluteFilePath();
				}
            }
        }
    }

    return lstImages;
}

/*
 * TODO For feature request ...... (Gamedatabase)
 */
void DB_BASE::insertGameInToDb( const QString &name, const QString &executable, QTreeWidget* qtw )
{
    qtw->setColumnCount( qtw->columnCount() );

    QTreeWidgetItem *item = new QTreeWidgetItem( qtw );
    item->setText( 0, executable );
    item->setText( 1, name );
}

/*
 * Returns current count of games
 */
int DB_BASE::removeGameFromDb( QTreeWidget* qtw )
{
    if ( qtw->currentItem() != NULL )
        delete qtw->currentItem();
    return qtw->topLevelItemCount();
}

/*
 * Save the gamedatabase file
 */
void DB_BASE::saveGameDb( const QString &file, QTreeWidget* qtw, int col1, int col2 )
{
    XMLPreferences games( "DBoxFE", "Alexander Saal" );
    games.setVersion( "v0.1.2" );

    for ( int i = 0; i < qtw->topLevelItemCount(); ++i ) {
        QTreeWidgetItem *item = qtw->topLevelItem( i );
        gamesList.append( item->text( col1 ) + ";" + item->text( col2 ) );
    }

    games.save( file );
}

/*
 * TODO For feature request ...... (Gamedatabase)
 */
void DB_BASE::readGameDb( const QString &file, QProgressBar *pBar, QTreeWidget* qtw )
{
	int i;
	QFile xmlFile( file );

	if( !xmlFile.open( QIODevice::ReadOnly ) ){
		return;
	}

    QDomDocument doc;
    doc.setContent( &xmlFile );
    xmlFile.close();
    QDomNode item = doc.documentElement().firstChild();

	while ( !item.isNull() ) {
      if ( item.isElement() && item.nodeName() == "game" ) {
        QDomNode subitem = item.toElement().firstChild();

		QTreeWidgetItem *qtwItem = new QTreeWidgetItem( qtw );
        while ( !subitem.isNull() ) {
			if( pBar != NULL ) {
				i = 0;
				pBar->setMaximum( subitem.childNodes().count() );
			}
/*
		<title>007: License to kill</title>
		<year>1989</year>
		<sw_house>Domark</sw_house>
		<link>http://dosbox.sourceforge.net/comp_list.php?showID=426</link>
		<dosbox>
			<info version="0.58" comp_percent="80"/>
			<info version="0.63" comp_percent="100"/>
		</dosbox>
*/
			if ( subitem.toElement().tagName() == "title" ) {
				qtwItem->setText( 0, subitem.toElement().text() );

			} else if ( subitem.toElement().tagName() == "year" ) {
				qtwItem->setText( 3, subitem.toElement().text() );

			} else if ( subitem.toElement().tagName() == "sw_house" ) {
				qtwItem->setText( 2, subitem.toElement().text() );

			} else if ( subitem.toElement().tagName() == "link" ) {
				qtwItem->setText( 6, subitem.toElement().text() );

			} else if ( subitem.toElement().tagName() == "dosbox" ) {
				QDomNode subSubItem = subitem.toElement().firstChild();
				while ( !subSubItem.isNull() ) {
					if ( subSubItem.toElement().tagName() == "info" ) {


					}
					subSubItem = subSubItem.nextSibling();
				}
			}
			subitem = subitem.nextSibling();
			
			if( pBar != NULL ) {
				i = i + 1;
				pBar->setValue( i );
			}
		}
	  }
	  
      item = item.nextSibling();
    }
}

/*
 * TODO Import DFend Profiles
 */
void DB_BASE::importDFendProfile( const QString &file, DBoxFE *dbfe )
{
	// DFend Profile is a native dosboxconfigurationfile ...
	QFileInfo fi( file );

	if( !file.isEmpty() || !file.isNull() ) {
		if( isDoubleEntry( fi.baseName(), dbfe ) ) {
			QMessageBox::information( 0, dbfe->winTitle(), QObject::tr( "Can not add the same profilename: '" ) + fi.baseName() + QObject::tr( "' to the list." ) );
			return;
		}

		dbfe->lwProfile->addItem( fi.baseName() );
		readConf( file, dbfe );
	}
}

/*
 * TODO Check for double entries in the profile list ( dbfe->lwProfile )
 */
bool DB_BASE::isDoubleEntry( const QString &name, DBoxFE* dbfe )
{
	if( !name.isEmpty() || !name.isNull() ) {
	    QList<QListWidgetItem *> it( dbfe->lwProfile->findItems( name, Qt::MatchExactly ) );
		for ( int a = 0; a < it.size(); ++a ) {
			QListWidgetItem *sItem;
			sItem = it.value( a );
			if( sItem->text() == name ) {
				return true;
			}
		}
	}

	return false;	
}
