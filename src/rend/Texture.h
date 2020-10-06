#include "mathutil.h"
#include "TextureAdapter.h"

#include <GL/glew.h>

#include <memory>
#include <vector>

namespace rend
{

struct Context;

struct Texture : public TextureAdapter
{
  Texture();
  ~Texture();

  void setSize(unsigned int width, unsigned int height);
  void setPixel(unsigned int x, unsigned int y, vec3 rgb);
  void setPixel(unsigned int x, unsigned int y, vec4 rgba);

  vec4 getPixel(unsigned int x, unsigned int y) const;
  ivec2 getSize() const;
  int getWidth() const;
  int getHeight() const;

  GLuint getId();
  GLuint getTexId();

private:
  friend struct Context;

  std::shared_ptr<Context> context;
  GLuint id = 0;
  std::vector<vec4> data;
  ivec2 size;
  bool dirty = false;
  int bpp = 0;

  Texture(const Texture&);
  Texture& operator=(const Texture&);

};

}
