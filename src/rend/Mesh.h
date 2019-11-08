#include <sr1/vector>
#include <sr1/memory>

#include <string>

namespace rend
{

struct BufferData;
struct Buffer;
struct Context;

struct Mesh
{
  void setBuffer(const std::string& name, const std::sr1::shared_ptr<Buffer>& buffer);

private:
  friend struct Context;

  std::sr1::shared_ptr<Context> context;
  std::sr1::vector<std::sr1::shared_ptr<BufferData> > buffers;

};

}
