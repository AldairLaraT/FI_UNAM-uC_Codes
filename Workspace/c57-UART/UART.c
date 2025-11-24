/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          23 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 57:      Universal Asynchronous Receiver/Transmitter (UART)
 *  Descripción:    Código en lenguaje C que utiliza el módulo UART0 (PA[1,0]) con baud rate de
 *                  115200, sin bit de paridad y un bit de parada, para enviar (con SW2) un
 *                  caracter en formato ASCII (ajustable con SW1) y recibir comandos por
 *                  interrupción para el control de los LED de usuario de la tarjeta de desarrollo.
 * 
 *  Archivo:        Archivo fuente del módulo UART
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "UART.h"                                                                                   /*  Archivo de cabecera del módulo UART */


/**************************************************************************************************
 *  Variables externas (parámetros)
 */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        UART0_Init
 * 
 *  Descripción:    Inicialización y configuración del UART0.
 */

void UART0_Init(void) {

    /********************************************
     *  Habilitación
     */

    /** 1.  Habilitar la señal de reloj del UART y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCUART_R |= 0x01;                                                                      /*  R0: UART0 Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRUART_R & 0x01)) {}                                                            /*  R0: UART0 Peripheral Ready -> UART0 is ready for access */

    /** 2.  Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x0001;                                                                    /*  R0: GPIO PortA Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x0001)) {}                                                          /*  R0: GPIO PortA Peripheral Ready -> GPIO PortA is ready for access */

    /** 3.  Habilitar las funciones alternas de hardware de los pines de los puertos GPIO. */
    GPIO_PORTA_AHB_AFSEL_R |= 0x03;                                                                 /*  PortA[1:0] => AFSEL: Alternate Function Select -> Alternate hardware function */

    /** 4.  Configurar el nivel de corriente y/o el slew rate de los pines de los puertos GPIO. */

    /** 5.  Seleccionar las funciones alternas de hardware de los pines del puerto GPIO. */
    GPIO_PORTA_AHB_PCTL_R = (GPIO_PORTA_AHB_PCTL_R & ~0x000000FF) | (1 << 4) | (1 << 0);            /*  PortA[1:0] => PMC1/0: Port Mux Control 1/0 -> UART0_Rx/UART0_Tx */

    /** 6.  Habilitar las funciones digitales de los pines de los puertos GPIO. */
    GPIO_PORTA_AHB_DEN_R |= 0x03;                                                                   /*  PortA[1:0] => DEN: Digital Enable -> Enabled */

    /**     Si se utiliza interrupción, configurar el nivel de la FIFO de recepción y desenmascarar
     *      la interrupción local. */

    /********************************************
     *  Configuración
     */

    /** 1.  Deshabilitar el UART. */
    UART0_CTL_R &= ~0x01;                                                                           /*  UART0 => UARTEN: UART Enable -> Disabled */

    /** 2.  Cargar la parte entera del baud rate divisor. */
    UART0_IBRD_R = 8;                                                                               /*  UART0 => DIVINT: Integer Baud-Rate Divisor */

    /** 3.  Cargar la parte decimal del baud rate divisor. */
    UART0_FBRD_R = 44;                                                                              /*  UART0 => DIVFRAC: Fractional Baud-Rate Divisor */

    /** 4.  Configurar la trama de datos. */
    UART0_LCRH_R = (UART0_LCRH_R & ~0xFF) | (0x3 << 5) | (1 << 4);
        /** (UART0_LCRH_R & ~0xFF)      ->  Máscara para limpiar los campos de configuración.
         *      SPS  = 0    ->  UART0 => SPS: UART Stick Parity Select -> Stick parity is disabled
         *      WLEN = 0x3  ->  UART0 => WLEN: UART Word Length -> 8 bits
         *      FEN  = 1    ->  UART0 => FEN: UART Enable FIFOs -> The transmit and receive FIFO buffers are enabled (FIFO mode)
         *      STP2 = 0    ->  UART0 => STP2: UART Two Stop Bits Select -> One stop bit is transmitted at the end of a frame
         *      EPS  = 0    ->  UART0 => EPS: Even Parity Select -> Odd parity is performed, which checks for an odd number of 1s
         *      PEN  = 0    ->  UART0 => PEN: UART Parity Enable -> Parity is disabled and no parity bit is added to the data frame
         *      BRK  = 0    ->  UART0 => BRK: UART Send Break -> Normal use
         */

    /** 5.  Configurar la fuente de reloj del UART. */
    UART0_CC_R = 0x5;                                                                               /*  UART0 => CS: UART Baud Clock Source -> Alternate clock source as defined by ALTCLKCFG (default: PIOSC) */

    /** 6.  De manera opcional, configurar el canal uDMA y habilitar las funciones del DMA. */

    /********************************************
     *  Interrupción
     */

    /** Configurar el nivel de la FIFO de recepción. */
    UART0_IFLS_R = (UART0_IFLS_R & ~(0x7 << 3)) | (0x0 << 3);                                       /*  UART0 => RXIFLSEL: UART Receive Interrupt FIFO Level Select -> RX FIFO >= 1/8 full */

    /** Desenmascarar la interrupción local. */
    UART0_IM_R |= 0x10;                                                                             /*  UART0 => RXIM: UART Receive Interrupt Mask -> Interrupt unmasked */

    /** Establecer el nivel de prioridad de la IRQ. */
    NVIC_PRI1_R = ((NVIC_PRI1_R & ~0x0000E000) | (1 << 13));                                        /*  IRQ_5 (UART0) => INTB: Interrupt Priority -> Cleared and set 1 */

    /** Habilitación de la IRQ en el NVIC. */
    NVIC_EN0_R |= (1 << (5 - 0));                                                                   /*  IRQ_5 (UART0) => INT: Interrupt Enable -> Enabled */

    /********************************************
     *  Habilitación
     */

    /** 7.  Habilitar el UART. */
    UART0_CTL_R |= 0x01;                                                                            /*  UART0 => UARTEN: UART Enable -> Enabled */

}
