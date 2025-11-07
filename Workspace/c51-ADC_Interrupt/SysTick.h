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
 * Archivo:     Archivo de cabecera del módulo SysTick
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef SysTick_H                                                                                   /*  Verificar si SysTick_H no ha sido definido previamente */
#define SysTick_H                                                                                   /*  Definir SysTick_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 * Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 * Definiciones y macros
 * System Timer (SysTick) registers                                                                     pp146   Register map
 */
#define NVIC_ST_CTRL_R              (*((volatile uint32_t *)0xE000E010))                            /*  pp150   SysTick Control and Status */
#define NVIC_ST_RELOAD_R            (*((volatile uint32_t *)0xE000E014))                            /*  pp152   SysTick Reload Value */
#define NVIC_ST_CURRENT_R           (*((volatile uint32_t *)0xE000E018))                            /*  pp153   SysTick Current Value */

/************************************************
 * Bit fields
 */
    //  Bit fields in the NVIC_ST_CTRL register                                                         pp150
#define NVIC_ST_CTRL_COUNT          0x00010000                                                      /*  Count Flag */


/**************************************************************************************************
 * Prototipos de funciones
 */

void SysTick_Init_OneShot(uint32_t SysTick_Reload);                                                 /*  Inicialización y configuración del SysTick en modo one-shot */


#endif                                                                                              /*  SysTick_H */
