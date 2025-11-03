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
#define NVIC_EN1_R                  (*((volatile uint32_t *)0xE000E104))                            /*  pp154   Interrupt 32-63 Set Enable */
#define NVIC_PRI12_R                (*((volatile uint32_t *)0xE000E430))                            /*  pp159   Interrupt 48-51 Priority */


/**************************************************************************************************
 * Prototipos de funciones
 */

void GPIO_PortJ_Handler(void);                                                                      /*  Rutina de servicio de interrupción (ISR) del GPIO PortJ */


#endif                                                                                              /*  NVIC_H */
