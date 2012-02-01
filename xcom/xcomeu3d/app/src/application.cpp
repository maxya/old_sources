/***************************************************************************
                 application.cpp  -  Base application wrapper
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
#include "error.h"

#include <neoengine/render.h>
#include <neoengine/log.h>
#include <neoengine/config.h>
#include <neoengine/texture.h>
#include <neoengine/strutil.h>

#ifdef WIN32
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  include <windows.h>
#endif

using namespace NeCore;
using namespace std;







NeApplication::NeApplication( const string &rstrAppName ) :
	m_pkResourceManager( 0 ),
	m_pkInputManager( 0 ),
	m_pkInputGroup( 0 ),
	m_strAppName( rstrAppName ),
	m_bRun( false ),
	m_pkErrorCallback( 0 )
{
}



NeApplication::~NeApplication()
{
}



bool NeApplication::Initialize( int argc, char **argv )
{
	#ifdef _DEBUG
	NeCore::SetLogLevel( LOGLEVEL_DEBUG );
	NeCore::SetLogOutput( LOGOUTPUT_STDOUT | LOGOUTPUT_FILE | LOGOUTPUT_CONSOLE );
	NeCore::SetLogFlush( LOGFLUSHMODE_LINE );
	#else
	NeCore::SetLogLevel( LOGLEVEL_INFO );
	NeCore::SetLogOutput( LOGOUTPUT_STDOUT | LOGOUTPUT_FILE | LOGOUTPUT_CONSOLE );
	NeCore::SetLogFlush( LOGFLUSHMODE_NONE );
	#endif

	NeoEngineInit( argc, argv );

	m_pkErrorCallback = new NeErrorCallback;

	NeCore::SetErrorCallback( m_pkErrorCallback );

	if( g_strRootPath != "." )
	{
#ifdef WIN32
		SetCurrentDirectory( g_strRootPath.c_str() );
#elif defined(POSIX) || defined(__APPLE__)
		chdir( g_strRootPath.c_str() );
#endif
	}

	NeFile *pkFile = new NeFile( "", "neoengine.cfg", NeFile::BINARY | NeFile::READ, false, 0 );

	if( !g_pkConfig->Load( pkFile ) )
	{
		Log( LOGLEVEL_ERROR, " *** unable to load config file\n" );
		return false;
	}

	delete pkFile;

	#ifdef _DEBUG
	g_pkConfig->Print();
	#endif

	{
		string strDebug;

		if( g_pkConfig->GetValue( "LogLevel", &strDebug ) )
		{
			if( strDebug == "debug" )
				NeCore::SetLogLevel( LOGLEVEL_DEBUG );
			else if( strDebug == "info" )
				NeCore::SetLogLevel( LOGLEVEL_INFO );
			else if( strDebug == "warning" )
				NeCore::SetLogLevel( LOGLEVEL_WARNING );
			else if( strDebug == "error" )
				NeCore::SetLogLevel( LOGLEVEL_ERROR );
			else if( strDebug == "panic" )
				NeCore::SetLogLevel( LOGLEVEL_PANIC );
		}

		if( g_pkConfig->GetValue( "LogOutput", &strDebug ) )
		{
			int iOutput = 0;

			if( strDebug.find( "stdout" ) != string::npos )
				iOutput |= LOGOUTPUT_STDOUT;
			if( strDebug.find( "file" ) != string::npos )
				iOutput |= LOGOUTPUT_FILE;
			if( strDebug.find( "console" ) != string::npos )
				iOutput |= LOGOUTPUT_CONSOLE;

			NeCore::SetLogOutput( iOutput );
		}

		if( g_pkConfig->GetValue( "LogFlush", &strDebug ) )
		{
			if( strDebug == "none" )
				NeCore::SetLogFlush( NeCore::LOGFLUSHMODE_NONE );
			else if( strDebug == "line" )
				NeCore::SetLogFlush( NeCore::LOGFLUSHMODE_LINE );
			else if( strDebug == "force" )
				NeCore::SetLogFlush( NeCore::LOGFLUSHMODE_FORCE );
		}
	}

	m_pkResourceManager = new NeResourceManager( "main resource manager" );

	//Get resource and module paths from config
	{
		vector< string > vstrPaths;
		string           strPaths;

		if( g_pkConfig->GetValue( "ResourcePaths", &strPaths ) )
			Explode( " ", strPaths, &vstrPaths );

		vector< string >::iterator pstrPath    = vstrPaths.begin();
		vector< string >::iterator pstrPathEnd = vstrPaths.end();

		for( ; pstrPath != pstrPathEnd; ++pstrPath )
			if( pstrPath->length() )
				m_pkResourceManager->AddPackage( *pstrPath );

		strPaths = "";
		vstrPaths.clear();

		if( g_pkConfig->GetValue( "ModulePaths", &strPaths ) )
			Explode( " ", strPaths, &vstrPaths );

		pstrPath    = vstrPaths.begin();
		pstrPathEnd = vstrPaths.end();

		for( ; pstrPath != pstrPathEnd; ++pstrPath )
			if( pstrPath->length() )
				g_pkModuleManager->AddSearchPath( *pstrPath );
	}

	m_pkInputManager = new NeInputManager();

	m_pkInputGroup   = new NeInputGroup( m_pkInputManager );

	new NeApplicationSystemInput( m_pkInputGroup, this );


	std::string     strDevice;
	bool            bFullscreen, bStencil;
	int             iWidth, iHeight, iDepth;

	if( !g_pkConfig->GetValue( "RenderDevice", &strDevice ) )
		strDevice = std::string( "opengl" );

	if( !CreateRenderDevice( strDevice, m_pkResourceManager, m_pkInputManager ) )
	{
		Log( LOGLEVEL_ERROR, " *** unable to create render device [%s]\n", strDevice.c_str() );
		return false;
	}

	if( g_pkConfig->GetValue( "RenderFullscreen", &bFullscreen ) && bFullscreen )
		m_kRenderCaps.Set( NeRenderCaps::FULLSCREEN );

	if( g_pkConfig->GetValue( "StencilBuffer", &bStencil ) && bStencil )
		m_kRenderCaps.Set( NeRenderCaps::STENCILBUFFER );

	if( !g_pkConfig->GetValue( "RenderWidth", &iWidth ) || !g_pkConfig->GetValue( "RenderHeight", &iHeight ) )
	{
		iWidth  = 640;
		iHeight = 480;
	}

	if( !g_pkConfig->GetValue( "RenderDepth", &iDepth ) )
		iDepth  = 16;

	if( !g_pkRenderDevice->Open( m_strAppName, &m_kRenderCaps, iWidth, iHeight, iDepth ) )
	{
		Log( LOGLEVEL_ERROR, " *** unable to open render device\n" );
		return false;
	}

	//Get image codecs from config
	{
		vector< string > vstrCodecs;
		string           strCodecs;

		if( g_pkConfig->GetValue( "ImageCodecs", &strCodecs ) )
			Explode( " ", strCodecs, &vstrCodecs );

		vector< string >::iterator pstrCodec    = vstrCodecs.begin();
		vector< string >::iterator pstrCodecEnd = vstrCodecs.end();

		for( ; pstrCodec != pstrCodecEnd; ++pstrCodec )
			if( pstrCodec->length() )
				g_pkRenderDevice->LoadCodec( *pstrCodec, "LGPL" );
	}

	//Get texture filtering modes from config
	string strFiltering;
	NeTexture::NETEXTUREFILTERMODE eMin = NeTexture::LINEAR;
	NeTexture::NETEXTUREFILTERMODE eMag = NeTexture::LINEAR;
	NeTexture::NETEXTUREFILTERMODE eMip = NeTexture::NEAREST;

	if( g_pkConfig->GetValue( "TextureFilterMin", &strFiltering ) )
	{
		if( strFiltering == "linear" )
			eMin = NeTexture::LINEAR;
		else
			eMin = NeTexture::NEAREST;
	}

	if( g_pkConfig->GetValue( "TextureFilterMag", &strFiltering ) )
	{
		if( strFiltering == "linear" )
			eMag = NeTexture::LINEAR;
		else
			eMag = NeTexture::NEAREST;
	}

	if( g_pkConfig->GetValue( "TextureFilterMip", &strFiltering ) )
	{
		if( strFiltering == "linear" )
			eMip = NeTexture::LINEAR;
		else
			eMin = NeTexture::NEAREST;
	}

	g_pkRenderDevice->SetDefaultTextureFiltering( NeTexture::BuildFilter( eMin, eMag, eMip ) );

	m_bRun = true;

	return true;
}


void NeApplication::Shutdown()
{
	DeleteRenderDevice();

	delete m_pkResourceManager;
	delete m_pkInputGroup;
	delete m_pkInputManager;

	NeoEngineShutdown();

	delete m_pkErrorCallback;
}


void NeApplication::Run()
{
	while( m_bRun )
		ExecuteFrame();
}


void NeApplication::Stop()
{
	m_bRun = false;
}


void NeApplication::ExecuteFrame()
{
	m_pkInputManager->Process();
}

