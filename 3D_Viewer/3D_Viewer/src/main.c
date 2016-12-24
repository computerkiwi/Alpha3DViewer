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
#include "tri_container.h"
#include "obj_parsing.h"

// ---------------------------------------------------------------------------
// Defines

// ---------------------------------------------------------------------------
// Globals

TriContainer *triangles;

// ---------------------------------------------------------------------------
// Functions


// Handles things to be done each cycle of the loop. Returns TRUE to continue running.
int GameLoop()
{
	static float time = 0;
	time += 0.025f;

	TriContainer_SetPos(triangles, 0, 0, 150, time, time * 1.2f, 70);

	// Start drawing.
	AESysFrameStart();

	TriContainer_Draw(triangles, NULL, 0, 0);

	// Finish drawing.
	AESysFrameEnd();

	return TRUE;
}

// It's main. It launches everything.
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{

	//Open a console.
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	//TODO: Load a .obj file.
	triangles = TriContainer_New(0, 0, 50, 43, 0, 1);
	ParseObj("model.obj", triangles);


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
