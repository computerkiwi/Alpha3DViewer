/******************************************************************************
filename    obj_parsing.c
author      Kieran Williams
DP email    kieran.williams@digipen.edu

Copyright © 2016 DigiPen (USA) Corporation

Brief Description:
This file contains declarations for parsing of obj files.

******************************************************************************/
#pragma once

//Forward declare required structs.
typedef struct TriContainer TriContainer;

//Parses a .obj file with the given filename and puts the resulting triangles in a tricontainer.
void ParseObj(char *filename, TriContainer *container);