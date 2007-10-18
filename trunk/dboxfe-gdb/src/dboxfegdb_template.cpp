/*
*   Copyright (C) 2007 by Alexander Saal <alex.saal@gmx.de>
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

#include "dboxfegdb_template.h"
#include "dboxfegdb_sql.h"

#include <XMLPreferences.h>

#include <QtCore>
#include <QtSql>

GameTemplateDialog::GameTemplateDialog( QDialog *parent, Qt::WFlags flags ) : QDialog( parent, flags )
{
	setupUi( this );

	gd_sql = new GameDatabaseSql( this );

	XMLPreferences xmlPreferences( "DBoxFE - GDB", "Alexander Saal" );
	xmlPreferences.load( QDir::homePath() + "/.dboxfe-gdb/dboxfegdb.xml" );

	database = xmlPreferences.getString( "Database", "DatabaseFile" );	

	gd_sql->createConnection( database );

	connect( btnLanguage, SIGNAL( clicked() ), this, SLOT( language() ) );
	connect( btnSerialAdd, SIGNAL( clicked() ), this, SLOT( serialAdd() ) );
	connect( btnSerialRemove, SIGNAL( clicked() ), this, SLOT( serialRemove() ) );
	connect( cbxDSOption, SIGNAL( currentIndexChanged ( int ) ), this, SLOT( cbxSerialIndexChanged ( int ) ) );
	connect( cbxKeyboardLayout, SIGNAL( currentIndexChanged ( int ) ), this, SLOT( cbxKeyboardLayoutIndexChanged ( int ) ) );

	connect( btnNew, SIGNAL( clicked() ), this, SLOT( newTemplate() ) );
	connect( btnSave, SIGNAL( clicked() ), this, SLOT( saveTemplate() ) );
	connect( btnCancel, SIGNAL( clicked() ), this, SLOT( cancel() ) );
	connect( comboBoxTemplate, SIGNAL( currentIndexChanged ( const QString & ) ), this, SLOT( comboBoxTemplateCurrentIndexChanged( const QString & ) ) );

	QDesktopWidget *desktop = qApp->desktop();
	const QRect rect = desktop->availableGeometry ( desktop->primaryScreen() );
	int left = ( rect.width() - width() ) / 2;
	int top = ( rect.height() - height() ) / 2;
	setGeometry ( left, top, width(), height() );

	object = parent;
}

GameTemplateDialog::~GameTemplateDialog()
{
}

void GameTemplateDialog::comboBoxTemplateCurrentIndexChanged( const QString &item )
{
	templateName = comboBoxTemplate->currentText();
}

void GameTemplateDialog::cbxSerialIndexChanged( int index )
{}

void GameTemplateDialog::cbxKeyboardLayoutIndexChanged( int index )
{}

void GameTemplateDialog::loadTemplate( const QString &templateName )
{}

void GameTemplateDialog::newTemplate()
{
}

void GameTemplateDialog::saveTemplate()
{
	if( templateName.isNull() || templateName.isEmpty() )
	{
		QMessageBox::critical( this, tr( "Gamedatabase - New Template" ), tr( "Please create template name first." ) );
		return;
	}

	gd_sql->insertTemplates( templateName, getSettings() );
}

void GameTemplateDialog::deleteTemplate()
{
	if( templateName.isNull() || templateName.isEmpty() )
	{
		QMessageBox::critical( this, tr( "Gamedatabase - New Template" ), tr( "Please select a template to delete it." ) );
		return;
	}

	gd_sql->deleteTemplates( templateName );
}

QMap< QString, QMap< QString, QString > > GameTemplateDialog::getSettings()
{
	settings.clear();

    // SDL settings
	subSettings.clear();
	subSettings.insert( "fullscreen", chkBoxFullScreen->isChecked() );
	subSettings.insert( "fulldouble", chkBoxFullDouble->isChecked() );
	subSettings.insert( "fullresolution", cbxFullWightHigh->currentText() );
	subSettings.insert( "windowresolution", cbxWindowWightHigh->currentText() );
	subSettings.insert( "output", cbxOutout->currentText() );
	subSettings.insert( "autolock", chkBoxAutolock->isChecked() );
	subSettings.insert( "sensitivity", lcdSV->intValue() );
	subSettings.insert( "waitonerror", chkBoxWaitOnError->isChecked() );
	subSettings.insert( "priority", cbxFocusUnfocus->currentText() );
	subSettings.insert( "mapperfile", "mapper.txt" );
	subSettings.insert( "usescancodes", chkBoxUseScanCode->isChecked() );
	settings.insert( "SDL", subSettings );

    // DOSBox settings
	subSettings.clear();
	subSettings.insert( "language", LELanguage->text() );
	subSettings.insert( "machine", cbxMachine->currentText() );
	subSettings.insert( "memsize", cbxMemsize->currentText() );
	subSettings.insert( "captures", cbxCaptures->currentText() );
	settings.insert( "DOSBOX", subSettings );

    // Render settings
	subSettings.clear();
	subSettings.insert( "frameskip", lcdFS->intValue() );
	subSettings.insert( "scaler", cbxScaler->currentText() );
	subSettings.insert( "aspect", chkBoxAspect->isChecked() );
	settings.insert( "RENDER", subSettings );
    

    // CPU settings
	subSettings.clear();
	subSettings.insert( "core", cbxCPUCore->currentText() );
	subSettings.insert( "cycles", cbxCPUCycles->currentText() );
	subSettings.insert( "cycleup", cbxCPUCycleUp->currentText() );
	subSettings.insert( "cycledown", cbxCPUCycleDown->currentText() );
	settings.insert( "CPU", subSettings );

    // Mixer settings
	subSettings.clear();
	subSettings.insert( "nosound", chkBoxMixerNoSound->isChecked() );
	subSettings.insert( "rate", cbxMixerRate->currentText() );
	subSettings.insert( "blocksize", cbxMixerBlockSize->currentText() );
	subSettings.insert( "prebuffer", spBoxPrebuffer->value() );
	settings.insert( "MIXER", subSettings );

    // Midi settings
	subSettings.clear();
	subSettings.insert( "mpu401", cbxMDIMPU->currentText() );
	subSettings.insert( "device", cbxMDIDevice->currentText() );
	if ( !LEMDIConfig->text().isEmpty() ) {
		subSettings.insert( "config", LEMDIConfig->text() );
    } else {
		subSettings.insert( "config", "" );
    }
	settings.insert( "MIDI", subSettings );
/*
    // Soundblaster settings
    "sbtype", cbxSBType->currentText() );
    "sbbase", cbxSBBase->currentText() );
    "irq", cbxSBIRQ->currentText() );
    "dma", cbxSBDMA->currentText() );
    "hdma", cbxSBHDMA->currentText() );
    "mixer", chkBoxSBMixer->isChecked() );
    "oplrate", cbxSBOPLRate->currentText() );
    "oplmode", cbxSBOplMode->currentText() );
    

    // GUS settings
    "gus", chkBoxGUS->isChecked() );
    "gusrate", cbxGUSRate->currentText() );
    "gusbase", cbxGUSBase->currentText() );
    "irq1", cbxGUSIrq_1->currentText() );
    "irq2", cbxGUSIrq_2->currentText() );
    "dma1", cbxGUSDMA_1->currentText() );
    "dma2", cbxGUSDMA_2->currentText() );
    "ultradir", LEGUSUltraDir->text() );
    

    // PC Speaker settings
    if ( cbxSpeaker->currentText() == "on" )
        "pcspeaker", "true" );
    else
        "pcspeaker", "false" );

    "pcrate", cbxSpeakerRate->currentText() );
    "tandy", cbxSpeakerTandy->currentText() );
    "tandyrate", cbxSpeakerTandyRate->currentText() );
    "disney", chkBoxDisney->isChecked() );
    

    // Joystick settings
    "joysticktype", cbxJoystickType->currentText() );
	"timed", chkBoxTimed->isChecked() );
	"autofire", chkBoxAutofire->isChecked() );
	"swap34", chkBoxSwap34->isChecked() );
	"buttonwrap", chkBoxButtonWrap->isChecked() );
    

    // Serial settings
    for ( int i = 0; i < twSerial->topLevelItemCount(); i++ ) {
        QTreeWidgetItem *item = twSerial->topLevelItem( i );
        item->text( 0 ), item->text( 1 ) );
    }

    if ( twSerial->topLevelItemCount() <= 0 ) {
        "serial1", "dummy" );
        "serial2", "dummy" );
        "serial3", "disabled" );
        "serial4", "disabled" );
    }
    

    // DOS settings
    "xms", chkBoxXMS->isChecked() );
    "ems", chkBoxEMS->isChecked() );
    "umb", chkBoxUMB->isChecked() );
    "keyboardlayout", cbxKeyboardLayout->currentText() );
    

    // IPX settings
    "ipx", chkBoxIPX->isChecked() );
*/
	return settings;
}