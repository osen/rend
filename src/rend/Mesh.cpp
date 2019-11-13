#include "Mesh.h"

namespace rend
{

void Mesh::setBuffer(const std::string& name, const std::sr1::shared_ptr<Buffer>& buffer)
{
  for(std::sr1::vector<std::sr1::shared_ptr<BufferData> >::iterator it =
    buffers.begin(); it != buffers.end(); it++)
  {
    if((*it)->name == name)
    {
      (*it)->buffer = buffer;

      return;
    }
  }

  std::sr1::shared_ptr<BufferData> bd = std::sr1::make_shared<BufferData>();
  bd->name = name;
  bd->buffer = buffer;
  buffers.push_back(bd);
}

}
