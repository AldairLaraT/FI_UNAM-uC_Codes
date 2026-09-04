/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          01 de diciembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 58:      Inter-Integrated Circuit (I2C)
 *  Descripción:    Código en lenguaje C que utiliza el módulo I2C0 (PB[3,2]) en velocidad estándar
 *                  (100kbps) para comunicarse con un reloj en tiempo real (RTC) DS1307.
 * 
 *  Archivo:        Archivo fuente del módulo I2C
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "I2C.h"                                                                                    /*  Archivo de cabecera del módulo I2C */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */


/**************************************************************************************************
 *  Variables externas (parámetros)
 */

extern int error;                                                                                   /*  Bandera ERROR */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        I2C0_Init
 * 
 *  Descripción:    Inicialización y configuración del I2C0.
 */

void I2C0_Init(void) {

    /********************************************
     *  Habilitación
     */

    /** 1.  Habilitar la señal de reloj del I2C y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCI2C_R |= 0x01;                                                                       /*  R0: I2C0 Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRI2C_R & 0x01)) {}                                                             /*  R0: I2C0 Peripheral Ready -> I2C0 is ready for access */

    /** 2.  Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x0002;                                                                    /*  R1: GPIO PortB Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x0002)) {}                                                          /*  R1: GPIO PortB Peripheral Ready -> GPIO PortB is ready for access */

    /** 3.  Habilitar las funciones alternas de hardware de los pines de los puertos GPIO. */
    GPIO_PORTB_AHB_AFSEL_R |= 0x0C;                                                                 /*  PortB[3:2] => AFSEL: Alternate Function Select -> Alternate hardware function */

    /** 4.  Configurar el GPIO correspondiente a SDA como open drain. */
    GPIO_PORTB_AHB_ODR_R |= 0x08;                                                                   /*  PortB[3] => ODE: Output Pad Open Drain Enable -> Enabled */

    /** 5.  Seleccionar las funciones alternas de hardware de los pines del puerto GPIO. */
    GPIO_PORTB_AHB_PCTL_R = (GPIO_PORTB_AHB_PCTL_R & ~0x0000FF00) | (2 << 12) | (2 << 8);           /*  PortB[3:2] => PMC3/2: Port Mux Control 3/2 -> I2C0_SDA/I2C0_SCL */

    /**     Habilitar las funciones digitales de los pines de los puertos GPIO. */
    GPIO_PORTB_AHB_DEN_R |= 0x0C;                                                                   /*  PortB[3:2] => DEN: Digital Enable -> Enabled */

    /** 6.  Configurar el I2C como maestro. */
    I2C0_MCR_R |= (1 << 4);                                                                         /*  I2C0 => MFE: I2C Master Function Enable -> Master mode is enabled */

    /** 7.  Configurar la velocidad del reloj de la señal SCL. */
    I2C0_MTPR_R = (I2C0_MTPR_R & ~0x7F) | (7 << 0);                                                 /*  I2C0 => TPR: Timer Period -> 100kbps */

}

/************************************************
 *  Función:        I2C0_RawInterrupt_wait
 * 
 *  Descripción:    Esperar a que termine la última operación y el controlador I2C esté libre.
 */

int I2C0_RawInterrupt_wait() {

    /** Read I2CMCS and poll the BUSY bit.
     *  NOTA:   De acuerdo con el Errata-sheet, hay un error con la bandera BUSY (I2C_MCS) en donde
     *          existe un retraso aproximado del 60% del periodo de reloj entre el envío del comando
     *          para comenzar con una trama y el cambio a '1' de la bandera BUSY.
     *          Para evitar el error, se monitorea (por polling) la bandera de interrupción cruda
     *          RIS (I2C_MRIS) que indica si está pendiente una interrupción del maestro.
    */

    /** Monitoreo de la bandera de interrupción cruda. */
    while (!(I2C0_MRIS_R & 0x01)) {}                                                                /*  I2C0 => RIS: Master Raw Interrupt Status -> A master interrupt is pending */

    /** Limpiar la bandera de interrupción. */
    I2C0_MICR_R |= 0x01;                                                                            /*  I2C0 => IC: Master Interrupt Clear -> RIS bit (I2C_MRIS) and MIS bit (I2C_MMIS) cleared */

    /** ERROR bit = 0 ? */
    if (I2C0_MCS_R & I2C_MCS_ERROR) {                                                               /*  I2C0 => ERROR: Error -> An error occurred on the last operation */
        /** Error Service. */
        error = 1;
    }

    return error;
}

/************************************************
 *  Función:        I2C0_TRANSMIT
 * 
 *  Descripción:    Transmisión de múltiples bytes.
 *  NOTA:           Código basado en el diagrama de flujo:
 *                  -> "Master TRANSMIT of Multiple Data Bytes" (pp.1292).
 */

