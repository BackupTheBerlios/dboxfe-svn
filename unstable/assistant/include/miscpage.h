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

#ifndef MISCPAGE_H
#define MISCPAGE_H

#include <ui_miscpage.h>

#include <QtCore>
#include <QtGui>

namespace asaal {

  /**
   * @brief MiscPage
   * 
   * @author Alexander Saal <alex.saal@gmx.de>
   * @sa http://dboxfe.belios.de/index
   * @date 2008/09/11
   * @version 0.2.5
   * @since 0.2.5
   */ 
  class MiscPage : public QWizardPage, public Ui::UiMiscPage {
      Q_OBJECT

    public:
      /**
       * \brief  Constructor of MiscPage
       *
       * @param parent the optional parent widget
       */
      MiscPage( QWidget *parent = 0 );

      /**
       * \brief Reimplemented from QWizardPage.
       * 
       * @return The ID from QWizardPage for next page on QWizard
       */ 
      int nextId() const;

      /**
       * \brief Get field widget value.
       * 
       * @param fieldName The registered field name on QWizardPage
       */ 
      QVariant fieldWidgetValue( const QString &fieldName );
  };
}

#endif // MISCPAGE_H
