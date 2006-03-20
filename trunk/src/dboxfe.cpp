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
#include "dboxfe_games.h"
#include "dboxfe_gamedatabase.h"
#include "dboxfe_profile.h"
#include "dboxfe_profilewizard.h"

// 3rdparty library
#include "XMLPreferences.h"

// Qt 4 Header
#include <QtCore>
#include <QtGui>


DBoxFE::DBoxFE(QWidget *parent, Qt::WFlags flags)
        : QWidget(parent, flags)
{

    ui.setupUi(this);

    // connection
    connect( ui.btnSaveGP, SIGNAL( clicked() ), this, SLOT( slotSaveGP() ) );
    connect( ui.btnRemoveGP, SIGNAL( clicked() ), this, SLOT( slotRemoveGP() ) );
    connect( ui.btnCreateGP, SIGNAL( clicked() ), this, SLOT( slotCreateGP() ) );
    connect( ui.btnWizard, SIGNAL( clicked() ), this, SLOT( slotWizard() ) );
    connect( ui.btnStartDBox, SIGNAL( clicked() ), this, SLOT( slotStartDBox() ) );
    connect( ui.btnSnapDir, SIGNAL( clicked() ), this, SLOT( slotSnapDir() ) );
    connect( ui.btnLanguage, SIGNAL( clicked() ), this, SLOT( slotLanguage() ) );
    connect( ui.btnDbxStable, SIGNAL( clicked() ), this, SLOT( slotChooseDbxBinary() ) );
    connect( ui.btnAutexecAdd, SIGNAL( clicked() ), this, SLOT( slotAutexecAdd() ) );
    connect( ui.btnAutexecRemove, SIGNAL( clicked() ), this, SLOT( slotAutexecRemove() ) );
    connect( ui.btnSerialAdd, SIGNAL( clicked() ), this, SLOT( slotSerialAdd() ) );
    connect( ui.btnSerialRemove, SIGNAL( clicked() ), this, SLOT( slotSerialRemove() ) );
    connect( ui.btnAutexecUpdate, SIGNAL( clicked() ), this, SLOT( slotAutexecUpdate() ) );
    connect( ui.btnAutexecDrive, SIGNAL( clicked() ), this, SLOT( slotAutexecDrive() ) );
    connect( ui.btnGame, SIGNAL( clicked() ), this, SLOT( slotGame() ) );
    connect( ui.lwProfile, SIGNAL( itemClicked( QListWidgetItem* ) ), this, SLOT( slotListWidget( QListWidgetItem* ) ) );
    connect( ui.cbxDSOption, SIGNAL( currentIndexChanged( int ) ), this, SLOT( slotCbxIndexChanged( int ) ) );

    // windows title for the application
    titleLin = "DOSBox - Front End for Linux " + getAppVersion();
    titleWin = "DOSBox - Front End for Windows " + getAppVersion();
    titleMac = "DOSBox - Front End for Mac " + getAppVersion();

#ifdef Q_OS_WIN32

    setWindowTitle( titleWin );
    QApplication::setStyle( "windowsxp" );
#endif

#ifdef Q_OS_MACX

    setWindowTitle( titleMac );
#endif

#ifdef Q_OS_MAC9

    setWindowTitle( titleMac );
#endif

#ifdef Q_OS_UNIX

    setWindowTitle( titleLin );
#endif

    // center the application on desktop screen
    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );
}

DBoxFE::~DBoxFE()
{}

/**
 * TODO Initial: configuration
 **/
void DBoxFE::init()
{
    m_file = QDir::homePath();
    m_file.append( "/.dboxfe/profile/profile.xml" );

    XMLPreferences settGP( "DBoxFE", "Alexander Saal" );
    settGP.setVersion( getAppVersion() );
    settGP.load( m_file );

    QStringList sList = settGP.getStringList( "Profile", "Name" );
    ui.lwProfile->addItems( sList );
    ui.LEDbxStabel->setText( QString( settGP.getString( "DOSBox", "binary" )) );
    ui.LEDbxVersion->setText( QString( settGP.getString( "DOSBox", "version" )) );
    ui.cbxLanguage->setCurrentIndex( settGP.getInt( "DBoxFE", "Lng" ) );
    ui.chkBoxWindowHide->setChecked( settGP.getBool( "DBoxFE", "winHide" ) );
    ui.btnGameDb->setHidden( true );
    m_file = "";
}

