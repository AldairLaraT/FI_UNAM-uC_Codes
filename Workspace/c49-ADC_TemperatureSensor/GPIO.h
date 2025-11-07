/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       04 de noviembre de 2025
 * 
 * Tema 09:     Periféricos
 * Código 49:   Convertidor analógico digital (ADC): Sensor de temperatura embebido
 * Descripción: Código en lenguaje C que configura el módulo ADC_0, empleando el secuenciador de
 *              muestras SS_3 para leer el valor del sensor de temperatura embebido en el
 *              microcontrolador y usar los LED de usuario de la tarjeta de desarrollo como
 *              indicador de la temperatura.
 * 
 * Archivo:     Archivo de cabecera del módulo GPIO
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef GPIO_H                                                                                      /*  Verificar si GPIO_H no ha sido definido previamente */
#define GPIO_H                                                                                      /*  Definir GPIO_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 * Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 * Definiciones y macros
 * General-Purpose Input/Output (GPIO) registers                                                        pp757   Register map
 */
    /*  GPIO Port F (PortF) */
#define GPIO_PORTF_AHB_DATA_R       (*((volatile uint32_t *)0x4005D044))                            /*  pp759   GPIO Data >> PortF[4,0] unmasked */
#define GPIO_PORTF_AHB_DIR_R        (*((volatile uint32_t *)0x4005D400))                            /*  pp760   GPIO Direction */
#define GPIO_PORTF_AHB_DEN_R        (*((volatile uint32_t *)0x4005D51C))                            /*  pp781   GPIO Digital Enable */
    /*  GPIO Port N (PortN) */
#define GPIO_PORTN_DATA_R           (*((volatile uint32_t *)0x4006400C))                            /*  pp759   GPIO Data >> PortN[1,0] unmasked */
#define GPIO_PORTN_DIR_R            (*((volatile uint32_t *)0x40064400))                            /*  pp760   GPIO Direction */
#define GPIO_PORTN_DEN_R            (*((volatile uint32_t *)0x4006451C))                            /*  pp781   GPIO Digital Enable */


/**************************************************************************************************
 * Prototipos de funciones
 */

void GPIO_PortF_Init();                                                                             /*  Inicialización y configuración del puerto GPIO F */
void GPIO_PortN_Init();                                                                             /*  Inicialización y configuración del puerto GPIO N */


#endif                                                                                              /*  GPIO_H */
