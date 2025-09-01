; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        31 de agosto de 2025
; 
; Tema 03:      Modos de direccionamiento y conjunto de instrucciones
; Código 08:    Instrucciones del procesador ARM Cortex-M4F | Multiplicación y división
; Descripción:  Uso de las instrucciones de multiplicación y división del ARM Cortex-M4F.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************

        .global main


; *************************************************************************************************
; Sección de código ejecutable
; ***********************************************

main:

        ;  Hexadecimal |     Decimal
        ; -------------+-----------------
        ;          1F4 |             500
        ;          3E8 |           1,000
        ;         1388 |           5,000
        ;         157C |           5,500
        ;    3B9A.CA00 |   1,000,000,000
        ;    FFFF.FFFF |   4,294,967,295
        ; 74.6A52.8800 | 500,000,000,000

        MOV   R0, #5                            ; R0 = 5
        MOV   R1, #500                          ; R1 = 500
        MOV   R2, #1000                         ; R2 = 1000
        MOVW  R3, #0xCA00
        MOVT  R3, #0x3B9A                       ; R3 = 1,000,000,000

    ; MUL (Multiply)

        MUL   R4, R0, R2                        ; R4 = R0 * R2
        MUL   R5, R1, R3                        ; R5 = R1 * R3

    ; MLA (Multiply with accumulate)

        MLA   R6, R0, R2, R1                    ; R6 = (R0 * R2) + R1

    ; MLS (Multiply and subtract)

        MLS   R7, R0, R2, R6                    ; R7 = R6 - (R0 * R2)

    ; UMULL (Unsigned multiply, 64-bit)

        UMULL R8, R9, R3, R1                    ; (R9, R8) = R3 * R1

    ; UDIV (Unsigned divide)

        ; Hexadecimal |     Decimal    |  Decimal
        ;             |  (no signado)  | (signado)
        ; ------------+----------------+-----------
        ;         1F4 |            500 | +   500
        ;        157C |          5,500 | + 5,500
        ;   FFFF.EA84 |  4,294,961,796 | - 5,500
        ;   FFFF.FE0C |  4,294,966,796 | -   500

        MOV   R0, #500                          ; R0 = 500
        MOV   R1, #5500                         ; R1 = 5,500
        MOVW  R2, #0xEA84
        MOVT  R2, #0xFFFF                       ; R2 = 4,294,961,796 | -5,500 (signed int)
        MOVW  R3, #0xFE0C
        MOVT  R3, #0xFFFF                       ; R3 = 4,294,966,796 | -500 (signed int)

        UDIV  R4, R1, R0                        ; R4 = R1 / R0
        UDIV  R5, R2, R0                        ; R5 = R2 / R0

    ; SDIV (Signed divide)

        SDIV  R6, R1, R0                        ; R6 = R1 / R0 (signada)
        SDIV  R7, R1, R3                        ; R7 = R1 / R3 (signada)
        SDIV  R8, R2, R0                        ; R8 = R2 / R0 (signada)
        SDIV  R9, R2, R3                        ; R9 = R2 / R3 (signada)

end     B     end
        .end
