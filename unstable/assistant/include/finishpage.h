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

#ifndef FINSIHPAGE_H
#define FINSIHPAGE_H

#include <ui_finishpage.h>

#include <QtGui>

namespace asaal {

  /**
   * \brief FinishPage
   * 
   * @author Alexander Saal
   * @sa http://dboxfe.belios.de/index
   * @date 2008/11/24
   * @version 0.2.5
   * @since 0.2.5
   */ 
  class FinishPage : public QWizardPage, public Ui::UiFinishPage {
      Q_OBJECT

    public:
      /**
       * \brief Constructor
       * 
       * @param parent Tho optional qwidget
       */ 
      FinishPage( QWidget *parent = 0 );

      /**
       * \brief The next id of QWizardPage
       * 
       * @return The next id for the wizard page or -1 for finish page.
       */ 
      int nextId() const;
  };
}

#endif // FINSIHPAGE_H