/**
 * TODO Close event
 **/
void DBoxFE::closeEvent( QCloseEvent *e )
{
    switch( QMessageBox::information( this, winTitle(), tr("Would you realy quit?"), tr("Yes"), tr("No"), 0, 1 ) )
    {
    case 0: // Yes clicked
        slotSaveGP(); /* Save profile list */
        e->accept(); /* accept the quit */
        break;
    case 1: // No clicked
        e->ignore();
        return;
        break;
    }
}

/**
 * TODO Save game profile
 **/
void DBoxFE::slotSaveGP()
{
    XMLPreferences settGP( "DBoxFE", "Alexander Saal" );
    settGP.setVersion( getAppVersion() );

    m_file = QDir::homePath();
    m_file.append( "/.dboxfe/profile/profile.xml" );

    QStringList sList;

    for( int a = 0; a < ui.lwProfile->count(); ++a )
    {
        sList.append( ui.lwProfile->item( a )->text() );
    }

    settGP.setStringList( "Profile", "Name", sList );
    settGP.setString( "DOSBox", "binary", ui.LEDbxStabel->text() );
    settGP.setString( "DOSBox", "version", ui.LEDbxVersion->text() );
    settGP.setInt( "DBoxFE", "Lng", ui.cbxLanguage->currentIndex() );
    settGP.setBool( "DBoxFE", "winHide", ui.chkBoxWindowHide->isChecked() );

    settGP.save( m_file);

    //Save configuration
    DB_BASE gpIni;

    gpItem = new QListWidgetItem;
    gpItem = ui.lwProfile->currentItem();

    if ( gpItem == NULL )
    {
        QMessageBox::information( this, winTitle(), tr("No Profile was selected to save it.") );
        return;
    }

    m_conf = QDir::homePath();
    m_conf.append( "/.dboxfe/" + gpItem->text() + ".conf" );

    QFile f( m_conf );
    f.remove();

    gpIni.saveConf( m_conf, this );
}

/**
 * TODO Create game profile file
 **/
void DBoxFE::slotCreateGP()
{
    gpItem = new QListWidgetItem;
    DBoxFE_Profile *dbfe_profile = new DBoxFE_Profile();

    if ( dbfe_profile->exec() == QDialog::Accepted )
    {
        gpItem->setText( dbfe_profile->ui.LEProfile->text() );
        ui.lwProfile->addItem( gpItem );
    }
}

/**
 * TODO Start dosbox with configuration file
 **/
void DBoxFE::slotStartDBox()
{
    gpItem = new QListWidgetItem;
    gpItem = ui.lwProfile->currentItem();

    if ( gpItem == NULL )
    {
        QMessageBox::information( this, winTitle(), tr("Please select profile.") );
        return;
    }

    gpTxt = gpItem->text();

    m_conf = QDir::homePath();
    m_conf.append( "/.dboxfe/" + gpTxt + ".conf" );

    if ( !QFile( m_conf ).exists() )
    {
        QMessageBox::information( this, winTitle(), tr("Configuration file not found!\n\n'") + m_conf + tr("'") );
        return;
    }

    if( ui.LEDbxStabel->text().isEmpty() )
    {
        QMessageBox::information( this, winTitle(), tr("Can not start dosbox, no dosbox binary was selected.\nPlease choose dosbox binary.") );
        ui.twDbx->setCurrentIndex( 3 );
        return;
    }
    start( ui.LEDbxStabel->text(), "-conf", m_conf );
}

/**
 * TODO Remove gameprofile from list
 **/
