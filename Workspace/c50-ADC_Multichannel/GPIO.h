/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          06 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 50:      Convertidor analógico digital (ADC): Multicanal
 *  Descripción:    Código en lenguaje C que configura el módulo ADC_0, empleando el secuenciador
 *                  de muestras SS_1 para leer el valor de dos potenciómetros conectados en las
 *                  entradas analógicas AIN_10 (PB4) y AIN_17 (PK1), usando los LED de usuario de
 *                  la tarjeta de desarrollo como indicador del nivel de voltaje de un
 *                  potenciómetro, dependiendo del último botón (SW1 o SW2) presionado.
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
    /** GPIO Port B (PortB) */
#define GPIO_PORTB_AHB_AFSEL_R      (*((volatile uint32_t *)0x40059420))                            /*  pp.770      GPIO Alternate Function Select */
#define GPIO_PORTB_AHB_DEN_R        (*((volatile uint32_t *)0x4005951C))                            /*  pp.781      GPIO Digital Enable */
#define GPIO_PORTB_AHB_AMSEL_R      (*((volatile uint32_t *)0x40059528))                            /*  pp.786      GPIO Analog Mode Select */
    /** GPIO Port F (PortF) */
#define GPIO_PORTF_AHB_DATA_R       (*((volatile uint32_t *)0x4005D044))                            /*  pp.759      GPIO Data >> PortF[4,0] unmasked */
#define GPIO_PORTF_AHB_DIR_R        (*((volatile uint32_t *)0x4005D400))                            /*  pp.760      GPIO Direction */
#define GPIO_PORTF_AHB_DEN_R        (*((volatile uint32_t *)0x4005D51C))                            /*  pp.781      GPIO Digital Enable */
    /** GPIO Port J (PortJ) */
#define GPIO_PORTJ_AHB_DATA_R       (*((volatile uint32_t *)0x4006000C))                            /*  pp.759      GPIO Data >> PortJ[1,0] unmasked */
#define GPIO_PORTJ_AHB_DIR_R        (*((volatile uint32_t *)0x40060400))                            /*  pp.760      GPIO Direction */
#define GPIO_PORTJ_AHB_IS_R         (*((volatile uint32_t *)0x40060404))                            /*  pp.761      GPIO Interrupt Sense */
#define GPIO_PORTJ_AHB_IBE_R        (*((volatile uint32_t *)0x40060408))                            /*  pp.762      GPIO Interrupt Both Edges */
#define GPIO_PORTJ_AHB_IEV_R        (*((volatile uint32_t *)0x4006040C))                            /*  pp.763      GPIO Interrupt Event */
#define GPIO_PORTJ_AHB_IM_R         (*((volatile uint32_t *)0x40060410))                            /*  pp.764      GPIO Interrupt Mask */
#define GPIO_PORTJ_AHB_MIS_R        (*((volatile uint32_t *)0x40060418))                            /*  pp.767      GPIO Masked Interrupt Status */
#define GPIO_PORTJ_AHB_ICR_R        (*((volatile uint32_t *)0x4006041C))                            /*  pp.769      GPIO Interrupt Clear */
#define GPIO_PORTJ_AHB_PUR_R        (*((volatile uint32_t *)0x40060510))                            /*  pp.776      GPIO Pull-Up Select */
#define GPIO_PORTJ_AHB_DEN_R        (*((volatile uint32_t *)0x4006051C))                            /*  pp.781      GPIO Digital Enable */
    /** GPIO Port K (PortK) */
#define GPIO_PORTK_AFSEL_R          (*((volatile uint32_t *)0x40061420))                            /*  pp.770      GPIO Alternate Function Select */
#define GPIO_PORTK_DEN_R            (*((volatile uint32_t *)0x4006151C))                            /*  pp.781      GPIO Digital Enable */
#define GPIO_PORTK_AMSEL_R          (*((volatile uint32_t *)0x40061528))                            /*  pp.786      GPIO Analog Mode Select */
    /** GPIO Port N (PortN) */
#define GPIO_PORTN_DATA_R           (*((volatile uint32_t *)0x4006400C))                            /*  pp.759      GPIO Data >> PortN[1,0] unmasked */
#define GPIO_PORTN_DIR_R            (*((volatile uint32_t *)0x40064400))                            /*  pp.760      GPIO Direction */
#define GPIO_PORTN_DEN_R            (*((volatile uint32_t *)0x4006451C))                            /*  pp.781      GPIO Digital Enable */


/**************************************************************************************************
 *  Prototipos de funciones
 */

void GPIO_PortF_Init();                                                                             /*  Inicialización y configuración del puerto GPIO F */
void GPIO_PortJ_Init();                                                                             /*  Inicialización y configuración del puerto GPIO J */
void GPIO_PortN_Init();                                                                             /*  Inicialización y configuración del puerto GPIO N */


#endif                                                                                              /*  GPIO_H */
