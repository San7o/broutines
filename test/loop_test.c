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
