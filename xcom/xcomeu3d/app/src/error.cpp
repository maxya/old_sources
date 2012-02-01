/***************************************************************************
                        error.cpp  -  Error callback
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

#include "error.h"

#include <string>

using namespace std;


std::string g_strError;



void NeErrorCallback::ErrorCallback( NeCore::NELOGLEVEL eLogLevel, const string &rstrMessage )
{
	g_strError += rstrMessage;
}


