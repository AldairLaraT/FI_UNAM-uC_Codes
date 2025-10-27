/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       22 de octubre de 2025
 * 
 * Tema 07:     Interrupciones y resets
 * Código 39:   Control de un contador con los SW de usuario, empleando interrupciones.
 * Descripción: Código en lenguaje C que actualiza el valor de un contador, dependiendo del botón
 *              que se presiona (SW1 y SW2 de la tarjeta de desarrollo), ejecutando una tarea
 *              distinta en el código principal (conmutación de los LED de usuario).
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 * Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 * Definiciones y macros
 */

/************************************************
 * Nested Vectored Interrupt Controller (NVIC) registers                                                pp146   Register map
 */
    // System Timer (SysTick) registers
#define NVIC_ST_CTRL_R              (*((volatile uint32_t *)0xE000E010))                            /*  pp150   SysTick Control and Status */
#define NVIC_ST_RELOAD_R            (*((volatile uint32_t *)0xE000E014))                            /*  pp152   SysTick Reload Value */
#define NVIC_ST_CURRENT_R           (*((volatile uint32_t *)0xE000E018))                            /*  pp153   SysTick Current Value */
    // Nested Vectored Interrupt Controller (NVIC) registers
#define NVIC_EN1_R                  (*((volatile uint32_t *)0xE000E104))                            /*  pp154   Interrupt 32-63 Set Enable */
#define NVIC_PRI12_R                (*((volatile uint32_t *)0xE000E430))                            /*  pp159   Interrupt 48-51 Priority */

/************************************************
 * System Control (SYSCTL) registers                                                                    pp247   Register map
 */
#define SYSCTL_RCGCGPIO_R           (*((volatile uint32_t *)0x400FE608))                            /*  pp382   GPIO Run Mode Clock Gating Control */
#define SYSCTL_PRGPIO_R             (*((volatile uint32_t *)0x400FEA08))                            /*  pp499   GPIO Peripheral Ready */

/************************************************
 * General-Purpose Input/Output (GPIO) registers                                                        pp757   Register map
 */
    // GPIO Port F (PortF)
#define GPIO_PORTF_AHB_DATA_R       (*((volatile uint32_t *)0x4005D044))                            /*  pp759   GPIO Data >> PortF[4,0] unmasked */
#define GPIO_PORTF_AHB_DIR_R        (*((volatile uint32_t *)0x4005D400))                            /*  pp760   GPIO Direction */
#define GPIO_PORTF_AHB_DEN_R        (*((volatile uint32_t *)0x4005D51C))                            /*  pp781   GPIO Digital Enable */
    // GPIO Port J (PortJ)
#define GPIO_PORTJ_AHB_DATA_R       (*((volatile uint32_t *)0x4006000C))                            /*  pp759   GPIO Data >> PortJ[1,0] unmasked */
#define GPIO_PORTJ_AHB_DIR_R        (*((volatile uint32_t *)0x40060400))                            /*  pp760   GPIO Direction */
#define GPIO_PORTJ_AHB_IS_R         (*((volatile uint32_t *)0x40060404))                            /*  pp761   GPIO Interrupt Sense */
#define GPIO_PORTJ_AHB_IBE_R        (*((volatile uint32_t *)0x40060408))                            /*  pp762   GPIO Interrupt Both Edges */
#define GPIO_PORTJ_AHB_IEV_R        (*((volatile uint32_t *)0x4006040C))                            /*  pp763   GPIO Interrupt Event */
#define GPIO_PORTJ_AHB_IM_R         (*((volatile uint32_t *)0x40060410))                            /*  pp764   GPIO Interrupt Mask */
#define GPIO_PORTJ_AHB_MIS_R        (*((volatile uint32_t *)0x40060418))                            /*  pp767   GPIO Masked Interrupt Status */
#define GPIO_PORTJ_AHB_ICR_R        (*((volatile uint32_t *)0x4006041C))                            /*  pp769   GPIO Interrupt Clear */
#define GPIO_PORTJ_AHB_PUR_R        (*((volatile uint32_t *)0x40060510))                            /*  pp776   GPIO Pull-Up Select */
#define GPIO_PORTJ_AHB_DEN_R        (*((volatile uint32_t *)0x4006051C))                            /*  pp781   GPIO Digital Enable */
    // GPIO Port N (PortN)
