#include <_algo_.h>

long
linear_search(void *what, void *base, size_t nel, size_t width,
							int (*comp)(const void *, const void *)) {
	for (size_t i = 0; i < nel; i++) {
		if (0 == comp((char*)what, (char*)base + i * width)) {
			return (long)i;
			break;
		}
	}
	return -1;
}

void
test_linear_search_int(void) {
	int found;
	int a1[] = { 0x3, 0x5, 0x4, 0x1, 0x2 };
	int what = 0x1;
	printf("linear search for %i\n----------\n", what);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = linear_search(&what, a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), comp_int);
	printf("found: [%i]\n", found);

  what = 0x6;
	printf("linear search for %i\n----------\n", what);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = linear_search(&what, a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), comp_int);
	printf("found: [%i]\n", found);
}

void
test_linear_search_str(void) {
  int found;
	char *s1[] = { "a", "ccc", "bb", "dddd" };
	char *ss1 = "dddd";
	printf("linear search for %s\n----------\n", ss1);
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found = linear_search(&ss1, s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), comp_str);
	printf("found: [%i]\n", found);

  ss1 = "eeeee";
	printf("linear search for %s\n----------\n", ss1);
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found = linear_search(&ss1, s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), comp_str);
	printf("found: [%i]\n", found);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

  test_linear_search_int();
  test_linear_search_str();

	return 0;
}
