#include "iType_iArray.h"

#include <stdio.h>
#include <stdlib.h>

iArray::iArray(ARRAY_METHOD m)
{
	node = NULL;
	count = 0;
	method = m;
}

iArray::~iArray()
{
	removeAllObject();
}

void iArray::addObject(void* data)
{
	xArray* a = (xArray*)malloc(sizeof(xArray));
	a->data = data;
	a->prev = node;

	node = a;

	count++;
}

void iArray::addObjectAtIndex(int index, void* data)
{
	if( index < 0 )
	{
		index = 0;
	}
	else if( index>=count )
	{
		addObject(data);
		return;
	}

	xArray* n = node;
	for(int i=0; i<count; i++)
	{
		if( count-1-i == index )
		{
			xArray* a = (xArray*)malloc(sizeof(xArray));
			a->data = data;
			a->prev = n->prev;

			n->prev = a;

			count++;
			return;
		}
		n = n->prev;
	}
}

void* iArray::getObjectAtIndex(int index)
{
	xArray* n = node;
	for(int i=0; i<count; i++)
	{
		if( count-1-i == index )
			return n->data;
		n = n->prev;
	}
	return NULL;
}

void iArray::removeObjectAtIndex(int index)
{
	xArray* prevN = NULL;
	xArray* n = node;
	for(int i=0; i<count; i++)
	{
		if( count-1-i == index )
		{
			xArray* prev = n->prev;
			if( method )
				method( n->data );
			free( n );

			if( prevN )
				prevN->prev = prev;
			else
				node = prev;
			count--;
			return;
		}
		else
		{
			prevN = n;
			n = n->prev;
		}
	}
}

void iArray::removeAllObject()
{
	xArray* n = node;
	while( n )
	{
		xArray* p = n->prev;

		if( method )
			method( n->data );
		free( n );

		n = p;
	}
	node = NULL;
	count = 0;
}

void iArray::removeObject(void* data)
{
	xArray* prevN = NULL;
	xArray* n = node;
	while( n )
	{
		if( n->data == data )
		{
			xArray* prev = n->prev;

			if( method )
				method( n->data );
			free( n );

			if( prevN )
				prevN->prev = prev;
			else
				n = prev;
			count--;
			continue;
		}

		prevN = n;
		n = n->prev;
	}
}