#define GPIO_PORTN_DATA_R           (*((volatile uint32_t *)0x4006400C))                            /*  pp759   GPIO Data >> PortN[1,0] unmasked */
#define GPIO_PORTN_DIR_R            (*((volatile uint32_t *)0x40064400))                            /*  pp760   GPIO Direction */
#define GPIO_PORTN_DEN_R            (*((volatile uint32_t *)0x4006451C))                            /*  pp781   GPIO Digital Enable */

/************************************************
 * Bit fields
 */
    // Bit fields in the NVIC_ST_CTRL register                                                          pp150
#define NVIC_ST_CTRL_COUNT          0x00010000                                                      /*  Count Flag */

/************************************************
 * Variables globales
 */

uint32_t Bounce_Delay = 200000;                                                                     /*  Valor de carga del SysTick para un retardo de rebote de 50ms (f = 4MHz) */
int counter = 0;


/**************************************************************************************************
 * Funciones
 */

/************************************************
 * Función:     GPIO_PortF_Init
 * 
 * Descripción: Inicialización y configuración del puerto GPIO F.
 */

void GPIO_PortF_Init(void) {

    /*  1. Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x0020;                                                                    /*  R5: GPIO PortF Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x0020)) {}                                                          /*  R5: GPIO PortF Peripheral Ready -> GPIO PortF is ready for access */

    /*  2. Configurar la dirección de los pines del puerto GPIO. */
    GPIO_PORTF_AHB_DIR_R |= 0x11;                                                                   /*  PortF[4,0] => DIR: GPIO Data direction -> Output */

    /*  3. Habilitar las funciones digitales de los pines del puerto GPIO. */
    GPIO_PORTF_AHB_DEN_R |= 0x11;                                                                   /*  PortF[4,0] => DEN: Digital Enable -> Enabled */

}

 /************************************************
 * Función:     GPIO_PortJ_Init
 * 
 * Descripción: Inicialización y configuración del puerto GPIO J.
 */

void GPIO_PortJ_Init(void) {

    /*  1. Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x0100;                                                                    /*  R8: GPIO PortJ Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x0100)) {}                                                          /*  R8: GPIO PortJ Peripheral Ready -> GPIO PortJ is ready for access */

    /*  2. Configurar la dirección de los pines del puerto GPIO. */
    GPIO_PORTJ_AHB_DIR_R &= ~0x03;                                                                  /*  PortJ[1,0] => DIR: GPIO Data direction -> Input */

    /*  3. Habilitar las resistencias de pull-up de los pines del puerto GPIO. */
    GPIO_PORTJ_AHB_PUR_R |= 0x03;                                                                   /*  PortJ[1,0] => PUE: Pad Weak Pull-Up Enable -> Enabled */

    /*  4. Habilitar las funciones digitales de los pines del puerto GPIO. */
    GPIO_PORTJ_AHB_DEN_R |= 0x03;                                                                   /*  PortJ[1,0] => DEN: Digital Enable -> Enabled */

    /**
     * Interrupción
     */

    /*  Habilitación y configuración de la interrupción */
    GPIO_PORTJ_AHB_IS_R &= ~0x03;                                                                   /*  PortJ[1,0] => IS: Interrupt Sense -> Edge-sensitive */
    GPIO_PORTJ_AHB_IBE_R &= ~0x03;                                                                  /*  PortJ[1,0] => IBE: Interrupt Both Edges -> Controlled by GPIO_IEV */
    GPIO_PORTJ_AHB_IEV_R &= ~0x03;                                                                  /*  PortJ[1,0] => IEV: Interrupt Event -> Falling edge */
    GPIO_PORTJ_AHB_ICR_R |= 0x03;                                                                   /*  PortJ[1,0] => IC: Interrupt Clear -> Interrupt cleared */

    /*  Desenmascarar la interrupción local */
    GPIO_PORTJ_AHB_IM_R |= 0x03;                                                                    /*  PortJ[1,0] => IME: Interrupt Mask Enable -> Interrupt unmasked */

    /*  Establecer el nivel de prioridad de la IRQ */
    NVIC_PRI12_R = ((NVIC_PRI12_R & ~0xE0000000) | (0 << 29));                                      /*  IRQ_51 (PortJ) => INTD: Interrupt Priority -> Cleared and set 0 */

    /*  Habilitación de la IRQ en el NVIC */
    NVIC_EN1_R |= (1 << (51 - 32));                                                                 /*  IRQ_51 (PortJ) => INT: Interrupt Enable -> Enabled */

}

