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

   sbuf_strings(sb, &n, &list);

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

   /* There will be unfreed memory */
#define _COLOR_CODE       0x1B
#define _COLOR_YELLOW     "[1;33m"
#define _COLOR_RESET      "[0m"
   printf("%c%s%s%c%s\n", _COLOR_CODE, _COLOR_YELLOW, "Intentionally not freeing memory",
          _COLOR_CODE, _COLOR_RESET);

   return 0;
}
