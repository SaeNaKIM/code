#ifndef CURVE25519_DONNA_H_ACRJFPL7
#define CURVE25519_DONNA_H_ACRJFPL7
////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>

typedef uint8_t u8;
typedef int64_t felem;

void curve25519_donna(u8 *mypublic, const u8 *secret, const u8 *basepoint);

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
#endif /* end of include guard: CURVE25519-DONNA_H_ACRJFPL7 */

