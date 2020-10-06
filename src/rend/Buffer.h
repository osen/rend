#include "mathutil.h"

#include <GL/glew.h>

#include <vector>
#include <memory>

namespace rend
{

struct Context;
struct Shader;

struct Buffer
{
  Buffer();
  ~Buffer();

  void add(float value);
  void add(vec2 value);
  void add(vec3 value);
  void add(vec4 value);

  GLuint getId();
  int getSize();

private:
  friend struct Context;
  friend struct Shader;

  std::shared_ptr<Context> context;
  std::vector<float> floatData;
  int type = 0;
  bool dirty = false;
  GLuint id = 0;

  Buffer(const Buffer&);
  Buffer& operator=(const Buffer&);

};

}
