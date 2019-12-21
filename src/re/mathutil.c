#include "mathutil.h"

struct ReVec4 ReVec4Xyzw(float x, float y, float z, float w)
{
  struct ReVec4 rtn = {0};

  rtn.x = x;
  rtn.y = y;
  rtn.z = z;
  rtn.w = w;

  return rtn;
}

struct ReVec4 ReVec4Rgba(float r, float g, float b, float a)
{
  return ReVec4Xyzw(r, g, b, a);
}
