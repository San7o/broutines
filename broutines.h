/*
 * MIT License
 *
 * Copyright (c) 2024 Giovanni Santini
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef _BROUTINE_H_
#define _BROUTINE_H_

#include <stdlib.h>

#ifdef __cplusplus__
extern "C" {
#endif

#define broBegin(ctx)        \
  if (!ctx)                  \
  {                          \
    ctx = *broContext = malloc(sizeof(*ctx));	\
    ctx->broState = 0;       \
  }                          \
  if (ctx)                   \
  switch(ctx->broState)      \
  {                          \
  case 0:

#define broReturn(retVal)    \
  do {                       \
    ((struct BroContextS*) *broContext)->broState = __LINE__;	\
    return retVal;           \
    case __LINE__:;          \
  } while(0)

#define broEnd(retVal)       \
  }                          \
  free(*broContext);         \
  return retVal
  
#define BroContextParam void** broContext
#define BroContext void*

#define broBeginContext()    \
  struct BroContextS {       \
    int broState

#define broEndContext(ctx)   \
  } *ctx = (struct BroContextS*) *broContext

#ifdef __cplusplus__
}
#endif

#endif // _BROUTINE_H_
