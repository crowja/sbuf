#include <stdlib.h>
#include <stdio.h>
#include "sbuf.h"

int
main(int argc, char *argv[])
{
   struct sbuf *sb = (struct sbuf *) sbuf_new();
   char      **list;
   char      **cpp;

#if 0
   char        cb[10];


   cb[0] = 'a';
   cb[1] = 'b';
   cb[2] = 'c';
   cb[3] = 'd';
   cb[4] = '\0';
   cb[5] = 'A';
   cb[6] = 'B';
   cb[7] = 'C';
   cb[8] = 'D';
   cb[9] = '\0';
#endif


   sbuf_putc(sb, 'a');
   sbuf_putc(sb, 'b');
   sbuf_putc(sb, 'c');
   sbuf_putc(sb, '\0');
   sbuf_putc(sb, 'd');
   sbuf_putc(sb, 'e');
   sbuf_putc(sb, 'f');
   sbuf_putc(sb, '\0');
   sbuf_putc(sb, 'g');
   sbuf_putc(sb, 'h');
   sbuf_putc(sb, 'i');
   sbuf_putc(sb, 'j');
   sbuf_putc(sb, 'k');
   sbuf_putc(sb, 'l');
   sbuf_putc(sb, 'm');
   sbuf_putc(sb, 'n');

#if 1
   sbuf_putc(sb, '\0');
#endif

#if 1
   list = sbuf_strings(sb);
#endif

#if 1
   cpp = list;
   while (NULL != *cpp) {                        /* seg faulting here */
      printf("JAC STRING is \"%s\"\n", *cpp);
      cpp++;
   }
#endif

   sbuf_free(&sb);


   return 0;
}
