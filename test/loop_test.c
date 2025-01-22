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

int loop(BroContextParam)
{
  broBeginContext();
  int i;
  broEndContext(ctx);
  
  broBegin(ctx);
  for (ctx->i = 1; ctx->i < 10; ++ctx->i)
  {
      broReturn(ctx->i);
  }
  broEnd(-1);
}

void loop_test()
{
  BroContext ctx = 0;
  assert(loop(&ctx) == 1);
  assert(loop(&ctx) == 2);
  assert(loop(&ctx) == 3);
  assert(loop(&ctx) == 4);
  assert(loop(&ctx) == 5);
  return;
}
