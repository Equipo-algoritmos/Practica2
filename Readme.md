# Práctica 2: Métodos de ordenamiento

Implementación en C de los ordenamientos por **inserción, burbuja, selección y mezcla**. El programa permite aplicar los cuatro métodos a un mismo arreglo de enteros, observar sus pasos con entradas pequeñas y medir el tiempo de ordenamiento con entradas mayores.

## Datos de la práctica

- **Institución:** Instituto Politécnico Nacional, Escuela Superior de Cómputo (ESCOM).
- **Carrera:** Ingeniería en Inteligencia Artificial.
- **Materia:** Algoritmos y Estructuras de Datos.
- **Grupo:** 2BM2.
- **Profesora:** Cecilia Albortante Morato.
- **Integrantes:** Josué Agudelo Mancera y Jesús Gabriel Ramírez González.

## Objetivo

Implementar cada algoritmo en una función independiente, seleccionar el método mediante un menú, definir el tamaño de entrada y mostrar los datos antes y después de ordenarlos. La generación aleatoria utiliza enteros entre **-100 y 100**, ambos incluidos, como indica la presentación de la práctica.

## Archivos principales

| Archivo | Contenido |
| --- | --- |
| `Programa1.c` | Programa principal que integra los cuatro métodos, el menú, la visualización de pasos, la medición de tiempo y la mediana. |
| `Burbuja.c` | Programa independiente para trabajar con burbuja. |
| `Seleccion.c` | Programa independiente para trabajar con selección. |
| `mezcla.c` | Programa independiente para trabajar con mezcla. |
| `JAM-JGRG-Práctica2.pdf` | Reporte de la práctica. |
| `Práctica 2 - Ordenamientos.pdf` | Presentación con las instrucciones de la actividad. |

## Compilación y ejecución

El programa principal está preparado para **Windows** y utiliza `conio.h`, `windows.h`, `getch()` y `system("cls")`. Se necesita GCC para Windows, por ejemplo el incluido en MinGW-w64, con soporte para C99 o posterior y arreglos de longitud variable.

Desde la carpeta `practica2`, compila con:

```powershell
gcc -std=c11 -O0 Programa1.c -o Programa1.exe
```

Ejecuta en una terminal interactiva:

```powershell
.\Programa1.exe
```

La opción `-O0` desactiva las optimizaciones del compilador. Al comparar tiempos, conserva las mismas opciones de compilación para todos los métodos.

Los archivos de los programas independientes contienen su propio `main`: se compilan por separado, no junto con `Programa1.c`.

```powershell
gcc -std=c11 -O0 Burbuja.c -o Burbuja.exe
gcc -std=c11 -O0 Seleccion.c -o Seleccion.exe
gcc -std=c11 -O0 mezcla.c -o mezcla.exe
```

## Uso del programa principal

El menú ofrece cuatro opciones:

1. **Inicializar arreglo:** solicita una cantidad entre 1 y 1 000 000, el tipo de entrada y si se desea mostrar el arreglo generado.
2. **Ver arreglo generado:** muestra los datos originales, aunque ya se haya realizado un ordenamiento.
3. **Ordenar el arreglo generado:** permite elegir inserción, burbuja, selección o mezcla. Después muestra la mediana y permite consultar el resultado.
4. **Salir del programa.**

Primero inicializa el arreglo y después utiliza las opciones de consulta u ordenamiento. Introduce las cantidades sin separadores de miles: por ejemplo, `10000`.

### Tipos de entrada

| Opción | Tipo | Valores generados |
| --- | --- | --- |
| 1 | Ordenado | De 1 a n. |
| 2 | Invertido | De n a 1. |
| 3 | Aleatorio | Enteros entre -100 y 100; pueden aparecer negativos, cero y repetidos. |

El programa conserva una copia del arreglo original. Antes de ordenar, restaura esos datos en el arreglo de trabajo mediante `memcpy`, de modo que se pueden probar varios métodos con la misma entrada.

### Ejemplo de ejecución

1. Elige `1` en el menú principal para inicializar.
2. Introduce `5` como cantidad y `2` como tipo de entrada invertida.
3. Elige `1` para ver el arreglo: `5, 4, 3, 2, 1`. Presiona una tecla para continuar.
4. Elige `3` en el menú principal y después `2` para ordenar con burbuja.
5. Observa las cuatro pasadas con intercambios. El resultado es `1, 2, 3, 4, 5` y la mediana es `3.00`.
6. Elige `1` para mostrar el resultado y presiona una tecla para volver al menú.

Para comparar otro método, vuelve a elegir la opción `3`: el programa recupera la entrada original antes de ordenar.

## Métodos implementados

| Método | Funcionamiento | Mejor caso | Peor caso |
| --- | --- | --- | --- |
| Inserción | Toma un elemento, desplaza los mayores de la parte inicial y lo inserta en su posición. | O(n) | O(n²) |
| Burbuja | Compara vecinos y los intercambia; cada pasada coloca el mayor pendiente al final. Termina antes si no hubo cambios. | O(n) | O(n²) |
| Selección | Busca el mínimo del tramo pendiente y lo coloca en la siguiente posición inicial. | O(n²) | O(n²) |
| Mezcla | Divide el arreglo recursivamente y une las mitades ordenadas mediante la función `merge`. | O(n log n) | O(n log n) |

Estas complejidades describen las versiones sin impresión de pasos. Mezcla reserva arreglos auxiliares `L` y `R` con `malloc` y los libera después de cada unión.

## Visualización de pasos

Con **1 a 10 elementos**, el programa utiliza las funciones terminadas en `Pasos`:

- **Inserción:** muestra dos columnas con los datos ordenados y los pendientes.
- **Burbuja:** muestra el estado inicial y una fila por pasada con intercambios. La pasada que detecta que no hubo cambios termina antes de imprimirse.
- **Selección:** muestra el estado inicial y el arreglo después de cada búsqueda y colocación del mínimo.
- **Mezcla:** muestra las mitades `L` y `R` y el resultado de cada unión. Con un solo elemento no se realizan uniones.

## Tiempo de ordenamiento y mediana

Con **más de 10 elementos**, se utiliza la versión sin pasos y se mide su duración mediante `clock()`. El resultado se presenta en milisegundos enteros. La generación de datos, la copia del arreglo original y la impresión del resultado quedan fuera del intervalo medido.

Un resultado de `0 ms` puede deberse a la resolución del reloj o a la conversión a entero; no significa que el algoritmo haya tardado exactamente cero. Los tiempos también dependen del tamaño, el orden inicial, el equipo y las opciones de compilación.

La mediana se calcula después de ordenar:

- Para una cantidad impar, es el elemento central.
- Para una cantidad par, es el promedio de los dos elementos centrales.

## Casos para comprobar el funcionamiento

- **Ordenado:** debe conservar los valores de 1 a n; burbuja termina en la primera revisión sin intercambios.
- **Invertido:** permite observar los desplazamientos e intercambios necesarios para obtener el orden ascendente.
- **Aleatorio:** permite comprobar la conservación de negativos y valores repetidos.
- **Un elemento:** debe permanecer igual y coincidir con su mediana.
- **10 y 11 elementos:** permiten observar el cambio entre visualización de pasos y medición de tiempo.

Para comparar métodos, utiliza el mismo arreglo original y comprueba tanto el orden final como la conservación de todos sus valores.
