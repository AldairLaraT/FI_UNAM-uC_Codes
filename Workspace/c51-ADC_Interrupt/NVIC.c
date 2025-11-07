/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       06 de noviembre de 2025
 * 
 * Tema 09:     Periféricos
 * Código 51:   Convertidor analógico digital (ADC): Interrupción
 * Descripción: Código en lenguaje C que configura el módulo ADC_0, empleando el secuenciador de
 *              muestras SS_1 para leer el valor de dos potenciómetros conectados en las entradas
 *              analógicas AIN_10 (PB4) y AIN_17 (PK1), empleando interrupciones, usando los LED
 *              de usuario de la tarjeta de desarrollo como indicador del nivel de voltaje de un
 *              potenciómetro, dependiendo del último botón (SW1 o SW2) presionado.
 * 
 * Archivo:     Archivo fuente del módulo NVIC
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 * Archivos de cabecera
 */

#include "ADC.h"                                                                                    /*  Archivo de cabecera del módulo ADC */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */


/**************************************************************************************************
 * Variables externas (parámetros)
 */

extern uint8_t pot_select;                                                                          /*  Selección del potenciómetro */
extern uint32_t Bounce_Delay;                                                                       /*  Valor de carga del SysTick para el retardo de rebote */
extern uint16_t ADC0_SS1_AIN10;                                                                     /*  Voltaje en la entrada analógica 10 (AIN_10, ADC_0, primera muestra del SS_1) */
extern uint16_t ADC0_SS1_AIN17;                                                                     /*  Voltaje en la entrada analógica 17 (AIN_17, ADC_0, segunda muestra del SS_1) */


/**************************************************************************************************
 * Funciones
 */

/************************************************
 * Función:     ADC0_SS1_Handler
 * 
 * Descripción: Rutina de servicio de interrupción (ISR) del ADC0 SS1.
 */

void ADC0_SS1_Handler(void) {

    /*  Limpiar la bandera de interrupción */
    ADC0_ISC_R |= 0x02;                                                                             /*  ADC0 => IN1: SS1 Interrupt Status and Clear -> IN1 bit (ADC0_ISC_R) and INR1 bit (ADC0_RIS_R) cleared */

    /** Leer el resultado de la conversión almacenado en la FIFO. */
    ADC0_SS1_AIN10 = (ADC0_SSFIFO1_R & 0x0FFF);                                                 /*  ADC0 SS1 => DATA: Conversion Result Data (1st sample) */
    ADC0_SS1_AIN17 = (ADC0_SSFIFO1_R & 0x0FFF);                                                 /*  ADC0 SS1 => DATA: Conversion Result Data (2nd sample) */

    /** Generar el evento de disparo para iniciar el muestro de la señal. */
    ADC0_PSSI_R |= 0x02;                                                                        /*  ADC0 => SS1: SS1 Initiate -> Begin sampling on SS1 */

}

/************************************************
 * Función:     GPIO_PortJ_Handler
 * 
 * Descripción: Rutina de servicio de interrupción (ISR) del GPIO PortJ.
 */

void GPIO_PortJ_Handler(void) {

    /*  Limpiar la bandera de interrupción */
    GPIO_PORTJ_AHB_ICR_R = (GPIO_PORTJ_AHB_MIS_R & 0x03);                                           /*  PortJ => IC: Interrupt Clear -> Interrupt cleared */

    /*  Retardo de rebote */
    SysTick_Init_OneShot (Bounce_Delay);                                                            /*  Inicialización y configuración del SysTick en modo one-shot */
    while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT)) {}                                               /*  SysTick => COUNT: Count Flag -> The SysTick timer has counted to 0 */

    /*  Confirmar qué botón se presionó */
    if (!(GPIO_PORTJ_AHB_DATA_R & 0x01)) {                                                          /*  IF (SW1 -> on) */
        pot_select = 0;
    }

    if (!(GPIO_PORTJ_AHB_DATA_R & 0x02)) {                                                          /*  IF (SW2 -> on) */
        pot_select = 1;
    }

}
