/***************************************************************************
                          error.h  -  Error callback
                             -------------------
    begin                : Sat Jul 12 2003
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

#ifndef __NEAPPLICATION_ERROR_H
#define __NEAPPLICATION_ERROR_H

#include "base.h"

#include <neoengine/log.h>


/**
  * \file error.h
  * Error callback
  */





/**
  * \class NeErrorPopup
  * \brief Error callback
  * \author Mattias Jansson (mattias@realityrift.com)
  */
class NeErrorCallback : public NeLogErrorCallback
{
	public:

		/**
		* Process error message
		* \param eLogLevel                            Log level for message (LOGLEVEL_ERROR or LOGLEVEL_PANIC)
		* \param rstrMessage                          Error message
		*/
		virtual void                                  ErrorCallback( NeCore::NELOGLEVEL eLogLevel, const std::string &rstrMessage );
};



#endif