void I2C0_TRANSMIT(uint8_t SlaveAddress, uint8_t StartRegister, uint8_t Data[], int index){

    /** Write Slave Address to I2CMSA. */
    I2C0_MSA_R = SlaveAddress << 1;                                                                 /*  I2C0 => SA: I2C Slave Address */
    I2C0_MSA_R &= ~0x1;                                                                             /*  I2C0 => R/S: Receive/Send -> Transmit */

    /** Write data to I2CMDR. */
    I2C0_MDR_R = StartRegister;                                                                     /*  I2C0 => DATA: Data transferred during the transaction -> Start register address */

    /** Write ---0-011 to I2CMCS. */
    I2C0_MCS_R = (I2C_MCS_START | I2C_MCS_RUN);                                                     /*  I2C0 => Idle state -> START condition followed by TRANSMIT (master goes to the Master Transmit state) */

    int i = 0;
    for (i = 0; i < index; i++) {

        /** BUSY bit = 0 ? */
        I2C0_RawInterrupt_wait();                                                                   /*  Esperar a que termine la última operación y el controlador I2C esté libre */

        /** Write data to I2CMDR. */
        I2C0_MDR_R = Data[i];                                                                       /*  I2C0 => DATA: Data transferred during the transaction -> Data[i] */

        if (i == (index - 1)) {
            /** Write ---0-101 to I2CMCS. */
            I2C0_MCS_R = (I2C_MCS_STOP | I2C_MCS_RUN);                                              /*  I2C0 => Master Transmit state -> TRANSMIT followed by STOP condition (master goes to Idle state) */
        } else {
            /** Write ---0-001 to I2CMCS. */
            I2C0_MCS_R = (I2C_MCS_RUN);                                                             /*  I2C0 => Master Transmit state -> TRANSMIT operation (master remains in Master Transmit state) */
        }
    }

    /** BUSY bit = 0 ? */
    I2C0_RawInterrupt_wait();                                                                       /*  Esperar a que termine la última operación y el controlador I2C esté libre */

}

/************************************************
 *  Función:        I2C0_RECEIVE
 * 
 *  Descripción:    Transmisión mixta: Transmisión de un byte + recepción de múltiples bytes.
 *  NOTA:           Código basado en el diagrama de flujo:
 *                  -> "Master RECEIVE with Repeated START after Master TRANSMIT" (pp.1294).
 */

void I2C0_RECEIVE(uint8_t SlaveAddress, uint8_t StartRegister, uint8_t RawData[], int index){

    /********************************************
     *  Master operates in Master Transmit mode (Master Single TRANSMIT, pp.1290).
     *  NOTA:   STOP condition is not generated.
     */

    /** Write Slave Address to I2CMSA. */
    I2C0_MSA_R = SlaveAddress << 1;                                                                 /*  I2C0 => SA: I2C Slave Address */
    I2C0_MSA_R &= ~0x1;                                                                             /*  I2C0 => R/S: Receive/Send -> Transmit */

    /** Write data to I2CMDR. */
    I2C0_MDR_R = StartRegister;                                                                     /*  I2C0 => DATA: Data transferred during the transaction -> Start register address */

    /** Write ---0-111 to I2CMCS (without the STOP bit). */
    I2C0_MCS_R = (I2C_MCS_START | I2C_MCS_RUN);                                                     /*  I2C0 => Idle state -> START condition followed by TRANSMIT (master goes to the Master Transmit state) */

    /** BUSY bit = 0 ? */
    I2C0_RawInterrupt_wait();                                                                       /*  Esperar a que termine la última operación y el controlador I2C esté libre */

    /********************************************
     *  Master RECEIVE with Repeated START after TRANSMIT, pp.1294.
     *  Repeated START condition is generated with changing data direction.
     */

    /** Write Slave Address to I2CMSA. */
    I2C0_MSA_R = SlaveAddress << 1;                                                                 /*  I2C0 => SA: I2C Slave Address */
    I2C0_MSA_R |= 0x1;                                                                              /*  I2C0 => R/S: Receive/Send -> Receive */

    /** Write ---01011 to I2CMCS. */
    I2C0_MCS_R = (I2C_MCS_ACK | I2C_MCS_START | I2C_MCS_RUN);                                       /*  I2C0 => Master Transmit state -> Repeated START condition followed by RECEIVE (master goes to the Master Receive state) */

    /********************************************
     *  Master operates in Master Receive mode (Master RECEIVE of Multiple Data Bytes, pp.1293).
     */

    int i = 0;
    for (i = 0; i < (index - 1); i++) {

        /** BUSY bit = 0 ? */
        I2C0_RawInterrupt_wait();                                                                   /*  Esperar a que termine la última operación y el controlador I2C esté libre */

        /** Read data from I2CMDR. */
        RawData[i] = I2C0_MDR_R;                                                                    /*  I2C0 => DATA: Data transferred during the transaction -> RawData[i] */

        if (i == (index - 2)) {
            /** Write ---00101 to I2CMCS. */
            I2C0_MCS_R = (I2C_MCS_STOP | I2C_MCS_RUN);                                              /*  I2C0 => Master Receive state -> RECEIVE followed by STOP condition (master goes to Idle state) */
        } else {
            /** Write ---01001 to I2CMCS. */
            I2C0_MCS_R = (I2C_MCS_ACK | I2C_MCS_RUN);                                               /*  I2C0 => Master Receive state -> RECEIVE operation (master remains in Master Receive state) */
        }
    }

    /** BUSY bit = 0 ? */
    I2C0_RawInterrupt_wait();                                                                       /*  Esperar a que termine la última operación y el controlador I2C esté libre */

    /** Read data from I2CMDR. */
    RawData[i] = I2C0_MDR_R;                                                                        /*  I2C0 => DATA: Data transferred during the transaction -> RawData[i] */
}
