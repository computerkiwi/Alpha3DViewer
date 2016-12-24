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

#define TRUE 1
#define FALSE 0

#define MAX_LINE_LENGTH 300
#define MAX_COMMAND_LENGTH 100
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
static int true = TRUE; //Avoid compiler warnings for constant loops.

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
	x1 = vertList->vertices[vIndex1 - 1][0];
	y1 = vertList->vertices[vIndex1 - 1][1];
	z1 = vertList->vertices[vIndex1 - 1][2];
	
	x2 = vertList->vertices[vIndex2 - 1][0];
	y2 = vertList->vertices[vIndex2 - 1][1];
	z2 = vertList->vertices[vIndex2 - 1][2];
	
	x3 = vertList->vertices[vIndex3 - 1][0];
	y3 = vertList->vertices[vIndex3 - 1][1];
	z3 = vertList->vertices[vIndex3 - 1][2];

	//Return the newly created triangle.
	return Triangle3D_New(x1, y1, z1, x2, y2, z2, x3, y3, z3);
}

// ---------------------------------------------------------------------------
// Parsing Functions

//Parses a single vertex line, putting the vertices into the given list.
static void ParseVert(char *lineBuffer, VertList *vertList)
{
	float x, y, z; //The coordinates of the vert.

	//Pull the coordinates out of the string.
	printf("%s\n", lineBuffer);
	sscanf(lineBuffer + 1, "%f%f%f", &x, &y, &z); //2 is to skip past "v"  at the start.
	//Insert the coordinates to the vertlist.
	AddVert(vertList, x, y, z);
}

//Gets the next coordinate given the index. Returns a negative value if no new character is found.
static int GetFaceCoord(const char *buffer, int *index)
{
	int num; // The number to return.
	//Find the next number.
	while (true)
	{
		char currentChar = buffer[*index];
		if (currentChar == '\n')
		{
			return -1;
		}
		else if (currentChar >= '0' && currentChar <= '9')
		{
			break;
		}
		(*index)++;
	}
	//Get that number.
	sscanf(buffer + *index, "%d", &num);
	//Move the index out of the number.
	while (buffer[*index] != ' ' && buffer[*index] != '\n')
	{
		(*index)++;
	}
	return num;
}

//Parses a single face, splitting the face into triangles and putting them into the tri list. Returns count of tris added.
static int ParseFace(const char *lineBuffer, VertList *vertList, TriContainer *triContainer)
{
	int vertAnchor; //The vertex included in every triangle.
	int vert1, vert2; //The other two vertices.

	int index = 0;//The index into the string.

	int totalTris = 0;

	//Set up our initial 3 vertices.
	vertAnchor = GetFaceCoord(lineBuffer, &index);
	vert1 = GetFaceCoord(lineBuffer, &index);
	vert2 = GetFaceCoord(lineBuffer, &index);

	while (true)
	{
		//If vert2 couldn't be found, we're done.
		if (vert2 < 0)
		{
			return totalTris;
		}
		//Add the new tri to the container.
		TriContainer_AddTri(triContainer, CreateTriFromVerts(vertList, vertAnchor, vert1, vert2));
		totalTris++;
		//Parse out another vert.
		vert1 = vert2;
		vert2 = GetFaceCoord(lineBuffer, &index);
	}
	return totalTris;
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

	//Set up our counts for printing later.
	int totalVerts = 0;
	int totalFaces = 0;
	int totalTris  = 0;

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
			//Handle a vertex.
			printf("Vertex line: %s\n", lineBuffer);
			ParseVert(lineBuffer, &vertices);
			totalVerts++;
		}
		else if (strcmp(commandBuffer, "f") == 0)
		{
			//Handle a face
			printf("Face line: %s\n", lineBuffer);
			totalTris += ParseFace(lineBuffer, &vertices, container);
			totalFaces++;
		}
	}

	printf("Finished parsing file \"%s\"\n", filename);
	printf(" Vertices: %d\n", totalVerts);
	printf("    Faces: %d\n", totalFaces);
	printf("Triangles: %d\n", totalTris);

	//Close the file.
	fclose(file);
}