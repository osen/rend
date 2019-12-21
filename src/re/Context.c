#include "Context.h"
#include "internal.h"

#define STENT_IMPLEMENTATION
#include "stent.h"

ref(ReContext) ReContextCreate()
{
  ref(ReContext) rtn = NULL;

  rtn = allocate(ReContext);

  if(glewInit() != GLEW_OK)
  {
    panic("Failed to initialize glew");
  }

  return rtn;
}

void ReContextDestroy(ref(ReContext) ctx)
{
  release(ctx);
}

ref(ReRenderer) ReContextCreateRenderer(ref(ReContext) ctx)
{
  ref(ReRenderer) rtn = NULL;

  rtn = allocate(ReRenderer);

  return rtn;
}

ref(ReBuffer) ReContextCreateBuffer(ref(ReContext) ctx)
{
  ref(ReBuffer) rtn = NULL;

  rtn = allocate(ReBuffer);

  return rtn;
}