void DBoxFE::slotRemoveGP()
{
    gpItem = new QListWidgetItem;

    gpItem = ui.lwProfile->currentItem();

    if ( gpItem == NULL )
    {
        QMessageBox::information( this, winTitle(), tr("Please select profile for remove from list!") );
        return;
    }

    gpTxt = gpItem->text();

    if( gpTxt.isEmpty() )
    {
        QMessageBox::information( this, winTitle(), tr("Please select profile for remove from list!") );
    }
    else
    {
        m_file = QDir::homePath();
        m_file.append( "/.dboxfe/" + gpTxt + ".conf" );
        QFile f( m_file );

        switch( QMessageBox::information( this, winTitle(), tr("Would you like delete the profile and configuration file?\nIf you click 'No' only the profile from list will be removed."), tr("Yes"), tr("No"), tr("Cancel"), 0, 2 ) )
        {
        case 0: // Yes clicked
            delete ui.lwProfile->currentItem();

            if( f.exists() )
            {
                f.remove();
            }

            ui.lwOutPut->addItem( tr("Game Profile -> ") + gpTxt + tr(" was deleted") );
            ui.lwOutPut->addItem( tr("Game configuration -> ") + f.fileName() + tr(" was deleted") );
            ui.lwOutPut->update();
            break;
        case 1: // No clicked but delete profile from list
            delete ui.lwProfile->currentItem();
            ui.lwOutPut->addItem( tr("Game Profile -> ") + gpTxt + tr(" was deleted") );
            ui.lwOutPut->update();
            break;
        case 2: // Cancel clicked or Escape pressed
            return;
            break;
        }
    }
}

/**
 * TODO Choose snapshot directory
 **/
void DBoxFE::slotSnapDir()
{
    QString strSnap = QFileDialog::getExistingDirectory( this, tr("Open snapshot directory"), QDir::homePath() );
    if ( strSnap.isEmpty() )
        return;

    ui.LESnapDir->setText( strSnap );
}

/**
 * TODO DOSBox language, eg.: german is my language :)
 **/
void DBoxFE::slotLanguage()
{
    QString strLng = QFileDialog::getOpenFileName( this, tr("Open language file"), QDir::homePath(), tr("Language file (*.*)") );
    if ( strLng.isEmpty() )
        return;
    ui.LELanguage->setText( strLng );
}

/**
 * TODO Choose stabel binary of dosbox and return the vesions number
 **/
void DBoxFE::slotChooseDbxBinary()
{
    QString strDbxStabel = QFileDialog::getOpenFileName( this, tr("Open DOSBox binary"), QDir::currentPath(), tr("DOSBox binary (dosbox)") );

    if ( strDbxStabel.isEmpty() )
        return;

    ui.LEDbxStabel->setText( strDbxStabel );

    QProcess *p = new QProcess( this );
    p->start( strDbxStabel, QStringList() << "-version" );

    while( p->waitForFinished() )
        ui.LEDbxVersion->setText( QString( tr("DOSBox Version: ") + p->readAll() ) );
    
    delete p;
}

/**
 * TODO Select game from database and insert in to Autoexec section
 **/
void DBoxFE::slotGame()
{
    DBoxFE_Game *dbfe_game = new DBoxFE_Game();
    if ( dbfe_game->exec() == QDialog::Accepted )
    {
	if( dbfe_game->ui.twGame->currentItem() == NULL )
	{
	    ui.lwAutoexec->addItem( dbfe_game->ui.LEGame->text() );
	    if( dbfe_game->chkBoxExitDosbox->isChecked() == true )
		ui.lwAutoexec->addItem( "exit" );
	}
	else
	{
	    ui.lwAutoexec->addItem( dbfe_game->ui.twGame->currentItem()->text( 1 ) );
	    if( dbfe_game->chkBoxExitDosbox->isChecked() == true )
		ui.lwAutoexec->addItem( "exit" );
	}
    }
}

/**
 * TODO Misc (Modem, Autoexec, Dos)
 **/
void DBoxFE::slotAutexecAdd()
{
    qDebug( "void DBoxFE::slotAutexecAdd()" );
}

/**
 * TODO Autoexec option
 **/
void DBoxFE::slotAutexecRemove()
{
    qDebug( "void DBoxFE::slotSerialRemove()" );
}

/**
 * TODO Update autexec item in the list
 **/
void DBoxFE::slotAutexecUpdate()
{
    qDebug( "void DBoxFE::slotAutexecUpdate()" );
}

/**
 * TODO Open the autexec drive, for automaunt in dosbox
 **/
void DBoxFE::slotAutexecDrive()
{
    qDebug( "void DBoxFE::slotAutexecDrive()" );
}

/**
 * TODO Serial option add
 **/
