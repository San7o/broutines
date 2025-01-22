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

#ifndef _BROUTINE_H_
#define _BROUTINE_H_

#include <stdlib.h>
#include <ucontext.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// -------------------------------------------------------------
// C++20 Style Coroutines
// -------------------------------------------------------------
// Example usage:
// ```
// int fib(BroContextParam) {
//   broBeginContext();
//   int a;
//   int b;
//   broEndContext(ctx);
// 
//   int tmp;
//   broBegin(ctx);
//   ctx->a = 0;
//   ctx->b = 1;
//   for (;;) {
//       tmp = ctx->b;
//       ctx->b = ctx->a + ctx->b;
//       ctx->a = tmp;
//       broReturn(ctx->b);
//   }
//   broEnd(-1);
// }
// 
// void fib_test() {
//   BroContext ctx = 0;
//   assert(fib(&ctx) == 1);
// }

#define BroContextParam void** broContext
#define BroContext void*

#define broBegin(ctx)                           \
  if (!ctx)                                     \
  {                                             \
    ctx = *broContext = malloc(sizeof(*ctx));	\
    ctx->broState = 0;                          \
  }                                             \
  if (ctx)                                      \
  switch(ctx->broState)                         \
  {                                             \
  case 0:

#define broReturn(retVal)                                       \
  do {                                                          \
    ((struct BroContextS*) *broContext)->broState = __LINE__;	\
    return retVal;                                              \
    case __LINE__:;                                             \
  } while(0)

#define broEnd(retVal)       \
  }                          \
  free(*broContext);         \
  return retVal

#define broBeginContext()    \
  struct BroContextS {       \
    int broState
// TODO: add more macro sorcery so that you do not need broEndContext()
//       inspired by clay CLAY() macro

#define broEndContext(ctx)                     \
  } *ctx = (struct BroContextS*) *broContext


// -------------------------------------------------------------
// Green Threads
// -------------------------------------------------------------
// Example usage:
// ```
// void taskA() {
//   while(true) {
//     printf("Routine A is running\n");
//     broSwitch(1);
//   }
//   return;
// }
// 
// void taskB() {
//   while(true) {
//     printf("Routine B is running\n");
//     broSwitch(2);
//   }
//   return;
// }
// 
// void task_test() {
//   broInit();
//   broStart(&taskA, 0, 64*1024);
//   broStart(&taskB, 0, 64*1024);
//   while(true) {
//     printf("Main is running\n");
//     broSwitch(0);
//   }
//   printf("DONE\n");
//   return;
// }
// ```
  
// TODO check that this is never surpassed
#define MAX_BROROUTINES 1024

// Reference standard structs
// typedef struct ucontext_t { 
//     struct ucontext_t *uc_link; 
//     sigset_t          uc_sigmask; 
//     stack_t           uc_stack; 
//     mcontext_t        uc_mcontext; 
//     ... 
// } ucontext_t; 
// typedef struct stack_t 
// { 
//   void *ss_sp;      // pointer to the base of the stack 
//   size_t ss_size;   // stack size 
//   int ss_flags;     // flags 
// } 

extern struct ucontext_t broContexts[MAX_BROROUTINES];
extern int broRoutinesSize;

int broSwitch(int broId);
// returns -1 and sets errno on error, 0 otherwise
int broStart(void (*routine)(void), int broId, size_t stackSize);
// returns -1 on error and sets errno, 0 otherwise
int broInit();
// returns -1 or error and sets errno, 0 otherwise

#ifdef BROUTINES_IMPLEMENTATION

struct ucontext_t broContexts[MAX_BROROUTINES];
int broRoutinesSize;
  
int broSwitch(int broId)
{
  if (swapcontext(&broContexts[broId],
		  &broContexts[(broId+1 >= broRoutinesSize) ? 0 : broId+1 ]) < 0)
    return -1;
  return 0;
}

int broStart(void (*routine)(void), int broId, size_t stackSize)
{
  broRoutinesSize++;

  ucontext_t* newContext = &broContexts[broRoutinesSize-1];
  if (getcontext(newContext) < 0) return -1;
  stack_t newStack;
  void* stackMemory = (void*) malloc(stackSize);
  if (posix_memalign(&stackMemory, 16, stackSize) != 0) return -1;
  newStack.ss_sp = stackMemory;
  newStack.ss_size = stackSize;
  newContext->uc_stack = newStack;
  newContext->uc_link = NULL;

  // Setup the jump
  bool jumped = false;
  if (getcontext(&broContexts[broId]) < 0) return -1;
  if (!jumped)
  {
    jumped = true;
    makecontext(&broContexts[broRoutinesSize-1], routine, 0);
    setcontext(&broContexts[broRoutinesSize-1]);
  }
  return 0;
}

int broInit()
{
  broRoutinesSize = 1;
  return getcontext(&broContexts[0]);
}

#endif // BROUTINES_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // _BROUTINE_H_
