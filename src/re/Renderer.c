#include "Renderer.h"
#include "internal.h"
#include "mathutil.h"
#include "Buffer.h"

void ReRendererDestroy(ref(ReRenderer) ctx)
{
  release(ctx);
}

void ReRendererClear(ref(ReRenderer) ctx, struct ReVec4 color)
{
  glClearColor(color.x, color.y, color.z, color.w);
  _RePollForError();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _RePollForError();
}

void ReRendererSetPositionBuffer(ref(ReRenderer) ctx, ref(ReBuffer) buffer)
{
  _(ctx).position = buffer;
}

void ReRendererRender(ref(ReRenderer) ctx)
{
  if(!_(ctx).position)
  {
    panic("No position buffer set");
  }

  glBindBuffer(GL_ARRAY_BUFFER, _ReBufferId(_(ctx).position));
  _RePollForError();

  /* TODO: Temp FFP for triangle */
  glVertexPointer(2, GL_FLOAT, 0, 0);
  glEnableClientState(GL_VERTEX_ARRAY);

  glDrawArrays(GL_TRIANGLES, 0, ReBufferSize(_(ctx).position));
  _RePollForError();

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  _RePollForError();
}
