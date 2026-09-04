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
 *  Archivo:        Archivo de cabecera del módulo I2C
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef I2C_H                                                                                       /*  Verificar si I2C_H no ha sido definido previamente */
#define I2C_H                                                                                       /*  Definir I2C_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 *  Definiciones y macros
 *  Inter-Integrated Circuit (I2C) registers                                                            pp.1300     Register map
 */
    /** I2C module 0 (I2C0) Master */
#define I2C0_MSA_R                  (*((volatile uint32_t *)0x40020000))                            /*  pp.1302     I2C Master Slave Address */
#define I2C0_MCS_R                  (*((volatile uint32_t *)0x40020004))                            /*  pp.1303     I2C Master Control/Status */
#define I2C0_MDR_R                  (*((volatile uint32_t *)0x40020008))                            /*  pp.1312     I2C Master Data */
#define I2C0_MTPR_R                 (*((volatile uint32_t *)0x4002000C))                            /*  pp.1313     I2C Master Timer Period */
#define I2C0_MRIS_R                 (*((volatile uint32_t *)0x40020014))                            /*  pp.1318     I2C Master Raw Interrupt Status */
#define I2C0_MICR_R                 (*((volatile uint32_t *)0x4002001C))                            /*  pp.1324     I2C Master Interrupt Clear */
#define I2C0_MCR_R                  (*((volatile uint32_t *)0x40020020))                            /*  pp.1326     I2C Master Configuration */

/************************************************
 *  Bit fields
 */
    //  Bit fields in the I2C_MCS (read-only) register                                                  pp.1303
#define I2C_MCS_CLKTO               0x00000080                                                      /*  Clock Timeout Error */
#define I2C_MCS_BUSBSY              0x00000040                                                      /*  Bus Busy */
#define I2C_MCS_IDLE                0x00000020                                                      /*  I2C Idle */
#define I2C_MCS_ARBLST              0x00000010                                                      /*  Arbitration Lost */
#define I2C_MCS_DATACK              0x00000008                                                      /*  Acknowledge Data */
#define I2C_MCS_ADRACK              0x00000004                                                      /*  Acknowledge Address */
#define I2C_MCS_ERROR               0x00000002                                                      /*  Error */
#define I2C_MCS_BUSY                0x00000001                                                      /*  I2C Busy */

    //  Bit fields in the I2C_MCS (write-only) register                                                 pp.1305
#define I2C_MCS_BURST               0x00000040                                                      /*  Burst Enable */
#define I2C_MCS_QCMD                0x00000020                                                      /*  Quick Command */
#define I2C_MCS_HS                  0x00000010                                                      /*  High-Speed Enable */
#define I2C_MCS_ACK                 0x00000008                                                      /*  Data Acknowledge Enable */
#define I2C_MCS_STOP                0x00000004                                                      /*  Generate STOP */
#define I2C_MCS_START               0x00000002                                                      /*  Generate START */
#define I2C_MCS_RUN                 0x00000001                                                      /*  I2C Master Enable */


/**************************************************************************************************
 *  Prototipos de funciones
 */

void I2C0_Init();                                                                                   /*  Inicialización y configuración del I2C0 */
int I2C0_RawInterrupt_wait();                                                                       /*  I2C0 => Esperar a que termine la última operación y el controlador I2C esté libre */
void I2C0_TRANSMIT(uint8_t SlaveAddress, uint8_t StartRegister, uint8_t Data[], int index);         /*  I2C0 => Transmisión de múltiples bytes */
void I2C0_RECEIVE(uint8_t SlaveAddress, uint8_t StartRegister, uint8_t RawData[], int index);       /*  I2C0 => Transmisión mixta: Transmisión de un byte + recepción de múltiples bytes */


#endif                                                                                              /*  I2C_H */
