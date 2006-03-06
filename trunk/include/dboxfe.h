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

#include <QtGui/QWidget>
#include <QtGui/QCloseEvent>
#include <QtGui/QListWidgetItem>
#include <QtCore/QProcess>
#include <QtCore/QString>

#include "ui_dboxfe.h"

class DBoxFE : public QWidget
{
    Q_OBJECT

public:
    DBoxFE(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~DBoxFE();

    Ui::DBoxFE ui;

private:
    QString getAppVersion()
    {
        return "v0.1.0";
    }

    QString titleLin, titleWin, titleMac, appVersion, gpTxt, winTitle, m_result;
    QStringList m_param;
    QProcess *dBox;
    QListWidgetItem *gpItem;

protected:
    void closeEvent( QCloseEvent *e );

private slots:
    void slotListWidget( QListWidgetItem* );
    void slotAutexecDrive();
    void slotAutexecUpdate();
    void slotAutexecRemove();
    void slotAutexecAdd();
    void slotDbxCvs();
    void slotDbxStable();
    void slotLanguage();
    void slotSnapDir();
    void slotRemoveGP();
    void slotStartDBox();
    void slotCreateGP();
    void slotSaveGP();

    void start( const QString& bin, const QString &param, const QString &conf );
    void readOutput();
    void finish();

public slots:
    void init();
};

#endif // DBOXFE_H
