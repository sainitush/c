#include <_io_.h>
#include <stdio.h>

int
main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "where the free txt located?\n");
    return 0;
  }

  int n = 0;
  int sum = 0;
  int num = 0;

  FILE *in = fopen(argv[1], "r");
  if (!in) {
    perror("!panic");
    return 1;
  }

  while (EOF != (fscanf(in, "%i", &num))) {
    n += 1;
    sum += num;
  }
  if (ferror(in)) {
    perror("!panic");
    goto clean_exit;
  }

  fprintf(stdout, "%dNo: numbers entered\n", n);
  fprintf(stdout, "sum: %d\n", sum);
  fprintf(stdout, "average: %3.2f\n", sum*1.0f/n);

 clean_exit:
  fclose(in);
  return 0;
}
