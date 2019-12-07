#include <stdlib.h>
#include <stdio.h>
#include "sbuf.h"

void
fake_reader(char ***list)
{

   struct sbuf *sb = (struct sbuf *) sbuf_new();
   char        c;

   while (EOF != (c = fgetc(stdin))) {
      if (c == ' ')
         sbuf_putc(sb, '\0');
      else
         sbuf_putc(sb, c);
   }

   sbuf_putc(sb, '\0');

   *list = sbuf_strings(sb);

   /* we're about to lose the pointer to sb, memory leak */
}

int
main(int argc, char *argv[])
{
   char      **l;
   char      **cpp;

   fake_reader(&l);

   cpp = l;

   while (NULL != *cpp) {
      printf("STRING is %s\n", *cpp);
      cpp++;
   }

   /* There will be unfreed memory set up by the sbuf */

   return 0;
}
