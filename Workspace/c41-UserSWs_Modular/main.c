/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       01 de noviembre de 2025
 * 
 * Tema 09:     Periféricos
 * Código 41:   Control de un LED con un SW de usuario (modular)
 * Descripción: Código en lenguaje C que enciende/apaga el LED D1 de la tarjeta de desarrollo,
 *              dependiendo del botón SW1.
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

    GPIO_PortJ_Init();                                                                              /*  Inicialización y configuración del puerto GPIO J */
    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */

    while (1) {
        if (GPIO_PORTJ_AHB_DATA_R == 0x00) {                                                        /*  IF (SW1 -> on) */
            GPIO_PORTN_DATA_R |= 0x02;                                                              /*  LED D1 -> on */
        } else {                                                                                    /*  IF (SW1 -> off) */
            GPIO_PORTN_DATA_R &= ~0x02;                                                             /*  LED D1 -> off */
        }
    }
}
