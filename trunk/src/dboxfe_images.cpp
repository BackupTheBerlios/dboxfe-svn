/*
*   Copyright (C) 2004 - 2007 by Alexander Saal <alex.saal@gmx.de>
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

#include "dboxfe_base.h"
#include "dboxfe_images.h"

// 3rdparty library
#include "XMLPreferences.h"

// Qt 4 Header
#include <QtCore>
#include <QtGui>

DBoxFE_Image::DBoxFE_Image( QDialog *parent, Qt::WFlags flags ) : QDialog( parent, flags ) {
  setupUi( this );

  // connection
  connect( btnApply, SIGNAL( clicked() ), this, SLOT( slotApply() ) );
  connect( btnAbort, SIGNAL( clicked() ), this, SLOT( slotAbort() ) );

  // center the wiget on desktop screen
  QDesktopWidget *desktop = qApp->desktop();
  const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
  int left = ( rect.width() - width() ) / 2;
  int top = ( rect.height() - height() ) / 2;
  setGeometry( left, top, width(), height() );
}

DBoxFE_Image::~DBoxFE_Image() {}

void DBoxFE_Image::slotApply() {
  QListWidgetItem * qlwItem = lwImage->currentItem();

  if ( qlwItem == NULL ) {
    QMessageBox::information( this, "DBox Front End", "No item was selected." );
  }

  QDialog::accept();
}

void DBoxFE_Image::slotAbort() {
  QDialog::reject();
}
