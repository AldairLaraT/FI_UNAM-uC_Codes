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
 * Archivo:     Archivo de cabecera del módulo NVIC
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef NVIC_H                                                                                      /*  Verificar si NVIC_H no ha sido definido previamente */
#define NVIC_H                                                                                      /*  Definir NVIC_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 * Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 * Definiciones y macros
 * Nested Vectored Interrupt Controller (NVIC) registers                                                pp146   Register map
 */
#define NVIC_EN0_R                  (*((volatile uint32_t *)0xE000E100))                            /*  pp154   Interrupt 0-31 Set Enable */
#define NVIC_EN1_R                  (*((volatile uint32_t *)0xE000E104))                            /*  pp154   Interrupt 32-63 Set Enable */
#define NVIC_PRI3_R                 (*((volatile uint32_t *)0xE000E40C))                            /*  pp159   Interrupt 12-15 Priority */
#define NVIC_PRI12_R                (*((volatile uint32_t *)0xE000E430))                            /*  pp159   Interrupt 48-51 Priority */


/**************************************************************************************************
 * Prototipos de funciones
 */

void ADC0_SS1_Handler(void);                                                                        /*  Rutina de servicio de interrupción (ISR) del ADC0 SS1 */
void GPIO_PortJ_Handler(void);                                                                      /*  Rutina de servicio de interrupción (ISR) del GPIO PortJ */


#endif                                                                                              /*  NVIC_H */
