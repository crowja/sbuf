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
   unsigned    n;

   while (EOF != (c = fgetc(stdin))) {
      if (c == ' ')
         sbuf_putc(sb, '\0');
      else
         sbuf_putc(sb, c);
   }

   sbuf_putc(sb, '\0');

   sbuf_strings(sb, &n, &list);

   cpp = list;
   while (NULL != *cpp) {
      printf("STRING is %s\n", *cpp);
      cpp++;
   }

   sbuf_free(&sb);

   return 0;
}
