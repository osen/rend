#include "mathutil.h"

struct ReVec2 ReVec2Xy(float x, float y)
{
  struct ReVec2 rtn = {0};

  rtn.x = x;
  rtn.y = y;

  return rtn;
}

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

struct ReMat4 ReMat4Identity()
{
  struct ReMat4 rtn = {0};

  rtn.m[0][0] = 1;
  rtn.m[1][1] = 1;
  rtn.m[2][2] = 1;
  rtn.m[3][3] = 1;

  return rtn;
}
