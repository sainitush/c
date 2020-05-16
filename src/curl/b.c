#include <_curl_.h>
#include <stdio.h>
#include <stdlib.h>

void
test_stdout() {
  CURL *curl = 0;
  CURLcode code = 0;
  char *errbuf = 0;

  curl_version_info_data *ver = curl_version_info(CURLVERSION_NOW);
  if (ver) {
    fprintf(stdout, "curl current version: %s\n----------\n", ver->version);
  }
  
  curl = curl_easy_init();
  if (!curl) {
    fprintf(stderr, "!panic, init failed\n");
    goto clean_exit;
  }
  code = curl_easy_setopt(curl, CURLOPT_URL, "https://curl.haxx.se");
  if (code) {
    fprintf(stderr, "!panic, setopt CURLOPT_URL failed\n");
    goto clean_exit;
  }
  
  errbuf = malloc(CURL_ERROR_SIZE);
  if (0 == errbuf) {
    perror("!panic, alloc memory for errbuf failed");
    goto clean_exit;
  }
  code = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
  if (code) {
    fprintf(stderr, "!panic, setopt CURLOPT_ERRORBUFFER failed\n");
    goto clean_exit;
  }
  
  code = curl_easy_perform(curl);
  if (code) {
    fprintf(stderr, "!panic, perform failed caused by: %s\n", errbuf);
  }

 clean_exit:
  curl_easy_cleanup(curl);
  free(errbuf);
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);
  
  CURLcode code = curl_global_init(CURL_GLOBAL_DEFAULT);
  if (CURLE_OK != code) {
    perror("!panic");
    return code;
  }
  
  test_stdout();
  
  return 0;
}
