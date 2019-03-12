#include <_lang_.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int 
main(int argc, const char* argv[]) {
	printf("----------\n");
	printf("#your can set COUNT, TEXT via command-line args or env vars\n");

	int count = 3;
	char text[32] = "Hello.";

	for (int i=1; i < argc; ++i) {
		sscanf(argv[i], "--COUNT=%i", &count);
		sscanf(argv[i], "--TEXT=%s", text);
	}

	char *c = getenv("COUNT");
	if (c) count = atoi(c);

	char *text_env = getenv("TEXT");
	if (text_env) strncpy(text, text_env, sizeof(text)/sizeof(text[0]));

	for (int i=0; i < count; i++) {
		printf("%s\n", text);
	}
	putchar('\n');
}
