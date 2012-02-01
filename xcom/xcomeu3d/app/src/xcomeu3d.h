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

#ifndef __NXCOMEU3D_XCOMEU3D_H
#define __NXCOMEU3D_XCOMEU3D_H

#include "application.h"

#include <neoengine/timer.h>
#include <neoengine/vertex.h>
#include <neoengine/polygon.h>


/*! External classes */
class NeErrorCallback;


/**
  * \class NXComEU3D
  * \brief X-COM: Enemy Unknown 3D application class
  * \author Yarik Kolomiyets (yarik@vershynin.com)
  */
class NXComEU3D : NeApplication
{
	protected:

		/*! temp */
		NeVertexBufferPtr    g_pkVertexBuffer;
		NePolygonBufferPtr   g_pkPolygonBuffer;

		/*! FPS timer*/
		NeTimer            m_kFPSTimer;

		/*! Holds current FPS value*/
		float              m_fFPS;

	public:

		/**
		* \param rstrAppName                                 Application name string
		*/
		                                                     NXComEU3D( const std::string &rstrAppName );

		/**
		*/
		virtual                                             ~NXComEU3D();

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
