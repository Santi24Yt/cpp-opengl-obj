#include "ventana.h"
#include "model.h"
#include "vecmatriz.h"
#include "objreader.h"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/io.hpp>
#include <iostream>

Model *model;

int main(int argc, char *argv[])
{
  std::string archivo;
  // int optimize = 0;
  if (argc < 2)
  {
    std::cout << "Introduce nombre de archivo: ";
    std::cin >> archivo;
  } else {
    archivo = argv[1];
    // if (argc >= 3)
    //   optimize = std::stoi(argv[2]);
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
  // modelo1.initgl();

  Puntof centroCuboPf = objf.centroProm();
  Vector3 centroCubo(centroCuboPf.x, centroCuboPf.y, centroCuboPf.z);

  Vector3 cam(centroCuboPf.x + objf.anchox() + 20, 2, 0);

  std::cout << "Modelo: " << objf.filedir << std::endl;
  std::cout << "No. de vértices: " << objf.vertices.size() << std::endl;
  std::cout << "No. de caras: " << objf.caras.size() << std::endl;

  model = new Model(modelo1);
  model->initModel();

  Matrix4 view = Matrix4::lookAt(cam, centroCubo, Vector3(0.0f,1.0f,0.0f));
  Matrix4 projection = Matrix4::perspective(45.0f, 1000.0f/800.0f, 0.1f, 100.0f);

  // glm::mat4 view1 = glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
  // glm::mat4 projection1 = glm::perspective(glm::radians(45.0f), 1000.0f / 800.0f, 0.1f, 100.0f);
  //
  //   std::cout << "View ----" << std::endl;
  //   std::cout << "vecmatriz" << std::endl;
  //   std::cout << view.glm() << std::endl;
  //   std::cout << "glm" << std::endl;
  //   std::cout << view1 << std::endl << std::endl;
  //   std::cout << "Project ----" << std::endl;
  //   std::cout << "vecmatriz" << std::endl;
  //   std::cout << projection.glm() << std::endl;
  //   std::cout << projection1 << std::endl;

  while (true)
  {
    w1.clear();

    model->renderModel(cam.glm(), view.glm(), projection.glm());

    if (w1.update() == -1)
      break;

    model->updateModel(glfwGetTime());
  }

  return 0;
}
