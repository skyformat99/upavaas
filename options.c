#include "options.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define checkarg(check) strncmp(argv[i],check,sizeof(check)-1)

#define getarg(check)\
  if (argv[i][sizeof(check)-1] == 0) { \
    if (i+1 == argc) { \
      fprintf(stderr, "%s: no argument provided\n", check); \
      goto failure; \
    } \
    arg = argv[++i]; \
  } \
  else if (argv[i][sizeof(check)-1] == '=') \
    arg = argv[i] + sizeof(check); \
  else { \
    fprintf(stderr, "unrecognized option: %s\n", argv[i]); \
    goto failure; \
  }

void
usage(FILE* file)
{
  fprintf(file, "usage: coniuncti [options]\n");
  fprintf(file, "   -h, --help        print this message\n");
  fprintf(file, "       --address     specify server address\n");
  fprintf(file, "       --port        specify server port\n");
  fprintf(file, "   -d, --directory   specify base directory of html files\n");
}

int
parse(int argc, char** argv, struct options* dest)
{
  uint32_t temp;
  uint8_t* tempptr = (uint8_t*)&temp;
  int i, ret, discard[4];
  char extra;
  char* arg;

  struct options opts;
  opts.address = 0;
  uint8_t* addrptr = (uint8_t*)&(opts.address);
  addrptr[0] = 127;
  addrptr[3] = 1;
  opts.port = 8080;
  opts.directory = "";

  for (i = 1; i != argc; i++) {
    if (strcmp(argv[i],"-h") == 0 || strcmp(argv[i],"--help") == 0) {
      usage(stdout);
      exit(0);
    }
    else if (checkarg("--address") == 0) {
      getarg("--address");
      ret = sscanf(arg, "%i.%i.%i.%i%c", discard, discard+1, discard+2, discard+3, &extra);
      if (ret != 4) {
        fprintf(stderr, "improper address: \"%s\"\n", arg);
        fprintf(stderr, "example of a proper address: 192.168.0.2\n");
        goto failure;
      }
      for (ret = 0; ret != 4; ret++) {
        if (discard[ret] > 255 || discard[ret] < 0) {
          printf("improper octet %i: \"%i\"\n", ret+1, discard[ret]);
          goto failure;
        }
        tempptr[ret] = discard[ret];
      }
      opts.address = temp;
    }
    else if (checkarg("--port") == 0) {
      getarg("--port");
      ret = sscanf(arg, "%i%c", discard, &extra);
      if (ret != 1 || discard[0] < 1 || discard[0] > 65535) {
        fprintf(stderr, "improper port number : \"%s\"\n", arg);
        goto failure;
      }
      opts.port = discard[0];
    }
    else if (checkarg("-d") == 0) {
      getarg("-d");
      opts.directory = arg;
    }
    else if (checkarg("--directory") == 0) {
      getarg("--directory");
      opts.directory = arg;
    }
  }
  *dest = opts;
  return 0;

  failure:
  usage(stderr);
  return -1;
}