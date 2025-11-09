/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          04 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 48:      Convertidor analógico digital (ADC)
 *  Descripción:    Código en lenguaje C que configura el módulo ADC_0, empleando el secuenciador
 *                  de muestras SS_3 para leer el valor de un potenciómetro conectado en la entrada
 *                  analógica AIN_10 (PB4) y usar los LED de usuario de la tarjeta de desarrollo
 *                  como indicador del nivel de voltaje.
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
