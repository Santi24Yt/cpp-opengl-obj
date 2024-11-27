#include "ventana.h"
#include "vecmatriz.h"
#include "objreader.h"
#include "modelo.h"
#include <iostream>

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
  Vector3 centroCubo(centroCuboPf.x, centroCuboPf.y, centroCuboPf.z);

  Vector3 cam(centroCuboPf.x + objf.anchox() + 10, 5, 0);

  std::cout << "Modelo: " << objf.filedir << std::endl;
  std::cout << "No. de vértices: " << objf.vertices.size() << std::endl;
  std::cout << "No. de caras: " << objf.caras.size() << std::endl;

  Matrix4 view = Matrix4::lookAt(cam, centroCubo, Vector3(0.0f,1.0f,0.0f));
  Matrix4 projection = Matrix4::perspective(45.0f, 1000.0f/800.0f, 0.1f, 100.0f);

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
