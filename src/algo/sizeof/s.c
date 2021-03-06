#include <_algo_.h>
#include <assert.h>

#define field_sizeof(t, f) sizeof(((t*)0)->f)
#define array_sizeof(a) (sizeof((a)) / sizeof((a)[0]))

struct point_s {
	short x;
	int y;
};


int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	assert(sizeof(short) == field_sizeof(struct point_s, x)
				 || "field_sizeof macro failed");

	assert(sizeof(int) == field_sizeof(struct point_s, y)
				 || "field_sizeof macro failed");

	assert(array_sizeof(argv) == argc
				 || "array_sizeof macro failed");

	return 0;
}
