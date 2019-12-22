#include "stent.h"

#include <GL/glew.h>

struct ReContext
{
  int todo;
};

struct ReBuffer
{
  GLuint id;
  int type;
  int dirty;
  vector(float) data;
};

GLuint _ReBufferId(ref(ReBuffer) ctx);

struct ReShader
{
  GLuint id;
};

ref(ReShader) _ReShaderCreate(ref(ReContext) context);
void _ReShaderDestroy(ref(ReShader) ctx);
GLuint _ReShaderId(ref(ReShader) ctx);

struct ReRenderer
{
  ref(ReShader) shader;
  ref(ReBuffer) position;
  int depthTest;
  int backfaceCull;
};

void _RePollForError();
