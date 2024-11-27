#include "ventana.h"
#include <iostream>

void Ventana::open()
{
  if (!glfwInit())
  {
    std::cerr << "Error al iniciar GLFW" << std::endl;
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  win = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

  if (!win)
  {
    glfwTerminate();
    std::cerr << "Error al crear ventana" << std::endl;
    return;
  }

  glfwMakeContextCurrent(win);

  initGLEW();

}

void Ventana::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int Ventana::update()
{
  glfwSwapBuffers(win);

  glfwPollEvents();
  if (glfwWindowShouldClose(win))
  {
    terminate();
    return -1;
  }

  return 0;
}

void Ventana::terminate()
{
  glfwTerminate();
}

void Ventana::initGLEW()
{
  if (glewInit() != GLEW_OK)
  {
    std::cerr << "Error al iniciar GLEW" << std::endl;
    return;
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BACK);
  glEnable(GL_CCW);
}
