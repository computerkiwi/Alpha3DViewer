/******************************************************************************
filename    tri_container.c
author      Kieran Williams
DP email    kieran.williams@digipen.edu

Copyright © 2016 DigiPen (USA) Corporation

Brief Description:
This file contains implementation for a 3D triangle container.

******************************************************************************/
#pragma once

typedef struct TriContainer
{
	Triangle3D **triangles;

	float offset[3];
	float pitch;
	float yaw;
} TriContainer;


//Returns a pointer to a newly allocated TriContainer given offset coordinates.
TriContainer *TriContainer_New(float x, float y, float z, float pitch, float yaw);

//Frees all the memory associated with a tri container.
void TriContainer_Free(TriContainer *triContainer);

//Adds a Triangle3D to the given TriContainer.
void TriContainer_AddTri(TriContainer *triContainer, Triangle3D *tri);

//Draws all the triangles in a TriContainer.
void TriContainer_Draw(TriContainer *triContainer, float cam_pos[], float cam_pitch, float cam_yaw);

//Sets the translation and rotation of the TriContainer.
void TriContainer_SetPos(TriContainer *triContainer, float x, float y, float z, float pitch, float yaw);