/************************************************
 * Función:     GPIO_PortN_Init
 * 
 * Descripción: Inicialización y configuración del puerto GPIO N.
 */

void GPIO_PortN_Init(void) {

    /*  1. Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x1000;                                                                    /*  R12: GPIO PortN Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x1000)) {}                                                          /*  R12: GPIO PortN Peripheral Ready -> GPIO PortN is ready for access */

    /*  2. Configurar la dirección de los pines del puerto GPIO. */
    GPIO_PORTN_DIR_R |= 0x03;                                                                       /*  PortN[1,0] => DIR: GPIO Data direction -> Output */

    /*  3. Habilitar las funciones digitales de los pines del puerto GPIO. */
    GPIO_PORTN_DEN_R |= 0x03;                                                                       /*  PortN[1,0] => DEN: Digital Enable -> Enabled */

}

/************************************************
 * Función:     SysTick_Init_OneShot
 * 
 * Descripción: Inicialización y configuración del SysTick en modo one-shot.
 * 
 * Parámetros:
 *      SysTick_Reload  : Valor de carga/inicio del SysTick (ST_RELOAD)
 */

void SysTick_Init_OneShot(uint32_t SysTick_Reload) {

    /*  1. Cargar el valor de cuenta del SysTick. */
    NVIC_ST_RELOAD_R = (SysTick_Reload & 0x00FFFFFF);                                               /*  RELOAD: Reload Value */

    /*  2. Limpiar el valor de cuenta actual del SysTick. */
    NVIC_ST_CURRENT_R = 0;                                                                          /*  CURRENT: Current Value -> Cleared */

    /*  3. Configurar el SysTick para la operación requerida. */
    NVIC_ST_CTRL_R |= 0x01;                                                                         /*  Enables SysTick to operate in a multi-shot way (PIOSC divided by 4) */

}

/************************************************
 * Función:     GPIO_PortJ_Handler
 * 
 * Descripción: Rutina de servicio de interrupción (ISR) del GPIO PortJ.
 */

void GPIO_PortJ_Handler(void) {

    /*  Limpiar la bandera de interrupción */
    GPIO_PORTJ_AHB_ICR_R = (GPIO_PORTJ_AHB_MIS_R & 0x03);                                           /*  PortJ => IC: Interrupt Clear -> Interrupt cleared */

    /*  Retardo de rebote */
    SysTick_Init_OneShot (Bounce_Delay);                                                            /*  Inicialización y configuración del SysTick en modo one-shot */
    while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT)) {}                                               /*  SysTick => COUNT: Count Flag -> The SysTick timer has counted to 0 */

    /*  Confirmar qué botón se presionó */
    if (!(GPIO_PORTJ_AHB_DATA_R & 0x01)) {                                                          /*  IF (SW1 -> on) */
        counter++;
    }

    if (!(GPIO_PORTJ_AHB_DATA_R & 0x02)) {                                                          /*  IF (SW2 -> on) */
        counter--;
    }

}


/**************************************************************************************************
 * Función principal
 */

int main(void) {

    GPIO_PortF_Init();                                                                              /*  Inicialización y configuración del puerto GPIO F */
    GPIO_PortJ_Init();                                                                              /*  Inicialización y configuración del puerto GPIO J */
    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */

    int i;

    while (1) {
        for (i = 0; i < 700000; i++) {}                                                             /*  Retardo aproximado de 500ms */
        GPIO_PORTN_DATA_R ^= 0x02;                                                                  /*  LED D1 -> toggle */

        for (i = 0; i < 700000; i++) {}                                                             /*  Retardo aproximado de 500ms */
        GPIO_PORTN_DATA_R ^= 0x01;                                                                  /*  LED D2 -> toggle */

        for (i = 0; i < 700000; i++) {}                                                             /*  Retardo aproximado de 500ms */
        GPIO_PORTF_AHB_DATA_R ^= 0x10;                                                              /*  LED D3 -> toggle */

        for (i = 0; i < 700000; i++) {}                                                             /*  Retardo aproximado de 500ms */
        GPIO_PORTF_AHB_DATA_R ^= 0x01;                                                              /*  LED D4 -> toggle */
    }
}
