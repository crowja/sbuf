#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sbuf.h"
#include "t/tinytest.h"

#ifdef  _COLOR_CODE
#undef  _COLOR_CODE
#endif
#define _COLOR_CODE       0x1B

#ifdef  _COLOR_RED
#undef  _COLOR_RED
#endif
#define _COLOR_RED        "[1;31m"

#ifdef  _COLOR_GREEN
#undef  _COLOR_GREEN
#endif
#define _COLOR_GREEN      "[1;32m"

#ifdef  _COLOR_YELLOW
#undef  _COLOR_YELLOW
#endif
#define _COLOR_YELLOW     "[1;33m"

#ifdef  _COLOR_RESET
#undef  _COLOR_RESET
#endif
#define _COLOR_RESET      "[0m"


static void
_printf_test_name(char *name, char *info)
{
   printf("%c%s%s%c%s", _COLOR_CODE, _COLOR_YELLOW, name, _COLOR_CODE, _COLOR_RESET);

   if (NULL != info)
      printf(" [%s]\n", info);
   else
      printf("\n");
}


static void
test_constr(void)
{
   struct sbuf *z;

   _printf_test_name("test_constr()", NULL);

   z = sbuf_new();
   ASSERT("Constructor test", z);
   sbuf_free(z);
}


static void
test_put_1(void)
{
   struct sbuf *z;
   char      **list;

   _printf_test_name("test_put_1()", NULL);

   z = sbuf_new();
   sbuf_putc(z, 'Z');
   sbuf_putc(z, 'e');
   sbuf_putc(z, 'b');

   list = sbuf_strings(z);

   ASSERT_STRING_EQUALS("Zeb", list[0]);
   ASSERT_EQUALS(NULL, list[1]);

   sbuf_free(z);
}


static void
test_put_2(void)
{
   struct sbuf *z;
   char      **list;

   _printf_test_name("test_put_2()", NULL);

   z = sbuf_new();
   sbuf_putc(z, 'S');
   sbuf_putc(z, '\0');
   sbuf_putc(z, 'Z');
   sbuf_putc(z, 'e');
   sbuf_putc(z, 'b');
   sbuf_putc(z, '\0');

   list = sbuf_strings(z);

   ASSERT_STRING_EQUALS("S", list[0]);
   ASSERT_STRING_EQUALS("Zeb", list[1]);
   ASSERT_EQUALS(NULL, list[2]);

   sbuf_free(z);
}


static void
test_strings_init_strings(void)
{
   struct sbuf *z;
   char      **list;
   char      **cpp;
   char       *test_a[] = { "Mr", "Dewey", "Dog" };
   char       *test_b[] = { "S", "Zeb" };
   unsigned    i;

   _printf_test_name("test_strings_init_strings()", NULL);

   z = sbuf_new();

   sbuf_putc(z, 'M');
   sbuf_putc(z, 'r');
   sbuf_putc(z, '\0');
   sbuf_putc(z, 'D');
   sbuf_putc(z, 'e');
   sbuf_putc(z, 'w');
   sbuf_putc(z, 'e');
   sbuf_putc(z, 'y');
   sbuf_putc(z, '\0');
   sbuf_putc(z, 'D');
   sbuf_putc(z, 'o');
   sbuf_putc(z, 'g');

   list = sbuf_strings(z);
#if 1
   cpp = list;
   i = 0;

   while (NULL != *cpp) {
      ASSERT_STRING_EQUALS(*cpp, test_a[i]);
      cpp += 1;
      i += 1;
   }
#else
   ASSERT_STRING_EQUALS("Mr", list[0]);
   ASSERT_STRING_EQUALS("Dewey", list[1]);
   ASSERT_STRING_EQUALS("Dog", list[2]);
#endif

   sbuf_init(z, NULL);

   sbuf_putc(z, 'S');
   sbuf_putc(z, '\0');
   sbuf_putc(z, 'Z');
   sbuf_putc(z, 'e');
   sbuf_putc(z, 'b');
   sbuf_putc(z, '\0');

   list = sbuf_strings(z);

#if 1
   cpp = list;
   i = 0;

   while (NULL != *cpp) {
      ASSERT_STRING_EQUALS(*cpp, test_b[i]);
      cpp += 1;
      i += 1;
   }
#else
   ASSERT_STRING_EQUALS("S", list[0]);
   ASSERT_STRING_EQUALS("Zeb", list[1]);
#endif

   ASSERT_EQUALS(NULL, list[2]);

   sbuf_free(z);
}


static void
test_empty(void)
{
   struct sbuf *z;
   char      **list;

   _printf_test_name("test_empty()", NULL);

   z = sbuf_new();

   sbuf_putc(z, '\0');
   list = sbuf_strings(z);

   ASSERT_STRING_EQUALS("", list[0]);

   sbuf_free(z);
}


static void
test_stub(void)
{
   struct sbuf *z;

   _printf_test_name("test_stub()", NULL);

   z = sbuf_new();
   ASSERT("Test stub", z);
   sbuf_free(z);
}


int
main(void)
{
   printf("%s\n", sbuf_version());

   test_stub();
   RUN(test_constr);
   RUN(test_put_1);
   RUN(test_put_2);
   RUN(test_strings_init_strings);
   RUN(test_empty);

   return TEST_REPORT();
}
