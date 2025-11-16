/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          15 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 55:      Módulo temporizador de propósito general (GPTM): 32bits, periodic, interrupción
 *  Descripción:    Código en lenguaje C que utiliza el temporizador TIMER0A en configuración
 *                  concatenada (32 bits) y modo periodic, empleando interrupción por time-out,
 *                  para hacer parpadear un LED de usuario (D1), habilitando/deshabilitando el
 *                  temporizador con los botones (SW1 y SW2) de la tarjeta de desarrollo.
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "GPTM.h"                                                                                   /*  Archivo de cabecera del módulo GPTM */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */


/**************************************************************************************************
 *  Variables globales
 */

uint32_t Bounce_Delay = 200000;                                                                     /*  Valor de carga del SysTick para un retardo de rebote de 50ms (f = 4MHz) */


/**************************************************************************************************
 *  Función principal
 */

int main(void) {

    GPIO_PortJ_Init();                                                                              /*  Inicialización y configuración del puerto GPIO J */
    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */
    GPTM0A_Periodic_Init(8000000);                                                                  /*  Inicialización y configuración del temporizador GPTM0 (subtimer A) en modo periodic */

    while (1) {}
}