void DBoxFE::slotSerialAdd()
{
    // Check if the item availabel in the list then show a message and exit function
    QList<QTreeWidgetItem *> it( ui.twSerial->findItems( ui.cbxDSSerial->currentText(), Qt::MatchExactly, 0 ) );
    for( int a = 0; a < it.size(); ++a )
    {
	QTreeWidgetItem *sItem;
	sItem = it.value( a );
	if( sItem->text( a ) == ui.cbxDSSerial->currentText() )
	{
	    QMessageBox::information( this, winTitle(), tr("Can not add the same serial '") + sItem->text( a ) + tr("' port to the list.") );
	    return;
	}
    }

    // Check if the list count higher as 4 then show message and exit function
    if( ui.twSerial->topLevelItemCount() >= 4 )
    {
        QMessageBox::information( this, winTitle(), tr("Can not add 5 serialports to the list, maximal 4 are allow.") );
        return;
    }

    QTreeWidgetItem *item = new QTreeWidgetItem( ui.twSerial );
    item->setText( 0, ui.cbxDSSerial->currentText() );

    QString serialOption;

    switch( ui.cbxDSOption->currentIndex() )
    {
    case 0: // diasabled
        item->setText( 1, ui.cbxDSOption->currentText() );
        break;
    case 1: // dummy
        item->setText( 1, ui.cbxDSOption->currentText() );
        break;
    case 2: // modem
        item->setText( 1, ui.cbxDSOption->currentText() );
        /* TODO Add code*/

        /*
        ui.lblDSComPort->setEnabled( true );
        ui.cbxDSComPort->setEnabled( true );
        ui.lblDSDefaultBps->setEnabled( true );
        ui.LEDSBps->setEnabled( true );
        ui.lblDSListenPort->setEnabled( true );
        ui.LEDSListenPort->setEnabled( true );
        ui.lblDSIrq->setEnabled( false );
        ui.LEDSIrq->setEnabled( false );
        ui.lblDSRealPort->setEnabled( false );
        ui.cbxDSRealPort->setEnabled( false );
        ui.lblDSByteSize->setEnabled( false );
        ui.cbxDSByteSize->setEnabled( false );
        ui.lblDSStopBit->setEnabled( false );
        ui.cbxDSStopBit->setEnabled( false );
        ui.lblDSParity->setEnabled( false );
        ui.cbxDSParity->setEnabled( false );
               */

        break;
    case 3: // directserial
        serialOption = ui.cbxDSOption->currentText() + " " +
                       "realport:" + ui.cbxDSRealPort->currentText() + " " +
                       "startbps:" + ui.LEDSBps->text() + " " +
                       "parity:" + ui.cbxDSParity->currentText() + " " +
                       "bytesize:" + ui.cbxDSByteSize->currentText() + " " +
                       "stopbits:" + ui.cbxDSStopBit->currentText() + " " +
                       "irq:" + ui.LEDSIrq->text();

        item->setText( 1, serialOption );
        break;
    }
}

/**
 * TODO Serial option remove
 **/
void DBoxFE::slotSerialRemove()
{
    QTreeWidgetItem *item = ui.twSerial->currentItem();
    
    if( item == NULL )
    {
        QMessageBox::information( this, winTitle(), tr("No item was selected.") );
        return;
    }
    
    delete item;
}

/**
 * TODO Open the Profilewizard
 **/
void DBoxFE::slotWizard()
{
    DBoxFE_ProfileWizard *dbfe_profilewizard = new DBoxFE_ProfileWizard();

    if ( dbfe_profilewizard->exec() == QDialog::Accepted )
    {
        init();
    }
}

/**
 * TODO Open the configuration file for selected profile
 **/
void DBoxFE::slotListWidget( QListWidgetItem* item )
{
    DB_BASE gpIni;

    QString file;
    file = QDir::homePath();
    file.append( "/.dboxfe/" + item->text() + ".conf" );

    // gpIni.readGPIni( file, ui.lwProfile  );
    gpIni.readConf( file, this );
}

/**
 * TODO Disable/Enable Serial option
 **/
