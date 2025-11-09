/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          15 de octubre de 2025
 * 
 *  Tema 08:        Lenguaje C
 *  Código 29:      Estructuras de control: WHILE
 *  Descripción:    Construcción de la estructura de control WHILE en lenguaje C.
 *                  Ejecución repetida de un bloque de instrucciones mientras se cumpla una
 *                  condición previa.
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/*********************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/*********************************************************************************
 *  Definiciones y macros
 */


/*********************************************************************************
 *  Funciones
 */


/*********************************************************************************
 *  Función principal
 */

int main(void) {

    int i = 0;

    int x = 5;                                                                                      /*  Variable de prueba (condición) */

    while (x == 5) {
        /** Código del bloque WHILE. */
        i++;
        i++;
    }
}
