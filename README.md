Sistema de Generación de Evaluaciones Basado en la Taxonomía de Bloom

Este proyecto fue desarrollado por estudiantes de tercer año de la carrera de Ingeniería en Computación e Informática para la asignatura de Paradigmas de Programación (PTEC102). El objetivo es construir un sistema que permita gestionar preguntas y generar evaluaciones utilizando los niveles de la taxonomía de Bloom como criterio pedagógico.

Propósito del proyecto

El propósito principal de esta herramienta es automatizar el proceso de creación de evaluaciones escritas, clasificando las preguntas por nivel taxonómico (Recordar, Entender, Aplicar, Analizar, Evaluar, Crear) y permitiendo acciones básicas como agregar, eliminar, actualizar y buscar preguntas.

Este enfoque nos ayuda a reflexionar sobre cómo diseñar evaluaciones alineadas a objetivos pedagógicos específicos, integrando conceptos de programación orientada a objetos y manipulación de datos en consola.

Funcionalidades principales
	•	Agregar pregunta con validaciones por ID, año y enunciado.
	•	Eliminar pregunta por ID.
	•	Actualizar el enunciado de una pregunta específica.
	•	Buscar por nivel taxonómico.
	•	Mostrar evaluación completa.
	•	Calcular tiempo total estimado para una evaluación.
	•	Generar evaluación filtrando por nivel y cantidad.

Estructura del código

El código fue modularizado y comentado para facilitar su lectura y mantenimiento. Las clases clave son:
	•	Pregunta: contiene atributos como ID, enunciado, nivel taxonómico, tipo, año y tiempo estimado.
	•	Evaluacion: maneja la colección de preguntas y las operaciones CRUD.
	•	SistemaEvaluacion: implementa el menú y la interacción con el usuario.

Validaciones destacadas
	•	No se permite repetir preguntas con el mismo enunciado y año (para cumplir la condición de no repetir preguntas en años consecutivos).
	•	Se evita duplicación por ID.
	•	Se maneja entrada incorrecta o vacía mediante limpieza de buffer y validaciones.

¿Por qué usamos consola?

El enfoque en consola busca mantener el código portable, accesible y fácil de ejecutar en evaluaciones o presentaciones donde no se puede depender de interfaces gráficas o dependencias externas.

Cómo ejecutar el programa
	1.	Clona el repositorio:

git clone https://github.com/vsqzHK/Taxonomy.git

	2.	Compila el archivo principal:

g++ main.cpp -o evaluador

	3.	Ejecuta desde terminal:

./evaluador

Créditos

Autores del proyecto:
	•	David Vásquez
	•	Lukas Flores GitHub: raizexs)

Este trabajo se realizó con el apoyo del docente de la asignatura y en colaboración activa entre los integrantes.

⸻

Si deseas aportar mejoras o detectar errores, puedes dejar un comentario o hacer un fork del repositorio.
