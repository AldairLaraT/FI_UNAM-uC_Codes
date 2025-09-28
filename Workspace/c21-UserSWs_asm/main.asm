; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        27 de septiembre de 2025
; 
; Tema 06:      Puertos de entrada/salida
; Código 21:    Control de un LED con un SW de usuario
; Descripción:  Código en lenguaje ensamblador que enciende/apaga el LED D1 de la tarjeta de
;               desarrollo, dependiendo del botón SW1.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************

        .global main


; *************************************************************************************************
; Sección de datos
; ***********************************************

        .data


; *************************************************************************************************
; Sección de código ejecutable
; ***********************************************

        .text


; ***********************************************
; Apuntadores

    ; System Control (SYSCTL) registers
SYSCTL_RCGCGPIO_R       .field 0x400FE608,32    ; pp382     GPIO Run Mode Clock Gating Control

    ; General-Purpose Input/Output (GPIO) registers
        ; GPIO PortJ
GPIO_PORTJ_AHB_DATA_R   .field 0x40060004,32    ; pp759     GPIO Data >> PortJ[0] unmasked
GPIO_PORTJ_AHB_DIR_R    .field 0x40060400,32    ; pp760     GPIO Direction
GPIO_PORTJ_AHB_PUR_R    .field 0x40060510,32    ; pp776     GPIO Pull-Up Select
GPIO_PORTJ_AHB_DEN_R    .field 0x4006051C,32    ; pp781     GPIO Digital Enable
        ; GPIO PortN
GPIO_PORTN_DATA_R       .field 0x40064008,32    ; pp759     GPIO Data >> PortN[1] unmasked
GPIO_PORTN_DIR_R        .field 0x40064400,32    ; pp760     GPIO Direction
GPIO_PORTN_DEN_R        .field 0x4006451C,32    ; pp781     GPIO Digital Enable


; ***********************************************
; Subrutinas

    ; ********************   ********************
    ; Subrutina:    GPIO_PortJ_Init
    ;
    ; Descripción:
    ;   Inicialización y configuración del puerto GPIO J.
    ; ********************   ********************

GPIO_PortJ_Init:
    ; 1. Habilitar la señal de reloj del puerto GPIO y esperar dos ciclos de instrucción
    ;    para que se estabilice el reloj.
        LDR   R0, SYSCTL_RCGCGPIO_R
        LDR   R1, [R0]
        ORR   R1, #0x0100
        STR   R1, [R0]                          ; GPIO PortJ Run Mode Clock Gating Control -> Enabled
        NOP
        NOP                                     ; Wait for the GPIO PortJ clock to stabilize

    ; 2. Configurar la dirección de los pines del puerto GPIO
        LDR   R0, GPIO_PORTJ_AHB_DIR_R
        LDR   R1, [R0]
        BIC   R1, #0x01
        STR   R1, [R0]                          ; PortJ[0] => DIR: GPIO Data direction -> Input

    ; 3. Habilitar las resistencias de pull-up de los pines del puerto GPIO
        LDR   R0, GPIO_PORTJ_AHB_PUR_R
        LDR   R1, [R0]
        ORR   R1, #0x01
        STR   R1, [R0]                          ; PortJ[0] => PUE: Pad Weak Pull-Up Enable -> Enabled

    ; 4. Habilitar las funciones digitales de los pines del puerto GPIO
        LDR   R0, GPIO_PORTJ_AHB_DEN_R
        LDR   R1, [R0]
        ORR   R1, #0x01
        STR   R1, [R0]                          ; PortJ[0] => Digital Enable -> Enabled

        BX    LR


    ; ********************   ********************
    ; Subrutina:    GPIO_PortN_Init
    ;
    ; Descripción:
    ;   Inicialización y configuración del puerto GPIO N.
    ; ********************   ********************

GPIO_PortN_Init:
    ; 1. Habilitar la señal de reloj del puerto GPIO y esperar dos ciclos de instrucción
    ;    para que se estabilice el reloj.
        LDR   R0, SYSCTL_RCGCGPIO_R
        LDR   R1, [R0]
        ORR   R1, #0x1000
        STR   R1, [R0]                          ; GPIO PortN Run Mode Clock Gating Control -> Enabled
        NOP
        NOP                                     ; Wait for the GPIO PortN clock to stabilize

    ; 2. Configurar la dirección de los pines del puerto GPIO
        LDR   R0, GPIO_PORTN_DIR_R
        LDR   R1, [R0]
        ORR   R1, #0x02
        STR   R1, [R0]                          ; PortN[1] => DIR: GPIO Data direction -> Output

    ; 3. Habilitar las funciones digitales de los pines del puerto GPIO
        LDR   R0, GPIO_PORTN_DEN_R
        LDR   R1, [R0]
        ORR   R1, #0x02
        STR   R1, [R0]                          ; PortN[1] => Digital Enable -> Enabled

        BX    LR


; ***********************************************
; Código principal

main:
        BL    GPIO_PortJ_Init                   ; Inicialización y configuración del puerto GPIO J
        BL    GPIO_PortN_Init                   ; Inicialización y configuración del puerto GPIO N

        LDR   R0, GPIO_PORTJ_AHB_DATA_R
        LDR   R1, GPIO_PORTN_DATA_R

loop
        LDR   R2, [R0]                          ; R2 = [GPIO_PORTJ_AHB_DATA_R]
        CMP   R2, #0x00                         ; Condición (SW1 = on)
        BNE   else

if                                              ; IF (SW1 -> on)
        MOV   R2, #0x02
        STR   R2, [R1]                          ; LED D1 -> on
        B     loop

else                                            ; IF (SW1 -> off)
        MOV   R2, #0x00
        STR   R2, [R1]                          ; LED D2 -> off
        B     loop

        .end
