// MIT License
//
// Copyright (c) 2024 Giovanni Santini
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "../broutines.h"
#include "test.h"
#include <assert.h>

int fib(BroContextParam)
{
  broBeginContext();
  int a;
  int b;
  broEndContext(ctx);

  int tmp;
  broBegin(ctx);
  ctx->a = 0;
  ctx->b = 1;
  for (;;)
  {
      tmp = ctx->b;
      ctx->b = ctx->a + ctx->b;
      ctx->a = tmp;
      broReturn(ctx->b);
  }
  broEnd(-1);
}

void fib_test()
{
  BroContext ctx = 0;
  assert(fib(&ctx) == 1);
  assert(fib(&ctx) == 2);
  assert(fib(&ctx) == 3);
  assert(fib(&ctx) == 5);
  assert(fib(&ctx) == 8);
  return;
}
