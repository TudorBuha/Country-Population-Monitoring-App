#include "dynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#pragma once

/*
  Function that creates a new dynamic array
*/
DynamicArray* createDynamicArray(int initialCapacityOfTheDynamicArray)
{
    DynamicArray* dynamicArray = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (dynamicArray == NULL)
        return NULL;
    dynamicArray->size = 0;
    dynamicArray->capacity = initialCapacityOfTheDynamicArray;
    dynamicArray->elements = (Country*)malloc(initialCapacityOfTheDynamicArray * sizeof(TElem));
    return dynamicArray;
}

/*
  Function that resizes a dynamic array
*/
void resize(DynamicArray* dynamicArray)
{
	dynamicArray->capacity *= 2;
	TElem* newElements = realloc(dynamicArray->elements, dynamicArray->capacity * sizeof(TElem));
	if (newElements == NULL) {
		exit(1);
	}
	dynamicArray->elements = newElements;
}

/*
  Function that destroys a dynamic array
*/
void destroyDynamicArray(DynamicArray* dynamicArrayToBeDestroyed)
{
    if (dynamicArrayToBeDestroyed == NULL)
        return;
    for (int i = 0; i < dynamicArrayToBeDestroyed->size; i++)
        destroyCountry(dynamicArrayToBeDestroyed->elements[i]);
    free(dynamicArrayToBeDestroyed->elements);
}

/*
  Function that returns the element from a dynamic array at a given index
*/
void addElement(DynamicArray* dynamicArray, TElem elementToBeAdded)
{
    if (dynamicArray->size >= dynamicArray->capacity) {
        dynamicArray->capacity *= 2;
        TElem* newElements = realloc(dynamicArray->elements, dynamicArray->capacity * sizeof(TElem));
        if (newElements == NULL) {
            exit(1);
        }
        dynamicArray->elements = newElements;
    }
    dynamicArray->elements[dynamicArray->size] = elementToBeAdded;
    dynamicArray->size++;
}

/*
  Function that deletes an element from a dynamic array at a given index
*/
void deleteElement(DynamicArray* dynamicArray, int indexOfTheElementToBeDeleted)
{
    for (int i = indexOfTheElementToBeDeleted; i < dynamicArray->size - 1; i++)
    {
        dynamicArray->elements[i] = dynamicArray->elements[i + 1];
    }
    dynamicArray->size--;
}

/*
  Function that updates an element from a dynamic array at a given index
*/
void updateElement(DynamicArray* dynamicArray, int indexOfTheElementToBeUpdated, TElem updatedElement)
{
    dynamicArray->elements[indexOfTheElementToBeUpdated] = updatedElement;
}

/*
  Function that returns the size of a dynamic array
*/
int getDynamicArraySize(DynamicArray* dynamicArray)
{
    return dynamicArray->size;
}

/*
  Function that returns the capacity of a dynamic array
*/
int getDynamicArrayCapacity(DynamicArray* dynamicArray)
{
    return dynamicArray->capacity;
}