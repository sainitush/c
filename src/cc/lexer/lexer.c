#include <_cc_.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>

#define DONE -1
#define BSIZE 128
#define STRMAX 64
#define SYMMAX 64

#define NUM 256
#define PUL 257
#define SUB 258
#define MUL 259
#define DIV 260


char lexbuf[BSIZE];
char lexemes[STRMAX];
char *lexptr;
int tokenval;

void error(char *, ...);
int lookahead(void);
void pushback(void);
int lexan(void);

void error(char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}

int lookahead(void) {
	if ('\0' == *lexptr || lexptr >= lexbuf + BSIZE - 1) {
		return EOF;
	}
	return *lexptr++;
}

void pushback(void) {
	if (lexbuf < lexptr) {
		lexptr--;
	}
}

int lexan(void) {
	int c = lookahead();
	while (1) {
		if (isblank(c)) {
			; /* skip */
		} else if (isdigit(c)) {
			tokenval = c - '0';
			c = lookahead();
			while (isdigit(c)) {
				tokenval = tokenval * 10 + c - '0';
				c = lookahead();
			}
			return NUM;
		} else if (ispunct(c)) {
			switch (c) {
			case '+': c = lookahead(); return PUL;
			case '-': c = lookahead(); return SUB;
			case '*': c = lookahead(); return MUL;
			case '/': c = lookahead(); return DIV;
			default:  error("!panic, invalid character: '%s'\n", c);
			};
		}	else if (EOF == c) {
			return DONE;
		}
  }
}

void test_lookahead(char *buf) {
	strncpy(lexbuf, buf, BSIZE);
	int c;
	while (EOF != (c = lookahead())) {
		fprintf(stdout, "%c, ", (int)c);
	}
}

void test_pushback(char *buf) {
	strncpy(lexbuf, buf, BSIZE);
	int c, p;
	c = lookahead();
	pushback();
	p = lookahead();
	assert(c == p && "test_pushback failed");
}

void test_lexan(char *buf) {
	strncpy(lexbuf, buf, BSIZE);
	int tok;
	while (DONE != (tok = lexan())) {
		fprintf(stdout, "%d |", tok);
	}
}


int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	if (argc > 1) {
		/* lexptr = lexbuf; */
		/* test_lookahead(argv[1]); */
		/* lexptr = lexbuf; */
		/* test_pushback(argv[1]); */
		lexptr = lexbuf;
		test_lexan(argv[1]);
	}
	return 0;
}
