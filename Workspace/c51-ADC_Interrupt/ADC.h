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
 * Archivo:     Archivo de cabecera del módulo ADC
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef ADC_H                                                                                       /*  Verificar si ADC_H no ha sido definido previamente */
#define ADC_H                                                                                       /*  Definir ADC_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 * Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 * Definiciones y macros
 * Analog-to-Digital Converter (ADC) registers                                                          pp1073  Register map
 */
    /*  ADC module 0 (ADC0) */
#define ADC0_ACTSS_R                (*((volatile uint32_t *)0x40038000))                            /*  pp1077  ADC Active Sample Sequencer */
#define ADC0_IM_R                   (*((volatile uint32_t *)0x40038008))                            /*  pp1082  ADC Interrupt Mask */
#define ADC0_ISC_R                  (*((volatile uint32_t *)0x4003800C))                            /*  pp1085  ADC Interrupt Status and Clear */
#define ADC0_EMUX_R                 (*((volatile uint32_t *)0x40038014))                            /*  pp1091  ADC Event Multiplexer Select */
#define ADC0_PSSI_R                 (*((volatile uint32_t *)0x40038028))                            /*  pp1103  ADC Processor Sample Sequence Initiate */
#define ADC0_SSMUX1_R               (*((volatile uint32_t *)0x40038060))                            /*  pp1129  ADC Sample Sequence Input Multiplexer 1 */
#define ADC0_SSCTL1_R               (*((volatile uint32_t *)0x40038064))                            /*  pp1130  ADC Sample SequenceM Control 1 */
#define ADC0_SSFIFO1_R              (*((volatile uint32_t *)0x40038068))                            /*  pp1118  ADC Sample Sequence Result FIFO 1 */
#define ADC0_SSEMUX1_R              (*((volatile uint32_t *)0x40038078))                            /*  pp1137  ADC Sample Sequence Extended Input Multiplexer Select 1 */
#define ADC0_CC_R                   (*((volatile uint32_t *)0x40038FC8))                            /*  pp1160  ADC Clock Configuration */


/**************************************************************************************************
 * Prototipos de funciones
 */

void ADC0_SS1_Init();                                                                               /*  Inicialización y configuración del ADC_0, SS_1 */


#endif                                                                                              /*  ADC_H */
