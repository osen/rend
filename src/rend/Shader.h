#include "mathutil.h"

#include <GL/glew.h>

#include <memory>
#include <vector>

#include <string>

namespace rend
{

struct Context;
struct VariableInfo;
struct Buffer;
struct RenderTexture;
struct TextureAdapter;
struct Mesh;

struct Shader
{
  Shader();
  ~Shader();

  void render();
  void render(const std::shared_ptr<RenderTexture>& target);

  GLuint getId();
  void setSource(const std::string& source);
  void parse(const std::string& source);

  void setUniform(const std::string& variable, float value);
  void setUniform(const std::string& variable, mat4 value);
  void setUniform(const std::string& variable, vec2 value);
  void setUniform(const std::string& variable, vec3 value);
  void setUniform(const std::string& variable, vec4 value);
  void setAttribute(const std::string& variable, const std::shared_ptr<Buffer>& value);
  void setSampler(const std::string& variable, const std::shared_ptr<TextureAdapter>& value);
  void setMesh(const std::shared_ptr<Mesh>& value);

private:
  friend struct Context;

  std::shared_ptr<Context> context;
  GLuint id = 0;
  std::vector<std::shared_ptr<VariableInfo> > cache;

  Shader(const Shader&);
  Shader& operator=(const Shader&);
  std::shared_ptr<VariableInfo> getVariableInfo(const std::string& name, GLenum type, bool attrib);

};

}
