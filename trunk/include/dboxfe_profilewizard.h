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

#ifndef DBOXFE_PROFILEWIZARD_H
#define DBOXFE_PROFILEWIZARD_H

#include <QtGui>

#include "dboxfe.h"
#include "ui_profilewizard.h"

class QString;
class QStringList;
class QFile;
class QHttp;
class QHttpResponseHeader;

class DBoxFE_ProfileWizard : public QDialog
{
    Q_OBJECT

public:
    DBoxFE_ProfileWizard(QDialog *parent = 0, Qt::WFlags flags = 0);
    ~DBoxFE_ProfileWizard();

private:
    Ui::DBoxFE_ProfileWizard ui;
    
    DBoxFE dbfe;
    
    QStringList gpList;
    QString m_gp_file;
    QHttp *m_http;
    QFile *m_file;
    
    int httpGetId;
    bool httpRequestAborted;
  
private slots:
    void slotBack();
    void slotNext();
    void slotHelp();
    void slotAbort();
    void slotFinish();
    void slotSelectDir();
    void slotSearch();
    void downloadFile();
    
    void httpRequestFinished( int requestId, bool error );
    void readResponseHeader( const QHttpResponseHeader &responseHeader );
};

#endif // DBOXFE_PROFILEWIZARD_H
