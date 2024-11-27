#ifndef VENTANA_H
#define VENTANA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Ventana
{
public:
  int width;
  int height;
  std::string name;
  GLFWwindow *win;

  Ventana(int w, int h, std::string n) : width(w), height(h), name(n) {};

  void open();
  void clear();
  int update();
  void terminate();


private:

  void initGLEW();
};

#endif