void DBoxFE::slotCbxIndexChanged( int index )
{
    switch( index )
    {
    case 0: // diasabled
        ui.gBoxSerialOption->setEnabled( false );
        break;
    case 1: // dummy
        ui.gBoxSerialOption->setEnabled( false );
        break;
    case 2: // modem
        ui.gBoxSerialOption->setEnabled( true );
        ui.lblDSComPort->setEnabled( true );
        ui.cbxDSComPort->setEnabled( true );
        ui.lblDSDefaultBps->setEnabled( true );
        ui.LEDSBps->setEnabled( true );
        ui.lblDSListenPort->setEnabled( true );
        ui.LEDSListenPort->setEnabled( true );
        ui.lblDSIrq->setEnabled( false );
        ui.LEDSIrq->setEnabled( false );
        ui.lblDSRealPort->setEnabled( false );
        ui.cbxDSRealPort->setEnabled( false );
        ui.lblDSByteSize->setEnabled( false );
        ui.cbxDSByteSize->setEnabled( false );
        ui.lblDSStopBit->setEnabled( false );
        ui.cbxDSStopBit->setEnabled( false );
        ui.lblDSParity->setEnabled( false );
        ui.cbxDSParity->setEnabled( false );
        break;
    case 3: // directserial
        ui.gBoxSerialOption->setEnabled( true );
        ui.lblDSRealPort->setEnabled( true );
        ui.cbxDSRealPort->setEnabled( true );
        ui.lblDSIrq->setEnabled( true );
        ui.LEDSIrq->setEnabled( true );
        ui.lblDSDefaultBps->setEnabled( true );
        ui.LEDSBps->setEnabled( true );
        ui.lblDSByteSize->setEnabled( true );
        ui.cbxDSByteSize->setEnabled( true );
        ui.lblDSStopBit->setEnabled( true );
        ui.cbxDSStopBit->setEnabled( true );
        ui.lblDSParity->setEnabled( true );
        ui.cbxDSParity->setEnabled( true );
        ui.lblDSComPort->setEnabled( false );
        ui.cbxDSComPort->setEnabled( false );
        break;
    }
}

/**
 * TODO Function for start dosbox and read output
 **/
void DBoxFE::start( const QString& bin, const QString &param, const QString &conf )
{
    dBox = new QProcess(this);

    m_param.append( param );
    m_param.append( conf );

    dBox->start( bin, m_param );
    connect( dBox, SIGNAL( readyReadStandardOutput()), this, SLOT( readOutput() ) );
    connect( dBox, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( finish( int, QProcess::ExitStatus ) ) );
    connect( dBox, SIGNAL( error( QProcess::ProcessError ) ), this, SLOT( err( QProcess::ProcessError ) ) );

    if( ui.chkBoxWindowHide->isChecked() == true )
    {
        this->hide();
    }

    ui.btnStartDBox->setEnabled( false );

    m_param.clear();
}

/**
 * TODO Function for start dosbox and read output
 **/
void DBoxFE::readOutput()
{
    while( dBox->canReadLine() )
    {
        m_result = dBox->readLine();
        ui.lwOutPut->addItem( tr("dosbox cmd output -> ") + m_result.mid( m_result.indexOf( ":" ) + 1 ) );
        ui.lwOutPut->update();
    }
}

/**
 * TODO dosbox process was exited
 **/
void DBoxFE::finish(int exitCode, QProcess::ExitStatus exitStatus )
{
    this->show();

    switch( exitStatus )
    {
    case QProcess::NormalExit:
        ui.lwOutPut->addItem( tr("dboxfe: dosbox process exited normally") );
        break;
    case QProcess::CrashExit:
        ui.lwOutPut->addItem( tr("dboxfe: dosbox process crashed") );
        break;
    }

    ui.btnStartDBox->setEnabled( true );
}

/**
 * TODO dosbox process was exited amd have an error returned
 **/
void DBoxFE::err( QProcess::ProcessError error )
{
    this->show();

    switch( error )
    {
    case QProcess::FailedToStart:
        ui.lwOutPut->addItem( tr("dboxfe: the dosbox process failed to start") );
        break;
    case QProcess::Crashed:
        ui.lwOutPut->addItem( tr("dboxfe: dosbox process crashed some time after starting successfully") );
        break;
    case QProcess::Timedout:
        ui.lwOutPut->addItem( tr("dboxfe: last waitFor...() function timed out") );
        break;
    case QProcess::WriteError:
        ui.lwOutPut->addItem( tr("dboxfe: an error occurred when attempting to write to the dosbox process") );
        break;
    case QProcess::ReadError:
        ui.lwOutPut->addItem( tr("dboxfe: an error occurred when attempting to read from the dosbox process") );
        break;
    case QProcess::UnknownError:
        ui.lwOutPut->addItem( tr("dboxfe: An unknown error occurred") );
        break;
    }

    ui.btnStartDBox->setEnabled( true );
}
