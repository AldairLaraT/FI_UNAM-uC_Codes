/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          01 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 45:      SysTick en modo one-shot (modular)
 *  Descripción:    Código en lenguaje C que conmuta el LED D1 de la tarjeta de desarrollo con una
 *                  frecuencia de 1Hz, empleando el SysTick en modo one-shot.
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */


/**************************************************************************************************
 *  Variables globales
 */


/**************************************************************************************************
 *  Función principal
 */

int main(void) {

    uint32_t Delay = 4000000;                                                                       /*  Valor de carga del SysTick para un retardo de 1s (f = 4MHz) */

    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */
    SysTick_Init_OneShot (Delay);                                                                   /*  Inicialización y configuración del SysTick en modo one-shot */

    while (1) {

        /** Esperar a que termine la cuenta del SysTick. */
        while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT)) {}                                           /*  SysTick => COUNT: Count Flag -> The SysTick timer has counted to 0 */

        GPIO_PORTN_DATA_R ^= 0x02;                                                                  /*  LED D1 -> toggle */
        SysTick_Init_OneShot (Delay);                                                               /*  Inicialización y configuración del SysTick en modo one-shot */
    }
}
