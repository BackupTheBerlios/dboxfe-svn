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
#include "dboxfe_about.h"
#include "dboxfe_base.h"
#include "dboxfe_gamefile.h"
#include "dboxfe_games.h"
#include "dboxfe_gamesettings.h"
#include "dboxfe_profile.h"
#include "dboxfe_profilewizard.h"

// 3rdparty library
#include "XMLPreferences.h"

// Qt 4 Header
#include <QtCore>
#include <QtGui>


DBoxFE::DBoxFE( QWidget *parent, Qt::WFlags flags ) : QWidget( parent, flags )
{

    setupUi( this );

    // connection
    connect( btnSaveGP, SIGNAL( clicked() ), this, SLOT( slotSaveGP() ) );
    connect( btnRemoveGP, SIGNAL( clicked() ), this, SLOT( slotRemoveGP() ) );
    connect( btnCreateGP, SIGNAL( clicked() ), this, SLOT( slotCreateGP() ) );
    connect( btnWizard, SIGNAL( clicked() ), this, SLOT( slotWizard() ) );
    connect( btnStartDBox, SIGNAL( clicked() ), this, SLOT( slotStartDBox() ) );
    connect( btnLanguage, SIGNAL( clicked() ), this, SLOT( slotLanguage() ) );
    connect( btnDbxStable, SIGNAL( clicked() ), this, SLOT( slotChooseDbxBinary() ) );
    connect( btnAutoexecAdd, SIGNAL( clicked() ), this, SLOT( slotAutoexecAdd() ) );
    connect( btnAutoexecRemove, SIGNAL( clicked() ), this, SLOT( slotAutoexecRemove() ) );
    connect( btnSerialAdd, SIGNAL( clicked() ), this, SLOT( slotSerialAdd() ) );
    connect( btnSerialRemove, SIGNAL( clicked() ), this, SLOT( slotSerialRemove() ) );
    connect( btnAutoexecUpdate, SIGNAL( clicked() ), this, SLOT( slotAutoexecUpdate() ) );
    connect( btnAutoexecDrive, SIGNAL( clicked() ), this, SLOT( slotAutoexecDrive() ) );
    connect( btnAutoexecUp, SIGNAL( clicked() ), this, SLOT( slotAutoexecUp() ) );
    connect( btnAutoexecDown, SIGNAL( clicked() ), this, SLOT( slotAutoexecDown() ) );
    connect( btnGame, SIGNAL( clicked() ), this, SLOT( slotGame() ) );
    connect( btnAbout, SIGNAL( clicked() ), this, SLOT( slotAbout() ) );
    connect( btnGamesettings, SIGNAL( clicked() ), this, SLOT( slotGameSettings() ) );
    connect( lwProfile, SIGNAL( itemClicked( QListWidgetItem* ) ), this, SLOT( slotListWidget( QListWidgetItem* ) ) );
    connect( lwOutPut, SIGNAL( customContextMenuRequested( QPoint ) ), this, SLOT( slotListWidgetOutPut( QPoint ) ) );
    connect( cbxDSOption, SIGNAL( currentIndexChanged( int ) ), this, SLOT( slotCbxSerialIndexChanged( int ) ) );
    connect( cbxAutoexecDirectoryOption, SIGNAL( currentIndexChanged( int ) ), this, SLOT( slotCbxAutoexecIndexChanged( int ) ) );

    // windows title for the application
    titleLin = tr( "DBoxFE - Front End for DOSBox 0.65 - Linux Version " ) + getAppVersion();
    titleWin = tr( "DBoxFE - Front End for DOSBox 0.65 - Windows Version " ) + getAppVersion();
    titleMac = tr( "DBoxFE - Front End for DOSBox 0.65 - Mac Version " ) + getAppVersion();

#ifdef Q_OS_WIN32
    setWindowTitle( titleWin );
#endif

#ifdef Q_OS_MACX
    setWindowTitle( titleMac );
    QApplication::setStyle( "plastique" );
#endif

#ifdef Q_OS_MAC9
    setWindowTitle( titleMac );
    QApplication::setStyle( "plastique" );
#endif

#ifdef Q_OS_UNIX
    setWindowTitle( titleLin );
    QApplication::setStyle( "plastique" );
#endif

    // center the application on desktop screen
    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );

    //setMouseTracking( true );
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
    lwProfile->addItems( sList );
    LEDbxStabel->setText( QString( settGP.getString( "DOSBox", "binary" ) ) );
    LEDbxVersion->setText( QString( settGP.getString( "DOSBox", "version" ) ) );
    cbxLanguage->setCurrentIndex( settGP.getInt( "DBoxFE", "Lng" ) );
    chkBoxWindowHide->setChecked( settGP.getBool( "DBoxFE", "winHide" ) );
    chkBoxStartmapper->setChecked( settGP.getBool( "DBoxFE", "keyMapper" ) );
    gBoxLanguage->setHidden( true );
    btnGameDb->setHidden( true );

    m_file = "";
}

