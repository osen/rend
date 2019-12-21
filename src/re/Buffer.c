#include "Buffer.h"
#include "internal.h"

void ReBufferDestroy(ref(ReBuffer) ctx)
{
  release(ctx);
}
