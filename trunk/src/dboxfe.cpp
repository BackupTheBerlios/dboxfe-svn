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
#include "dboxfe_profile.h"
#include "dboxfe_base.h"

// QtGui Header
#include <QtGui/QFileDialog>
#include <QtGui/QWidget>
#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QDesktopWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QCloseEvent>

// QtCore Header
#include <QtCore/QProcess>
#include <QtCore/QStringList>
#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QRect>

DBoxFE::DBoxFE(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
  ui.setupUi(this);

  // connection
  connect( ui.btnSaveGP, SIGNAL( clicked() ), this, SLOT( slotSaveGP() ) );
  connect( ui.btnRemoveGP, SIGNAL( clicked() ), this, SLOT( slotRemoveGP() ) );
  connect( ui.btnCreateGP, SIGNAL( clicked() ), this, SLOT( slotCreateGP() ) );
  connect( ui.btnStartDBox, SIGNAL( clicked() ), this, SLOT( slotStartDBox() ) );

  connect( ui.btnSnapDir, SIGNAL( clicked() ), this, SLOT( slotSnapDir() ) );
  connect( ui.btnLanguage, SIGNAL( clicked() ), this, SLOT( slotLanguage() ) );
  connect( ui.btnDbxStable, SIGNAL( clicked() ), this, SLOT( slotDbxStable() ) );
  connect( ui.btnDbxCvs, SIGNAL( clicked() ), this, SLOT( slotDbxCvs() ) );

  connect( ui.btnAutexecAdd, SIGNAL( clicked() ), this, SLOT( slotAutexecAdd() ) );
  connect( ui.btnAutexecRemove, SIGNAL( clicked() ), this, SLOT( slotAutexecRemove() ) );
  connect( ui.btnAutexecUpdate, SIGNAL( clicked() ), this, SLOT( slotAutexecUpdate() ) );
  connect( ui.btnAutexecDrive, SIGNAL( clicked() ), this, SLOT( slotAutexecDrive() ) );

  // itemChanged
  connect( ui.lwProfile, SIGNAL( itemClicked( QListWidgetItem* ) ), this, SLOT( slotListWidget( QListWidgetItem* ) ) );

  // windows title for the application
  appVersion = getAppVersion();

  titleLin = "DOSBox - Front End for Linux " + appVersion;
  titleWin = "DOSBox - Front End for Windows " + appVersion;
  titleMac = "DOSBox - Front End for Mac " + appVersion;

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

void DBoxFE::closeEvent( QCloseEvent *e )
{
  slotSaveGP();
  e->accept();
}

void DBoxFE::init()
{
  DB_BASE gpIni;

  QString file;
  file = QDir::homePath();
  file.append( "/.dboxfe/profile/profile.ini" );
  gpIni.readGPIni( file, ui.lwProfile );
}

// ############### Profile ###############
void DBoxFE::slotSaveGP()
{
  DB_BASE gpIni;

  QString file;
  file = QDir::homePath();
  file.append( "/.dboxfe/profile/profile.ini" );

  gpIni.saveGPIni( file, ui.lwProfile );
}

void DBoxFE::slotCreateGP()
{
  // create new profileitem
  QListWidgetItem *gpItem = new QListWidgetItem;

  // create new instance
  DBoxFE_Profile *dbfe_profile = new DBoxFE_Profile();


  if ( dbfe_profile->exec() == QDialog::Accepted )
  {
    gpItem->setText( dbfe_profile->ui.LEProfile->text() );
    ui.lwProfile->addItem( gpItem );
  }
}

void DBoxFE::slotStartDBox()
{
  DB_BASE gpIni;
  QStringList out = gpIni.start( "dosbox", "-conf", ""  );

  for( int x = 0; x < out.count(); ++x )
  {
    ui.lwOutPut->addItem( out.value( x ) );
  }
}

void DBoxFE::slotRemoveGP()
{
  gpItem = new QListWidgetItem;

  gpItem = ui.lwProfile->currentItem();
  winTitle = windowTitle();

  if ( gpItem == NULL )
  {
    QMessageBox::information( this, winTitle, "Please select profile to delet it!" );
    return;
  }

  gpTxt = gpItem->text();

  if( gpTxt.isEmpty() )
  {
    QMessageBox::information( this, winTitle, "Please select a profile to delet it!" );
  }
  else
  {
    switch( QMessageBox::information( this, winTitle, "Would you delete the configutation file for this Profile?\nIf you click 'No' only the profile from list will be delete.", "Yes", "No", "Cancel", 0, 2 ) )
    {
    case 0: // Yes clicked
      delete ui.lwProfile->currentItem();
      ui.lwOutPut->addItem( "Game Profile -> " + gpTxt + " was deleted" );
      ui.lwOutPut->update();
      break;
    case 1: // No clicked but delete profile from list
      delete ui.lwProfile->currentItem();
      ui.lwOutPut->addItem( "Game Profile -> " + gpTxt + " was deleted" );
      ui.lwOutPut->update();
      break;
    case 2: // Cancel clicked or Escape pressed
      return;
      break;
    }

  }
}

void DBoxFE::slotSnapDir()
{
  qDebug( "void DBoxFE::slotSnapDir()" );
}

// ############### DOSBox ###############
void DBoxFE::slotLanguage()
{
  qDebug( "void DBoxFE::slotLanguage()" );
}

void DBoxFE::slotDbxStable()
{
  qDebug( "void DBoxFE::slotDbxStable()" );
}

void DBoxFE::slotDbxCvs()
{
  qDebug( "void DBoxFE::slotDbxCvs()" );
}

// ############### Misc (Modem, Autoexec, Dos) ###############
void DBoxFE::slotAutexecAdd()
{
  qDebug( "void DBoxFE::slotAutexecAdd()" );
}

void DBoxFE::slotAutexecRemove()
{
  qDebug( "void DBoxFE::slotAutexecRemove()" );
}

void DBoxFE::slotAutexecUpdate()
{
  qDebug( "void DBoxFE::slotAutexecUpdate()" );
}

void DBoxFE::slotAutexecDrive()
{
  qDebug( "void DBoxFE::slotAutexecDrive()" );
}

void DBoxFE::slotListWidget(QListWidgetItem* item)
{
  DB_BASE gpIni;

  QString file;
  file = QDir::homePath();
  file.append( "/.dboxfe/profile/" + item->text() + ".conf" );

  //gpIni.readGPIni( file, ui.lwProfile  );
  gpIni.readDBConf( file, this );
}
