; -------------------------------------------------------------------------------------------------
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
;
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        03 de septiembre de 2025
;
; Tema 04:      Lenguaje ensamblador y el ensamblador
; Código 10:    Programa en lenguaje ensamblador
; Descripción:  Ejemplo de un programa en lenguaje ensamblador.
;
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; -------------------------------------------------------------------------------------------------

        .global main                            ; Declaración del símbolo "main" para que sea
                                                ; visible por el enlazador (linker)


; -------------------------------------------------------------------------------------------------
; Sección de datos
; -------------------------------------------------------------------------------------------------

        .data                                   ; Sección de datos inicializados para utilizarse en
                                                ; el programa

Dato32b .word   0                               ; Reserva y almacena un dato de 32 bits
Dato16b .half   0xFFFF                          ; Reserva y almacena un dato de 16 bits
Dato8b  .byte   0xAA                            ; Reserva y almacena un dato de 8 bits
DOS     .equ    0x02                            ; Asigna un nombre a un valor constante, sustituido
                                                ; por el ensamblador


; -------------------------------------------------------------------------------------------------
; Sección de código ejecutable
; -------------------------------------------------------------------------------------------------

        .text                                   ; Sección de código ejecutable


; -------------------------------------------------------------------------------------------------
; Apuntadores

SRAM    .field  0x20000000,32                   ; Define un campo de bits dentro de una estructura


; -------------------------------------------------------------------------------------------------
; Subrutinas

    ; -----------------------------------------
    ; Subrutina:    twos_complement
    ; Descripción:  Cálculo del complemento a dos de un número.
    ; Parámetros:
    ;   R0  : Número a calcular el complemento a dos.
    ; Retorno:
    ;   R0  : Complemento a dos del número.
    ; -----------------------------------------

twos_complement:

    ; Complemento a dos
        MVN     R0, R0                          ; R0 = not(R0)
        ADD     R0, #1                          ; R0 = R0 + 1

    ; Retorno de subrutina
        BX      LR                              ; Salto indirecto a LR (link register)


; -------------------------------------------------------------------------------------------------
; Código principal

main:

        MOV     R0, #50                         ; R0 = 50
        BL      twos_complement                 ; Salto con liga a twos_complement

        MOVW    R0, Dato16b
        MOVT    R0, Dato16b                     ; R0 = Dirección(Dato16b)
        LDRH    R1, [R0]                        ; R1(15..0) = Dato16b

        MOVW    R0, Dato8b
        MOVT    R0, Dato8b                      ; R0 = Dirección(Dato8b)
        LDRB    R2, [R0]                        ; R2(7..0) = Dato8b

        ADD     R1, R2                          ; R1 = R1 + R2
        MOV     R2, #DOS                        ; R2 = DOS
        MUL     R1, R2                          ; R1 = R1 * R2
        MOVW    R0, Dato32b
        MOVT    R0, Dato32b                     ; R0 = Dirección(Dato32b)
        STR     R1, [R0]                        ; [Dato32b] = R1

        LDR     R0, SRAM                        ; R0 = SRAM
        LDR     R1, [R0]                        ; R1 = [SRAM]


halt    B       halt

        .end                                    ; Final del programa fuente
