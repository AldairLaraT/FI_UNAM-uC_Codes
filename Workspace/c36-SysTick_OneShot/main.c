/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          15 de octubre de 2025
 * 
 *  Tema 08:        Lenguaje C
 *  Código 37:      SysTick en modo one-shot
 *  Descripción:    Código en lenguaje C que conmuta el LED D1 de la tarjeta de desarrollo con una
 *                  frecuencia de 1Hz, empleando el SysTick en modo one-shot.
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
 *  System Timer (SysTick) registers                                                                    pp.146      Register map
 */
#define NVIC_ST_CTRL_R              (*((volatile uint32_t *)0xE000E010))                            /*  pp.150      SysTick Control and Status */
#define NVIC_ST_RELOAD_R            (*((volatile uint32_t *)0xE000E014))                            /*  pp.152      SysTick Reload Value */
#define NVIC_ST_CURRENT_R           (*((volatile uint32_t *)0xE000E018))                            /*  pp.153      SysTick Current Value */

/************************************************
 *  System Control (SYSCTL) registers                                                                   pp.247      Register map
 */
#define SYSCTL_RCGCGPIO_R           (*((volatile uint32_t *)0x400FE608))                            /*  pp.382      GPIO Run Mode Clock Gating Control */
#define SYSCTL_PRGPIO_R             (*((volatile uint32_t *)0x400FEA08))                            /*  pp.499      GPIO Peripheral Ready */

/************************************************
 *  General-Purpose Input/Output (GPIO) registers                                                       pp.757      Register map
 */
    /** GPIO Port N (PortN) */
#define GPIO_PORTN_DATA_R           (*((volatile uint32_t *)0x40064008))                            /*  pp.759      GPIO Data >> PortN[1] unmasked */
#define GPIO_PORTN_DIR_R            (*((volatile uint32_t *)0x40064400))                            /*  pp.760      GPIO Direction */
#define GPIO_PORTN_DEN_R            (*((volatile uint32_t *)0x4006451C))                            /*  pp.781      GPIO Digital Enable */

/************************************************
 *  Bit fields
 */
    // Bit fields in the NVIC_ST_CTRL register                                                          pp.150
#define NVIC_ST_CTRL_COUNT          0x00010000                                                      /*  Count Flag */


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
    GPIO_PORTN_DIR_R |= 0x02;                                                                       /*  PortN[1] => DIR: GPIO Data direction -> Output */

    /** 3.  Habilitar las funciones digitales de los pines del puerto GPIO. */
    GPIO_PORTN_DEN_R |= 0x02;                                                                       /*  PortN[1] => DEN: Digital Enable -> Enabled */

}

/************************************************
 *  Función:        SysTick_Init_OneShot
 * 
 *  Descripción:    Inicialización y configuración del SysTick en modo one-shot.
 * 
 *  Parámetros:
 *      SysTick_Reload  : Valor de carga/inicio del SysTick (ST_RELOAD)
 */

void SysTick_Init_OneShot(uint32_t SysTick_Reload) {

    /** 1.  Cargar el valor de cuenta del SysTick. */
    NVIC_ST_RELOAD_R = (SysTick_Reload & 0x00FFFFFF);                                               /*  RELOAD: Reload Value */

    /** 2.  Limpiar el valor de cuenta actual del SysTick. */
    NVIC_ST_CURRENT_R = 0;                                                                          /*  CURRENT: Current Value -> Cleared */

    /** 3.  Configurar el SysTick para la operación requerida. */
    NVIC_ST_CTRL_R |= 0x01;                                                                         /*  Enables SysTick to operate in a multi-shot way (PIOSC divided by 4) */
    // NVIC_ST_CTRL_R |= 0x05;                                                                         /*  Enables SysTick to operate in a multi-shot way (System clock) */

    /** Limpiar el valor de carga/inicio del SysTick para deshabilitar el contador en el siguiente ciclo. */
    NVIC_ST_RELOAD_R = 0;                                                                           /*  RELOAD: Reload Value -> Cleared */

}


/**************************************************************************************************
 *  Función principal
 */

int main(void) {

    uint32_t Delay = 4000000;                                                                       /*  Valor de carga del SysTick para un retardo de 1s (f = 4MHz) */

    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */
    SysTick_Init_OneShot (Delay);                                                                   /*  Inicialización y configuración del SysTick en modo one-shot */

    while (1) {

        /** Esperar a que termine la cuenta del SysTick. */
        while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT)) {}                                           /*  SysTick => COUNT: Count Flag -> The SysTick timer has counted to 0 */

        GPIO_PORTN_DATA_R ^= 0x02;                                                                  /*  LED D1 -> toggle */
        SysTick_Init_OneShot (Delay);                                                               /*  Inicialización y configuración del SysTick en modo one-shot */
    }
}
