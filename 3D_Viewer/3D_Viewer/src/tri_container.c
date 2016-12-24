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

#define MAX_TRIS 10000
#define PI 3.1415926535f

// ---------------------------------------------------------------------------
// Globals

// ---------------------------------------------------------------------------
// Functions

//Returns a pointer to a newly allocated TriContainer given offset coordinates.
TriContainer *TriContainer_New(float x, float y, float z, float pitch, float yaw, float scale)
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
	new_container->scale = scale;

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

//Comparison function for qsort basing on distance from the origin.
static int TriangleCompare(const void *tri1, const void *tri2)
{
	//Dereference the void pointers into triangles we can use.
	Triangle3D *triangle1 = *(Triangle3D **)tri1;
	Triangle3D *triangle2 = *(Triangle3D **)tri2;

	//Return the magnitude of one vector subtracted from the magnitude of the other.
	float mag1 = ArrayVector_Magnitude((triangle1)->centroid, 3);
	float mag2 = ArrayVector_Magnitude((triangle2)->centroid, 3);
	return (int)((mag1 - mag2) * 10000); //Multiply to help mitigate rounding errors to int.
}

//Sorts all the triangles in a tricontainer based on their distance from the origin.
static void TriContainer_Sort(TriContainer *triContainer)
{
	int i = -1; //Index into the array.
	while (triContainer->triangles[++i] != NULL && i < MAX_TRIS)
	{
		// Set i to the amount of triangles and update their centroids.
		Triangle3D_UpdateCentroid(triContainer->triangles[i]);
	}

	qsort(triContainer->triangles, i, sizeof(TriContainer *), TriangleCompare);
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
		ArrayVector_ScalarMultiply(tri->points[0], triContainer->scale, tri->points[0], 3);
		ArrayVector_ScalarMultiply(tri->points[1], triContainer->scale, tri->points[1], 3);
		ArrayVector_ScalarMultiply(tri->points[2], triContainer->scale, tri->points[2], 3);
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
	TriContainer_Sort(triContainer);

	for (int i = 0; i < MAX_TRIS; i++)
	{
		if (triContainer->triangles[i])
		{
			Triangle3D_Draw(triContainer->triangles[i], cam_pos, cam_pitch, cam_yaw);
		}
	}
}

//Sets the translation and rotation of the TriContainer.
void TriContainer_SetPos(TriContainer *triContainer, float x, float y, float z, float pitch, float yaw, float scale)
{
	//Undo our current transformation.
	for (int i = 0; i < MAX_TRIS; i++)
	{
		Triangle3D *tri = triContainer->triangles[i];
		if (tri)
		{
			ArrayVector_Subtract(tri->points[0], triContainer->offset, tri->points[0], 3);
			ArrayVector_Subtract(tri->points[1], triContainer->offset, tri->points[1], 3);
			ArrayVector_Subtract(tri->points[2], triContainer->offset, tri->points[2], 3);

			//We have to do pitch/yaw in the opposite order.
			ArrayVector_Rotate(tri->points[0], 0, triContainer->yaw * -1);
			ArrayVector_Rotate(tri->points[1], 0, triContainer->yaw * -1);
			ArrayVector_Rotate(tri->points[2], 0, triContainer->yaw * -1);

			ArrayVector_Rotate(tri->points[0],triContainer->pitch * -1, 0);
			ArrayVector_Rotate(tri->points[1],triContainer->pitch * -1, 0);
			ArrayVector_Rotate(tri->points[2],triContainer->pitch * -1, 0);

			ArrayVector_ScalarDivide(tri->points[0], triContainer->scale, tri->points[0], 3);
			ArrayVector_ScalarDivide(tri->points[1], triContainer->scale, tri->points[1], 3);
			ArrayVector_ScalarDivide(tri->points[2], triContainer->scale, tri->points[2], 3);
		}
	}

	//Save our new transformation.
	triContainer->offset[0] = x;
	triContainer->offset[1] = y;
	triContainer->offset[2] = z;

	triContainer->pitch = pitch;
	triContainer->yaw = yaw;

	triContainer->scale = scale;

	//Apply our new transformation to each triangle.
	for (int i = 0; i < MAX_TRIS; i++)
	{
		Triangle3D *tri = triContainer->triangles[i];
		if (tri)
		{
			ArrayVector_ScalarMultiply(tri->points[0], triContainer->scale, tri->points[0], 3);
			ArrayVector_ScalarMultiply(tri->points[1], triContainer->scale, tri->points[1], 3);
			ArrayVector_ScalarMultiply(tri->points[2], triContainer->scale, tri->points[2], 3);

			ArrayVector_Rotate(tri->points[0], triContainer->pitch, triContainer->yaw);
			ArrayVector_Rotate(tri->points[1], triContainer->pitch, triContainer->yaw);
			ArrayVector_Rotate(tri->points[2], triContainer->pitch, triContainer->yaw);

			ArrayVector_Add(tri->points[0], triContainer->offset, tri->points[0], 3);
			ArrayVector_Add(tri->points[1], triContainer->offset, tri->points[1], 3);
			ArrayVector_Add(tri->points[2], triContainer->offset, tri->points[2], 3);
		}
	}
}
