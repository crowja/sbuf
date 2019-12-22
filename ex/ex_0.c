#include <stdlib.h>
#include <stdio.h>

int
main(void)
{
   char cb[10];
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

   printf("STRING IS: %s\n", cb);
   printf("STRING IS: %s\n", cb + 2);
   printf("STRING IS: %s\n", cb + 5);
   
   return 0;
}
