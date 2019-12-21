/**
 *  @file sbuf.h
 *  @version 0.1.0-dev0
 *  @date Fri Dec 20 21:16:27 CST 2019
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
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
 *  @brief Initialize a sbuf object.
 *  @details Initializes/empties the sbuf.
 *  @param p Pointer to a sbuf object
 *  @param x FIXME
 */

int         sbuf_init(struct sbuf *p, void *x);

/**
 *  @brief Append a character to the sbuf.
 *  @details Append a character to the tail of the sbuf. Strings are 
 *  constructed by explicitly putting a '\0'.
 *  @param p Pointer to a sbuf object
 *  @param x FIXME
 */

int         sbuf_putc(struct sbuf *p, int c);

/**
 *  @brief Returns a list of strings.
 *  @details Parse the sbuf for the embedded strings.
 *  @param p Pointer to a sbuf object
 *  @param x FIXME
 */

char      **sbuf_strings(struct sbuf *p);



#endif
