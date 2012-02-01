/***************************************************************************
              base.h  -  Base includes and defines for application
                             -------------------
    begin                : Sun Jun 15 2003
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

#ifndef __NEAPPLICATION_BASE_H
#define __NEAPPLICATION_BASE_H

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <string>

/*! Root project path relative program binary location */
extern std::string g_strRootPath;

/*! Error string */
extern std::string g_strError;


#endif

