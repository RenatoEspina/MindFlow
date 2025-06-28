*PROYECTO APLICACIÓN MINDFLOW - ASISTENTE DE ORGANIZACIÓN ACADÉMICA* 

# Descripción

 MindFlow, creado en el entorno de programación C, busca a ayudar a estudiantes de enseñanza media y superior a poder organizar y gestionar sus responsabilidades de forma clara y eficiente. Esta herramienta combina planificación y estudio personalizado. Teniendo una interfaz intuitiva y clara para el usuario. 
 
 MindFlow incluye un calendario mensual interactivo, una agenda en donde el usuario puede agregar, modificar, eliminar tareas que a su vez puede marcar como "Realizada" o "Pendiente", tarjetas de memoria para poder estudiar y una calculadora de notas, que puede el usuario tener la opción de ser de promedio simple o ponderado. Todas estas funciones enfocadas en fomentar una autonomia y autodisciplina academica, asi bajando los niveles de estres y sobrecarga academica. 


### Cómo compilar y ejecutar ###
 El programa está escrito en lenguaje C y puede ejecutarse fácilmente usando Visual Studio Code con soporte para C/C++. Sigue estos pasos para ejecutarlo en tu maquina local.
 
 *** REQUISITOS ***
 - Visual Studio Code.
 - Extensión C/C++ de Microsoft.
 - Compilador C (gcc). Si usas Windows, se recomienda instalar MinGW o usar WSL.
 - Usar una terminal con soporte para UTF-8 (como la de Visual Studio Code configurada correctamente o Windows Terminal).

 *** PASOS ***
 1. Descarga y descomprime el proyecto.
 2. Abre la carpeta en Visual Studio Code(archivo > Abrir carpeta...).
 3. Abre una terminal integrada (Terminal > Nueva Terminal).
 4. COMPILAR CON "gcc Mindflow.c complementos/*.c -o Mindflow.exe -Wall". Esto generará un archivo ejecutable en la misma carpeta.
 5. Para hacerlo correr "./Mindflow.exe" 


### Funcionalidades ###

*** Calendario mensual interactivo ***
 Permite registrar y visualizar eventos académicos (pruebas, controles, trabajos) por día. Ayuda a planificar y anticipar fechas importantes.

*** Agenda Personalizada ***
 Gestión de actividades diarias con estado “Pendiente” o “Realizada”. Las tareas pueden ser modificadas o eliminadas en cualquier momento.

*** Tarjetas de Memoria ***
 Creación, clasificación y estudio de contenidos mediante tarjetas personalizadas. Incluye un Modo Estudio que permite autoevaluarse y obtener estadísticas de desempeño.

*** Calculadora de Notas ***
 Cálculo de promedios simples y ponderados por materia, permitiendo al usuario hacer seguimiento a su rendimiento académico.

*** Problemas conocidos ***
 Si el usuario ingresa caracteres no válidos (como letras donde se esperan números), el programa puede comportarse de forma inesperada o cerrarse abruptamente.

*** A mejorar ***
 - Validación robusta de entradas del usuario.
 - Interfaz más amigable e intuitiva.
 - Edición de datos ya ingresados, como materias o eventos pasados.
 - Opciones como 


### EJEMPLO DE USO ###

*** Menú Principal y Submenus ***
 - Menú Principal: Presenta las 5 funcionalidades clave: Calendario, Agenda, Tarjetas de Memoria, Calculadora de Notas y Salir. Las selecciona con número. 

 - Submenú Ver calendario: Permite seleccionar si desea ver calendario mensual y ver el detalle de un día en especifico. Registro visual de tareas con detalles editables. 

 - Submenú Ver cursos: Muestra los cursos registrados por el usuario y su ID correspondiente.
 Al seleccionar un curso se puede modificar notas y calcular promedio.

 - Submenú Repaso: Aqui el usuario puede seleccionar un curso para comenzar con el repaso, la segunda opción permite agregar preguntas al repaso de un curso. Al seleccionar un curso puede hacer un repaso con preguntas secuenciales o en opción aleatoria.

 - Submenú Salir: Sale del programa y lo cierra.
 
### CONTRIBUCIÓN INDIVIDUAL ###
Este proyecto fue desarrollado de manera colaborativa por un equipo de cuatro integrantes, donde cada uno asumió roles específicos que permitieron complementar el desarrollo tanto a nivel estructural como funcional y visual de la aplicación.

- Renato Espina: Diseñó la base del proyecto, estableciendo la estructura general del código y proponiendo las primeras definiciones de los Tipos Abstractos de Datos (TDA).

- Andres Miranda: Encargado del desarrollo e implementación de la Calculadora de Notas, incluyendo el diseño del submenú, ingreso de datos, cálculo de promedios simples y ponderados. Colaboró en pruebas de funcionamiento general y en la detección de errores lógicos en distintas funcionalidades.

- Felipe Silva (Your Name): Desarrolló el menú principal de la aplicación, estableciendo la navegación general entre las distintas funcionalidades. Se encargó de la mejora estética de la interfaz textual, ordenando visualmente la distribución de las opciones y mensajes. Desarrolló la funcionalidad para iniciar un repaso, integrando la lógica de flashcards (tarjetas de memoria) y el modo de estudio aleatorio o secuencial. Encargado de diseñar la interfaz de los submenús "Ver cursos" y "Repaso", con navegación intuitiva y retorno al menú principal.

- Martina Valenzuela: Participó activamente en la redacción del README y en la documentación general del proyecto, asegurando claridad y comprensión para usuarios y evaluadores. Colaboró en pruebas integrales del sistema y en la propuesta de mejoras para la interfaz de usuario y flujo general.