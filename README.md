# Graficación por Computadora Práctica 5
## .obj Render sin texturas OpenGL

Repositorio: https://github.com/Santi24Yt/cpp-opengl-obj/tree/main

## Especificaciones
- Se utilizará OpenGL con GLSL 4.x, GLFW y C/C++.
- El programa leerá el modelo desde un archivo OBJ y se guardará en una
estructura de datos que utilicen en el programa.
- En la terminal, después de leer el OBJ, desplegar el número de vértices y
el número de caras del modelo.
- El modelo debe de visualizarse utilizando GL POINTS, GL LINES o GL LINE LOOP
y GL TRIANGLES O GL TRIANGLE STRIP, la interacción la podrán
hacer utilizando el teclado.
- El modelo debe de girar sobre el eje Y.
- Los shaders serán a consideración del alumno.

Para ejecución y compilación ver `README`



https://github.com/user-attachments/assets/800c00e0-3c00-4cf6-a6bf-5c0c152da098



En el video se puede ver como el shader por default pinta todos los pixeles del modelo
de blanco, también como se puede elegir un shader para el modelo, en este caso se
tiene implementado iluminación con el modelo de Gouraud y Phong, aunque estos dependen
de que el .obj tenga definidas las normales.

Todavía hay algunos pequeños fallos difíciles de notar en casos en los que se define un mismo
vértice para multiples caras con distintas normales. (No recuerdo si sale en el video).

También podemos ver que como ya usamos OpenGL este aprovecha al máximo las capacidades
de nuestra computadora por lo que el modelo del dragon ya funciona de manera fluida.
