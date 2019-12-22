#include <stdlib.h>
#include <stdio.h>
#include "sbuf.h"

int
main(void)
{
   struct sbuf *sb = (struct sbuf *) sbuf_new();
   char      **list;
   char      **cpp;
   char        c;

   while (EOF != (c = fgetc(stdin))) {
      if (c == ' ')
         sbuf_putc(sb, '\0');
      else
         sbuf_putc(sb, c);
   }

   sbuf_putc(sb, '\0');

   list = sbuf_strings(sb);

   cpp = list;
   while (NULL != *cpp) {
      printf("STRING is %s\n", *cpp);
      cpp++;
   }

   sbuf_free(&sb);

   return 0;
}
