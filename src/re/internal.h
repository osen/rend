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

struct ReRenderer
{
  ref(ReBuffer) position;
  int depthTest;
  int backfaceCull;
};

GLuint _ReBufferId(ref(ReBuffer) ctx);

void _RePollForError();
