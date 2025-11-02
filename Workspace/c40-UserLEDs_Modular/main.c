/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       01 de noviembre de 2025
 * 
 * Tema 09:     Periféricos
 * Código 40:   Control de los LED de usuario (modular)
 * Descripción: Código en lenguaje C que enciende y apaga los LED D1 y D2 de la tarjeta de desarrollo.
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 * Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */


/**************************************************************************************************
 * Variables globales
 */


/**************************************************************************************************
 * Función principal
 */

int main(void) {

    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */

    while (1) {
        GPIO_PORTN_DATA_R ^= 0x02;                                                                  /*  LED D1 -> toggle */
        GPIO_PORTN_DATA_R ^= 0x01;                                                                  /*  LED D2 -> toggle */
    }
}
