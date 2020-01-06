/**
 *  @file sbuf.h
 *  @version 0.5.2-dev0
 *  @date Sun Jan  5 21:31:55 CST 2020
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 *  @brief Methods for creating and parsing a buffer of strings.
 *  @details Probably mostly useful for lexers building up a buffer of text
 *  one character at a time. Sbuf_putc() collects characters. Sbuf_strings()
 *  returns a list of strings embedded in the collection. A goal in this
 *  implementation has been to minimize mallocs and frees.
 */

#ifndef _SBUF_H_
#define _SBUF_H_

#ifdef  _PACKAGE_NAME
#undef  _PACKAGE_NAME
#endif
#define _PACKAGE_NAME "sbuf"

struct sbuf;

/**
 *  @brief Constructor.
 *  @details Create and return a new sbuf object.
 *  @returns New pqueue object.
 */
struct sbuf *sbuf_new(void);

/**
 *  @brief Destructor.
 *  @details Clean up and free an sbuf structure.
 *  @param[in, out] pp. It is assumed *pp has been created by a call to
 *  sbuf_new(), and on return *pp is set to NULL.
 */
void        sbuf_free(struct sbuf **pp);

/**
 *  @brief Return the version of this package.
 *  @details Version string.
 */
const char *sbuf_version(void);

/**
 *  @brief Append a character to the sbuf.
 *  @details Append a character to the tail of the sbuf. Strings are 
 *  constructed by explicitly putting a '\0'.
 *  @param p Pointer to a sbuf object
 *  @param x FIXME
 */

int         sbuf_putc(struct sbuf *p, int c);

/**
 *  @brief Resets an sbuf object.
 *  @details Reset/empties the sbuf.
 *  @param p Pointer to a sbuf object
 *  @param x FIXME
 */
int         sbuf_reset(struct sbuf *p);

/**
 *  @brief Returns a list of strings.
 *  @details Parse the sbuf for the embedded strings.
 *  @param p Pointer to a sbuf object
 *  @param x FIXME
 */

int         sbuf_strings(struct sbuf *p, unsigned *np, char ***cpp);


#endif
