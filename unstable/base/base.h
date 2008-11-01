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


#ifndef BASE_H
#define BASE_H

#include <QtCore>

namespace asaal {

  /**
   * @author Alexander Saal <alex.saal@gmx.de>
   * @sa http://dboxfe.belios.de/index
   * @date 2008/31/10
   * @version 0.2.5
   * @since 0.2.5
   */

  class Configuration {

    public:
      /** Set/Get sdl settings */
      QMap< QString, QString > sdl;

      /** Set/Get dosbox settings */
      QMap< QString, QString > dosbox;

      /** Set/Get render settings */
      QMap< QString, QString > render;

      /** Set/Get ipx settings */
      QMap< QString, QString > cpu;

      /** Set/Get mixer settings */
      QMap< QString, QString > mixer;

      /** Set/Get mdi settings */
      QMap< QString, QString > mdi;

      /** Set/Get sblaster settings */
      QMap< QString, QString > sblaster;

      /** Set/Get gus settings */
      QMap< QString, QString > gus;

      /** Set/Get speaker settings */
      QMap< QString, QString > speaker;

      /** Set/Get joystick settings */
      QMap< QString, QString > joystick;

      /** Set/Get serial settings */
      QMap< QString, QString > serial;

      /** Set/Get dos settings */
      QMap< QString, QString > dos;

      /** Set/Get ipx settings */
      QMap< QString, QString > ipx;

      /** Set/Get autoexec settings */
      QString autoexec;


      /**
       * Returns true if other points the same item of other; otherwise returns false.
       */
      bool operator == ( const Configuration &other ) const {
        return sdl == other.sdl &&
               dosbox == other.dosbox &&
               render == other.render &&
               cpu == other.cpu &&
               mixer == other.mixer &&
               mdi == other.mdi &&
               sblaster == other.sblaster &&
               gus == other.gus &&
               speaker == other.speaker &&
               joystick == other.joystick &&
               serial == other.serial &&
               dos == other.dos &&
               ipx == other.ipx &&
               autoexec == other.autoexec;
      }

      /**
       * Returns true if other points to a different item than this other; otherwise returns false.
       */
      bool operator != ( const Configuration &other ) const {
        return sdl != other.sdl ||
               dosbox != other.dosbox ||
               render != other.render ||
               cpu != other.cpu ||
               mixer != other.mixer ||
               mdi != other.mdi ||
               sblaster != other.sblaster ||
               gus != other.gus ||
               speaker != other.speaker ||
               joystick != other.joystick ||
               serial != other.serial ||
               dos != other.dos ||
               ipx != other.ipx ||
               autoexec != other.autoexec;
      }

      /**
       * Returns true if the cache contains no objects; otherwise returns false.
       */
      bool isEmpty() const {
        return sdl.isEmpty() &&
               dosbox.isEmpty() &&
               render.isEmpty() &&
               cpu.isEmpty() &&
               mixer.isEmpty() &&
               mdi.isEmpty() &&
               sblaster.isEmpty() &&
               gus.isEmpty() &&
               speaker.isEmpty() &&
               joystick.isEmpty() &&
               serial.isEmpty() &&
               dos.isEmpty() &&
               ipx.isEmpty() &&
               ( autoexec.isEmpty() || autoexec.isNull() );
      }

      /**
       * Deletes all the objects in the cache.
       */
      void clear() {
        sdl.clear();
        dosbox.clear();
        render.clear();
        cpu.clear();
        mixer.clear();
        mdi.clear();
        sblaster.clear();
        gus.clear();
        speaker.clear();
        joystick.clear();
        serial.clear();
        dos.clear();
        ipx.clear();
        autoexec = QString( "" );
      }
  };

  /**
   * @author Alexander Saal <alex.saal@gmx.de>
   * @sa http://dboxfe.belios.de/index
   * @date 2008/31/10
   * @version 0.2.5
   * @since 0.2.5
   */

  class ConfigBase : public QObject {

      Q_OBJECT

    public:
      /**
       * @brief Constructor
       *
       * @param parent The optional QObject object
       */
      ConfigBase( QObject *parent = 0 );

      /**
       * @brief Destructor
       */
      ~ConfigBase();

      /**
       * Get instance of @link ConfigBase
       */
      inline static ConfigBase* innstance() {

        if ( !m_Instance ) {
          m_Instance = new ConfigBase();
        }

        return m_Instance;
      }

      /**
       * Get @link Configuration for the given profile
       *
       * @param profile The DBoxFE profile
       */
      Configuration readConfiguration( const QString &profile );

      /**
       * Convert D-Fend Reloaded profiles to DBoxFE profiles
       *
       * @param profile The D-Fend Reloaded profile
       */
      Configuration convertConfiguration( const QString &profile );

    public slots:
      /**
       * Convert D-Fend Reloaded profiles to DBoxFE profiles
       *
       * @param profile The DBoxFE profile
       * @param config The @link Configuration
       */
      void writeConfiguration( const QString &profile, const Configuration &config );

    private:
      /**
       * Deletes all the objects in the cache.
       */
      void clearSettings() {
        m_Sdl.clear();
        m_Dosbox.clear();
        m_Render.clear();
        m_Cpu.clear();
        m_Mixer.clear();
        m_Mdi.clear();
        m_Sblaster.clear();
        m_Gus.clear();
        m_Speaker.clear();
        m_Joystick.clear();
        m_Serial.clear();
        m_Dos.clear();
        m_Ipx.clear();
        m_Autoexec = QString( "" );
      }

      static ConfigBase* m_Instance;
      Configuration m_Configuration;
      QObject *m_Parent;

      QMap< QString, QString >  m_Sdl, m_Dosbox, m_Render, m_Cpu, m_Mixer, m_Mdi, m_Sblaster, m_Gus, m_Speaker, m_Joystick, m_Serial,  m_Dos, m_Ipx;
      QString m_Autoexec;
  };
}

#endif // BASE_H
