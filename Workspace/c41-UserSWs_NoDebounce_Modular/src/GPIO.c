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
 *  Archivo:        Archivo fuente del módulo GPIO
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */


/**************************************************************************************************
 *  Variables externas (parámetros)
 */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        GPIO_PortJ_Init
 * 
 *  Descripción:    Inicialización y configuración del puerto GPIO J.
 */

void GPIO_PortJ_Init(void) {

    /** 1.  Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x0100;                                                                    /*  R8: GPIO PortJ Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x0100)) {}                                                          /*  R8: GPIO PortJ Peripheral Ready -> GPIO PortJ is ready for access */

    /** 2.  Configurar la dirección de los pines del puerto GPIO. */
    GPIO_PORTJ_AHB_DIR_R &= ~0x01;                                                                  /*  PortJ[0] => DIR: GPIO Data direction -> Input */

    /** 3.  Habilitar las resistencias de pull-up de los pines del puerto GPIO. */
    GPIO_PORTJ_AHB_PUR_R |= 0x01;                                                                   /*  PortJ[0] => PUE: Pad Weak Pull-Up Enable -> Enabled */

    /** 4.  Habilitar las funciones digitales de los pines del puerto GPIO. */
    GPIO_PORTJ_AHB_DEN_R |= 0x01;                                                                   /*  PortJ[0] => DEN: Digital Enable -> Enabled */

}

/************************************************
 *  Función:        GPIO_PortN_Init
 * 
 *  Descripción:    Inicialización y configuración del puerto GPIO N.
 */

void GPIO_PortN_Init(void) {

    /** 1.  Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x1000;                                                                    /*  R12: GPIO PortN Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x1000)) {}                                                          /*  R12: GPIO PortN Peripheral Ready -> GPIO PortN is ready for access */

    /** 2.  Configurar la dirección de los pines del puerto GPIO. */
    GPIO_PORTN_DIR_R |= 0x02;                                                                       /*  PortN[1] => DIR: GPIO Data direction -> Output */

    /** 3.  Habilitar las funciones digitales de los pines del puerto GPIO. */
    GPIO_PORTN_DEN_R |= 0x02;                                                                       /*  PortN[1] => DEN: Digital Enable -> Enabled */

}
