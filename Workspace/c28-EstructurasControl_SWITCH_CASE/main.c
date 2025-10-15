/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       15 de octubre de 2025
 * 
 * Tema 08:     Lenguaje C
 * Código 28:   Estructuras de control: SWITCH-CASE
 * Descripción: Construcción de la estructura de control SWITCH-CASE en lenguaje C.
 *              Selección de un bloque de instrucciones entre varias opciones, a partir del valor de una variable.
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
    int k = 0;

    int x = 1;                                                                                      /*  Variable de prueba (condición) */

    switch (x){
        case 1:
            /*  Código del bloque case1 */
            i++;
            i++;
            break;
        case 2:
            /*  Código del bloque case2 */
            j++;
            j++;
            break;
        default:
            /*  Código del bloque DEFAULT */
            k++;
            k++;
            break;
    }
}
