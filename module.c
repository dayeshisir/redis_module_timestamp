/*
Copyright (c) 2017 Eran Sandler <eran at sandler dot co dot il>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include <stdio.h>
#include<sys/time.h>
#include "redismodule.h"

int GetTimeCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  struct timeval tp;
  gettimeofday(&tp, NULL);
  long int millisecs = tp.tv_sec * 1000 + tp.tv_usec/1000;
  RedisModule_ReplyWithLongLong(ctx, millisecs);
  return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  if (RedisModule_Init(ctx, "time", 1, REDISMODULE_APIVER_1) ==
      REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  RedisModule_Log(ctx, "info", "time start up");

  if (RedisModule_CreateCommand(ctx, "timestamp.gettime", GetTimeCommand, "readonly",
                                1, 1, 1) == REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  return REDISMODULE_OK;
}
