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
 *  Archivo:        Archivo fuente del módulo GPIO
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */


/**************************************************************************************************
 *  Variables externas (parámetros)
 */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        GPIO_PortF_Init
 * 
 *  Descripción:    Inicialización y configuración del puerto GPIO F.
 */

void GPIO_PortF_Init(void) {

    /** 1.  Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x0020;                                                                    /*  R5: GPIO PortF Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x0020)) {}                                                          /*  R5: GPIO PortF Peripheral Ready -> GPIO PortF is ready for access */

    /** 2.  Configurar la dirección de los pines del puerto GPIO. */
    GPIO_PORTF_AHB_DIR_R |= 0x11;                                                                   /*  PortF[4,0] => DIR: GPIO Data direction -> Output */

    /** 3.  Deshabilitar las funciones alternas de hardware de los pines de los puertos GPIO. */

    /** 4.  Configurar los modos de controlador extendidos. */

    /** 5.  Configurar el driver de 4mA de los pines del puerto GPIO. */

    /** 6.  Configurar el driver de 8mA de los pines del puerto GPIO. */

    /** 7.  Configurar el driver de 12mA de los pines del puerto GPIO. */

    /** 8.  Configurar como open drain y las resistencias de pull-up / pull-down. */

    /** 9.  Habilitar las funciones digitales de los pines del puerto GPIO. */
    GPIO_PORTF_AHB_DEN_R |= 0x11;                                                                   /*  PortF[4,0] => DEN: Digital Enable -> Enabled */

    /** 10. Si se utiliza interrupción, configurar la sensibilidad y el tipo de evento. Además de
     *      desenmascarar la interrupción local. */

}

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
    GPIO_PORTJ_AHB_DIR_R &= ~0x03;                                                                  /*  PortJ[1,0] => DIR: GPIO Data direction -> Input */

    /** 3.  Deshabilitar las funciones alternas de hardware de los pines de los puertos GPIO. */

    /** 4.  Configurar los modos de controlador extendidos. */

    /** 5.  Configurar el driver de 4mA de los pines del puerto GPIO. */

    /** 6.  Configurar el driver de 8mA de los pines del puerto GPIO. */

    /** 7.  Configurar el driver de 12mA de los pines del puerto GPIO. */

    /** 8.  Configurar como open drain y las resistencias de pull-up / pull-down. */
    GPIO_PORTJ_AHB_PUR_R |= 0x03;                                                                   /*  PortJ[1,0] => PUE: Pad Weak Pull-Up Enable -> Enabled */

    /** 9.  Habilitar las funciones digitales de los pines del puerto GPIO. */
    GPIO_PORTJ_AHB_DEN_R |= 0x03;                                                                   /*  PortJ[1,0] => DEN: Digital Enable -> Enabled */

    /** 10. Si se utiliza interrupción, configurar la sensibilidad y el tipo de evento. Además de
     *      desenmascarar la interrupción local. */
    GPIO_PORTJ_AHB_IS_R &= ~0x03;                                                                   /*  PortJ[1,0] => IS: Interrupt Sense -> Edge-sensitive */
    GPIO_PORTJ_AHB_IBE_R &= ~0x03;                                                                  /*  PortJ[1,0] => IBE: Interrupt Both Edges -> Controlled by GPIO_IEV */
    GPIO_PORTJ_AHB_IEV_R &= ~0x03;                                                                  /*  PortJ[1,0] => IEV: Interrupt Event -> Falling edge */

    /** Limpiar la bandera de interrupción. */
    GPIO_PORTJ_AHB_ICR_R |= 0x03;                                                                   /*  PortJ[1,0] => IC: Interrupt Clear -> Interrupt cleared */

    /********************************************
     *  Interrupción
     */

    /** Desenmascarar la interrupción local. */
    GPIO_PORTJ_AHB_IM_R |= 0x03;                                                                    /*  PortJ[1,0] => IME: Interrupt Mask Enable -> Interrupt unmasked */

    /** Establecer el nivel de prioridad de la IRQ. */
    NVIC_PRI12_R = ((NVIC_PRI12_R & ~0xE0000000) | (0 << 29));                                      /*  IRQ_51 (PortJ) => INTD: Interrupt Priority -> Cleared and set 0 (highest) */

    /** Habilitación de la IRQ en el NVIC. */
    NVIC_EN1_R |= (1 << (51 - 32));                                                                 /*  IRQ_51 (PortJ) => INT: Interrupt Enable -> Enabled */

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
    GPIO_PORTN_DIR_R |= 0x03;                                                                       /*  PortN[1,0] => DIR: GPIO Data direction -> Output */

    /** 3.  Deshabilitar las funciones alternas de hardware de los pines de los puertos GPIO. */

    /** 4.  Configurar los modos de controlador extendidos. */

    /** 5.  Configurar el driver de 4mA de los pines del puerto GPIO. */

    /** 6.  Configurar el driver de 8mA de los pines del puerto GPIO. */

    /** 7.  Configurar el driver de 12mA de los pines del puerto GPIO. */

    /** 8.  Configurar como open drain y las resistencias de pull-up / pull-down. */

    /** 9.  Habilitar las funciones digitales de los pines del puerto GPIO. */
    GPIO_PORTN_DEN_R |= 0x03;                                                                       /*  PortN[1,0] => DEN: Digital Enable -> Enabled */

    /** 10. Si se utiliza interrupción, configurar la sensibilidad y el tipo de evento. Además de
     *      desenmascarar la interrupción local. */

}
