#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "new.r"
#include "String.h"
#include "../abstract_data_types/new.h"

struct String {
	const void * class;
	char * text;
};

void * new(const void * _class, ...)
{
        const struct Class * class = _class;
        void * p = calloc(1, class->size);
        * (const struct Class **) p = class;
        if(class->ctor)
        {
                va_list ap;
                va_start(ap,_class);
                p = class->ctor(p,&ap);
                va_end(ap);
        }
        return p;
}

void delete (void * self)
{
        const struct Class ** cp = self;

        if(self && *cp && (*cp)->dtor)
                self = (*cp)->dtor(self);
        free(self);
}

size_t sizeOf(const void *self)
{
        const struct Class * const *cp = self;
        return (*cp)->size;
}

int differ (const void * a, const void *b)
{
        return a != b;
}

static void * String_ctor(void * _self, va_list * app)
{
	struct String * self = _self;
	const char * text = va_arg(* app, const char*);
	self->text = malloc(strlen(text) + 1);
	strcpy(self->text,text);
	return self;
}

static void * String_dtor (void * _self)
{
	struct String * self = _self;

	free(self->text), self->text = 0;
	return self;
}

static void * String_clone (const void * _self)
{
	const struct String * self = _self;
	return new(String, self->text);
}

static int String_differ(const void * _self, const void *_b)
{
	const struct String * self = _self;
	const struct String * b = _b;
	if(self == b)
		return 0;
	if(!b || b->class != String)
		return 1;
	return strcmp(self->text, b->text);
}

static const struct Class _String = {
	sizeof(struct String),
	String_ctor, String_dtor,
	String_clone, String_differ
};

const void * String = &_String;
