#if ! defined MANY || MANY < 1
#define MANY	10
#endif
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


struct Set { unsigned count; };
struct Object { unsigned count; struct Set * in; };
static const size_t _Set = sizeof(struct Set);
static const size_t _Object = sizeof(struct Object);

const void *Set = &_Set;
const void *Object = &_Object;

void * new (const void * type, ...)
{
	const size_t size = * (const size_t *) type;
	void * p = calloc(1,size);
	return p;
}

void * add (void * _set, const void * _element)
{
	struct Set * set = _set;
	struct Object * element  = (void *) _element;

	if(!element->in)
		element->in = set;
	++ element->count, ++set->count;

	return element;
}

void * find (const void * _set, const void * _element)
{
	const struct Object * element = _element;

	return element->in == _set?(void *) element : 0;
}

int contains ( const void * _set, const void * _element)
{
	return find(_set, _element) != 0;
	
}


void * drop (void * _set, const void * _element)
{
	struct Set * set = _set;
	struct Object * element = find(set,_element);

	if(element)
	{
		if( --element->count == 0)
			element->in = 0;
		--set->count;
	}
	
	return element;	
}

int differ (const void * a, const void *b)
{
	return a != b;
}

unsigned count(const void * _set)
{
	const struct Set * set = _set;

	return set->count;
}

