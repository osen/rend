#include <re/re.h>
#include <SDL2/SDL.h>

int main()
{
  SDL_Window* window = NULL;
  SDL_GLContext glContext = 0;

  ref(ReContext) context = NULL;
  ref(ReRenderer) renderer = NULL;
  ref(ReBuffer) buffer = NULL;

  window = SDL_CreateWindow("Rend Test",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    800, 600,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if(!window)
  {
    panic("Failed to create window");
  }

  glContext = SDL_GL_CreateContext(window);

  if(!glContext)
  {
    panic("Failed to create OpenGL context");
  }

  context = ReContextCreate();
  renderer = ReContextCreateRenderer(context);

  buffer = ReContextCreateBuffer(context);
  //ReBufferAddVec2(ReVec2Xy(0, 0.5f));
  //ReBufferAddVec2(ReVec2Xy(-0.5f, -0.5f));
  //ReBufferAddVec2(ReVec2Xy(0.5f, -0.5f));

  int running = 1;
  SDL_Event e = {0};

  while(running)
  {
    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        running = 0;
      }
    }

    ReRendererClear(renderer, ReVec4Rgba(0.39f, 0.58f, 0.93f, 1.0f));

    //RendererSetBuffer(renderer, "a_Position", buffer);
    //RendererRender(renderer);

    SDL_GL_SwapWindow(window);
  }

  ReBufferDestroy(buffer);
  ReRendererDestroy(renderer);
  ReContextDestroy(context);

  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

