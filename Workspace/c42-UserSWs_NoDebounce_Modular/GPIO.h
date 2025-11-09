/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          01 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 42:      Control de un LED con un SW de usuario sin debounce (modular)
 *  Descripción:    Código en lenguaje C que conmuta el LED D1 de la tarjeta de desarrollo,
 *                  dependiendo del botón SW1, sin considerar el efecto rebote.
 * 
 *  Archivo:        Archivo de cabecera del módulo GPIO
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef GPIO_H                                                                                      /*  Verificar si GPIO_H no ha sido definido previamente */
#define GPIO_H                                                                                      /*  Definir GPIO_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 *  Definiciones y macros
 *  General-Purpose Input/Output (GPIO) registers                                                       pp.757      Register map
 */
    /** GPIO Port J (PortJ) */
#define GPIO_PORTJ_AHB_DATA_R       (*((volatile uint32_t *)0x40060004))                            /*  pp.759      GPIO Data >> PortJ[0] unmasked */
#define GPIO_PORTJ_AHB_DIR_R        (*((volatile uint32_t *)0x40060400))                            /*  pp.760      GPIO Direction */
#define GPIO_PORTJ_AHB_PUR_R        (*((volatile uint32_t *)0x40060510))                            /*  pp.776      GPIO Pull-Up Select */
#define GPIO_PORTJ_AHB_DEN_R        (*((volatile uint32_t *)0x4006051C))                            /*  pp.781      GPIO Digital Enable */
    /** GPIO Port N (PortN) */
#define GPIO_PORTN_DATA_R           (*((volatile uint32_t *)0x40064008))                            /*  pp.759      GPIO Data >> PortN[1] unmasked */
#define GPIO_PORTN_DIR_R            (*((volatile uint32_t *)0x40064400))                            /*  pp.760      GPIO Direction */
#define GPIO_PORTN_DEN_R            (*((volatile uint32_t *)0x4006451C))                            /*  pp.781      GPIO Digital Enable */


/**************************************************************************************************
 *  Prototipos de funciones
 */

void GPIO_PortJ_Init();                                                                             /*  Inicialización y configuración del puerto GPIO J */
void GPIO_PortN_Init();                                                                             /*  Inicialización y configuración del puerto GPIO N */


#endif                                                                                              /*  GPIO_H */
