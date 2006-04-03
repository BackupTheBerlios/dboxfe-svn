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
{
    QSettings *getConf = new QSettings( dbconf, QSettings::IniFormat );
    getConf->beginGroup( "sdl" );
    dbfe->ui.chkBoxFullScreen->setChecked( getConf->value( "fullscreen" ).toBool() );
    dbfe->ui.chkBoxFullDouble->setChecked( getConf->value( "fulldouble" ).toBool() );
    dbfe->ui.chkBoxFullFixed->setChecked( getConf->value( "fullfixed" ).toBool() );
    int fullresolution = dbfe->ui.cbxFullWightHigh->findText( getConf->value( "fullresolution" ).toString() ); dbfe->ui.cbxFullWightHigh->setCurrentIndex(fullresolution);
    int windowresolution = dbfe->ui.cbxWindowWightHigh->findText( getConf->value( "windowresolution" ).toString() ); dbfe->ui.cbxWindowWightHigh->setCurrentIndex(windowresolution);
    int priority = dbfe->ui.cbxFocusUnfocus->findText( getConf->value( "priority" ).toString() ); dbfe->ui.cbxFocusUnfocus->setCurrentIndex(priority);
    int output = dbfe->ui.cbxOutout->findText( getConf->value( "output" ).toString() ); dbfe->ui.cbxOutout->setCurrentIndex(output);
    dbfe->ui.chkBoxAutolock->setChecked( getConf->value( "autolock" ).toBool() );
    dbfe->ui.chkBoxWaitOnError->setChecked( getConf->value( "waitonerror" ).toBool() );
    dbfe->ui.chkBoxUseScanCode->setChecked( getConf->value( "usescancodes" ).toBool() );
    dbfe->ui.lcdSV->display( getConf->value( "sensitivity" ).toInt() );
    dbfe->ui.sliderSV->setValue( getConf->value( "sensitivity" ).toInt() );
    /*settConf->setValue( "mapperfile", "mapper.txt" );*/
    getConf->endGroup();
    
    // DOSBox settings
    getConf->beginGroup( "dosbox" );
    dbfe->ui.LELanguage->setText( getConf->value( "language" ).toString() );
    int machine = dbfe->ui.cbxMachine->findText( getConf->value( "machine" ).toString() ); dbfe->ui.cbxMachine->setCurrentIndex(machine);
    int memsize = dbfe->ui.cbxMemsize->findText( getConf->value( "memsize" ).toString() ); dbfe->ui.cbxMemsize->setCurrentIndex(memsize);
    int captures = dbfe->ui.cbxCaptures->findText( getConf->value( "captures" ).toString() ); dbfe->ui.cbxCaptures->setCurrentIndex(captures);
    getConf->endGroup();
    
    // Render settings
    getConf->beginGroup( "render" );
    dbfe->ui.lcdFS->display( getConf->value( "frameskip" ).toInt() );
    dbfe->ui.sliderFS->setValue( getConf->value( "frameskip" ).toInt() );
    int scaler = dbfe->ui.cbxScaler->findText( getConf->value( "scaler" ).toString() ); dbfe->ui.cbxScaler->setCurrentIndex(scaler);
    dbfe->ui.chkBoxAspect->setChecked( getConf->value( "aspect" ).toBool() );
    getConf->endGroup();
    
    // CPU settings
    getConf->beginGroup( "cpu" );
    int core = dbfe->ui.cbxCPUCore->findText( getConf->value( "core" ).toString() ); dbfe->ui.cbxCPUCore->setCurrentIndex(core);
    int cycles = dbfe->ui.cbxCPUCycles->findText( getConf->value( "cycles" ).toString() ); dbfe->ui.cbxCPUCycles->setCurrentIndex(cycles);
    int cycleup = dbfe->ui.cbxCPUCycleUp->findText( getConf->value( "cycleup" ).toString() ); dbfe->ui.cbxCPUCycleUp->setCurrentIndex(cycleup);
    int cycledown = dbfe->ui.cbxCPUCycleDown->findText( getConf->value( "cycledown" ).toString() ); dbfe->ui.cbxCPUCycleDown->setCurrentIndex(cycledown);
    getConf->endGroup();
    
    // Mixer settings
    getConf->beginGroup( "mixer" );
    dbfe->ui.chkBoxMixerNoSound->setChecked( getConf->value( "nosound" ).toBool() );
    int rate = dbfe->ui.cbxMixerRate->findText( getConf->value( "rate" ).toString() ); dbfe->ui.cbxMixerRate->setCurrentIndex(rate);
    int blocksize = dbfe->ui.cbxMixerBlockSize->findText( getConf->value( "blocksize" ).toString() ); dbfe->ui.cbxMixerBlockSize->setCurrentIndex(blocksize);
    dbfe->ui.spBoxPrebuffer->setValue( getConf->value( "prebuffer" ).toInt() );
    getConf->endGroup();
    
    // Mdi settings
    getConf->beginGroup( "midi" );
    int mpu = dbfe->ui.cbxMDIMPU->findText( getConf->value( "mpu401" ).toString() ); dbfe->ui.cbxMDIMPU->setCurrentIndex(mpu);
    int device = dbfe->ui.cbxMDIDevice->findText( getConf->value( "device" ).toString() ); dbfe->ui.cbxMDIDevice->setCurrentIndex(device);
    dbfe->ui.LEMDIConfig->setText( getConf->value( "config" ).toString() );
    getConf->endGroup();
    
    // Soundblaster settings
    getConf->beginGroup( "sblaster" );
    int sbtype = dbfe->ui.cbxSBType->findText( getConf->value( "sbtype" ).toString() ); dbfe->ui.cbxSBType->setCurrentIndex(sbtype);
    int sbbase = dbfe->ui.cbxSBBase->findText( getConf->value( "sbbase" ).toString() ); dbfe->ui.cbxSBBase->setCurrentIndex(sbbase);
    int irq = dbfe->ui.cbxSBIRQ->findText( getConf->value( "irq" ).toString() ); dbfe->ui.cbxSBIRQ->setCurrentIndex(irq);
    int dma = dbfe->ui.cbxSBDMA->findText( getConf->value( "dma" ).toString() ); dbfe->ui.cbxSBDMA->setCurrentIndex(dma);
    int hdma = dbfe->ui.cbxSBHDMA->findText( getConf->value( "hdma" ).toString() ); dbfe->ui.cbxSBHDMA->setCurrentIndex(hdma);
    int oplrate = dbfe->ui.cbxSBOPLRate->findText( getConf->value( "oplrate" ).toString() ); dbfe->ui.cbxSBOPLRate->setCurrentIndex(oplrate);
    int oplmode = dbfe->ui.cbxSBOplMode->findText( getConf->value( "oplmode" ).toString() ); dbfe->ui.cbxSBOplMode->setCurrentIndex(oplmode);
    dbfe->ui.chkBoxSBMixer->setChecked( getConf->value( "mixer" ).toBool() );  
    getConf->endGroup();

    // GUS settings
    getConf->beginGroup( "gus" );
    dbfe->ui.chkBoxGUS->setChecked( getConf->value( "gus" ).toBool() );
    int gusrate = dbfe->ui.cbxGUSRate->findText( getConf->value( "gusrate" ).toString() ); dbfe->ui.cbxGUSRate->setCurrentIndex(gusrate);
    int gusbase = dbfe->ui.cbxGUSBase->findText( getConf->value( "gusbase" ).toString() ); dbfe->ui.cbxGUSBase->setCurrentIndex(gusbase);
    int irq1 = dbfe->ui.cbxGUSIrq_1->findText( getConf->value( "irq1" ).toString() ); dbfe->ui.cbxGUSIrq_1->setCurrentIndex(irq1);
    int irq2 = dbfe->ui.cbxGUSIrq_2->findText( getConf->value( "irq2" ).toString() ); dbfe->ui.cbxGUSIrq_2->setCurrentIndex(irq2);
    int dma1 = dbfe->ui.cbxGUSDMA_1->findText( getConf->value( "dma1" ).toString() ); dbfe->ui.cbxGUSDMA_1->setCurrentIndex(dma1);
    int dma2 = dbfe->ui.cbxGUSDMA_2->findText( getConf->value( "dma2" ).toString() ); dbfe->ui.cbxGUSDMA_2->setCurrentIndex(dma2);
    dbfe->ui.LEGUSUltraDir->setText( getConf->value( "ultradir" ).toString() );
    getConf->endGroup();
    
    // PC Speaker settings
    getConf->beginGroup( "speaker" );
    int pcspeaker = dbfe->ui.cbxSpeaker->findText( getConf->value( "pcspeaker" ).toString() ); dbfe->ui.cbxSpeaker->setCurrentIndex(pcspeaker);
    int pcrate = dbfe->ui.cbxSpeakerRate->findText( getConf->value( "pcrate" ).toString() ); dbfe->ui.cbxSpeakerRate->setCurrentIndex(pcrate);
    int tandy = dbfe->ui.cbxSpeakerTandy->findText( getConf->value( "tandy" ).toString() ); dbfe->ui.cbxSpeakerTandy->setCurrentIndex(tandy);
    int tandyrate = dbfe->ui.cbxSpeakerTandyRate->findText( getConf->value( "tandyrate" ).toString() ); dbfe->ui.cbxSpeakerTandyRate->setCurrentIndex(tandyrate);
    dbfe->ui.chkBoxDisney->setChecked( getConf->value( "disney" ).toBool() );
    getConf->endGroup();
    
    // Serial settings
    getConf->beginGroup( "serial" );
    dbfe->ui.twSerial->clear();
    QTreeWidgetItem *serial1 = new QTreeWidgetItem( dbfe->ui.twSerial ); serial1->setText( 0, "serial1" ); serial1->setText( 1, getConf->value( "serial1" ).toString() );
    QTreeWidgetItem *serial2 = new QTreeWidgetItem( dbfe->ui.twSerial ); serial2->setText( 0, "serial2" ); serial2->setText( 1, getConf->value( "serial2" ).toString() );
    QTreeWidgetItem *serial3 = new QTreeWidgetItem( dbfe->ui.twSerial ); serial3->setText( 0, "serial3" ); serial3->setText( 1, getConf->value( "serial3" ).toString() );
    QTreeWidgetItem *serial4 = new QTreeWidgetItem( dbfe->ui.twSerial ); serial4->setText( 0, "serial4" ); serial4->setText( 1, getConf->value( "serial4" ).toString() );
    getConf->endGroup();
    
    // Autoexec settings
    QFile f( dbconf );

    if ( !f.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
	delete getConf;
	return;
    }
    
    QTextStream in( &f );
    QString line;
    
    dbfe->ui.lwAutoexec->clear();
    
    while( !in.atEnd() ) {
	line = in.readLine();
	if( line == "[autoexec]" ){
	    while( !in.atEnd() ){
		line = in.readLine();
		QListWidgetItem *autoexec = new QListWidgetItem( dbfe->ui.lwAutoexec );
		autoexec->setText(line);
	    }
	}	
    }
    
    f.close();
    delete getConf;
}

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
{
    XMLPreferences settGP( "DBoxFE", "Alexander Saal" );
    settGP.setVersion( "v0.1.0" );
    settGP.setStringList( "Profile", "Name", gamesList );
    settGP.setString( "DOSBox", "binary", "" );
    settGP.setString( "DOSBox", "version", "" );
    settGP.setInt( "DBoxFE", "Lng", 0 );
    settGP.setBool( "DBoxFE", "winHide", false );
    settGP.save( file );
    
    QString fileName;
    QFile *createFile;
    
    fileName = ":/default/default.conf";
    QFile readFile(fileName);
    if( !readFile.open(QIODevice::ReadOnly | QIODevice::Text )) { return; }
    QTextStream in( &readFile );
    
    for( int x= 0; x < gamesList.size(); ++x ) {
	fileName = "";
	fileName = QDir::homePath();
	fileName.append( "/.dboxfe/" + gamesList.value(x) + ".conf" );
	
	createFile = new QFile( fileName );
	if( !createFile->open(QIODevice::WriteOnly | QIODevice::Text )) { return; }
	
	QTextStream out( createFile );
	out << in.readAll();
	out.flush();
    }
    createFile->close();
    readFile.close();
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
    if( qtw->currentItem() != NULL ) delete qtw->currentItem();
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
    
    for( int i = 0; i < gamesList.size(); i++ )
    {
	QTreeWidgetItem *item = new QTreeWidgetItem(qtw);
        lst = gamesList[i].split(";");
        item->setText( 0, lst.value(0) );
        item->setText( 1, lst.value(1) );
    }
}
