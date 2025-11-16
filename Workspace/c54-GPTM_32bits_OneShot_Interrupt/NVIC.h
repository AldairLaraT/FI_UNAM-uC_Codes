/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          11 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 54:      Módulo temporizador de propósito general (GPTM): 32bits, one-shot, interrupción
 *  Descripción:    Código en lenguaje C que utiliza el temporizador TIMER0A en configuración
 *                  concatenada (32 bits) y modo one-shot, empleando interrupción por time-out,
 *                  para generar un retardo al presionar un botón (SW1) y conmutar el LED de
 *                  usuario (D1) de la tarjeta de desarrollo.
 * 
 *  Archivo:        Archivo de cabecera del módulo NVIC
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef NVIC_H                                                                                      /*  Verificar si NVIC_H no ha sido definido previamente */
#define NVIC_H                                                                                      /*  Definir NVIC_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 *  Definiciones y macros
 *  Nested Vectored Interrupt Controller (NVIC) registers                                               pp.146      Register map
 */
#define NVIC_EN0_R                  (*((volatile uint32_t *)0xE000E100))                            /*  pp.154      Interrupt 0-31 Set Enable */
#define NVIC_EN1_R                  (*((volatile uint32_t *)0xE000E104))                            /*  pp.154      Interrupt 32-63 Set Enable */
#define NVIC_PRI4_R                 (*((volatile uint32_t *)0xE000E410))                            /*  pp.159      Interrupt 16-19 Priority */
#define NVIC_PRI5_R                 (*((volatile uint32_t *)0xE000E414))                            /*  pp.159      Interrupt 20-23 Priority */
#define NVIC_PRI12_R                (*((volatile uint32_t *)0xE000E430))                            /*  pp.159      Interrupt 48-51 Priority */


/**************************************************************************************************
 *  Prototipos de funciones
 */

void TIMER0A_Handler(void);                                                                         /*  Rutina de servicio de interrupción (ISR) del TIMER 0A */
void GPIO_PortJ_Handler(void);                                                                      /*  Rutina de servicio de interrupción (ISR) del GPIO PortJ */


#endif                                                                                              /*  NVIC_H */
