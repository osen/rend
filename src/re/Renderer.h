#include "stent.h"

struct ReRenderer;
struct ReVec4;

void ReRendererDestroy(ref(ReRenderer) ctx);
void ReRendererClear(ref(ReRenderer) ctx, struct ReVec4 color);

