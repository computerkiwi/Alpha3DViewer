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
#include "triangle3d.h"

// ---------------------------------------------------------------------------
// Defines

// ---------------------------------------------------------------------------
// Globals

Triangle3D *tri1;
Triangle3D *tri2;

// ---------------------------------------------------------------------------
// Functions


// Handles things to be done each cycle of the loop. Returns TRUE to continue running.
int GameLoop()
{
	static float z_distance = 0.2f;

	z_distance += 0.001f;

	// Start drawing.
	AESysFrameStart();

	tri1->points[0][2] = z_distance;
	tri1->points[1][2] = z_distance;
	tri1->points[2][2] = z_distance;
	Triangle3D_Draw(tri1, NULL, 0, 0);

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



	// Initialize Alpha Engine 
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

	//Initialize 3D triangles
	Triangle3D_Init();

	//Make some triangles
	tri1 = Triangle3D_New(100, 0, 1, 150, 0, 1, 95, 50, 1);

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
