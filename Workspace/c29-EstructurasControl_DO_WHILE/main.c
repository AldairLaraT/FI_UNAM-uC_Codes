/** -----------------------------------------------------------------------------------------------
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 *
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       15 de octubre de 2025
 *
 * Tema 08:     Lenguaje C
 * Código 29:   Estructuras de control: DO-WHILE
 * Descripción: Construcción de la estructura de control DO-WHILE en lenguaje C.
 *              Ejecución de un bloque de instrucciones al menos una vez y repetición si se cumple
 *              una condición.
 *              NOTA: Se usan instrucciones NOP de lenguaje ensamblador para indicar el cuerpo del
 *                    código o la estructura de control.
 *
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 */


/** -----------------------------------------------------------------------------------------------
 * Archivos de cabecera
 */

#include <stdint.h>                                                                                 /* Tipos enteros con tamaños fijos */


/** -----------------------------------------------------------------------------------------------
 * Definiciones y macros
 */


/** -----------------------------------------------------------------------------------------------
 * Funciones
 */


/** -----------------------------------------------------------------------------------------------
 * Función principal
 */

int main (void) {

    int32_t x = 5;                                                                                  /* Variable de prueba (condición) */

    do {

        __asm(" NOP");
        __asm(" NOP");

    } while (x == 5);

    while (1) {

    }
}
