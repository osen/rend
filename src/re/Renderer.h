#include "stent.h"

struct ReRenderer;
struct ReVec4;
struct ReBuffer;

void ReRendererDestroy(ref(ReRenderer) ctx);
void ReRendererClear(ref(ReRenderer) ctx, struct ReVec4 color);
void ReRendererSetPositionBuffer(ref(ReRenderer) ctx, ref(ReBuffer) buffer);
void ReRendererRender(ref(ReRenderer) ctx);
