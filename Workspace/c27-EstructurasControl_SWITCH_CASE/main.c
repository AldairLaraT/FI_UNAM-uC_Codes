/** -----------------------------------------------------------------------------------------------
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 *
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       15 de octubre de 2025
 *
 * Tema 08:     Lenguaje C
 * Código 27:   Estructuras de control: SWITCH-CASE
 * Descripción: Construcción de la estructura de control SWITCH-CASE en lenguaje C.
 *              Selección de un bloque de instrucciones entre varias opciones, a partir del valor
 *              de una variable.
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

    int32_t x = 1;                                                                                  /* Variable de prueba (condición) */

    switch (x){

        case 1:
            __asm(" NOP");
            __asm(" NOP");
            break;

        case 2:
            __asm(" NOP");
            __asm(" NOP");
            break;

        default:
            __asm(" NOP");
            __asm(" NOP");
            break;

    }

    while (1) {

    }
}
