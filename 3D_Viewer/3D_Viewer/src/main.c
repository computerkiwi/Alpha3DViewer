/******************************************************************************
filename    main.c
author      Kieran Williams
DP email    kieran.williams@digipen.edu

Copyright © 2016 DigiPen (USA) Corporation

Brief Description:
This file contains the entry into the program.

******************************************************************************/

// ---------------------------------------------------------------------------
// Includes

#include "AEEngine.h"
#include <stdio.h>

// ---------------------------------------------------------------------------
// Defines


// ---------------------------------------------------------------------------
// Globals

AEGfxVertexList *triangle_mesh;

// ---------------------------------------------------------------------------
// Functions


// Handles things to be done each cycle of the loop. Returns TRUE to continue running.
int GameLoop()
{
	static float angle = 0.0f;

	angle += 0.5;

	// Start drawing.
	AESysFrameStart();

	//Draw out test mesh
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	float transform[3][3] = { { 50.0f,0.0f,0.0f },
	                          { 0.0f,50.0f,0.0f },
	                          { 0.0f,0.0f,1.0f } };

	AEGfxSetTransform(transform);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(triangle_mesh, AE_GFX_MDM_TRIANGLES);

	// Finish drawing.
	AESysFrameEnd();

	return TRUE;
}

// It's main. It launches everything.
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	//TODO: Load a .obj file.


	_Unreferenced_parameter_(prevInstanceH);
	_Unreferenced_parameter_(command_line);

	// Initialize the system 
	AESysInitInfo sysInitInfo;
	sysInitInfo.mCreateWindow = 1;
	sysInitInfo.mWindowHandle = NULL;
	sysInitInfo.mAppInstance = instanceH;
	sysInitInfo.mShow = show;
	sysInitInfo.mWinWidth = 1280;
	sysInitInfo.mWinHeight = 800;
	sysInitInfo.mCreateConsole = 0;
	sysInitInfo.mMaxFrameRate = 60;
	sysInitInfo.mpWinCallBack = NULL;
	sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
	sysInitInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;
	sysInitInfo.mHandleWindowMessages = 1;

	AESysInit(&sysInitInfo);

	//Not totally sure what this does. Example says "reset the system modules"
	AESysReset();

	//Make the triangle mesh
	AEGfxMeshStart();

	AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	triangle_mesh = AEGfxMeshEnd();
	

	//Set the background to black.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	int gameRunning = TRUE;
	while (gameRunning)
	{
		gameRunning = GameLoop();
	}

	// Free the system
	AESysExit();
}
