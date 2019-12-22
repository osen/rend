#include "Renderer.h"
#include "internal.h"
#include "mathutil.h"
#include "Buffer.h"

void ReRendererDestroy(ref(ReRenderer) ctx)
{
  _ReShaderDestroy(_(ctx).shader);
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

void ReRendererSetColor(ref(ReRenderer) ctx, struct ReVec4 col)
{
  _(ctx).color = col;
}

void ReRendererRender(ref(ReRenderer) ctx)
{
  if(!_(ctx).position)
  {
    panic("No position buffer set");
  }

  if(_(ctx).blend)
  {
    glEnable(GL_BLEND);
    _RePollForError();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _RePollForError();
  }

  if(_(ctx).depthTest)
  {
    glEnable(GL_DEPTH_TEST);
    _RePollForError();
  }

  if(_(ctx).backfaceCull)
  {
    glEnable(GL_CULL_FACE);
    _RePollForError();
  }

  glBindBuffer(GL_ARRAY_BUFFER, _ReBufferId(_(ctx).position));
  _RePollForError();

  glUseProgram(_ReShaderId(_(ctx).shader));
  _RePollForError();
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  _RePollForError();
  glEnableVertexAttribArray(0);
  _RePollForError();

  glUniform4f(_ReShaderColorLoc(_(ctx).shader),
    _(ctx).color.x,
    _(ctx).color.y,
    _(ctx).color.z,
    _(ctx).color.w);
  _RePollForError();

  glDrawArrays(GL_TRIANGLES, 0, ReBufferSize(_(ctx).position));
  _RePollForError();

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  _RePollForError();

  glDisable(GL_BLEND);
  _RePollForError();
  glDisable(GL_DEPTH_TEST);
  _RePollForError();
  glDisable(GL_CULL_FACE);
  _RePollForError();
}

void ReRendererSetBackfaceCull(ref(ReRenderer) ctx, int enabled)
{
  _(ctx).backfaceCull = enabled;
}

void ReRendererSetBlend(ref(ReRenderer) ctx, int enabled)
{
  _(ctx).blend = enabled;
}

void ReRendererSetDepthTest(ref(ReRenderer) ctx, int enabled)
{
  _(ctx).depthTest = enabled;
}

