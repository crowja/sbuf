/**
 *  @file sbuf.h
 *  @version 0.0.1-dev0
 *  @date Thu Nov  1 09:02:04 CDT 2018
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
 *  @brief Create and return a new sbuf object.
 *  @details FIXME longer description here ...
 */

struct sbuf *sbuf_new(void);

/**
 *  @brief Clean up and free a sbuf structure.
 *  @details FIXME longer description here ...
 */

void        sbuf_free(struct sbuf *p);

/**
 *  @brief Return the version of this package.
 *  @details FIXME longer description here ...
 */

const char *sbuf_version(void);

/**
 *  @brief Initialize a sbuf object.
 *  @details FIXME longer description here ...
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
