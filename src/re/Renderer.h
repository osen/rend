#include "stent.h"

struct ReRenderer;
struct ReVec4;
struct ReBuffer;

void ReRendererDestroy(ref(ReRenderer) ctx);
void ReRendererClear(ref(ReRenderer) ctx, struct ReVec4 color);
void ReRendererSetPositionBuffer(ref(ReRenderer) ctx, ref(ReBuffer) buffer);
void ReRendererSetColor(ref(ReRenderer) ctx, struct ReVec4 col);
void ReRendererRender(ref(ReRenderer) ctx);
void ReRendererSetBackfaceCull(ref(ReRenderer) ctx, int enabled);
void ReRendererSetBlend(ref(ReRenderer) ctx, int enabled);
void ReRendererSetDepthTest(ref(ReRenderer) ctx, int enabled);
