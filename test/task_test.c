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

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

int A = 0;
int B = 0;
int Main = 0;

void taskA()
{
  while(true)
  {
    A++;
    broSwitch(1);
  }

  return;
}

void taskB()
{
  while(true)
  {
    B++;
    broSwitch(2);
  }

  return;
}

void task_test()
{
  if (broInit() < 0) perror("broInit");
  
  broStart(&taskA, 0, 64*1024);
  broStart(&taskB, 0, 64*1024);

  //while(true)
  for (int i = 0; i < 5; ++i)
  {
    Main++;
    broSwitch(0);
  }

  assert(A == 6);
  assert(B == 6);
  assert(Main == 5);

  return;
}
