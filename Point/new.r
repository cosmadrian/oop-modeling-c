#ifndef __NEW_R__
#define __NEW_R__

struct Class {
	size_t size;
	void * (*ctor) (void * self, va_list * app);
	void * (*dtor) (void * self);
	void (*draw) (const void * self);
};

#endif
