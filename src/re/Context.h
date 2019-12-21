#include "stent.h"

struct ReContext;
struct ReRenderer;

ref(ReContext) ReContextCreate();
void ReContextDestroy(ref(ReContext) ctx);

ref(ReRenderer) ReContextCreateRenderer(ref(ReContext) ctx);
ref(ReBuffer) ReContextCreateBuffer(ref(ReContext) ctx);
