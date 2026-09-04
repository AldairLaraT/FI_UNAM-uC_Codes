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
 *  Archivo:        Archivo fuente del módulo NVIC
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "GPTM.h"                                                                                   /*  Archivo de cabecera del módulo GPTM */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */


/**************************************************************************************************
 *  Variables externas (parámetros)
 */

extern uint32_t Bounce_Delay;                                                                       /*  Valor de carga del SysTick para el retardo de rebote */
extern uint32_t PWM_DutyCycle;                                                                      /*  Ciclo de trabajo de la señal PWM */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        GPIO_PortJ_Handler
 * 
 *  Descripción:    Rutina de servicio de interrupción (ISR) del GPIO PortJ.
 */

void GPIO_PortJ_Handler(void) {

    /** Limpiar la bandera de interrupción. */
    GPIO_PORTJ_AHB_ICR_R = (GPIO_PORTJ_AHB_MIS_R & 0x03);                                           /*  PortJ => IC: Interrupt Clear -> Interrupt cleared */

    /** Retardo de rebote. */
    SysTick_Init_OneShot (Bounce_Delay);                                                            /*  Inicialización y configuración del SysTick en modo one-shot */
    while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT)) {}                                               /*  SysTick => COUNT: Count Flag -> The SysTick timer has counted to 0 */

    /** Confirmar qué botón se presionó. */
    if (!(GPIO_PORTJ_AHB_DATA_R & 0x01)) {                                                          /*  IF (SW1 -> on) */
        if (PWM_DutyCycle < 14400) {
            PWM_DutyCycle += 1600;
        }
    }

    if (!(GPIO_PORTJ_AHB_DATA_R & 0x02)) {                                                          /*  IF (SW2 -> on) */
        if (PWM_DutyCycle > 1600) {
            PWM_DutyCycle -= 1600;
        }
    }

    /** Actualizar el valor de comparación. */
    TIMER2_TAPMR_R = (PWM_DutyCycle & 0x00FF0000) >> 16;                                            /*  GPTM2 => TAPSMR: GPTM Timer A Prescale Match -> Loads the prescaler match value for Timer A */
    TIMER2_TAMATCHR_R = (PWM_DutyCycle & 0xFFFF);                                                   /*  GPTM2 => TAMR: GPTM TImer A Match -> Loads the match value for Timer A */

}
