#include <re/re.h>
#include <SDL2/SDL.h>

struct State;

struct Camera
{
  ReVec3 position;
  ReVec3 rotation;
  ref(State) state;
};

struct State
{
  ref(Camera) camera;
  vector(int) keys;
  ReVec2 mouse;
  vector(int) buttons;
};

ref(State) StateCreate();
void CameraUpdate(ref(Camera) ctx);
ReMat4 CameraView(ref(Camera) ctx);
ReMat4 CameraProjection(ref(Camera) ctx);

int main()
{
  SDL_Window* window = NULL;
  SDL_GLContext glContext = 0;
  ReVec4 col = ReVec4Rgba(1, 1, 1, 1);
  ReMat4 model = ReMat4Identity();
  float rotation = 0;
  ref(State) state = NULL;

  ref(ReContext) context = NULL;
  ref(ReRenderer) renderer = NULL;
  ref(ReBuffer) positions = NULL;

  state = StateCreate();

  window = SDL_CreateWindow("Re Test",
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

  positions = ReContextCreateBuffer(context);
  ReBufferAddVec2(positions, ReVec2Xy(0, 0.5f));
  ReBufferAddVec2(positions, ReVec2Xy(-0.5f, -0.5f));
  ReBufferAddVec2(positions, ReVec2Xy(0.5f, -0.5f));

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

    CameraUpdate(_(state).camera);

    col.x += 0.01f;
    rotation += 1;

    if(col.x > 1)
    {
      col.x = 0;
    }

    model = ReMat4Identity();
    model = ReMat4Translate(model, ReVec3Xyz(0, 0, 0));
    model = ReMat4RotateY(model, rotation);
    model = ReMat4Translate(model, ReVec3Xyz(0, 0, -3));
    model = ReMat4RotateZ(model, -rotation * 2);

    ReRendererClear(renderer, ReVec4Rgba(0.39f, 0.58f, 0.93f, 1.0f));

    ReRendererSetBackfaceCull(renderer, 0);
    ReRendererSetModel(renderer, model);
    ReRendererSetView(renderer, CameraView(_(state).camera));
    ReRendererSetProjection(renderer, CameraProjection(_(state).camera));
    ReRendererSetColor(renderer, col);
    ReRendererSetPositionBuffer(renderer, positions);
    ReRendererRender(renderer);

    SDL_GL_SwapWindow(window);
  }

  ReBufferDestroy(positions);
  ReRendererDestroy(renderer);
  ReContextDestroy(context);

  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

ref(State) StateCreate()
{
  ref(State) rtn = NULL;
  ref(Camera) cam = NULL;

  rtn = allocate(State);
  _(rtn).camera = allocate(Camera);

  cam = _(rtn).camera;
  _(cam).state = rtn;

  return rtn;
}

void CameraUpdate(ref(Camera) ctx)
{
  _(ctx).position = ReVec3Xyz(0, 10, 10);
  _(ctx).rotation = ReVec3Xyz(-45, 0, 0);
}

ReMat4 CameraView(ref(Camera) ctx)
{
  ReMat4 rtn = ReMat4Identity();

  rtn = ReMat4Translate(rtn, _(ctx).position);
  rtn = ReMat4RotateX(rtn, _(ctx).rotation.x);
  rtn = ReMat4Inverse(rtn);

  return rtn;
}

ReMat4 CameraProjection(ref(Camera) ctx)
{
  return ReMat4Perspective(45, 1, 0.1f, 100.0f);
}
