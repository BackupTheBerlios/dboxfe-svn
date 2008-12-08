/***************************************************************************
 *   Copyright (C) 2008 by Alexander Saal                                  *
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

#include <messagebox.h>

#include <QtCore>
#include <QtGui>

namespace asaal {

  MessageBox::MessageBox( QWidget *parent, const QString &cmdBtn1Id, const QString &cmdBtn2Id ) : QDialog( parent )  {

    setupUi( this );

    connect( cmdButtonOne, SIGNAL( clicked() ), this, SLOT( commandButtonClicked() ) );
    connect( cmdButtonTwo, SIGNAL( clicked() ), this, SLOT( commandButtonClicked() ) );

    cmdButtonOne->setObjectName( cmdBtn1Id );
    cmdButtonTwo->setObjectName( cmdBtn2Id );
  }

  MessageBox::~MessageBox() {}

  void MessageBox::setMessageBoxTitle( const QString &title ) {

    setWindowTitle( title );
  }

  void MessageBox::setMessageBoxInstruction( const QString &instruction  ) {

    labelInstruction->setText( instruction );
  }

  void MessageBox::setCommandButton1Text( const QString &text  ) {

    cmdButtonOne->setText( text );
  }

  void MessageBox::setCommandButton1Description( const QString &description  ) {

    cmdButtonOne->setDescription( description );
  }

  void MessageBox::setCommandButton2Text( const QString &text  ) {
    
    cmdButtonTwo->setText( text );
  }

  void MessageBox::setCommandButton2Description( const QString &description  ) {
    
    cmdButtonTwo->setDescription( description );
  }

  void MessageBox::commandButtonClicked() {

    QCommandLinkButton *cmdLinkButton = qobject_cast< QCommandLinkButton* >( sender() );
    if( cmdLinkButton ) {

      emit commandLinkButtonClicked( cmdLinkButton );
      accept();
    } else {

      reject();
    }
  }

  void MessageBox::closeEvent( QCloseEvent *e ) {

    e->accept();
  }
}
