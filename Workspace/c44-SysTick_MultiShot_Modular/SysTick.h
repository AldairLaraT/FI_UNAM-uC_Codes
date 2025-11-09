/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          01 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 44:      SysTick en modo multi-shot (modular)
 *  Descripción:    Código en lenguaje C que conmuta el LED D1 de la tarjeta de desarrollo con una
 *                  frecuencia de 1Hz, empleando el SysTick en modo multi-shot.
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

void SysTick_Init(uint32_t SysTick_Reload);                                                         /*  Inicialización y configuración del SysTick */


#endif                                                                                              /*  SysTick_H */
