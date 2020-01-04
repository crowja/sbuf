/**
 *  @file sbuf.c
 *  @version 0.4.1-dev0
 *  @date Sat Jan  4 11:58:33 CST 2020
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 *  @brief Methods for creating and parsing a buffer of strings.
 *  @details Probably mostly useful for lexers building up a buffer of text
 *  one character at a time. Sbuf_putc() collects characters and sbuf_strings()
 *  returns a list of embedded strings. A goal in this implementation has been
 *  to minimize mallocs and frees.
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME when printf() is gone */
#include "sbuf.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

/* Character buffer size extensions */
#ifdef  _EXTEND_BUFSZ
#undef  _EXTEND_BUFSZ
#endif
#define _EXTEND_BUFSZ  1024

/* Character pointer array size extensions */
#ifdef  _EXTEND_LSTSZ
#undef  _EXTEND_LSTSZ
#endif
#define _EXTEND_LSTSZ  1024

struct sbuf {
   char      **list;                        /* the array of pointers to strings */
   size_t      lsize;                       /* malloced size of list */
   char       *buffer;                      /* the array of chars */
   size_t      bsize;                       /* malloced size of buffer */
   unsigned    bpos;                        /* next buffer position to to write to */
};

struct sbuf *
sbuf_new(void)
{
   struct sbuf *tp;

   tp = (struct sbuf *) malloc(sizeof(struct sbuf));
   if (_IS_NULL(tp))
      return NULL;

   tp->list = NULL;
   tp->lsize = 0;
   tp->buffer = NULL;
   tp->bsize = 0;
   tp->bpos = 0;

   return tp;
}

void
sbuf_free(struct sbuf **pp)
{
   _FREE((*pp)->list);
   _FREE((*pp)->buffer);
   _FREE(*pp);
   *pp = NULL;
}

const char *
sbuf_version(void)
{
   return "0.4.1-dev0";
}

int
sbuf_putc(struct sbuf *p, int c)
{

   /* More space for the buffer? */
   if (p->bpos + 2 > p->bsize) {
      char       *tp = realloc(p->buffer, sizeof(char) * (p->bsize + _EXTEND_BUFSZ));
      if (_IS_NULL(tp))
         return EOF;
      p->buffer = tp;
      p->bsize += _EXTEND_BUFSZ;
   }

   (p->buffer)[p->bpos] = c;

#if 0
   printf("DEBUG JUST SET (p->buffer)[%d] as %c\n", p->bpos, c);
#endif

   p->bpos += 1;

   return c;
}

int
sbuf_reset(struct sbuf *p)
{
   p->bpos = 0;
   return 0;
}

char      **
sbuf_strings(struct sbuf *p)
{
   unsigned    bpos;
   unsigned    start = 0;
   unsigned    lpos = 0;
   void      **tp;

   if (p->bpos == 0)
      return NULL;

   if ((p->buffer)[p->bpos - 1] != '\0') {
      sbuf_putc(p, '\0');
   }

   for (bpos = 0; bpos < p->bpos; bpos++) {

      if ((p->buffer)[bpos] == '\0') {           /* end of string */

         if (lpos + 2 >= p->lsize) {
            tp = realloc(p->list, sizeof(char *) * (p->lsize + _EXTEND_LSTSZ));
            p->list = (char **) tp;
            p->lsize += _EXTEND_LSTSZ;
         }

         (p->list)[lpos] = p->buffer + start;    /* need to extend list size? */
         lpos += 1;
         start = bpos + 1;
      }
   }

   (p->list)[lpos] = (char *) NULL;              /* terminal NULL */

   return (char **) p->list;
}

#undef _EXTEND_BUFSZ
#undef _EXTEND_LSTSZ
#undef _IS_NULL
#undef _FREE
