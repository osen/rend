#include <rend/rend.h>
#include <sr1/memory>
#include <SDL2/SDL.h>

#include <iostream>

using namespace rend;

const char* src =
"\n#ifdef VERTEX\n" \
"attribute vec3 a_Position;" \
"attribute vec2 a_TexCoord;" \
""\
"uniform mat4 u_Projection;" \
"" \
"varying vec2 v_TexCoord;" \
"" \
"void main()" \
"{" \
"  gl_Position = u_Projection * vec4(a_Position + vec3(0, 0, -5), 1);" \
"  v_TexCoord = a_TexCoord;" \
"}" \
"" \
"\n#endif\n" \
"\n#ifdef FRAGMENT\n" \
"" \
"varying vec2 v_TexCoord;" \
"" \
"void main()" \
"{" \
"  gl_FragColor = vec4(v_TexCoord, 0, 1);" \
"}" \
"" \
"\n#endif\n";

const char* obj =
"\n\n" \
"\nv -1 1 0\n" \
"\nv -1 -1 0\n" \
"\nv 1 -1 0\n" \
"\nv 1 1 0\n" \
"\n\n" \
"\nvt 0 1\n" \
"\nvt 0 0\n" \
"\nvt 1 0\n" \
"\nvt 1 1\n" \
"\n\n" \
"\nf 1/1 2/2 3/3 4/4\n" \
"\n\n";

int main()
{
  std::cout << "Rend Mesh Test" << std::endl;

  SDL_Window* window = SDL_CreateWindow("Rend Mesh Test",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    800, 600,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if(!window)
  {
    throw Exception("Failed to create window");
  }

  SDL_GLContext glContext = SDL_GL_CreateContext(window);

  if(!glContext)
  {
    throw Exception("Failed to create OpenGL context");
  }

  std::sr1::shared_ptr<Context> context = Context::initialize();
  std::sr1::shared_ptr<Shader> shader = context->createShader();
  shader->setSource(src);

  std::sr1::shared_ptr<Mesh> shape = context->createMesh();
  shape->parse(obj);

/*
  std::sr1::shared_ptr<Buffer> buffer = context->createBuffer();
  buffer->add(vec2(0, 1));
  buffer->add(vec2(-1, -1));
  buffer->add(vec2(1, -1));
  shape->setBuffer("a_Position", buffer);

  buffer = context->createBuffer();
  buffer->add(vec4(1, 0, 0, 1));
  buffer->add(vec4(0, 1, 0, 1));
  buffer->add(vec4(1, 0, 0, 0.5f));
  shape->setBuffer("a_Color", buffer);
*/

  bool running = true;
  SDL_Event e = {0};

  while(running)
  {
    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        running = false;
      }
    }

    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->setUniform("u_Projection", perspective(45.0f, 1.0f, 0.1f, 100.0f));
    shader->setMesh(shape);
    shader->render();

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

