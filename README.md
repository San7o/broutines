# b-routines

So, recently I was wondering how you could implement goroutines in C.
Since C is a very powerful language that lets you do all kinds of
abominations with memory, there must be a way to make this work. A
goroutine is a [green-thread](https://en.wikipedia.org/wiki/Green_thread),
that is, a "virtual" thread that is not managed by the OS and lives
only in user space.

I was also experimenting with C++20 coroutines in C wich are functions
that can be suspended and resumed later and maintain state.
You could Implement infinite generators like the following fibonacci
generator example:

```cpp
int fib(BroContextParam) {
  broBeginContext();
  int a;
  int b;
  broEndContext(ctx);

  int tmp;
  broBegin(ctx);
  ctx->a = 0;
  ctx->b = 1;
  for (;;) {
      tmp = ctx->b;
      ctx->b = ctx->a + ctx->b;
      ctx->a = tmp;
      broReturn(ctx->b);
  }
  broEnd(-1);
}

void fib_test() {
  BroContext ctx = 0;
  assert(fib(&ctx) == 1);
  assert(fib(&ctx) == 2);
  assert(fib(&ctx) == 3);
  assert(fib(&ctx) == 5);
  assert(fib(&ctx) == 8);
  return;
}
```

many thanks to [Simon Tatham](https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html)
for his tricks and love for coroutines. The above example uses
[broutines.h](./broutines.h), I think I can merge this technology to
build green-threads. Some good inspiration is
[State Threads library](https://state-threads.sourceforge.net/),
[libdill](https://github.com/sustrik/libdill),
[boost.fiber](https://www.boost.org/doc/libs/1_75_0/libs/fiber/doc/html/fiber/overview.html) and
[many more](https://www.gnu.org/software/pth/related.html). Actually 
there are so many implementations holy shit, C in the '90s was rocking,
fuck go. But I still want to implement everything myself, just for fun.

Here is an example of my implementation:
```cpp
int A = 0;
int B = 0;
int Main = 0;

void taskA() {
  while(true) {
    A++;
    broSwitch(1);
  }
  return;
}

void taskB() {
  while(true) {
    B++;
    broSwitch(2);
  }
  return;
}

void task_test() {
  broInit();
  broStart(&taskA, 0, 64*1024);
  broStart(&taskB, 0, 64*1024);

  for (int i = 0; i < 5; ++i) {
    Main++;
    broSwitch(0);
  }

  assert(A == 6);
  assert(B == 6);
  assert(Main == 5);
  return;
}
```

I used cooperative green-threads that pass control to the next thread
after calling `broSwitch()`.  I tried with an implementation with
`setjmp()` and `longjmp()` but I failed miserabely baucase all the
functions were using the same stack and this would corrupt variables.
The final implementation uses `makecontext()` and `setcontext()` to
create new stacks and do the jump.

All my code is MIT licensed.
