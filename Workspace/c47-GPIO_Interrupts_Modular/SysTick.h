/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       01 de noviembre de 2025
 * 
 * Tema 09:     Periféricos
 * Código 47:   Control de un contador con los SW de usuario, empleando interrupciones (modular)
 * Descripción: Código en lenguaje C que actualiza el valor de un contador, dependiendo del botón
 *              que se presiona (SW1 y SW2 de la tarjeta de desarrollo), ejecutando una tarea
 *              distinta en el código principal (conmutación de los LED de usuario).
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
