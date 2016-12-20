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
#include "arrayvector.h"
#include "AEEngine.h"
#include <math.h>

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

//Updates the normal vector on a given Triangle3D.
void Triangle3D_UpdateNormal(Triangle3D *tri)
{
	//Get two direction vectors of the triangle.
	float dirVector1[3];
	ArrayVector_Subtract(tri->points[0], tri->points[1], dirVector1, 3);
	float dirVector2[3];
	ArrayVector_Subtract(tri->points[0], tri->points[2], dirVector2, 3);


	//Cross product of those two is the normal.
	ArrayVector_CrossProduct(dirVector1, dirVector2, tri->normal);
}

//Draws a given triangle given a camera's position (3-large array), pitch, and yaw. Currently does not actually handle the camera.
void Triangle3D_Draw(Triangle3D *tri, float cam_pos[], float cam_pitch, float cam_yaw)
{
	float points_2d[3][2]; //Newly projected points.

	//TODO: Transform 3d points based on camera position.
	_Unreferenced_parameter_(cam_pos);
	_Unreferenced_parameter_(cam_pitch);
	_Unreferenced_parameter_(cam_yaw);


	float vectorForward[3] = { 0.0f, 0.0f, 1.0f };

	Triangle3D_UpdateNormal(tri);

	//If the dot product is less than than zero, the triangle is pointing away from us so we don't draw it.
	if (ArrayVector_DotProduct(vectorForward, tri->normal, 3) < 0) //This might be backwards. Fix it later.
	{
		return;
	}

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

	//Get the shade we want the triangle to be based on angle to the camera.

	float tint = 1.0f;
	float vAngle = ArrayVector_Angle(tri->normal, vectorForward, 3);
	if (vAngle > 90)
	{
		vAngle = 180 - vAngle;
	}

	tint -=vAngle / 95.0f;

	//Actually draw it.
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTintColor(tint, tint, tint, 1.0f);
	AEGfxSetTransform(matrix);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(triangle_mesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
}