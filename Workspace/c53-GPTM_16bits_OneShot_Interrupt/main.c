/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          11 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 53:      Módulo temporizador de propósito general (GPTM): 16bits, one-shot, interrupción
 *  Descripción:    Código en lenguaje C que utiliza los temporizadores TIMER0A y TIMER0B en
 *                  configuración individual (16 bits) y modo one-shot, empleando interrupciones
 *                  por time-out, para generar retardos al presionar un botón (SW1 o SW2) y
 *                  conmutar los LED de usuario (D1 o D2) de la tarjeta de desarrollo.
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
    GPTM0A_OneShot_Init(65535, 0);                                                                  /*  Inicialización y configuración del temporizador GPTM0 (subtimer A) en modo one-shot */
    GPTM0B_OneShot_Init(65535, 255);                                                                /*  Inicialización y configuración del temporizador GPTM0 (subtimer A) en modo one-shot */

    while (1) {}
}
