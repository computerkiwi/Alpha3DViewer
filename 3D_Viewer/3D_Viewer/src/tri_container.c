/******************************************************************************
filename    tri_container.c
author      Kieran Williams
DP email    kieran.williams@digipen.edu

Copyright © 2016 DigiPen (USA) Corporation

Brief Description:
This file contains implementation for a 3D triangle container.

******************************************************************************/

// ---------------------------------------------------------------------------
// Includes

#include "triangle3d.h"
#include "tri_container.h"
#include "arrayvector.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ---------------------------------------------------------------------------
// Defines

#define MAX_TRIS 100
#define PI 3.1415926535f

// ---------------------------------------------------------------------------
// Globals

// ---------------------------------------------------------------------------
// Functions

//Returns a pointer to a newly allocated TriContainer given offset coordinates.
TriContainer *TriContainer_New(float x, float y, float z, float pitch, float yaw)
{
	//Make a new tri container.
	TriContainer *new_container = malloc(sizeof(TriContainer));

	//Allocate the triangle pointer array and initialize it to null.
	new_container->triangles = malloc(sizeof(Triangle3D *) * MAX_TRIS);
	memset(new_container->triangles, 0, sizeof(Triangle3D *) * MAX_TRIS);

	//Initialize our offset.
	new_container->offset[0] = x;
	new_container->offset[1] = y;
	new_container->offset[2] = z;
	new_container->pitch = pitch * PI / 180;
	new_container->yaw = yaw * PI / 180;

	return new_container;
}

//Frees all the memory associated with a tri container.
void TriContainer_Free(TriContainer *triContainer)
{
	//This doesn't do anything yet. Please write it.
	_CRT_UNUSED(triContainer);

	//TODO: Free every triangle in the list.
	//TODO: Free triContainer->triangles.
	//TODO: Free the TriContainer.
}

//Adds a Triangle3D to the given TriContainer.
void TriContainer_AddTri(TriContainer *triContainer, Triangle3D *tri)
{
	int i = -1; //Index into the array.
	while (triContainer->triangles[++i] != NULL && i < MAX_TRIS)
		/* Do nothing till we reach a free spot. */;

	//If we're within our max array size...
	if (i < MAX_TRIS)
	{
		//Rotate first. (HACKY)
		ArrayVector_Rotate(tri->points[0], triContainer->pitch, triContainer->yaw);
		ArrayVector_Rotate(tri->points[1], triContainer->pitch, triContainer->yaw);
		ArrayVector_Rotate(tri->points[2], triContainer->pitch, triContainer->yaw);
		//Apply our offset. (This is a fake hacky way to do this at the moment.)
		ArrayVector_Add(triContainer->offset, tri->points[0], tri->points[0], 3);
		ArrayVector_Add(triContainer->offset, tri->points[1], tri->points[1], 3);
		ArrayVector_Add(triContainer->offset, tri->points[2], tri->points[2], 3);

		//Add the tri to the container.
		triContainer->triangles[i] = tri;
	}
}

//Draws all the triangles in a TriContainer.
void TriContainer_Draw(TriContainer *triContainer, float cam_pos[], float cam_pitch, float cam_yaw)
{
	for (int i = 0; i < MAX_TRIS; i++)
	{
		if (triContainer->triangles[i])
		{
			Triangle3D_Draw(triContainer->triangles[i], cam_pos, cam_pitch, cam_yaw);
		}
	}
}
