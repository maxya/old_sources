/***************************************************************************
             main.cpp  -  Entry points for NeoEngine applications
                             -------------------
    begin                : Mon Jun 2 2003
    copyright            : (C) 2003 by Reality Rift Studios
    email                : mattias@realityrift.com
 **************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "base.h"
#include "xcomeu3d.h"
#include "error.h"

#include <neoengine/base.h>
#include <neoengine/strutil.h>

#ifdef WIN32
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  include <windows.h>
#endif

using namespace NeCore;
using namespace std;


std::string g_strRootPath = ".";


inline int real_main( int argc, char **argv )
{
	/*! Change this to your application object */
	NXComEU3D *pkApp = new NXComEU3D( "XCOM: Enemy Unknown 3D" );

	if( pkApp->Initialize( argc, argv ) )
		pkApp->Run();

	pkApp->Shutdown();

	delete pkApp;

	return 0;
}






#if defined( WIN32 ) && !defined( _CONSOLE )

/*! Win32 entry point, credits to Microsoft for ignoring yet another standard... */

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	//Get command line on argc/argv format
	//Get and parse command line
	int    argc = 0;
	char **argv = 0;

	{
		char *pszCmdLineReal = strdup( GetCommandLine() );

		char *pszCmdLine     = pszCmdLineReal;

		vector<char*> vpszCmdLine;

		//If executable path contains spaces, it will be quoted
		if( *pszCmdLine == '\"' )
		{
			++pszCmdLine;

			while( *pszCmdLine++ != '\"' );

			*pszCmdLine++ = 0;
			
			vpszCmdLine.push_back( pszCmdLineReal );
		}

		Explode( " \t", pszCmdLine, &vpszCmdLine );

		argv = new char*[ vpszCmdLine.size() ];

		vector<char*>::iterator ppszArg = vpszCmdLine.begin();
		vector<char*>::iterator ppszEnd = vpszCmdLine.end();

		for( ; ppszArg != ppszEnd; ++ppszArg, ++argc )
			argv[ argc ] = strdup( *ppszArg );

		free( pszCmdLineReal );
	}

	int iRet = real_main( argc, argv );

	//Free memory
	for( int i = 0; i < argc; ++i )
		free( argv[i] );

	delete [] argv;

	if( g_strError.length() )
		MessageBox( 0, g_strError.c_str(), "Error", MB_OK );

	return iRet;
}

#else

/*! Normal entry point */

int main( int argc, char **argv )
{
	return real_main( argc, argv );
}

#endif


