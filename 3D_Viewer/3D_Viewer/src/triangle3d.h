/******************************************************************************
filename    triangle3d.h
author      Kieran Williams
DP email    kieran.williams@digipen.edu

Copyright © 2016 DigiPen (USA) Corporation

Brief Description:
This file contains definitions for 3D triangles.

******************************************************************************/
#pragma once

typedef struct Triangle3D
{
	float points[3][3];

	float normal[3];
} Triangle3D;

//Sets up everything the 3D triangle system needs to function. Must be initialized after AEGfx.
void Triangle3D_Init();

//Returns a pointer to a newly allocated Triangle3D
Triangle3D *Triangle3D_New(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

//Draws a given triangle given a camera's position (3-large array), pitch, and yaw. Currently does not actually handle the camera.
void Triangle3D_Draw(Triangle3D *tri, float cam_pos[], float cam_pitch, float cam_yaw);
