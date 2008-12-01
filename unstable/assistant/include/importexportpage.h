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

#ifndef IMPORTEXPORTPAGE_H
#define IMPORTEXPORTPAGE_H

#include <ui_importexportpage.h>

#include <QtGui>

namespace asaal {

  /**
   * \brief ImportExportPage
   * 
   * @author Alexander Saal <alex.saal@gmx.de>
   * @sa http://dboxfe.belios.de/index
   * @date 2008/09/11
   * @version 0.2.5
   * @since 0.2.5
   */ 
  class ImportExportPage : public QWizardPage, public Ui::UiImportExportPage {
      Q_OBJECT

    public:

      /**
       * \brief Constructor of ImportExportPage
       * 
       * @param parent The optional parent widget
       */ 
      ImportExportPage( QWidget *parent = 0 );

      /**
       * \brief Reimplemented from QWizardPage
       * 
       * @return The id from QWizardPage for next page on QWizard
       */ 
      int nextId() const;

      /**
       * \brief Hides the modal dialog and sets the result code to Accepted.
       */ 
      void accept();

    private slots:
      /**
       * \brief Choose D-Fend Reloaded directory
       */
      void chooseDfendDirectory();

      /**
       * \brief Choose D-Fend Reloaded directory
       */
      void chooseDboxFeDirectory();

      /**
       * \brief Make all profiles as marked
       */
      void markAllProfiles();

      /**
       * \brief Make all profiles as unmarked
       */
      void unmarkAllProfiles();

      /**
       * \brief Import D-Fend Reloaded profiles
       *
       * @param path the path of D-Fend profile
       * @param name the name of D-Fend profile
       */
      void importDfendProfiles( const QString &path, const QString &name );

      /**
       * \brief Export DBoxFE profiles
       *
       * @param path the path of DBoxFE profile
       * @param name the name of DBoxFE profile
       */
      void exportDboxFeProfile( const QString &path, const QString &name );

    private:
      QMap< QString, QString > profileList;

  };
}

#endif // IMPORTEXPORTPAGE_H
