/***************************************************************************
               systeminput.cpp  -  System input event processor
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

#include "application.h"
#include "systeminput.h"




NeApplicationSystemInput::NeApplicationSystemInput( NeInputGroup *pkGroup, NeApplication *pkApplication ) :
	NeInputEntity( pkGroup ),
	m_pkApplication( pkApplication )
{
}


void NeApplicationSystemInput::Input( const NeInputEvent *pkEvent )
{
	if( ( pkEvent->m_iType == NEIE_SYSEVENT ) && ( pkEvent->m_aArgs[0].m_iData == NEIE_SYSEVENT_KILL ) )
		m_pkApplication->Stop();
	else if( pkEvent->m_iType == NEIE_KEYDOWN ) switch( pkEvent->m_aArgs[0].m_iData ) {

		case NEKC_F1:
		{
			NeCore::g_pkConsole->Toggle();
			break;
		}

		default:
			break;
	}
}


