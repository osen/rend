#ifndef RE_MATHUTIL_H
#define RE_MATHUTIL_H

struct ReVec4
{
  float x;
  float y;
  float z;
  float w;
};

struct ReVec4 ReVec4Xyzw(float x, float y, float z, float w);
struct ReVec4 ReVec4Rgba(float r, float g, float b, float a);

#endif
