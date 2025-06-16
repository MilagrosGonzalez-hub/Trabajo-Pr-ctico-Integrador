# Trabajo-Pr-ctico-Integrador
Com.3-Grupo Noche
-Integrantes: -Cruz Micaela. rol:desarrollar el programa
             -Gonzalez Milagros. rol: crear el Readme/repositorio,ayudar brevemente con el desarrollo
- Instrucciones: esencialmente se debe contar con compilador de lenguaje c instalado.
1. **Descargar ZinjaI** (incluye su propio compilador)
   - ir a https://zinjai.sourceforge.net
   - Seleccionar la versión para **Windows**.
   - Descarga el archivo `.exe`.
   - Ejecutar el instalador y seguir los pasos en pantalla.
 - Descripción: Este programa permite al usuario de manera sencilla llevar un control de los reclamos que se hayan hecho en la vecindad. Además de: 
-Agregar nuevos reclamos vecinales.
- Buscar reclamos según nombre, tipo o estado.
- Modificar el estado de un reclamo (pendiente, resuelto, en proceso).
- Mostrar reclamos ordenados por fecha o estado.  
- Descripcion del programa en base a las sentencias y estructuras aprendidas en las unidades 1, 2, 3  y 4 que fueron desarolladas en las clases de programacion:
- UNIDAD 1: Introducción a la Algoritmia y al Lenguaje C;
El programa presenta una estructura básica en lenguaje C teniendo en el, directivas de preprocesador (#include), la definición de constantes, la declaración de estructuras (typedef struct). Presenta variables para almacenar datos dinámicos, como cantidad (el número actual de reclamos), constantes definidas mediante #define, en este caso: MAX_RECLAMOS, MAX_NOMBRE, que son necesarios para establecer límites de tamaño de arreglos y cadenas. Y ademas operaciones de salida como printf para presentar el menu al usuario. 

- UNIDAD 2: Estructura de Datos;
Se utilizó struct para definir un tipo de dato (Reclamo) que agrupa información relacionada. Empleando así, un arreglo estático de estas estructuras (Reclamo reclamos[MAX_RECLAMOS]) para almacenar la colección de reclamos en memoria.  Dicha estructura, agrupa tipos de datos primitivos como; nombre, dirección, tipo y fecha. Los (char, int) se utilizan para definir las cantidades y opciones con valores enteros en el dominio del programa. Los operadores matemáticos se vieron reflejados al usar las sentencias aprendidas como ser: Relacionales: Operadores como < o >;  (idx < 1 || idx > cantidad). == (igualdad) y != (desigualdad) que son omnipresentes en las comparaciones de cadenas (strcmp(criterio, "nombre") == 0) y validaciones de entrada (scanf("%d", &opcion) != 1).
Lógicos: && (AND lógico) y || (OR lógico) son cruciales en la función buscarReclamos(), permitiendo combinar múltiples condiciones para la búsqueda ((criterio == "nombre" && strstr(nombre, valor)) || (criterio == "tipo" && strstr(tipo, valor))).
Se emplearon ademas funciones de entrada (scanf, fgets). El scanf () para la lectura de enteros (la opción del menú, el índice del reclamo), y el fgets () para la lectura de cadenas (leerCadena()).

-UNIDAD 3: sentencias de control e iteracion;
Para la estructura de decision, se emplean If-else y switch; el If-else para las validaciones, control de errores y para dirigir el flujo del programa. Y el switch es para el menú interactivo, permitiendo seleccionar eficientemente la función a ejecutar. Para la estructura de Iteracion se utilizaron las sentencias for y do-while; el for para recorrer los arreglos y emplea un bucle do-while para el menu principal, asegurando que el menu se muestre al menos una vez y se repita hasta que el usuario decida salir. 

-UNIDAD 4: Arreglos, Cadenas y Estructuras Dinámicas (Archivos);


