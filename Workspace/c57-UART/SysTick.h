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
 *  Archivo:        Archivo de cabecera del módulo SysTick
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef SysTick_H                                                                                   /*  Verificar si SysTick_H no ha sido definido previamente */
#define SysTick_H                                                                                   /*  Definir SysTick_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 *  Definiciones y macros
 *  System Timer (SysTick) registers                                                                    pp.146      Register map
 */
#define NVIC_ST_CTRL_R              (*((volatile uint32_t *)0xE000E010))                            /*  pp.150      SysTick Control and Status */
#define NVIC_ST_RELOAD_R            (*((volatile uint32_t *)0xE000E014))                            /*  pp.152      SysTick Reload Value */
#define NVIC_ST_CURRENT_R           (*((volatile uint32_t *)0xE000E018))                            /*  pp.153      SysTick Current Value */

/************************************************
 *  Bit fields
 */
    //  Bit fields in the NVIC_ST_CTRL register                                                         pp.150
#define NVIC_ST_CTRL_COUNT          0x00010000                                                      /*  Count Flag */


/**************************************************************************************************
 *  Prototipos de funciones
 */

void SysTick_Init_OneShot(uint32_t SysTick_Reload);                                                 /*  Inicialización y configuración del SysTick en modo one-shot */


#endif                                                                                              /*  SysTick_H */
