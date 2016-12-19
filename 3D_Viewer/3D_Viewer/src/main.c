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


// ---------------------------------------------------------------------------
// Functions


// Handles things to be done each cycle of the loop. Returns TRUE to continue running.
int GameLoop()
{
	// Start drawing.
	AESysFrameStart();

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

	int gameRunning = TRUE;

	while (gameRunning)
	{
		gameRunning = GameLoop();
	}

	// Free the system
	AESysExit();
}
