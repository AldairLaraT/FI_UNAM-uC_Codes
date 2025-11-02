/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       01 de noviembre de 2025
 * 
 * Tema 09:     Periféricos
 * Código 43:   Control de un LED con un SW de usuario con debounce (modular)
 * Descripción: Código en lenguaje C que conmuta el LED D1 de la tarjeta de desarrollo,
 *              dependiendo del botón SW1, considerando el efecto rebote.
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 * Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */


/**************************************************************************************************
 * Variables globales
 */


/**************************************************************************************************
 * Función principal
 */

int main(void) {

    uint32_t Bounce_Delay = 320000;                                                                 /*  Valor de carga del SysTick para un retardo de rebote de 80ms (f = 4MHz) */

    GPIO_PortJ_Init();                                                                              /*  Inicialización y configuración del puerto GPIO J */
    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */

    while (1) {
        if (GPIO_PORTJ_AHB_DATA_R == 0x00) {                                                        /*  IF (SW1 -> on) */
            SysTick_Init_OneShot (Bounce_Delay);                                                    /*  Inicialización y configuración del SysTick en modo one-shot */
            while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT)) {}                                       /*  SysTick => COUNT: Count Flag -> The SysTick timer has counted to 0 */
            if (GPIO_PORTJ_AHB_DATA_R == 0x00) {                                                    /*  IF (SW1 -> on) */
                GPIO_PORTN_DATA_R ^= 0x02;                                                          /*  LED D1 -> toggle */
            }
        }
    }
}
