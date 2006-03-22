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

DB_BASE::DB_BASE()
{}

QString DB_BASE::applicationDir()
{
    return QCoreApplication::applicationDirPath();
}

void DB_BASE::readConf( const QString &dbconf, DBoxFE* dbfe )
{}

void DB_BASE::saveConf( const QString &dbconf, DBoxFE* dbfe )
{
    QSettings *settConf = new QSettings( dbconf, QSettings::IniFormat );
    // SDL settings
    settConf->beginGroup( "sdl" );
    settConf->setValue( "fullscreen", dbfe->ui.chkBoxFullScreen->isChecked() );
    settConf->setValue( "fulldouble", dbfe->ui.chkBoxFullDouble->isChecked() );
    settConf->setValue( "fullfixed", dbfe->ui.chkBoxFullFixed->isChecked() );
    settConf->setValue( "fullresolution", dbfe->ui.cbxFullWightHigh->currentText() );
    settConf->setValue( "windowresolution", dbfe->ui.cbxWindowWightHigh->currentText() );
    settConf->setValue( "output", dbfe->ui.cbxOutout->currentText() );
    settConf->setValue( "autolock", dbfe->ui.chkBoxAutolock->isChecked() );
    settConf->setValue( "sensitivity", dbfe->ui.lcdSV->intValue() );
    settConf->setValue( "waitonerror", dbfe->ui.chkBoxWaitOnError->isChecked() );
    settConf->setValue( "priority", dbfe->ui.cbxFocusUnfocus->currentText() );
    settConf->setValue( "mapperfile", "mapper.txt" );
    settConf->setValue( "usescancodes", dbfe->ui.chkBoxUseScanCode->isChecked() );
    settConf->endGroup();

    // DOSBox settings
    settConf->beginGroup( "dosbox" );
    settConf->setValue( "language", dbfe->ui.LELanguage->text() );
    settConf->setValue( "machine", dbfe->ui.cbxMachine->currentText() );
    settConf->setValue( "memsize", dbfe->ui.cbxMemsize->currentText() );
    settConf->setValue( "captures", dbfe->ui.cbxCaptures->currentText() );
    settConf->endGroup();

    // Render settings
    settConf->beginGroup( "render" );
    settConf->setValue( "frameskip", dbfe->ui.lcdFS->intValue() );
    settConf->setValue( "snapdir", dbfe->ui.LESnapDir->text() );
    settConf->setValue( "scaler", dbfe->ui.cbxScaler->currentText() );
    settConf->setValue( "aspect", dbfe->ui.chkBoxAspect->isChecked() );
    settConf->endGroup();

    // CPU settings
    settConf->beginGroup( "cpu" );
    settConf->setValue( "core", dbfe->ui.cbxCPUCore->currentText() );
    settConf->setValue( "cycles", dbfe->ui.cbxCPUCycles->currentText() );
    settConf->setValue( "cycleup", dbfe->ui.cbxCPUCycleUp->currentText() );
    settConf->setValue( "cycledown", dbfe->ui.cbxCPUCycleDown->currentText() );
    settConf->endGroup();

    // Mixer settings
    settConf->beginGroup( "mixer" );
    settConf->setValue( "nosound",  dbfe->ui.chkBoxMixerNoSound->isChecked() );
    settConf->setValue( "rate",  dbfe->ui.cbxMixerRate->currentText() );
    settConf->setValue( "blocksize",  dbfe->ui.cbxMixerBlockSize->currentText() );
    settConf->setValue( "prebuffer",  dbfe->ui.spBoxPrebuffer->value() );
    settConf->endGroup();

    // Mdi settings
    settConf->beginGroup( "midi" );
    settConf->setValue( "mpu401", dbfe->ui.cbxMDIMPU->currentText() );
    settConf->setValue( "device", dbfe->ui.cbxMDIDevice->currentText() );
    settConf->setValue( "config", dbfe->ui.LEMDIConfig->text() );
    settConf->endGroup();

    // Soundblaster settings
    settConf->beginGroup( "sblaster" );
    settConf->setValue( "sbtype", dbfe->ui.cbxSBType->currentText() );
    settConf->setValue( "sbbase", dbfe->ui.cbxSBBase->currentText() );
    settConf->setValue( "irq", dbfe->ui.cbxSBIRQ->currentText() );
    settConf->setValue( "dma", dbfe->ui.cbxSBDMA->currentText() );
    settConf->setValue( "hdma", dbfe->ui.cbxSBHDMA->currentText() );
    settConf->setValue( "mixer", dbfe->ui.chkBoxSBMixer->isChecked() );
    settConf->setValue( "oplrate", dbfe->ui.cbxSBOPLRate->currentText() );
    settConf->setValue( "oplmode", dbfe->ui.cbxSBOplMode->currentText() );
    settConf->endGroup();

    // GUS settings
    settConf->beginGroup( "gus" );
    settConf->setValue( "gus", dbfe->ui.chkBoxGUS->isChecked() );
    settConf->setValue( "gusrate", dbfe->ui.cbxGUSRate->currentText() );
    settConf->setValue( "gusbase", dbfe->ui.cbxGUSBase->currentText() );
    settConf->setValue( "irq1", dbfe->ui.cbxGUSIrq_1->currentText() );
    settConf->setValue( "irq2", dbfe->ui.cbxGUSIrq_2->currentText() );
    settConf->setValue( "dma1", dbfe->ui.cbxGUSDMA_1->currentText() );
    settConf->setValue( "dma2", dbfe->ui.cbxGUSDMA_2->currentText() );
    settConf->setValue( "ultradir", dbfe->ui.LEGUSUltraDir->text() );
    settConf->endGroup();

    // PC Speaker settings
    settConf->beginGroup( "speaker" );
    settConf->setValue( "pcspeaker", dbfe->ui.cbxSpeaker->currentText() );
    settConf->setValue( "pcrate", dbfe->ui.cbxSpeakerRate->currentText() );
    settConf->setValue( "tandy", dbfe->ui.cbxSpeakerTandy->currentText() );
    settConf->setValue( "tandyrate", dbfe->ui.cbxSpeakerTandyRate->currentText() );
    settConf->setValue( "disney", dbfe->ui.chkBoxDisney->isChecked() );
    settConf->endGroup();

    // Serial settings
    settConf->beginGroup( "serial" );
    for ( int i = 0; i < dbfe->ui.twSerial->topLevelItemCount(); i++ )
    {
        QTreeWidgetItem *item =  dbfe->ui.twSerial->topLevelItem( i );
        settConf->setValue( item->text( 0 ), item->text( 1 ) );
    }

    if( dbfe->ui.twSerial->topLevelItemCount() <= 0 )
    {
        settConf->setValue( "serial1", "dummy" );
        settConf->setValue( "serial2", "dummy" );
        settConf->setValue( "serial3", "disabled" );
        settConf->setValue( "serial4", "disabled" );
    }
    settConf->endGroup();

    // IPX settings
    settConf->beginGroup( "ipx" );
    settConf->setValue( "ipx", dbfe->ui.chkBoxIPX->isChecked() );
    settConf->endGroup();

    settConf->sync();
    
    // Autoexec settings
    QFile f( dbconf );

    if ( !f.open( QFile::Append | QFile::WriteOnly ) )
    {
	delete settConf;
	return;
    }
    
    QTextStream t( &f );
    t << "\n[autoexec]\n";
    
    for( int q = 0; q < dbfe->ui.lwAutoexec->count(); q++ )
    {
        t << dbfe->ui.lwAutoexec->item( q )->text() << "\n";
    }
    
    t.flush();
    f.close();
    
    delete settConf;

}

void DB_BASE::parseAutoexecSection( const QString &dbconf, QListWidget* qlw, const QString &section = QString("[autoexec]") )
{
    QSettings settAuto( dbconf, QSettings::IniFormat );
    settAuto.beginGroup( section );

    QStringList execList = settAuto.allKeys();
    for( int i = 0; i < execList.size(); ++i )
    {
        qlw->addItem( QString( execList.value(i) ) );
    }

    settAuto.endGroup();
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

    for ( int i = 0; i < qtw->topLevelItemCount(); ++i )
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
    //QTreeWidgetItem *item = new QTreeWidgetItem(qtw);

    for( int i = 0; i < gamesList.size(); i++ )
    {
	QTreeWidgetItem *item = new QTreeWidgetItem(qtw);
        lst = gamesList[i].split(";");
        item->setText( 0, lst.value(0) );
        item->setText( 1, lst.value(1) );
    }
}
