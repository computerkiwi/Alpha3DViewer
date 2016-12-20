/******************************************************************************
filename    arrayvector.c
author      Kieran Williams
DP email    kieran.williams@digipen.edu

Copyright © 2016 DigiPen (USA) Corporation

Brief Description:
This file contains implementation for functions for manipulating arrays as vectors.

******************************************************************************/

// ---------------------------------------------------------------------------
// Includes

#include <stdlib.h>
#include <math.h>
#include "AEMath.h"

// ---------------------------------------------------------------------------
// Defines

// ---------------------------------------------------------------------------
// Globals

// ---------------------------------------------------------------------------
// Functions


//Multiplies a vector by a scalar and stores it in a second vector. Vectors may be more than one parameter.
void ArrayVector_ScalarMultiply(const float vector[], const float scalar, float vecOut[], int size)
{
	for (int i = 0; i < size; i++)
	{
		vecOut[i] = vector[i] * scalar;
	}
}

//Divides a vector by a scalar and stores it in a second vector. Vectors may be more than one parameter.
void ArrayVector_ScalarDivide(const float vector[], const float scalar, float vecOut[], int size)
{
	ArrayVector_ScalarMultiply(vector, 1.0f / scalar, vecOut, size);
}

//Adds two vectors into a third. Vectors may be more than one parameter.
void ArrayVector_Add(const float vec1[], const float vec2[], float vecOut[], int size)
{
	for (int i = 0; i < size; i++)
	{
		vecOut[i] = vec1[i] + vec2[i];
	}
}

//Subtracts the second vector from the first. Vectors may be more than one parameter.
void ArrayVector_Subtract(const float vec1[], const float vec2[], float vecOut[], int size)
{
	float *inverseVector = malloc(size * sizeof(float));

	ArrayVector_ScalarMultiply(vec2, -1.0f, inverseVector, size);
	ArrayVector_Add(vec1, inverseVector, vecOut, size);

	free(inverseVector);
}

//Returns the dot product of two vectors.
float ArrayVector_DotProduct(const float vec1[], const float vec2[], int size)
{
	float result = 0;

	for (int i = 0; i < size; i++)
	{
		result += vec1[i] * vec2[i];
	}

	return result;
}

//Returns the magnitude of a vector.
float ArrayVector_Magnitude(const float vector[], int size)
{
	float sum = 0;

	//Get the sum of each element squared.
	for (int i = 0; i < size; i++)
	{
		sum += vector[i] * vector[i];
	}

	return sqrtf(sum);
}

//Stores a normalized copy of a vector in a second vector.
void ArrayVector_Normalized(float vector[], float vecOut[], int size)
{
	ArrayVector_ScalarDivide(vector, ArrayVector_Magnitude(vector, size), vecOut, size);
}

//Normalizes a given vector.
void ArrayVector_Normalize(float vector[], int size)
{
	ArrayVector_Normalized(vector, vector, size);
}

//Stores the cross product of two 3d vectors in a 3rd vector.
void ArrayVector_CrossProduct(const float vec1[], const float vec2[], float vecOut[])
{
	//New vector so we don't overwrite things we shouldn't if vecOut is vec1 or vec2.
	float newVector[3]; 

	newVector[0] = vec1[1] * vec2[2] - vec2[1] * vec1[2];
	newVector[1] = vec1[2] * vec2[0] - vec2[2] * vec1[0];
	newVector[2] = vec1[0] * vec2[1] - vec2[0] * vec1[1];

	for (int i = 0; i < 3; i++)
	{
		vecOut[i] = newVector[i];
	}
}

//Returns the angle between two vectors in degrees.
float ArrayVector_Angle(const float vec1[], const float vec2[], int size)
{
	float angle_radians = acosf(ArrayVector_DotProduct(vec1, vec2, size) / 
		             (ArrayVector_Magnitude(vec1, size) * ArrayVector_Magnitude(vec2, size)));

	return angle_radians * 180.0f / PI;
}