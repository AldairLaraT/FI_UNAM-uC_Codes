/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          15 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 56:      Módulo temporizador de propósito general (GPTM): Pulse Width Modulation (PWM)
 *  Descripción:    Código en lenguaje C que utiliza el temporizador TIMER2A en configuración PWM,
 *                  generando una señal de 1 KHz con un ciclo de trabajo del 50% en el puerto GPIO
 *                  M[0] y los botones (SW1 y SW2) de la tarjeta de desarrollo para modificar el
 *                  ciclo de trabajo en saltos del 10%.
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

uint32_t PWM_DutyCycle = 8000;                                                                      /*  Ciclo de trabajo de la señal PWM */

int main(void) {

    GPIO_PortJ_Init();                                                                              /*  Inicialización y configuración del puerto GPIO J */
    GPTM2A_PWM_Init(16000, PWM_DutyCycle);                                                          /*  Inicialización y configuración del temporizador GPTM2 (subtimer A) en modo PWM */

    while (1) {}
}
