/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       15 de octubre de 2025
 * 
 * Tema 08:     Lenguaje C
 * Código 31:   Estructuras de control: FOR
 * Descripción: Construcción de la estructura de control FOR en lenguaje C.
 *              Ejecución repetida de un bloque de instrucciones controlada por un contador.
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

    int x = 0;

    for (i = 0; i < 5; i++) {
        /*  Código del bloque FOR */
        x++;
        x++;
    }
}
