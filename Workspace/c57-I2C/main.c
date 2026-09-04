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
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "I2C.h"                                                                                    /*  Archivo de cabecera del módulo I2C */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */


/**************************************************************************************************
 *  Variables globales
 */

int Seconds, Minutes, Hours, Day, Date, Month, Year = 0;                                            /*  DS1307 => RTC data */
int error = 0;                                                                                      /*  Bandera ERROR */


/**************************************************************************************************
 *  Función principal
 */

int main(void) {

    I2C0_Init();                                                                                    /*  Inicialización y configuración del I2C0 */

    uint8_t DS1307_Address = 0x68;                                                                  /*  DS1307 => Slave Address */
    uint8_t DS1307_Seconds_Reg = 0x00;                                                              /*  DS1307 => Seconds register pointer */
    uint8_t DS1307_Date_Today[7] = {0x00, 0x30, 0x17, 0x04, 0x03, 0x12, 0x25};                      /*  DS1307 Today Date (Seconds, Minutes, Hours, Day, Date, Month, Year) */
    // uint8_t DS1307_Date_NewYear[7] = {0x40, 0x59, 0x23, 0x07, 0x31, 0x12, 0x24};                    /*  DS1307 New Year Date (Seconds, Minutes, Hours, Day, Date, Month, Year) */

    /********************************************
     *  Transmisión de múltiples bytes para configurar al RTC.
     */
    I2C0_TRANSMIT(DS1307_Address, DS1307_Seconds_Reg, DS1307_Date_Today, 7);

    uint8_t DS1307_RawData[7];                                                                      /*  DS1307 => Datos crudos del RTC */

    do {

        /********************************************
         *  Transmisión mixta: Transmisión de un byte + recepción de múltiples bytes para leer los
         *  datos del RTC.
         */
        I2C0_RECEIVE(DS1307_Address, DS1307_Seconds_Reg, DS1307_RawData, 7);

        /********************************************
         *  Conversión de los datos crudos del RTC: BCD -> Decimal
         */
        Seconds = (((DS1307_RawData[0] & 0x70) >> 4)*10) + (DS1307_RawData[0] & 0x0F);
        Minutes = (((DS1307_RawData[1] & 0x70) >> 4)*10) + (DS1307_RawData[1] & 0x0F);
        Hours   = (((DS1307_RawData[2] & 0x30) >> 4)*10) + (DS1307_RawData[2] & 0x0F);
        Day     = DS1307_RawData[3];
        Date    = (((DS1307_RawData[4] & 0x30) >> 4)*10) + (DS1307_RawData[4] & 0x0F);
        Month   = (((DS1307_RawData[5] & 0x10) >> 4)*10) + (DS1307_RawData[5] & 0x0F);
        Year    = (((DS1307_RawData[6] & 0xF0) >> 4)*10) + (DS1307_RawData[6] & 0x0F);

    } while (error != 1);

    while (1) {}
}
