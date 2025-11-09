/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          15 de octubre de 2025
 * 
 *  Tema 08:        Lenguaje C
 *  Código 32:      Control de los LED de usuario
 *  Descripción:    Código en lenguaje C que enciende y apaga los LED D1 y D2 de la tarjeta de
 *                  desarrollo.
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 *  Definiciones y macros
 */

/************************************************
 *  System Control (SYSCTL) registers                                                                   pp.247      Register map
 */
#define SYSCTL_RCGCGPIO_R           (*((volatile uint32_t *)0x400FE608))                            /*  pp.382      GPIO Run Mode Clock Gating Control */
#define SYSCTL_PRGPIO_R             (*((volatile uint32_t *)0x400FEA08))                            /*  pp.499      GPIO Peripheral Ready */

/************************************************
 *  General-Purpose Input/Output (GPIO) registers                                                       pp.757      Register map
 */
    /** GPIO Port N (PortN) */
#define GPIO_PORTN_DATA_R           (*((volatile uint32_t *)0x4006400C))                            /*  pp.759      GPIO Data >> PortN[1,0] unmasked */
#define GPIO_PORTN_DIR_R            (*((volatile uint32_t *)0x40064400))                            /*  pp.760      GPIO Direction */
#define GPIO_PORTN_DEN_R            (*((volatile uint32_t *)0x4006451C))                            /*  pp.781      GPIO Digital Enable */


/**************************************************************************************************
 *  Funciones
 */

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
    GPIO_PORTN_DIR_R |= 0x03;                                                                       /*  PortN[1,0] => DIR: GPIO Data direction -> Output */

    /** 3.  Habilitar las funciones digitales de los pines del puerto GPIO. */
    GPIO_PORTN_DEN_R |= 0x03;                                                                       /*  PortN[1,0] => DEN: Digital Enable -> Enabled */

}


/**************************************************************************************************
 *  Función principal
 */

int main(void) {

    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */

    while (1) {

        GPIO_PORTN_DATA_R ^= 0x02;                                                                  /*  LED D1 -> toggle */
        GPIO_PORTN_DATA_R ^= 0x01;                                                                  /*  LED D2 -> toggle */
    }
}
