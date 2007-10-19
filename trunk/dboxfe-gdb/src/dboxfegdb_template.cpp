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

#include "dboxfegdb_template_new.h"
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
	GameTemplateNewDialog *gt_nd = new GameTemplateNewDialog( 0 );
	if( gt_nd->exec() == QDialog::Accepted )
	{
		templateName = gt_nd->lineEditTemplateName->text();
	}

	if( templateName.isNull() || templateName.isEmpty() )
	{
		QMessageBox::critical( this, tr( "Gamedatabase - New Template" ), tr( "Please create template name first." ) );
		return;
	}

	gd_sql->insertTemplates( templateName, comboBoxTemplate );
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

void GameTemplateDialog::cancel()
{}

void GameTemplateDialog::language()
{}

void GameTemplateDialog::serialAdd()
{}

void GameTemplateDialog::serialRemove()
{}

QMap< QString, QMap< QString, QVariant > > GameTemplateDialog::getSettings()
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

    // Soundblaster settings
	subSettings.clear();
    subSettings.insert( "sbtype", cbxSBType->currentText() );
    subSettings.insert( "sbbase", cbxSBBase->currentText() );
    subSettings.insert( "irq", cbxSBIRQ->currentText() );
    subSettings.insert( "dma", cbxSBDMA->currentText() );
    subSettings.insert( "hdma", cbxSBHDMA->currentText() );
    subSettings.insert( "mixer", chkBoxSBMixer->isChecked() );
    subSettings.insert( "oplrate", cbxSBOPLRate->currentText() );
    subSettings.insert( "oplmode", cbxSBOplMode->currentText() );
	settings.insert( "SBLASTER", subSettings );
    

    // GUS settings
	subSettings.clear();
    subSettings.insert( "gus", chkBoxGUS->isChecked() );
    subSettings.insert( "gusrate", cbxGUSRate->currentText() );
    subSettings.insert( "gusbase", cbxGUSBase->currentText() );
    subSettings.insert( "irq1", cbxGUSIrq_1->currentText() );
    subSettings.insert( "irq2", cbxGUSIrq_2->currentText() );
    subSettings.insert( "dma1", cbxGUSDMA_1->currentText() );
    subSettings.insert( "dma2", cbxGUSDMA_2->currentText() );
    subSettings.insert( "ultradir", LEGUSUltraDir->text() );
	settings.insert( "GUS", subSettings );
    

    // PC Speaker settings
	subSettings.clear();
    if ( cbxSpeaker->currentText() == "on" )
        subSettings.insert( "pcspeaker", "true" );
    else
        subSettings.insert( "pcspeaker", "false" );

    subSettings.insert( "pcrate", cbxSpeakerRate->currentText() );
    subSettings.insert( "tandy", cbxSpeakerTandy->currentText() );
    subSettings.insert( "tandyrate", cbxSpeakerTandyRate->currentText() );
    subSettings.insert( "disney", chkBoxDisney->isChecked() );
	settings.insert( "SPEAKER", subSettings );
    

    // Joystick settings
	subSettings.clear();
    subSettings.insert( "joysticktype", cbxJoystickType->currentText() );
	subSettings.insert( "timed", chkBoxTimed->isChecked() );
	subSettings.insert( "autofire", chkBoxAutofire->isChecked() );
	subSettings.insert( "swap34", chkBoxSwap34->isChecked() );
	subSettings.insert( "buttonwrap", chkBoxButtonWrap->isChecked() );
	settings.insert( "JOYSTICK", subSettings );
    

    // Serial settings
	subSettings.clear();
    for ( int i = 0; i < twSerial->topLevelItemCount(); i++ ) {
        QTreeWidgetItem *item = twSerial->topLevelItem( i );
        subSettings.insert( item->text( 0 ), item->text( 1 ) );
    }

    if ( twSerial->topLevelItemCount() <= 0 ) {
        subSettings.insert( "serial1", "dummy" );
        subSettings.insert( "serial2", "dummy" );
        subSettings.insert( "serial3", "disabled" );
        subSettings.insert( "serial4", "disabled" );
    }
	settings.insert( "SERIAL", subSettings );
    

    // DOS settings
	subSettings.clear();
    subSettings.insert( "xms", chkBoxXMS->isChecked() );
    subSettings.insert( "ems", chkBoxEMS->isChecked() );
    subSettings.insert( "umb", chkBoxUMB->isChecked() );
    subSettings.insert( "keyboardlayout", cbxKeyboardLayout->currentText() );
	settings.insert( "DOS", subSettings );
    

    // IPX settings
	subSettings.clear();
    subSettings.insert( "ipx", chkBoxIPX->isChecked() );
	settings.insert( "IPX", subSettings );

	return settings;
}