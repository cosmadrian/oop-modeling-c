#ifndef __POINT_R__
#define __POINT_R__

struct Point {
	const void *class;
	int x,y;
};

#define x(p) (((const struct Point *) (p)) -> x)
#define y(p) (((const struct Point *) (p)) -> y)

#endif
