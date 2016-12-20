/******************************************************************************
filename    arrayvector.c
author      Kieran Williams
DP email    kieran.williams@digipen.edu

Copyright © 2016 DigiPen (USA) Corporation

Brief Description:
This file contains definitions for functions for manipulating arrays as vectors.

******************************************************************************/
#pragma once


//Multiplies a vector by a scalar and stores it in a second vector. Vectors may be more than one parameter.
void ArrayVector_ScalarMultiply(const float vector[], const float scalar, float vecOut[], int size);

//Divides a vector by a scalar and stores it in a second vector. Vectors may be more than one parameter.
void ArrayVector_ScalarDivide(const float vector[], const float scalar, float vecOut[], int size);

//Adds two vectors into a third. Vectors may be more than one parameter.
void ArrayVector_Add(const float vec1[], const float vec2[], float vecOut[], int size);

//Subtracts the second vector from the first. Vectors may be more than one parameter.
void ArrayVector_Subtract(const float vec1[], const float vec2[], float vecOut[], int size);

//Returns the dot product of two vectors.
float ArrayVector_DotProduct(const float vec1[], const float vec2[], int size);

//Returns the magnitude of a vector.
float ArrayVector_Magnitude(const float vector[], int size);

//Stores a normalized copy of a vector in a second vector.
void ArrayVector_Normalized(float vector[], float vecOut[], int size);

//Normalizes a given vector.
void ArrayVector_Normalize(float vector[], int size);

//Stores the cross product of two 3d vectors in a 3rd vector.
void ArrayVector_CrossProduct(const float vec1[], const float vec2[], float vecOut[]);

//Returns the angle between two vectors.
float ArrayVector_Angle(const float vec1[], const float vec2[], int size);