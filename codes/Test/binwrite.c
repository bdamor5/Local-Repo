/*
 * binwrite.c
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  unsigned int sample[] = { 10000111, 
                            20000222, 
                            30000333, 
                            40000444,
                            50000555,
                            60000666, 
  };
  unsigned int element_count;
  FILE *fp;

  if (argc != 2) {
    fprintf(stderr, "syntax for command should be: %s filename\n", argv[0]);
    exit(1);
  }

  /* The mode "wb" means write a binary file.  The "b" is
   * not necessary in Linux systems, but is needed in
   * MS Windows and various other OSes. */
  if ((fp = fopen(argv[1], "wb")) == NULL) {
    fprintf(stderr, "failed to open file %s for output\n", argv[1]);
    exit(1);
  }

  element_count = sizeof(sample) / sizeof(unsigned int);
  fwrite(&element_count, sizeof(unsigned int), 1, fp);
  fwrite(sample, sizeof(unsigned int), element_count, fp);

  if (fclose(fp) != 0) {
    fprintf(stderr,
            "Error detected closing %s; write may be incomplete.\n",
            argv[1]);
    exit(1);
  }

  return 0;
}
