/***************************************************************************
                   application.h  -  Base application wrapper
                             -------------------
    begin                : Wed Jun 4 2003
    copyright            : (C) 2003 by Reality Rift Studios
    email                : mattias@realityrift.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef __NEAPPLICATION_H
#define __NEAPPLICATION_H

#include "base.h"

#include <neoengine/base.h>
#include <neoengine/resource.h>
#include <neoengine/input.h>
#include <neoengine/rendercaps.h>


/*! External classes */
class NeErrorCallback;




/**
  * \class NeApplication
  * \brief Basic application wrapper class
  * \author Cirdan (gero@dowhatyoufeel.de)
  * \author Mattias Jansson (mattias@realityrift.com)
  */
class NeApplication
{
	protected:

		/*! Main resource manager */
		NeResourceManager                                   *m_pkResourceManager;

		/*! Main input manager */
		NeInputManager                                      *m_pkInputManager;

		/*! Main input group */
		NeInputGroup                                        *m_pkInputGroup;

		/*! Application name */
		std::string                                          m_strAppName;

		/*! Run flag */
		bool                                                 m_bRun;

		/*! Render capabilities */
		NeRenderCaps                                         m_kRenderCaps;

		/*! Error callback */
		NeErrorCallback                                     *m_pkErrorCallback;


	public:

		/**
		* \param rstrAppName                                 Application name string
		*/
		                                                     NeApplication( const std::string &rstrAppName );

		/**
		*/
		virtual                                             ~NeApplication();

		/**
		* Initialize engine and all subsystems
		* \param argc                                        Number of arguments in command line
		* \param argv                                        Command line
		* \return                                            true if successful, false if error
		*/
		virtual bool                                         Initialize( int argc, char **argv );

		/**
		* Shutdown engine and all subsystems
		*/
		virtual void                                         Shutdown();

		/**
		* Run application until Stop() is called
		*/
		virtual void                                         Run();

		/**
		* Stop application
		*/
		virtual void                                         Stop();

		/**
		* Execute a frame
		*/
		virtual void                                         ExecuteFrame();
};



#endif
