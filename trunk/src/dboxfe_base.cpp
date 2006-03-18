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
}

void DB_BASE::saveConf( const QString &dbconf, const DBoxFE &dbfe )
{
    QSettings settSdl( dbconf, QSettings::IniFormat );
    settSdl.beginGroup( "sdl" );
    settSdl.setValue( "fullscreen", dbfe.ui.chkBoxFullScreen->isChecked() );
    settSdl.setValue( "fulldouble", dbfe.ui.chkBoxFullDouble->isChecked() );
    settSdl.setValue( "fullfixed", dbfe.ui.chkBoxFullFixed->isChecked() );
    settSdl.setValue( "fullresolution", dbfe.ui.cbxFullWightHigh->currentText() );
    settSdl.setValue( "windowresolution", dbfe.ui.cbxWindowWightHigh->currentText() );
    settSdl.setValue( "output", dbfe.ui.cbxOutout->currentText() );
    settSdl.setValue( "autolock", dbfe.ui.chkBoxAutolock->isChecked() );
    settSdl.setValue( "sensitivity", dbfe.ui.lcdSV->intValue() );
    settSdl.setValue( "waitonerror", dbfe.ui.chkBoxWaitOnError->isChecked() );
    settSdl.setValue( "priority", dbfe.ui.cbxFocusUnfocus->currentText() );
    settSdl.setValue( "mapperfile", "mapper.txt" );
    settSdl.setValue( "usescancodes", dbfe.ui.chkBoxUseScanCode->isChecked() );
    settSdl.sync();
    
    // DosBox
    QSettings settDosbox( dbconf, QSettings::IniFormat );
    settDosbox.beginGroup( "dosbox" );
    settDosbox.setValue( "language", dbfe.ui.LELanguage->text() );
    settDosbox.setValue( "machine", dbfe.ui.cbxMachine->currentText() );
    settDosbox.setValue( "memsize", dbfe.ui.cbxMemsize->currentText() );
    settDosbox.setValue( "captures", dbfe.ui.cbxCaptures->currentText() );
    settDosbox.sync();


    // Render settGPuratin
    QSettings settRender( dbconf, QSettings::IniFormat );
    settRender.beginGroup( "render" );
    settRender.setValue( "frameskip", dbfe.ui.lcdFS->intValue() );
    settRender.setValue( "snapdir", dbfe.ui.LESnapDir->text() );
    settRender.setValue( "scaler", dbfe.ui.cbxScaler->currentText() );
    settRender.setValue( "aspect", dbfe.ui.chkBoxAspect->isChecked() );
    settRender.sync();

    // CPU settGPuratin
    QSettings settCPU( dbconf, QSettings::IniFormat );
    settCPU.beginGroup( "cpu" );
    settCPU.setValue( "core", dbfe.ui.cbxCPUCore->currentText() );
    settCPU.setValue( "cycles", dbfe.ui.cbxCycles->currentText() );
    settCPU.setValue( "cycleup", dbfe.ui.cbxCycleUp->currentText() );
    settCPU.setValue( "cycledown", dbfe.ui.cbxCycleDown->currentText() );
    settCPU.sync();

    // Sound value
    /*QSettings settMixer( dbconf, QSettings::IniFormat );
    settMixer->setGroup( "mixer" );
    settMixer.setValue( "nosound",  dbfe.ui.CheckBox_Mixer_NoSound->isChecked() );
    settMixer.setValue( "rate",  dbfe.ui.ComboBox_Mixer_Rate->currentText() );
    settMixer.setValue( "blocksize",  dbfe.ui.ComboBox_Mix_BlockSize->currentText() );
    settMixer.setValue( "prebuffer",  dbfe.ui.LineEdit_Mixer_WaveDir->text() );

    QSettings settMidi( dbconf, QSettings::IniFormat );
    settMidisettGP->setGroup( "midi" );
    settMidi.setValue( "mpu401", CheckBox_Midi_MPU401->isChecked() );
    settMidi.setValue( "device", ComboBox_Midi_Device->currentText() );
    settMidi.setValue( "settGP", LineEdit_Midi_settGP->text() );
    settMidi.setValue( "intelligent", CheckBox_Midi_Intelligent->isChecked() );

    QSettings settSblaster( dbconf, QSettings::IniFormat );
    settSblaster->setGroup( "sblaster" );
    settSblaster.setValue( "type", ComboBox_SBlaster_Type_CVS->currentText() );
    settSblaster.setValue( "base", ComboBox_SBlaster_Base_CVS->currentText() );
    settSblaster.setValue( "irq", ComboBox_SBlaster_IRQ_CVS->currentText() );
    settSblaster.setValue( "dma", ComboBox_SBlaster_DMA_CVS->currentText() );
    settSblaster.setValue( "hdma", ComboBox_SBlaster_HDMA_CVS->currentText() );
    settSblaster.setValue( "mixer", CheckBox_SBlaster_Mixer_CVS->isChecked() );
    settSblaster.setValue( "oplrate", ComboBox_SBlaster_OPLRate_CVS->currentText() );
    settSblaster.setValue( "oplmode", ComboBox_Sblaster_OPLMode_CVS->currentText() );

    QSettings settGus( dbconf, QSettings::IniFormat );
    settGus->setGroup( "gus" );
    settGus.setValue( "gus", CheckBox_GravisUltraSound->isChecked() );
    settGus.setValue( "base", ComboBox_GUS_Base->currentText() );
    settGus.setValue( "rate", ComboBox_GUS_Rate->currentText() );
    settGus.setValue( "irq1", ComboBox_GUS_IRQ1->currentText() );
    settGus.setValue( "irq2", ComboBox_GUS_IRQ2->currentText() );
    settGus.setValue( "dma1", ComboBox_GUS_DMA1->currentText() );
    settGus.setValue( "dma2", ComboBox_GUS_DMA2->currentText() );
    settGus.setValue( "ultradir", LineEdit_GUS_UltraDir->text() );

    QSettings settSpeaker( dbconf, QSettings::IniFormat );
    settSpeaker->setGroup( "speaker" );
    settSpeaker.setValue( "pcspeaker", CheckBox_PC_Speaker->isChecked() );
    settSpeaker.setValue( "pcrate", ComboBox_PC_SpeakerRate->currentText() );
    settSpeaker.setValue( "tandy", CheckBox_PC_Tandy->isChecked() );
    settSpeaker.setValue( "tandyrate", ComboBox_PC_TandyRate->currentText() );
    settSpeaker.setValue( "disney", CheckBox_PC_Disney->isChecked() );

    // Misc ( DOS, Modem and Autoexc )
    QSettings settDos( dbconf, QSettings::IniFormat );
    settDos->setGroup( "dos" );
    settDos.setValue( "xms", CheckBox_Dos_XMS->isChecked() );
    settDos.setValue( "ems", CheckBox_Dos_EMS->isChecked() );

    QSettings settModem( dbconf, QSettings::IniFormat );
    settGP->setGroup( "modem" );
    settGP.setValue( "modem", CheckBox_Modem->isChecked() );
    settGP.setValue( "comport", ComboBox_Modem_ComPort->currentText() );
    settGP.setValue( "listenport", ComboBox_Modem_ListenPort->currentText() );

    QSettings settGP( dbconf, QSettings::IniFormat );
    settGP->setGroup( "ipx" );
    settGP.setValue( "ipx", CheckBox_IPX->isChecked() );
    settGP.setValue( "", "" );
    settGP.setValue( "", "" );*/

}

