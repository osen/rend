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
  _(rtn).shader = _ReShaderCreate(ctx);
  _(rtn).blend = 1;
  _(rtn).backfaceCull = 1;
  _(rtn).depthTest = 1;
  _(rtn).projection = ReMat4Identity();
  _(rtn).view = ReMat4Identity();
  _(rtn).model = ReMat4Identity();

  return rtn;
}

ref(ReBuffer) ReContextCreateBuffer(ref(ReContext) ctx)
{
  ref(ReBuffer) rtn = NULL;

  rtn = allocate(ReBuffer);
  _(rtn).data = vector_new(float);

  glGenBuffers(1, &_(rtn).id);
  _RePollForError();

  if(_(rtn).id == 0)
  {
    panic("Failed to generate buffer");
  }

  return rtn;
}
