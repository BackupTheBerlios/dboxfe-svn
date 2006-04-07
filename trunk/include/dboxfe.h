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

#ifndef DBOXFE_H
#define DBOXFE_H

#include <QtGui>
#include <QtCore>

#include "ui_dboxfe.h"

class DBoxFE : public QWidget
{
    Q_OBJECT

public:
    DBoxFE(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~DBoxFE();
    
    Ui::DBoxFE ui;
    QString getAppVersion(){ return tr("v0.1.0"); }
    QString winTitle(){ return tr("DBox Front End"); }
    
private:
    QString titleLin, titleWin, titleMac, gpTxt, m_result, m_conf, m_file;
    QStringList m_param;
    QProcess *dBox;
    QListWidgetItem *gpItem;
    
protected:
    void closeEvent( QCloseEvent *e );
    
private slots:
    void slotListWidget( QListWidgetItem* );
    void slotCbxSerialIndexChanged( int );
    void slotCbxAutoexecIndexChanged( int );
    void slotAutexecDrive();
    void slotAutexecUpdate();
    void slotAutexecRemove();
    void slotAutexecAdd();
    void slotSerialRemove();
    void slotSerialAdd();
    void slotChooseDbxBinary();
    void slotLanguage();
    void slotRemoveGP();
    void slotStartDBox();
    void slotGame();
    void slotCreateGP();
    void slotSaveGP();
    void slotWizard();
    void slotSearchBin();
    
    void start( const QString& bin, const QString &param, const QString &conf );
    void readOutput();
    void finish(int, QProcess::ExitStatus);
    void err( QProcess::ProcessError );
    
public slots:
    void init();
};

#endif // DBOXFE_H
