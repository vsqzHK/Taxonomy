Sistema de Evaluaciones Basado en la Taxonomía de Bloom:

Este proyecto fue desarrollado como parte de la asignatura Paradigmas de Programación, correspondiente al tercer año de la carrera de Ingeniería en Computación e Informática.

El objetivo es construir una aplicación de consola en C++ que permita la gestión de preguntas clasificadas según los niveles de la Taxonomía de Bloom. El sistema está pensado para facilitar la planificación de evaluaciones escritas por parte de docentes, y está diseñado siguiendo principios de programación orientada a objetos.


Objetivos del Proyecto:

Registrar preguntas con atributos clave como ID, enunciado, nivel taxonómico, tipo de pregunta, año de uso y tiempo estimado.
Administrar un banco de preguntas de forma segura y controlada.
Generar evaluaciones automáticas filtradas por nivel y cantidad de preguntas.
Aplicar validaciones para evitar duplicidades e inconsistencias lógicas.


Tecnologías Utilizadas:

Lenguaje: C++
Estándar: C++11 o superior
Entorno de desarrollo: Replit, CLion, Visual Studio Code


Plataforma de ejecución: Consola / Terminal


Funcionalidades:

Agregar preguntas al banco de datos con:
  * ID numérico único
  * Enunciado de texto
  * Nivel taxonómico (Recordar, Entender, Aplicar, Analizar, Evaluar, Crear)
  * Tipo de pregunta (Opción múltiple / Verdadero o falso)
  * Año de uso
  * Tiempo estimado (en minutos)
* Eliminar preguntas por ID
* Actualizar el enunciado de una pregunta existente
* Buscar preguntas por nivel taxonómico
* Mostrar todas las preguntas registradas
* Calcular el tiempo total estimado de una evaluación
* Generar evaluaciones por nivel taxonómico y cantidad de preguntas solicitadas

Validaciones

Prevención de IDs duplicados
Rechazo de preguntas con el mismo enunciado usadas en años consecutivos (para cumplir con la restricción del enunciado)
Control de entradas inválidas (texto en vez de números, valores fuera de rango, etc.)


Compilación y Ejecución:

Desde terminal:
g++ main.cpp -o evaluador
./evaluador

Ejemplo de Flujo:
1.-Agregar Pregunta
2.-Eliminar Pregunta
3.-Actualizar Pregunta
4.-Buscar por Nivel Taxonomico
5.-Mostrar Evaluacion
6.-Calcular Tiempo Total
7.-Generar Evaluacion por Nivel y Cantidad
8.-Salir


Diagrama de Clases:
El diagrama de clases se encuentra disponible como imagen en el informe técnico del proyecto.


Observaciones Finales
Este sistema fue diseñado para ser extendible y escalable. Puede ser adaptado en el futuro para utilizar almacenamiento en archivos, bases de datos o interfaces gráficas. Actualmente cumple con los requerimientos funcionales solicitados para la entrega académica.


Licencia y Uso:
Este proyecto fue creado con fines educativos y puede ser utilizado libremente como referencia para trabajos académicos o aprendizaje personal.

Autores:
Proyecto desarrollado por estudiantes de tercer año de Ingeniería en Informática. 
Colaboradores: Lukas Flores (@Raizexs), David Vásquez
