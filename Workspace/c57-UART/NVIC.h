/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          23 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 57:      Universal Asynchronous Receiver/Transmitter (UART)
 *  Descripción:    Código en lenguaje C que utiliza el módulo UART0 (PA[1,0]) con baud rate de
 *                  115200, sin bit de paridad y un bit de parada, para enviar (con SW2) un
 *                  caracter en formato ASCII (ajustable con SW1) y recibir comandos por
 *                  interrupción para el control de los LED de usuario de la tarjeta de desarrollo.
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
#define NVIC_PRI1_R                 (*((volatile uint32_t *)0xE000E404))                            /*  pp.159      Interrupt 4-7 Priority */
#define NVIC_PRI12_R                (*((volatile uint32_t *)0xE000E430))                            /*  pp.159      Interrupt 48-51 Priority */


/**************************************************************************************************
 *  Prototipos de funciones
 */

void UART0_Handler(void);                                                                           /*  Rutina de servicio de interrupción (ISR) del UART0 */
void GPIO_PortJ_Handler(void);                                                                      /*  Rutina de servicio de interrupción (ISR) del GPIO PortJ */


#endif                                                                                              /*  NVIC_H */
