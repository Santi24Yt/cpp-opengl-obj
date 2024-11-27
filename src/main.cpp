#include "ventana.h"
#include "vecmatriz.h"
#include "objreader.h"
#include "modelo.h"
#include <GLFW/glfw3.h>
#include <iostream>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
Vector3 cam;
Matrix4 view;
Vector3 centroCubo;

int main(int argc, char *argv[])
{
  std::string archivo;
  std::string vert = "./shader/blanco.vert";
  std::string frag = "./shader/blanco.frag";
  if (argc < 2)
  {
    std::cout << "Introduce nombre de archivo: ";
    std::cin >> archivo;
  } else {
    archivo = argv[1];
    if (argc >= 3)
    {
      vert = argv[2];
      frag = argv[3];
    }
  }

  Ventana w1 = Ventana(1000, 800, "Ventana 1");
  w1.open();

  Obj objf(archivo);

  objf.abrir();
  objf.leer();
  // objf.imprimir();
  objf.cerrar();

  Modelo modelo1(&objf);
  modelo1.genVertexArray();
  modelo1.initgl(vert, frag);

  Puntof centroCuboPf = objf.centroProm();
  centroCubo = Vector3(centroCuboPf.x, centroCuboPf.y, centroCuboPf.z);

  cam = Vector3(centroCuboPf.x + objf.anchox() + 10, 5, 0);

  std::cout << "Modelo: " << objf.filedir << std::endl;
  std::cout << "No. de vértices: " << objf.vertices.size() << std::endl;
  std::cout << "No. de caras: " << objf.caras.size() << std::endl;

  view = Matrix4::lookAt(cam, centroCubo, Vector3(0.0f,1.0f,0.0f));
  Matrix4 projection = Matrix4::perspective(45.0f, 1000.0f/800.0f, 0.1f, 100.0f);

  glfwSetKeyCallback(w1.win, keyCallback);

  while (true)
  {
    w1.clear();

    modelo1.rendergl(cam, view, projection);

    if (w1.update() == -1)
      break;

    modelo1.update(glfwGetTime());
  }

  return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS)
  {
    switch (key)
    {
      case GLFW_KEY_DOWN:
        cam = Vector3(cam.x+0.5, cam.y, cam.z);
        break;
        
      case GLFW_KEY_UP:
        cam = Vector3(cam.x-0.5, cam.y, cam.z);
        break;

      case GLFW_KEY_LEFT:
        cam = Vector3(cam.x, cam.y, cam.z+1.0);
        break;

      case GLFW_KEY_RIGHT:
        cam = Vector3(cam.x, cam.y, cam.z-1.0);
        break;

      case GLFW_KEY_SPACE:
        cam = Vector3(cam.x, cam.y+1.0, cam.z);
        break;

      case GLFW_KEY_LEFT_SHIFT:
      case GLFW_KEY_RIGHT_SHIFT:
        cam = Vector3(cam.x, cam.y-1.0, cam.z);
        break;
    }
  }

  view = Matrix4::lookAt(cam, centroCubo, Vector3(0.0f,1.0f,0.0f));
}
