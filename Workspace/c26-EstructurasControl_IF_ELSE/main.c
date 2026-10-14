/** -----------------------------------------------------------------------------------------------
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 *
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       15 de octubre de 2025
 *
 * Tema 08:     Lenguaje C
 * Código 26:   Estructuras de control: IF-ELSE
 * Descripción: Construcción de la estructura de control IF-ELSE en lenguaje C.
 *              Selección entre dos bloques de instrucciones, a partir del cumplimiento de una
 *              condición.
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

    if (x == 5){

        __asm(" NOP");
        __asm(" NOP");

    } else {

        __asm(" NOP");
        __asm(" NOP");

    }

    while (1) {

    }
}
