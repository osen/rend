#include "mathutil.h"
#include "TextureAdapter.h"

#include <GL/glew.h>

#include <memory>
#include <vector>

namespace rend
{

struct Context;
struct Shader;

struct RenderTexture : public TextureAdapter
{
  RenderTexture();
  ~RenderTexture();

  void setSize(unsigned int width, unsigned int height);

  ivec2 getSize() const;
  int getWidth() const;
  int getHeight() const;

  GLuint getTexId();
  GLuint getId();
  void clear();

private:
  friend struct Context;
  friend struct Shader;

  std::shared_ptr<Context> context;
  GLuint fboId = 0;
  GLuint rboId = 0;
  GLuint id = 0;
  ivec2 size;
  bool dirty = false;

  RenderTexture(const RenderTexture&);
  RenderTexture& operator=(const RenderTexture&);

};

}
