; -------------------------------------------------------------------------------------------------
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
;
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        27 de septiembre de 2025
;
; Tema 06:      Puertos de entrada/salida
; Código 19:    Retardos con lenguaje ensamblador
; Descripción:  Código en lenguaje ensamblador que enciende el LED D1 de la tarjeta de desarrollo
;               al finalizar un retardo de 5s.
;
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; -------------------------------------------------------------------------------------------------

        .global main


; -------------------------------------------------------------------------------------------------
; Sección de datos
; -------------------------------------------------------------------------------------------------

        .data


; -------------------------------------------------------------------------------------------------
; Sección de código ejecutable
; -------------------------------------------------------------------------------------------------

        .text


; -------------------------------------------------------------------------------------------------
; Apuntadores

    ; System Control (SYSCTL) registers
SYSCTL_RCGCGPIO_R       .field 0x400FE608,32    ; pp382     GPIO Run Mode Clock Gating Control

    ; General-Purpose Input/Output (GPIO) registers
        ; GPIO PortN
GPIO_PORTN_DATA_R       .field 0x40064008,32    ; pp759     GPIO Data >> PortN[1] unmasked
GPIO_PORTN_DIR_R        .field 0x40064400,32    ; pp760     GPIO Direction
GPIO_PORTN_DEN_R        .field 0x4006451C,32    ; pp781     GPIO Digital Enable


; -------------------------------------------------------------------------------------------------
; Subrutinas

    ; -----------------------------------------
    ; Subrutina:    GPIO_PortN_Init
    ; Descripción:  Inicialización y configuración del puerto GPIO N.
    ; -----------------------------------------

GPIO_PortN_Init:

    ; 1. Habilitar la señal de reloj del puerto GPIO y esperar dos ciclos de instrucción para que
    ;    se estabilice el reloj.
        LDR     R0, SYSCTL_RCGCGPIO_R
        LDR     R1, [R0]
        ORR     R1, #0x1000
        STR     R1, [R0]                        ; R12: GPIO PortN Run Mode Clock Gating Control -> Enabled
        NOP
        NOP                                     ; Wait for the GPIO PortN clock to stabilize

    ; 2. Configurar la dirección de los pines del puerto GPIO.
        LDR     R0, GPIO_PORTN_DIR_R
        LDR     R1, [R0]
        ORR     R1, #0x02
        STR     R1, [R0]                        ; PortN[1] => DIR: GPIO Data direction -> Output

    ; 3. Habilitar las funciones digitales de los pines del puerto GPIO.
        LDR     R0, GPIO_PORTN_DEN_R
        LDR     R1, [R0]
        ORR     R1, #0x02
        STR     R1, [R0]                        ; PortN[1] => DEN: Digital Enable -> Enabled

    ; Retorno de subrutina
        BX      LR


    ; -----------------------------------------
    ; Subrutina:    Delay
    ; Descripción:  Retardo implementado con un ciclo for, de n ciclos de instrucción.
    ; Parámetros:
    ;   R0  : Número de ciclos for (n)
    ; Registros reservados (variables locales):
    ;   R4  : Índice (i)
    ; -----------------------------------------

Delay:

    ; Preservar contexto (registros usados como variables locales)
        PUSH    {R4}

    ; Inicializar variables locales
        MOV     R4, #0                          ; Inicialización (i = 0)

Delay_for
    ; Condición (i < n)
        CMP     R4, R0
        BEQ     Delay_for_end                   ; Salto si Z = 1 (i = n)

    ; Actualización del contador (i++)
        ADD     R4, #1

        B       Delay_for

Delay_for_end

    ; Restaurar contexto (registros usados como variables locales)
        POP     {R4}                            ; Restaurar contexto (registros usados como variables locales)

    ; Retorno de subrutina
        BX      LR


; -------------------------------------------------------------------------------------------------
; Código principal

main:

        BL      GPIO_PortN_Init                 ; Inicialización y configuración del puerto GPIO N

    ; Parámetros para subrutina Delay
        MOVW    R0, #0x7354
        MOVT    R0, #0x00CB                     ; Número de ciclos FOR (n = 13,333,332)
        BL      Delay                           ; Retardo (t = 5s)

    ; Encender el LED D1 de la tarjeta de desarrollo
        LDR     R0, GPIO_PORTN_DATA_R
        LDR     R1, [R0]                        ; R1 = [GPIO_PORTN_DATA_R]
        ORR     R1, #0x02
        STR     R1, [R0]                        ; LED D1 -> on


halt    B       halt

        .end
