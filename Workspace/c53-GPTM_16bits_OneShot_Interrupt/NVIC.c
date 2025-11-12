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


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        TIMER0A_Handler
 * 
 *  Descripción:    Rutina de servicio de interrupción (ISR) del TIMER 0A.
 */

void TIMER0A_Handler(void) {

    /** Limpiar la bandera de interrupción. */
    TIMER0_ICR_R |= 0x01;                                                                           /*  GPTM0 => TATOCINT: GPTM Timer A Time-Out Raw Interrupt -> TATORIS bit (GPTMRIS) and TATOMIS bit (GPTMMIS) cleared */

    GPIO_PORTN_DATA_R ^= 0x02;                                                                      /*  LED D1 -> toggle */

}

/************************************************
 *  Función:        TIMER0B_Handler
 * 
 *  Descripción:    Rutina de servicio de interrupción (ISR) del TIMER 0B.
 */

void TIMER0B_Handler(void) {

    /** Limpiar la bandera de interrupción. */
    TIMER0_ICR_R |= 0x0100;                                                                         /*  GPTM0 => TBTOCINT: GPTM Timer B Time-Out Raw Interrupt -> TBTORIS bit (GPTMRIS) and TBTOMIS bit (GPTMMIS) cleared */

    GPIO_PORTN_DATA_R ^= 0x01;                                                                      /*  LED D2 -> toggle */

}

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

        /** 7.  Habilitar el temporizador y que comience con la cuenta. */
        TIMER0_CTL_R |= 0x01;                                                                       /*  GPTM0 => TAEN: GPTM Timer A Enable -> Enabled and begins counting */
    }

    if (!(GPIO_PORTJ_AHB_DATA_R & 0x02)) {                                                          /*  IF (SW2 -> on) */

        /** 7.  Habilitar el temporizador y que comience con la cuenta. */
        TIMER0_CTL_R |= 0x0100;                                                                     /*  GPTM0 => TBEN: GPTM Timer B Enable -> Enabled and begins counting */
    }

}