void DB_BASE::findGames( const QString &dirName, QListWidget* qlw )
{
    QDir dir( dirName );

    m_file = QDir::homePath();
    m_file.append( "/.dboxfe/profile/games.xml" );

    XMLPreferences games( "DBoxFE", "Alexander Saal" );
    games.setVersion( "v0.1.0" );
    games.load( m_file );

    gameList = games.getStringList( "Games", "Name" );

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
                    if( fi.fileName() == lst.value(1) )
                        qlw->addItem( lst.value(0) );
                }
            }
        }
    }
}

/*
 * Create game profiles
 */
void DB_BASE::createGameProfiles( const QString &file, const QStringList &gamesList )
{}

/*
 * TODO For feature request ...... (Gamedatabase)
 */
void DB_BASE::insertGameInToDb( const QString &name, const QString &executable, QTreeWidget* qtw )
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
int DB_BASE::removeGameFromDb( QTreeWidget* qtw )
{
    delete qtw->currentItem();
    return qtw->topLevelItemCount();
}

/*
 * Save the gamedatabase file
 */
void DB_BASE::saveGameDb( const QString &file, QTreeWidget* qtw, int col1, int col2 )
{
    XMLPreferences games( "DBoxFE", "Alexander Saal" );
    games.setVersion( "v0.1.0" );

    for ( int i = 0; i < qtw->topLevelItemCount(); i++ )
    {
        QTreeWidgetItem *item =  qtw->topLevelItem( i );
        gamesList.append( item->text( col1 ) + ";" + item->text( col2 ) );
    }

    games.save( file );
    delete qtw;
}

/*
 * Read the gamedatabase file and list the items in to QTreeWidget
 */
void DB_BASE::readGameDb( const QString &file, QTreeWidget* qtw )
{
    XMLPreferences games( "DBoxFE", "Alexander Saal" );
    games.setVersion( "v0.1.0" );
    games.load( file);
    gamesList = games.getStringList( "Games", "Name" );

    QStringList lst;
    QTreeWidgetItem *item = new QTreeWidgetItem(qtw);

    for( int i = 0; i < gamesList.size(); ++i )
    {
        lst = gamesList[i].split(";");
        item->setText( 0, lst.value(0) );
        item->setText( 1, lst.value(2) );
    }
    delete qtw;
    delete item;
}
