/******************************************************************************
filename    triangle3d.c
author      Kieran Williams
DP email    kieran.williams@digipen.edu

Copyright © 2016 DigiPen (USA) Corporation

Brief Description:
This file contains implementation for 3D triangles.

******************************************************************************/

// ---------------------------------------------------------------------------
// Includes

#include "triangle3d.h"
#include "AEEngine.h"

// ---------------------------------------------------------------------------
// Defines

// ---------------------------------------------------------------------------
// Globals

AEGfxVertexList *triangle_mesh; //The white triangle we use to draw everything.

// ---------------------------------------------------------------------------
// Functions

//Sets up everything the 3D triangle system needs to function. Must be initialized after AEGfx.
void Triangle3D_Init()
{
	//Make the global triangle mesh
	AEGfxMeshStart();

	AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	triangle_mesh = AEGfxMeshEnd();
}

//Returns a pointer to a newly allocated Triangle3D
Triangle3D *Triangle3D_New(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
	Triangle3D *new_tri = malloc(sizeof(Triangle3D));

	new_tri->points[0][0] = x1;
	new_tri->points[0][1] = y1;
	new_tri->points[0][2] = z1;

	new_tri->points[1][0] = x2;
	new_tri->points[1][1] = y2;
	new_tri->points[1][2] = z2;

	new_tri->points[2][0] = x3;
	new_tri->points[2][1] = y3;
	new_tri->points[2][2] = z3;

	return new_tri;
}

//Draws a given triangle given a camera's position (3-large array), pitch, and yaw. Currently does not actually handle the camera.
void Triangle3D_Draw(Triangle3D *tri, float cam_pos[], float cam_pitch, float cam_yaw)
{
	float points_2d[3][2]; //Newly projected points.

	//TODO: Transform 3d points based on camera position.
	_Unreferenced_parameter_(cam_pos);
	_Unreferenced_parameter_(cam_pitch);
	_Unreferenced_parameter_(cam_yaw);
	//TODO: Set color or don't draw based on dot product of normal and camera.

	//For each point...
	for (int p = 0; p < 3; p++)
	{
		//Do a simple perspective projection.
		for (int i = 0; i < 2; i++)
		{
			points_2d[p][i] = tri->points[p][i] / tri->points[p][2];
		}
	}

	//Brute force really dumb matrix multiplication with T^-1 where T is a matrix representing the triangle mesh's points.
	float matrix[3][3];
	matrix[0][0] = points_2d[0][0] - points_2d[2][0];
	matrix[0][1] = points_2d[1][0] - points_2d[2][0];
	matrix[0][2] = points_2d[2][0];

	matrix[1][0] = points_2d[0][1] - points_2d[2][1];
	matrix[1][1] = points_2d[1][1] - points_2d[2][1];
	matrix[1][2] = points_2d[2][1];

	matrix[2][0] = 0.0f;
	matrix[2][1] = 0.0f;
	matrix[2][2] = 0.0f;
	//Seriously, this is really bad. Fix it when you have actual matrices.

	//Actually draw it.
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTransform(matrix);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(triangle_mesh, AE_GFX_MDM_TRIANGLES);
}