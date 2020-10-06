#include <vector>
#include <memory>

#include <string>

namespace rend
{

struct Buffer;
struct Context;
struct Shader;
struct TextureAdapter;

struct BufferData
{
  std::string name;
  std::shared_ptr<Buffer> buffer;
};

struct TextureData
{
  std::string name;
  std::shared_ptr<TextureAdapter> texture;
};

struct Mesh
{
  void setBuffer(const std::string& name, const std::shared_ptr<Buffer>& buffer);
  void setTexture(const std::string& name, const std::shared_ptr<TextureAdapter>& texture);
  void parse(const std::string& data);

private:
  friend struct Context;
  friend struct Shader;

  std::shared_ptr<Context> context;
  std::vector<std::shared_ptr<BufferData> > buffers;
  std::vector<std::shared_ptr<TextureData> > textures;

  void safeParse(const std::string& data, std::string& currentLine);

};

}
