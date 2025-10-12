; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        12 de octubre de 2025
; 
; Tema 06:      Puertos de entrada/salida
; Código 25:    SysTick en modo one-shot
; Descripción:  Código en lenguaje ensamblador que conmuta el LED D1 de la tarjeta de desarrollo con
;               una frecuencia de 1Hz, empleando el SysTick en modo one-shot.
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

    ; Nested Vectored Interrupt Controller (NVIC) registers
NVIC_ST_CTRL_R          .field 0xE000E010,32    ; pp150     SysTick Control and Status
NVIC_ST_RELOAD_R        .field 0xE000E014,32    ; pp152     SysTick Reload Value
NVIC_ST_CURRENT_R       .field 0xE000E018,32    ; pp153     SysTick Current Value

    ; System Control (SYSCTL) registers
SYSCTL_RCGCGPIO_R       .field 0x400FE608,32    ; pp382     GPIO Run Mode Clock Gating Control

    ; General-Purpose Input/Output (GPIO) registers
        ; GPIO PortN
GPIO_PORTN_DATA_R       .field 0x40064008,32    ; pp759     GPIO Data >> PortN[1] unmasked
GPIO_PORTN_DIR_R        .field 0x40064400,32    ; pp760     GPIO Direction
GPIO_PORTN_DEN_R        .field 0x4006451C,32    ; pp781     GPIO Digital Enable


; ***********************************************
; Subrutinas

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

    ; 2. Configurar la dirección de los pines del puerto GPIO.
        LDR   R0, GPIO_PORTN_DIR_R
        LDR   R1, [R0]
        ORR   R1, #0x02
        STR   R1, [R0]                          ; PortN[1] => DIR: GPIO Data direction -> Output

    ; 3. Habilitar las funciones digitales de los pines del puerto GPIO.
        LDR   R0, GPIO_PORTN_DEN_R
        LDR   R1, [R0]
        ORR   R1, #0x02
        STR   R1, [R0]                          ; PortN[1] => Digital Enable -> Enabled

        BX    LR


    ; ********************   ********************
    ; Subrutina:    SysTick_Init_OneShot
    ;
    ; Descripción:
    ;   Inicialización y configuración del SysTick.
    ;
    ; Parámetros:
    ;   R1  : Valor de carga/inicio del SysTick (ST_RELOAD)
    ; ********************   ********************

SysTick_Init_OneShot:
    ; 1. Cargar el valor de cuenta del SysTick.
        LDR   R0, NVIC_ST_RELOAD_R
        STR   R1, [R0]                          ; RELOAD: Reload Value

    ; 2. Limpiar el valor de cuenta actual del SysTick.
        LDR   R0, NVIC_ST_CURRENT_R
        MOV   R1, #0
        STR   R1, [R0]                          ; CURRENT: Current Value -> Cleared

    ; 3. Configurar el SysTick para la operación requerida.
        LDR   R0, NVIC_ST_CTRL_R
        LDR   R1, [R0]
        BIC   R1, #0x04                         ; CLK_SRC: Clock Source -> Precision internal oscillator (PIOSC) divided by 4
        ; ORR   R1, #0x04                         ; CLK_SRC: Clock Source -> System clock
        BIC   R1, #0x02                         ; INTEN: Interrupt Enable -> Disabled
        ORR   R1, #0x01                         ; ENABLE: Enable -> Enables SysTick to operate in a multi-shot way
        STR   R1, [R0]

    ; Limpiar el valor de carga/inicio del SysTick para deshabilitar al contador en el siguiente ciclo.
        LDR   R0, NVIC_ST_RELOAD_R
        MOV   R1, #0
        STR   R1, [R0]                          ; RELOAD: Reload Value -> Cleared

        BX    LR


    ; ********************   ********************
    ; Subrutina:    SysTick_Wait
    ;
    ; Descripción:
    ;   Esperar a que el SysTick termine de contar.
    ;
    ; Registros reservados (variables locales):
    ;   R4  : Apuntador (NVIC_ST_CTRL_R)
    ;   R5  : Apuntador (ST_CURRENT)
    ;   R6  : Bandera COUNT (ST_CTRL)
    ;   R7  : Contenido de ST_CURRENT
    ; ********************   ********************

SysTick_Wait:
        PUSH  {R4, R5, R6, R7}                  ; Preservar contexto (registros usados como variables locales)
        LDR   R4, NVIC_ST_CTRL_R
        LDR   R5, NVIC_ST_CURRENT_R
        MOVW  R6, #0x0000
        MOVT  R6, #0x0001                       ; R6 = COUNT flag

SysTick_Loop
        LDR   R7, [R4]                          ; R7 = [NVIC_ST_CTRL_R]
        ANDS  R7, R6                            ; Condición (COUNT = 1)
        BEQ   SysTick_Loop                      ; Salto si Z = 1

        POP   {R4, R5, R6, R7}                  ; Restaurar contexto (registros usados como variables locales)
        BX    LR


; ***********************************************
; Código principal

main:
        BL    GPIO_PortN_Init                   ; Inicialización y configuración del puerto GPIO N

    ; Parámetros para subrutina SysTick_Init
        MOVW  R1, #0x0900
        MOVT  R1, #0x003D                       ; Valor de carga/inicio del SysTick (ST_RELOAD) -> #0x003D.0900 (4,000,000)
        BL    SysTick_Init_OneShot              ; Inicialización y configuración del SysTick en modo one-shot

        LDR   R4, GPIO_PORTN_DATA_R
loop
        BL    SysTick_Wait                      ; Esperar a que el SysTick termine de contar

        LDR   R5, [R4]                          ; R5 = [GPIO_PORTN_DATA_R]
        EOR   R5, #0x02
        STR   R5, [R4]                          ; LED D1 -> toggle

    ; Parámetros para subrutina SysTick_Init
        ; MOVW  R1, #0x0900
        ; MOVT  R1, #0x003D                       ; Valor de carga/inicio del SysTick (ST_RELOAD) -> #0x003D.0900 (4,000,000)
        ; BL    SysTick_Init_OneShot              ; Inicialización y configuración del SysTick en modo one-shot

        B     loop

        .end
