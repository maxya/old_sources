/***************************************************************************
                systeminput.h  -  System input event processor
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

#ifndef __NEAPPLICATION_SYSTEMINPUT_H
#define __NEAPPLICATION_SYSTEMINPUT_H

#include "base.h"

#include <neoengine/input.h>


/*! External classes */
class NeApplication;



/**
  * \class NeApplicationSystemInput
  * \brief System input event processor
  * \author Mattias Jansson (mattias@realityrift.com)
  */
class NeApplicationSystemInput : public NeInputEntity
{
	protected:

		/*! Application object */
		NeApplication                                       *m_pkApplication;


	public:

		/**
		* \param pkGroup                                     Input group
		* \param pkApplication                               Application object
		*/
		                                                     NeApplicationSystemInput( NeInputGroup *pkGroup, NeApplication *pkApplication );

		/**
		* Process system events
		* \param pkEvent                                     Input event
		*/
		virtual void                                         Input( const NeInputEvent *pkEvent );
};






#endif
