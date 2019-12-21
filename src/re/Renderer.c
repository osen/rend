#include "Renderer.h"
#include "internal.h"
#include "mathutil.h"

void ReRendererDestroy(ref(ReRenderer) ctx)
{
  release(ctx);
}

void ReRendererClear(ref(ReRenderer) ctx, struct ReVec4 color)
{
  glClearColor(color.x, color.y, color.z, color.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
