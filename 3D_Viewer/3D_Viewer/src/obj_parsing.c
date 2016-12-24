/******************************************************************************
filename    obj_parsing.c
author      Kieran Williams
DP email    kieran.williams@digipen.edu

Copyright © 2016 DigiPen (USA) Corporation

Brief Description:
This file contains implementation for parsing of obj files.

******************************************************************************/
// ---------------------------------------------------------------------------
// Includes

#include "triangle3d.h"
#include "tri_container.h"
#include <stdio.h>
#include <string.h>

// ---------------------------------------------------------------------------
// Defines

#define MAX_LINE_LENGTH 300
#define MAX_COMMAND_LENGTH 3
#define MAX_VERTICIES 10000
// ---------------------------------------------------------------------------
// Structs

typedef struct VertList
{
	int count; //The amount of vertices in the list.
	float vertices[MAX_VERTICIES][3];
} VertList;

// ---------------------------------------------------------------------------
// Globals

// ---------------------------------------------------------------------------
// VertList Functions

//Adds coordinates as a vertex to a given VertList.
static void AddVert(VertList *vertList, float x, float y, float z)
{
	int index = vertList->count;

	vertList->vertices[index][0] = x;
	vertList->vertices[index][1] = y;
	vertList->vertices[index][2] = z;

	vertList->count++;
}

//Returns a dynamically allocated triangle from vertices in a VertList.
static Triangle3D *CreateTriFromVerts(VertList *vertList, int vIndex1, int vIndex2, int vIndex3)
{
	//Declare the coordinates of each vert.
	float x1, y1, z1;
	float x2, y2, z2;
	float x3, y3, z3;

	//Assign all the coordinates.
	x1 = vertList->vertices[vIndex1][0];
	y1 = vertList->vertices[vIndex1][1];
	z1 = vertList->vertices[vIndex1][2];

	x2 = vertList->vertices[vIndex2][0];
	y2 = vertList->vertices[vIndex2][1];
	z2 = vertList->vertices[vIndex2][2];

	x3 = vertList->vertices[vIndex3][0];
	y3 = vertList->vertices[vIndex3][1];
	z3 = vertList->vertices[vIndex3][2];

	//Return the newly created triangle.
	return Triangle3D_New(x1, y1, z1, x2, y2, z2, x3, y3, z3);
}

// ---------------------------------------------------------------------------
// Parsing Functions

//Parses a single vertices line, putting the vertices into the given list.
static void ParseVert(char *lineBuffer, VertList *vertList)
{
	float x, y, z; //The coordinates of the vert.

	//Pull the coordinates out of the string.
	printf("%s\n", lineBuffer);
	sscanf(lineBuffer + 1, "%f%f%f", &x, &y, &z); //2 is to skip past "v"  at the start.
	//Insert the coordinates to the vertlist.
	AddVert(vertList, x, y, z);
}

//Parses a .obj file with the given filename and puts the resulting triangles in a tricontainer.
void ParseObj(char *filename, TriContainer *container)
{
	//Load the file.
	FILE *file = fopen(filename, "rt");
	//Check if we actually opened the file.
	if (!file)
	{
		printf("Failed to open file %s.", filename);
		return;
	}

	//Set up our list of vertices.
	VertList vertices;
	vertices.count = 0;

	char lineBuffer[MAX_LINE_LENGTH];

	//Go through each line of the file. Only handle vertices and faces.
	while (fgets(lineBuffer, MAX_LINE_LENGTH, file))
	{
		char commandBuffer[MAX_COMMAND_LENGTH] = { 0 }; //Stores an obj command (v, f, etc.)

		//Get the command at the start of the line.

		sscanf(lineBuffer, "%s", commandBuffer);
		if (strcmp(commandBuffer, "v") == 0)
		{
			//TODO: Handle a vertex.
			printf("Vertex line: %s\n", lineBuffer);
			ParseVert(lineBuffer, &vertices);
		}
		else if (strcmp(commandBuffer, "f") == 0)
		{
			//TODO: Handle a face
			printf("Face line: %s\n", lineBuffer);
			_CRT_UNUSED(container);
		}
	}

	//Close the file.
	fclose(file);
}