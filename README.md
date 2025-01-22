# b-routines

So, recently I was wondering how you could implement gorotuines in C.
Since C is a very powerful language that lets you do all kinds of
abominations with memory, there must be a way to make this work. A
goroutine is a [green-thread](https://en.wikipedia.org/wiki/Green_thread)
, that is, a "virtual" thread that is not managed by the OS and lives
only in user space.

I was also experimenting with C++20 coroutines in C wich are producers
that can be suspended and resumed later. You could Implement infinite
generators like the following fibonacci generator example:

```cpp
#include "../broutines.h"
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

```

great thanks to [Simon Tatham](https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html)
for his tricks and love for coroutines. The above example uses
[broutines.h](./broutines.h), I think I can merge this tecnology to
build green-threads. Some good inspiration is
[State Threads library](https://state-threads.sourceforge.net/)
and [libdill](https://github.com/sustrik/libdill) but I want to
implement everything myself, just for fun. I will need a scheduler,
maybe a simple RR, and a way to context switch threads and save the
stack. I can also choose to have a cooperative sheduler (where coroutines explicitly yield control) or preemptive scheduling (the runtime determines when to switch tasks). I think bot are doable with enough memory sorcery.
