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

#ifndef INSTALLPROCESSPAGE_H
#define INSTALLPROCESSPAGE_H

#include <ui_installprocesspage.h>

#include <QtGui>

namespace asaal {

  /**
   * @brief $(CLASSNAME)
   * 
   * @author Alexander Saal <alex.saal@gmx.de>
   * @sa http://dboxfe.belios.de/index
   * @date 2008/09/11
   * @version 0.2.5
   * @since 0.2.5
   */ 
  class InstallProcessPage : public QWizardPage, public Ui::UiInstallProcessPage {
      Q_OBJECT

    public:
      /**
       * @brief $(CONSTRUCTORNAME)
       *
       * @param parent the optional parent widget
       */
      InstallProcessPage( QWidget *parent = 0 );

      /**
       * \brief Reimplemented from QWizardPage
       * 
       * @return The ID from QWizardPage for next page on QWizard
       */ 
      int nextId() const;

    private slots:
      /**
       * \brief Prepare installation
       */ 
      void prepareInstallation();

      /**
       * \brief Install game with dosbox
       * 
       * @param bin The dosbox binary
       * @param param The QStringList with all parameters
       * @param conf The dosbox configuration file
       * @param button 
       */ 
      void install( const QString& bin, const QString &param, const QString &conf, QAbstractButton *button = 0 );

      /**
       * \brief 
       */ 
      void processReadOutput();

      /**
       * \brief 
       * 
       * @param 
       * @param 
       */ 
      void processFinish( int, QProcess::ExitStatus );

      /**
       * \brief 
       * 
       * @param 
       */ 
      void processError( QProcess::ProcessError );

    private:
      QString dosBoxBinary;
      QString installSetupFile;
      QString installFolder;
      QString m_OutputResult;
      QStringList m_param;
      QProcess *m_installProcess;
  };
}

#endif // INSTALLPROCESSPAGE_H
