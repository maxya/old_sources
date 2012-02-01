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

#include "xcomeu3d.h"

#include <neoengine/render.h>
#include <neoengine/log.h>
#include <neoengine/config.h>
#include <neoengine/console.h>
#include <neoengine/strutil.h>
#include <neoengine/renderprimitive.h>
#include <neoengine/material.h>

using namespace NeCore;
using namespace std;


NXComEU3D::NXComEU3D( const string &rstrAppName ) :
	NeApplication( rstrAppName ),
	m_fFPS( 0.0f )
{
}



NXComEU3D::~NXComEU3D()
{
}



bool NXComEU3D::Initialize( int argc, char **argv )
{
	if( !NeApplication::Initialize( argc, argv ) )
		return false;
	
	g_pkConsole->SetDimensions(20, 100, 320, 200);
	g_pkConsole->LoadDefaultFont();

	// TEMP
	g_pkVertexBuffer = g_pkRenderDevice->CreateVertexBuffer( NeBuffer::NORMAL, 3, NEFVF_XYZC );

	g_pkVertexBuffer->Lock( NeBuffer::WRITE );
	{
		NeVertexIterator kIterator( g_pkVertexBuffer->GetIterator() );
	
		kIterator.GetXYZ()->Set(  0.0f,  5.0f, -20.0f ); 
		kIterator.GetColor()->Set( 1.0f, 0.0f, 0.0f, 1.0f );
		++kIterator;

		kIterator.GetXYZ()->Set( -5.0f, -5.0f, -20.0f );
		kIterator.GetColor()->Set( 0.0f, 1.0f, 0.0f, 1.0f );
		++kIterator;

		kIterator.GetXYZ()->Set(  5.0f, -5.0f, -20.0f );
		kIterator.GetColor()->Set( 0.0f, 0.0f, 1.0f, 1.0f );
	}
	g_pkVertexBuffer->Unlock();


	g_pkPolygonBuffer = g_pkRenderDevice->CreatePolygonBuffer( NeBuffer::NORMAL, 1 );

	g_pkPolygonBuffer->Lock( NeBuffer::WRITE );
	{
		NePolygon *pkPolygon = g_pkPolygonBuffer->GetElement();

		(*pkPolygon)[0] = 0;
		(*pkPolygon)[1] = 1;
		(*pkPolygon)[2] = 2;
	}
	g_pkPolygonBuffer->Unlock();
	// TEMP

	return true;
}


void NXComEU3D::Shutdown()
{
	g_pkVertexBuffer  = 0;
	g_pkPolygonBuffer = 0;

	NeApplication::Shutdown();
}


void NXComEU3D::Run()
{
	m_kFPSTimer.Reset();
	NeApplication::Run();
}


void NXComEU3D::Stop()
{
	NeApplication::Stop();
}


void NXComEU3D::ExecuteFrame()
{
	NeApplication::ExecuteFrame();
	
	g_pkRenderDevice->Clear( NeRenderDevice::COLORBUFFER 
							| NeRenderDevice::ZBUFFER, 
							NeColor::BLACK, 
							1.0f, 0 );
	g_pkRenderDevice->Begin( NeMatrix::IDENTITY );
	{
			NeRenderPrimitive kPrim;

			kPrim.m_ePrimitive      = NeRenderPrimitive::TRIANGLES;
			kPrim.m_pkVertexBuffer  = g_pkVertexBuffer;
			kPrim.m_pkPolygonBuffer = g_pkPolygonBuffer;
			kPrim.m_uiNumPrimitives = 1;

			g_pkRenderDevice->Render( kPrim );
	}
	g_pkRenderDevice->End();

	g_pkRenderDevice->SetOrthographicProjection();

	g_pkRenderDevice->Begin( NeMatrix::IDENTITY );
	{
		if( g_pkConsole->IsActive() )
		{
			g_pkConsole->Render();
		}
		//else
		//{
			float fFPS = 1 / m_kFPSTimer.GetDeltaTime(true);
			g_pkDefaultConsoleFont->Printf( 10, 10, "FPS: %.1f\n\nHit F1 to toogle console", fFPS );
		//}
	}
	g_pkRenderDevice->End();

	g_pkRenderDevice->SetPerspectiveProjection();

	g_pkRenderDevice->Flip();
}