/**
 * TODO Close event
 **/
void DBoxFE::closeEvent( QCloseEvent *e )
{
    slotSaveGP();
    e->accept();
    qApp->quit();
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

    for ( int a = 0; a < lwProfile->count(); ++a ) {
        sList.append( lwProfile->item( a ) ->text() );
    }

    settGP.setStringList( "Profile", "Name", sList );
    settGP.setString( "DOSBox", "binary", LEDbxStabel->text() );
    settGP.setString( "DOSBox", "version", LEDbxVersion->text() );
    settGP.setInt( "DBoxFE", "Lng", cbxLanguage->currentIndex() );
    settGP.setBool( "DBoxFE", "winHide", chkBoxWindowHide->isChecked() );
    settGP.setBool( "DBoxFE", "keyMapper", chkBoxStartmapper->isChecked() );

    settGP.save( m_file );

    //Save configuration
    gpItem = new QListWidgetItem;
    gpItem = lwProfile->currentItem();

    if ( gpItem != NULL ) {
        DB_BASE gpIni;
        m_conf = QDir::homePath();
        m_conf.append( "/.dboxfe/" + gpItem->text() + ".conf" );

        QFile f( m_conf );
        f.remove();
        gpIni.saveConf( m_conf, this );
    }
}

void DBoxFE::slotSearchBin()
{}

/**
 * TODO Create game profile file
 **/
void DBoxFE::slotCreateGP()
{
    gpItem = new QListWidgetItem;
    DBoxFE_Profile *dbfe_profile = new DBoxFE_Profile();

    if ( dbfe_profile->exec() == QDialog::Accepted ) {

		DB_BASE gpIni;
		if( gpIni.isDoubleEntry( dbfe_profile->LEProfile->text(), this ) ) {
			QMessageBox::information( this, winTitle(), tr( "Can not add the same profilename: '" ) + dbfe_profile->LEProfile->text() + tr( "' to the list." ) );
			return;
		}

        gpItem->setText( dbfe_profile->LEProfile->text() );
        lwProfile->addItem( gpItem );
    }
}

/**
 * TODO Start dosbox with configuration file
 **/
