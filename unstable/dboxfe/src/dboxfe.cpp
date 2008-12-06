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

#include <base.h>
#include <dboxfe.h>

#include <QtGui>
#include <QtCore>

namespace asaal {

  ConfigBase *configBase;
  DBoxFE *dboxfe;
  DBoxFE::DBoxFE( QWidget *parent, Qt::WFlags flags ) : QWidget( parent, flags ) {

    setupUi( this );

    dboxfe = this;
    configBase = new ConfigBase( dboxfe );

    connect( btnOpenDescriptionText, SIGNAL( clicked() ), this, SLOT( openDescription() ) );
    connect( btnApplyDescriptionText, SIGNAL( clicked() ), this, SLOT( applyDescription() ) );
    connect( btnClearDescriptionText, SIGNAL( clicked() ), this, SLOT( clearDescription() ) );

    connect( btnOpenScreenCapture, SIGNAL( clicked() ), this, SLOT( openScreenCapture() ) );
    connect( btnApplyScreenCapture, SIGNAL( clicked() ), this, SLOT( applyScreenCapture() ) );
    connect( btnClearScreenCapture, SIGNAL( clicked() ), this, SLOT( clearScreenCapture() ) );

    connect( btnStartGame, SIGNAL( clicked() ), this, SLOT( startGame() ) );
    connect( btnNewProfile, SIGNAL( clicked() ), this, SLOT( newGame() ) );
    connect( btnEditProfile, SIGNAL( clicked() ), this, SLOT( editGame() ) );
    connect( btnDeleteProfile, SIGNAL( clicked() ), this, SLOT( deleteGame() ) );

    connect( btnAssistant, SIGNAL( clicked() ), this, SLOT( newGameWithAssistant() ) );

    connect( textEditGameDescription, SIGNAL( customContextMenuRequested( const QPoint & ) ), this, SLOT( textEditCustomContextMenuRequested( const QPoint & ) ) );

    connect( listWidgetGames, SIGNAL( itemClicked( QListWidgetItem * ) ), this, SLOT( listWidgetItemClicked( QListWidgetItem * ) ) );
    connect( listWidgetGames, SIGNAL( itemDoubleClicked( QListWidgetItem * ) ), this, SLOT( listWidgetItemDoubleClicked( QListWidgetItem * ) ) );

    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );
  }

  DBoxFE::~DBoxFE() {

    configBase = NULL;
    dboxfe = NULL;
  }

  void DBoxFE::closeEvent( QCloseEvent *event ) {

    delete configBase;
    configBase = 0;

    delete dboxfe;
    dboxfe = 0;

    event->accept();
    qApp->quit();
    QApplication::quit();
    QCoreApplication::quit();
  }

  void DBoxFE::initialProfiles() {

    QStringList profiles = configBase->readProfiles();
    listWidgetGames->addItems( profiles );

  }

  void DBoxFE::openDescription() {
  }

  void DBoxFE::applyDescription() {
  }

  void DBoxFE::clearDescription() {
  }

  void DBoxFE::openScreenCapture() {
  }

  void DBoxFE::applyScreenCapture() {
  }

  void DBoxFE::clearScreenCapture() {
  }

  void DBoxFE::startGame() {
    initialProfiles();
  }

  void DBoxFE::newGame() {
  }

  void DBoxFE::editGame() {
  }

  void DBoxFE::deleteGame() {
  }

  void DBoxFE::textEditCustomContextMenuRequested( const QPoint &pos ) {
  }

  void DBoxFE::listWidgetItemClicked( QListWidgetItem *item ) {
  }

  void DBoxFE::listWidgetItemDoubleClicked( QListWidgetItem *item ) {
  }

  void DBoxFE::newGameWithAssistant() {
  }

  void DBoxFE::processStart( const QString& bin, const QString &param, const QString &conf ) {
  }

  void DBoxFE::processOutput() {
  }

  void DBoxFE::processFinish( int exitCode, QProcess::ExitStatus exitStatus ) {
  }

  void DBoxFE::processError( QProcess::ProcessError error ) {
  }
}
