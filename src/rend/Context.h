#include <memory>

namespace rend
{

struct Texture;
struct Shader;
struct Buffer;
struct RenderTexture;
struct Mesh;

struct Context
{
  static std::shared_ptr<Context> initialize();

  std::shared_ptr<Texture> createTexture();
  std::shared_ptr<Shader> createShader();
  std::shared_ptr<Buffer> createBuffer();
  std::shared_ptr<Mesh> createMesh();
  std::shared_ptr<RenderTexture> createRenderTexture();

private:
  std::weak_ptr<Context> self;

};

}
