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