void DBoxFE::slotStartDBox()
{
    gpItem = new QListWidgetItem;
    gpItem = lwProfile->currentItem();

    if ( gpItem == NULL ) {
        QMessageBox::information( this, winTitle(), tr( "Please select profile." ) );
        return ;
    }

    gpTxt = gpItem->text();

    m_conf = QDir::homePath();
    m_conf.append( "/.dboxfe/" + gpTxt + ".conf" );

    if ( !QFile( m_conf ).exists() ) {
        QMessageBox::information( this, winTitle(), tr( "Configuration file not found!\n\n'" ) + m_conf + tr( "'" ) );
        return ;
    }

    if ( LEDbxStabel->text().isEmpty() ) {
        QMessageBox::information( this, winTitle(), tr( "Can not start dosbox, no dosbox binary was selected.\nPlease choose dosbox binary." ) );
        twDbx->setCurrentIndex( 3 );
        return ;
    }
    start( LEDbxStabel->text(), "-conf", """" + m_conf + """" );
}

/**
 * TODO Remove gameprofile from list
 **/
void DBoxFE::slotRemoveGP()
{
    gpItem = new QListWidgetItem;

    gpItem = lwProfile->currentItem();

    if ( gpItem == NULL ) {
        QMessageBox::information( this, winTitle(), tr( "Please select profile for remove from list!" ) );
        return ;
    }

    gpTxt = gpItem->text();

    if ( gpTxt.isEmpty() ) {
        QMessageBox::information( this, winTitle(), tr( "Please select profile for remove from list!" ) );
    } else {
        m_file = QDir::homePath();
        m_file.append( "/.dboxfe/" + gpTxt + ".conf" );
        QFile f( m_file );

        switch ( QMessageBox::information( this, winTitle(), tr( "Would you like delete the profile and configuration file?\nIf you click 'No' only the profile from list will be removed." ), tr( "Yes" ), tr( "No" ), tr( "Cancel" ), 0, 2 ) ) {
            case 0:               // Yes clicked
                delete lwProfile->currentItem();

                if ( f.exists() ) {
                    f.remove();
                }

                lwOutPut->addItem( tr( "Game Profile -> " ) + gpTxt + tr( " was deleted" ) );
                lwOutPut->addItem( tr( "Game configuration -> " ) + f.fileName() + tr( " was deleted" ) );
                lwOutPut->update();
                break;
            case 1:               // No clicked but delete profile from list
                delete lwProfile->currentItem();
                lwOutPut->addItem( tr( "Game Profile -> " ) + gpTxt + tr( " was deleted" ) );
                lwOutPut->update();
                break;
            case 2:               // Cancel clicked or Escape pressed
                return ;
                break;
        }
    }
}

/**
 * TODO DOSBox language, eg.: german is my language :)
 **/
void DBoxFE::slotLanguage()
{
    QString strLng = QFileDialog::getOpenFileName( this, tr( "Open language file" ), QDir::homePath(), tr( "Language file (*.*)" ) );
    if ( strLng.isEmpty() )
        return ;
    LELanguage->setText( strLng );
}

/**
 * TODO Choose stabel binary of dosbox and return the vesions number
 **/
void DBoxFE::slotChooseDbxBinary()
{
    QString strDbxStabel = QFileDialog::getOpenFileName( this, tr( "Open DOSBox binary" ), QDir::currentPath(), tr( "DOSBox binary (dosbox);;DOSBox binary (*.exe)" ) );

    if ( strDbxStabel.isEmpty() )
        return ;

#ifdef Q_OS_WIN32

    QFileInfo dboxBin( strDbxStabel );

    QProcess *p = new QProcess( this );
    m_param.append( "-version" );

    p->setWorkingDirectory( dboxBin.absolutePath() );
    p->start( strDbxStabel, m_param );

    while ( p->waitForFinished() ) {
        QFile dboxOutFile( dboxBin.absolutePath() + "/stdout.txt" );

        if ( !dboxOutFile.open( QFile::ReadOnly | QFile::Text ) ) {
            QMessageBox::information( this, winTitle(), tr( "Can not read " ) + dboxOutFile.fileName() );
            delete p;
            return ;
        }

        QTextStream t( &dboxOutFile );
        QString dboxVersion = t.readAll();

        if ( QString( dboxVersion.simplified() ).trimmed().isEmpty() ) {
            QMessageBox::information( this, winTitle(), tr( "This is not a valid dosbox binary." ) );
            delete p;
            return ;
        }

        if ( QString( dboxVersion.simplified() ).trimmed() == "0.65" ) {
            LEDbxStabel->setText( strDbxStabel );
            LEDbxVersion->setText( QString( tr( "DOSBox Version:  " ) + dboxVersion ) );
        } else {
            QMessageBox::information( this, winTitle(), tr( "Wrong dosbox version: " ) + QString( dboxVersion.simplified() ).trimmed() + tr( ", i need 0.65" ) );
            delete p;
            return ;
        }
    }

    m_param.clear();
    delete p;
#else

    QProcess *p = new QProcess( this );
    p->start( strDbxStabel, QStringList() << "-version" );

    while ( p->waitForFinished() ) {
        QString dboxVersion = p->readAll();

        if ( QString( dboxVersion.simplified() ).trimmed().isEmpty() ) {
            QMessageBox::information( this, winTitle(), tr( "This is not a valid dosbox binary." ) );
            delete p;
            return ;
        }

        if ( QString( dboxVersion.simplified() ).trimmed() == "0.65" ) {
            LEDbxStabel->setText( strDbxStabel );
            LEDbxVersion->setText( QString( tr( "DOSBox Version:  " ) + dboxVersion ) );
        } else {
            QMessageBox::information( this, winTitle(), tr( "Wrong dosbox version: " ) + QString( dboxVersion.simplified() ).trimmed() + tr( ", i need 0.65" ) );
            delete p;
            return ;
        }
    }

    delete p;
#endif
}

/**
 * TODO Select game from database and insert in to Autoexec section
 **/
void DBoxFE::slotGame()
{
    DBoxFE_Game * dbfe_game = new DBoxFE_Game();
    if ( dbfe_game->exec() == QDialog::Accepted ) {
        if ( dbfe_game->twGame->currentItem() == NULL ) {
            lwAutoexec->addItem( dbfe_game->LEGame->text() );
            if ( dbfe_game->chkBoxExitDosbox->isChecked() == true )
                lwAutoexec->addItem( "exit" );
        } else {
            lwAutoexec->addItem( dbfe_game->twGame->currentItem() ->text( 1 ) );
            if ( dbfe_game->chkBoxExitDosbox->isChecked() == true )
                lwAutoexec->addItem( "exit" );
        }
    }
}

/**
 * TODO Misc (Modem, Autoexec, Dos)
 **/
void DBoxFE::slotAutoexecAdd()
{
    QList<QListWidgetItem *> it( lwAutoexec->findItems( "mount " + cbxDrive->currentText().toLower(), Qt::MatchContains ) );
    for ( int a = 0; a < it.size(); ++a ) {
        QListWidgetItem *sItem;
        sItem = it.value( a );
        if ( sItem->text().startsWith( "mount " + cbxDrive->currentText().toLower() ) ) {
            QMessageBox::information( this, winTitle(), tr( "Can not add the same drive '" ) + cbxDrive->currentText().toLower() + tr( "' to the list." ) );
            return ;
        }
    }

    QString addStr;

    if ( LEDrives->text().isEmpty() ) {
        QMessageBox::information( this, winTitle(), tr( "No directory was selected." ) );
        return ;
    } else {
        switch ( cbxAutoexecDirectoryOption->currentIndex() ) {
            case 0:               // Default
                if ( chkBoxLabelCDDVD->isChecked() ) {
                    if ( !LEDeviceLabel->text().isEmpty() ) {
                        addStr = "mount " + cbxDrive->currentText().toLower() + " " + LEDrives->text() + " -label " + LEDeviceLabel->text();
                    } else {
                        QMessageBox::information( this, winTitle(), tr( "Please enter a valid name for label." ) );
                        return ;
                    }
                } else {
                    LEDeviceLabel->setText( "" );
                    addStr = "mount " + cbxDrive->currentText().toLower() + " " + LEDrives->text();
                }
                break;
            case 1:               // Use Directory as CD/DVD
                switch ( cbxAutoexecCDDVDROMOption->currentIndex() ) {
                    case 0:             // Windows 2000/XP/Linux
                        if ( chkBoxLabelCDDVD->isChecked() ) {
                            if ( !LEDeviceLabel->text().isEmpty() ) {
                                addStr = "mount " + cbxDrive->currentText().toLower() + " " + LEDrives->text() + " -t cdrom -usecd 0 -ioctl -label " + LEDeviceLabel->text();
                            } else {
                                QMessageBox::information( this, winTitle(), tr( "Please enter a valid name for label." ) );
                                return ;
                            }
                        } else {
                            LEDeviceLabel->setText( "" );
                            addStr = "mount " + cbxDrive->currentText().toLower() + " " + LEDrives->text() + " -t cdrom -usecd 0 -ioctl";
                        }
                        break;
                    case 1:             // Windows 98
                        if ( chkBoxLabelCDDVD->isChecked() ) {
                            if ( !LEDeviceLabel->text().isEmpty() ) {
                                addStr = "mount " + cbxDrive->currentText().toLower() + " " + LEDrives->text() + " -t cdrom -usecd 0 -aspi -label " + LEDeviceLabel->text();
                            } else {
                                QMessageBox::information( this, winTitle(), tr( "Please enter a valid name for label." ) );
                                return ;
                            }
                        } else {
                            LEDeviceLabel->setText( "" );
                            addStr = "mount " + cbxDrive->currentText().toLower() + " " + LEDrives->text() + " -t cdrom -usecd 0 -aspi";
                        }
                        break;
                }
                break;
            case 2:               // Use Directory as Floppy
                if ( chkBoxLabelCDDVD->isChecked() ) {
                    if ( !LEDeviceLabel->text().isEmpty() ) {
                        addStr = "mount " + cbxDrive->currentText().toLower() + " " + LEDrives->text() + " -t floppy -label " + LEDeviceLabel->text();
                    } else {
                        QMessageBox::information( this, winTitle(), tr( "Please enter a valid name for label." ) );
                        return ;
                    }
                } else {
                    LEDeviceLabel->setText( "" );
                    addStr = "mount " + cbxDrive->currentText().toLower() + " " + LEDrives->text() + " -t floppy";
                }
                break;
        }
    }

    if ( chkBoxSwitchDir->isChecked() ) {
        QListWidgetItem * item = new QListWidgetItem( lwAutoexec );
        item->setText( addStr );
        QListWidgetItem *itemDir = new QListWidgetItem( lwAutoexec );
        itemDir->setText( cbxDrive->currentText().toLower() + ":" );
        chkBoxSwitchDir->setChecked( false );
    } else {
        QListWidgetItem *item = new QListWidgetItem( lwAutoexec );
        item->setText( addStr );
    }
    addStr = "";
}

/**
 * TODO Autoexec option
 **/
void DBoxFE::slotAutoexecRemove()
{
    QListWidgetItem * item = lwAutoexec->currentItem();

    if ( item == NULL ) {
        QMessageBox::information( this, winTitle(), tr( "No item was selected." ) );
        return ;
    }

    delete item;
}

/**
 * TODO Update autexec item in the list
 **/
void DBoxFE::slotAutoexecUpdate()
{
    qDebug( "void DBoxFE::slotAutexecUpdate()" );
}

/**
 * TODO Open the autexec drive, for automaunt in dosbox
 **/
void DBoxFE::slotAutoexecDrive()
{
    QString strAutoDrive = QFileDialog::getExistingDirectory( this, tr( "Open directory for mount in dosbox" ), QDir::homePath() );
    if ( strAutoDrive.isEmpty() )
        return ;

    LEDrives->setText( strAutoDrive );
}

/**
 * TODO move autexec item up
 **/
void DBoxFE::slotAutoexecUp()
{
    if ( lwAutoexec->currentItem() == NULL )
        return ;

    if ( lwAutoexec->row( lwAutoexec->currentItem() ) <= 0 )
        return ;

    QListWidgetItem *item = lwAutoexec->currentItem();
    lwAutoexec->insertItem( lwAutoexec->row( lwAutoexec->currentItem() ), lwAutoexec->takeItem( lwAutoexec->row( lwAutoexec->currentItem() ) ) );
    lwAutoexec->setCurrentItem( item );
}

/**
 * TODO move autexec item down
 **/
void DBoxFE::slotAutoexecDown()
{
    if ( lwAutoexec->currentItem() == NULL )
        return ;

    if ( ( lwAutoexec->row( lwAutoexec->currentItem() ) + 1 ) >= lwAutoexec->count() )
        return ;

    lwAutoexec->insertItem( lwAutoexec->row( lwAutoexec->currentItem() ), lwAutoexec->takeItem( lwAutoexec->row( lwAutoexec->currentItem() ) + 1 ) );
}

/**
 * TODO Serial option add
 **/
void DBoxFE::slotSerialAdd()
{
    // Check if the item availabel in the list then show a message and exit function
    QList<QTreeWidgetItem *> it( twSerial->findItems( cbxDSSerial->currentText(), Qt::MatchExactly, 0 ) );
    for ( int a = 0; a < it.size(); ++a ) {
        QTreeWidgetItem *sItem;
        sItem = it.value( a );
        if ( sItem->text( a ) == cbxDSSerial->currentText() ) {
            QMessageBox::information( this, winTitle(), tr( "Can not add the same serial '" ) + sItem->text( a ) + tr( "' port to the list." ) );
            return ;
        }
    }

    // Check if the list count higher as 4 then show message and exit function
    if ( twSerial->topLevelItemCount() >= 4 ) {
        QMessageBox::information( this, winTitle(), tr( "Can not add 5 serialports to the list, maximal 4 are allow." ) );
        return ;
    }

    QTreeWidgetItem *item = new QTreeWidgetItem( twSerial );
    item->setText( 0, cbxDSSerial->currentText() );

    QString serialOption;

    switch ( cbxDSOption->currentIndex() ) {
        case 0:               // diasabled
            item->setText( 1, cbxDSOption->currentText() );
            break;
        case 1:               // dummy
            item->setText( 1, cbxDSOption->currentText() );
            break;
        case 2:               // modem
            serialOption = cbxDSOption->currentText() + " " +
                           "listenport:" + LEDSListenPort->text() + " " +
                           "realport:" + cbxDSRealPort->currentText() + " " +
                           "startbps:" + LEDSBps->text() + " " +
                           "parity:" + cbxDSParity->currentText() + " " +
                           "bytesize:" + cbxDSByteSize->currentText() + " " +
                           "stopbits:" + cbxDSStopBit->currentText() + " " +
                           "irq:" + LEDSIrq->text();

            item->setText( 1, serialOption );
            break;
        case 3:               // directserial
            serialOption = cbxDSOption->currentText() + " " +
                           "realport:" + cbxDSRealPort->currentText() + " " +
                           "startbps:" + LEDSBps->text() + " " +
                           "parity:" + cbxDSParity->currentText() + " " +
                           "bytesize:" + cbxDSByteSize->currentText() + " " +
                           "stopbits:" + cbxDSStopBit->currentText() + " " +
                           "irq:" + LEDSIrq->text();

            item->setText( 1, serialOption );
            break;
    }
}

/**
 * TODO Serial option remove
 **/
void DBoxFE::slotSerialRemove()
{
    QTreeWidgetItem * item = twSerial->currentItem();

    if ( item == NULL ) {
        QMessageBox::information( this, winTitle(), tr( "No item was selected." ) );
        return ;
    }

    delete item;
}

/**
 * TODO Open the Profilewizard
 **/
void DBoxFE::slotWizard()
{
    DBoxFE_ProfileWizard * dbfe_profilewizard = new DBoxFE_ProfileWizard();
    dbfe_profilewizard->dbfe = this;
    if ( dbfe_profilewizard->exec() == QDialog::Accepted ) {
        init();
    }
}

/**
 * TODO Gamepreferences
 **/
void DBoxFE::slotGameSettings()
{
    DBoxFE_GameSettings * dbfe_gamesettings = new DBoxFE_GameSettings();
    dbfe_gamesettings->show();
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

    QFile f( file );
    if ( !f.exists() )
        return ;

    // gpIni.readGPIni( file, lwProfile  );
    gpIni.readConf( file, this );
}

/**
 * TODO Clear Log output or save it ....
 **/
void DBoxFE::slotListWidgetOutPut( QPoint point )
{
    QMenu menu( this );

    QMouseEvent *mevent = new QMouseEvent( QEvent::MouseButtonPress, point, Qt::RightButton, Qt::RightButton, Qt::NoModifier );

    QAction *acClear = new QAction( tr( "Clear" ), this );
    acClear->setIcon( QIcon( QString::fromUtf8( ":/pics/images/cut_16.png" ) ) );

    menu.clear();
    menu.addAction( acClear );

    QAction *mnu = menu.exec( mevent->globalPos() );
    if ( mnu == NULL )
        return ;
    if ( mnu->text() == NULL )
        return ;
    if ( mnu->text().isEmpty() )
        return ;

    if ( mnu->text() == tr( "Clear" ) ) {
        QString logFile;
        logFile = QDir::homePath();
        logFile.append( "/.dboxfe/dboxfe.log" );

        QFile f( logFile );
        if ( f.size() >= 5645 )
            f.rename( "dboxfe-" + QDateTime::currentDateTime().toString( "dd.MM.yyyy : hh:mm:ss" ) + ".log" );

        QFile f1( logFile );

        if ( !f1.open( QFile::Append | QFile::WriteOnly ) ) {
            return ;
        }

        QTextStream t( &f1 );
        t << "**** " << QDateTime::currentDateTime().toString( "dd.MM.yyyy : hh:mm:ss" ) << " ****\n";

        for ( int i = 0; i < lwOutPut->count(); i++ ) {
            t << lwOutPut->item( i ) ->text();
        }

        t << "\n**** " << QDateTime::currentDateTime().toString( "dd.MM.yyyy : hh:mm:ss" ) << " ****\n\n";

        t.flush();
        f1.close();

        lwOutPut->clear();
        return ;
    }
}

/**
 * TODO Disable/Enable Serial option
 **/
void DBoxFE::slotCbxSerialIndexChanged( int index )
{
    switch ( index ) {
        case 0:               // diasabled
            gBoxSerialOption->setEnabled( false );
            break;
        case 1:               // dummy
            gBoxSerialOption->setEnabled( false );
            break;
        case 2:               // modem
            gBoxSerialOption->setEnabled( true );
            lblDSRealPort->setEnabled( true );
            cbxDSRealPort->setEnabled( true );
            lblDSIrq->setEnabled( true );
            LEDSIrq->setEnabled( true );
            lblDSDefaultBps->setEnabled( true );
            LEDSBps->setEnabled( true );
            lblDSByteSize->setEnabled( true );
            cbxDSByteSize->setEnabled( true );
            lblDSStopBit->setEnabled( true );
            cbxDSStopBit->setEnabled( true );
            lblDSParity->setEnabled( true );
            cbxDSParity->setEnabled( true );
            lblDSComPort->setEnabled( false );
            cbxDSComPort->setEnabled( false );
            break;
        case 3:               // directserial
            gBoxSerialOption->setEnabled( true );
            lblDSRealPort->setEnabled( true );
            cbxDSRealPort->setEnabled( true );
            lblDSIrq->setEnabled( true );
            LEDSIrq->setEnabled( true );
            lblDSDefaultBps->setEnabled( true );
            LEDSBps->setEnabled( true );
            lblDSByteSize->setEnabled( true );
            cbxDSByteSize->setEnabled( true );
            lblDSStopBit->setEnabled( true );
            cbxDSStopBit->setEnabled( true );
            lblDSParity->setEnabled( true );
            cbxDSParity->setEnabled( true );
            lblDSComPort->setEnabled( false );
            cbxDSComPort->setEnabled( false );
            break;
    }
}
void DBoxFE::slotCbxAutoexecIndexChanged( int index )
{
    switch ( index ) {
        case 0:               // Default
            lblAutoexecCDDVDROMOption->setEnabled( false );
            cbxAutoexecCDDVDROMOption->setEnabled( false );
            break;
        case 1:               // Use directory as CD/DVD ROM
            lblAutoexecCDDVDROMOption->setEnabled( true );
            cbxAutoexecCDDVDROMOption->setEnabled( true );
            break;
        case 2:               // Use directory as floppy drive
            lblAutoexecCDDVDROMOption->setEnabled( false );
            cbxAutoexecCDDVDROMOption->setEnabled( false );
            break;
    }
}

void DBoxFE::slotAbout()
{
    DBoxFE_About * about = new DBoxFE_About( 0 );
    about->show();
}

/**
 * TODO Function for start dosbox and read output
 **/
void DBoxFE::start( const QString& bin, const QString &param, const QString &conf )
{

    dBox = new QProcess( this );

#ifdef Q_OS_WIN32

    m_param.append( "-noconsole" );
#endif

    m_param.append( param );
    m_param.append( conf );

    if ( chkBoxStartmapper->isChecked() )
        m_param.append( "-startmapper" );

#ifdef Q_OS_WIN32

    QFileInfo dboxBin( conf );
    dBox->setWorkingDirectory( dboxBin.absolutePath() );
#endif

    dBox->start( bin, m_param );

    connect( dBox, SIGNAL( readyReadStandardOutput() ), this, SLOT( readOutput() ) );
    connect( dBox, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( finish( int, QProcess::ExitStatus ) ) );
    connect( dBox, SIGNAL( error( QProcess::ProcessError ) ), this, SLOT( err( QProcess::ProcessError ) ) );


    if ( chkBoxWindowHide->isChecked() == true ) {
        this->hide();
    }

    btnStartDBox->setEnabled( false );

    m_param.clear();
}

/**
 * TODO Function for start dosbox and read output 
 **/
void DBoxFE::readOutput()
{
    while ( dBox->canReadLine() ) {
        m_result = dBox->readLine();
        lwOutPut->addItem( tr( "dosbox cmd output -> " ) + m_result.mid( m_result.indexOf( ":" ) + 1 ) );
        lwOutPut->update();
    }
}

/**
 * TODO dosbox process was exited
 **/
void DBoxFE::finish( int exitCode, QProcess::ExitStatus exitStatus )
{
    this->show();

#ifdef Q_OS_WIN32

    QString path, outLine;
    path = QDir::homePath();
    path.append( "/.dboxfe/stdout.txt" );

    QFile outFile( path );

    if ( !outFile.open( QFile::ReadOnly | QFile::Text ) ) {
        QMessageBox::information( this, winTitle(), tr( "Can not read file " ) + path );
        outFile.close();
        return ;
    }

    QTextStream t( &outFile );
    while ( !t.atEnd() ) {
        outLine = t.readLine();
        lwOutPut->addItem( tr( "dosbox cmd output -> " ) + outLine.mid( outLine.indexOf( ":" ) + 1 ) );
        lwOutPut->update();
    }

    outFile.close();
#endif

    switch ( exitStatus ) {
        case QProcess::NormalExit:
            lwOutPut->addItem( tr( "dboxfe: dosbox process exited normally" ) );
            qDebug() << exitCode;
            break;
        case QProcess::CrashExit:
            lwOutPut->addItem( tr( "dboxfe: dosbox process crashed" ) );
            qDebug() << exitCode;
            break;
    }

    btnStartDBox->setEnabled( true );
}

/**
 * TODO dosbox process was exited amd have an error returned
 **/
void DBoxFE::err( QProcess::ProcessError error )
{
    this->show();

    switch ( error ) {
        case QProcess::FailedToStart:
            lwOutPut->addItem( tr( "dboxfe: the dosbox process failed to start" ) );
            break;
        case QProcess::Crashed:
            lwOutPut->addItem( tr( "dboxfe: dosbox process crashed some time after starting successfully" ) );
            break;
        case QProcess::Timedout:
            lwOutPut->addItem( tr( "dboxfe: last waitFor...() function timed out" ) );
            break;
        case QProcess::WriteError:
            lwOutPut->addItem( tr( "dboxfe: an error occurred when attempting to write to the dosbox process" ) );
            break;
        case QProcess::ReadError:
            lwOutPut->addItem( tr( "dboxfe: an error occurred when attempting to read from the dosbox process" ) );
            break;
        case QProcess::UnknownError:
            lwOutPut->addItem( tr( "dboxfe: An unknown error occurred" ) );
            break;
    }

    btnStartDBox->setEnabled( true );
}
