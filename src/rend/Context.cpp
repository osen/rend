#include "Context.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Exception.h"
#include "Shader.h"
#include "Buffer.h"
#include "Mesh.h"

#include <GL/glew.h>

namespace rend
{

std::shared_ptr<Context> Context::initialize()
{
  std::shared_ptr<Context> rtn = std::make_shared<Context>();

  if(glewInit() != GLEW_OK)
  {
    throw Exception("Failed to initialize glew");
  }

  rtn->self = rtn;

  return rtn;
}

std::shared_ptr<Shader> Context::createShader()
{
  GLuint id = 0;
  id = glCreateProgram();

  if(id == 0)
  {
    throw Exception("Failed to create shader program");
  }

  pollForError();

  std::shared_ptr<Shader> rtn = std::make_shared<Shader>();
  rtn->context = self.lock();
  rtn->id = id;

  return rtn;
}

std::shared_ptr<Texture> Context::createTexture()
{
  GLuint id = 0;
  glGenTextures(1, &id);
  pollForError();

  std::shared_ptr<Texture> rtn = std::make_shared<Texture>();
  rtn->context = self.lock();
  rtn->id = id;

  rtn->setSize(256, 256);

  return rtn;
}

std::shared_ptr<RenderTexture> Context::createRenderTexture()
{
  GLuint id = 0;
  glGenTextures(1, &id);
  pollForError();

  GLuint fboId = 0;
  glGenFramebuffers(1, &fboId);
  pollForError();

  GLuint rboId = 0;
  glGenRenderbuffers(1, &rboId);
  pollForError();

  std::shared_ptr<RenderTexture> rtn = std::make_shared<RenderTexture>();

  rtn->context = self.lock();
  rtn->id = id;
  rtn->fboId = fboId;
  rtn->rboId = rboId;

  rtn->setSize(256, 256);

  return rtn;
}

std::shared_ptr<Buffer> Context::createBuffer()
{
  GLuint id = 0;
  glGenBuffers(1, &id);
  pollForError();

  std::shared_ptr<Buffer> rtn = std::make_shared<Buffer>();
  rtn->context = self.lock();
  rtn->id = id;

  return rtn;
}

std::shared_ptr<Mesh> Context::createMesh()
{
  std::shared_ptr<Mesh> rtn = std::make_shared<Mesh>();
  rtn->context = self.lock();

  return rtn;
}

}
