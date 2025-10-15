/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       15 de octubre de 2025
 * 
 * Tema 08:     Lenguaje C
 * Código 27:   Estructuras de control: IF-ELSE
 * Descripción: Construcción de la estructura de control IF-ELSE en lenguaje C.
 *              Selección entre dos bloques de instrucciones, a partir del cumplimiento de una condición.
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


/*********************************************************************************
 * Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/*********************************************************************************
 * Definiciones y macros
 */


/*********************************************************************************
 * Funciones
 */


/*********************************************************************************
 * Función principal
 */

int main(void) {

    int i = 0;
    int j = 0;

    int x = 5;                                                                                      /*  Variable de prueba (condición) */

    if (x == 5){
        /*  Código del bloque IF */
        i++;
        i++;
    } else {
        /*  Código del bloque ELSE */
        j++;
        j++;
    }
}
