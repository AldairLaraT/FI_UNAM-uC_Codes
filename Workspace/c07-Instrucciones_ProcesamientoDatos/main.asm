; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        26 de agosto de 2025
; 
; Tema 03:      Modos de direccionamiento y conjunto de instrucciones
; Código 07:    Instrucciones del procesador ARM Cortex-M4F | Procesamiento de datos
; Descripción:  Uso de las instrucciones de procesamiento de datos del ARM Cortex-M4F.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************


; *************************************************************************************************
; Sección de directivas
; ***********************************************

        .global main


; *************************************************************************************************
; Sección del código principal
; ***********************************************

main:

; ***********************************************
; Operaciones de transferencia de datos

    ; MOV (Move)

        MOV   R0, #0x20000000                   ; R0 = 0x2000.0000

    ; MVN (Move NOT)

        MVN   R1, #0x20000000                   ; R1 = not(0x2000.0000)

    ; MOVW (Move wide)

        MOVW  R2, #0x0010                       ; R2(15..0) = 0x0010

    ; MOVT (Move top)

        MOVT  R2, #0x2000                       ; R2(31..16) = 0x2000

        ; MOV   R3, #0x20000010
        MOV   R3, #0x00AB00AB                   ; R3 = 0x00AB.00AB
        MOV   R3, #0xAB00AB00                   ; R3 = 0xAB00.AB00
        MOV   R3, #0xABABABAB                   ; R3 = 0xABAB.ABAB

        MOVW  R4, #0x1234                       ; R4(15..0) = 0x1234
        MOVT  R4, #0x5678                       ; R4(31..16) = 0x5678

        MOVT  R5, #0x5678                       ; R5(31..16) = 0x5678
        MOVW  R5, #0x1234                       ; R5(15..0) = 0x1234, R5(31..16) = 0x0000

; ***********************************************
; Operaciones lógicas

        MOV   R0, #0x44444444                   ; R0 = 0x4444.4444
        MOV   R1, #0x77777777                   ; R1 = 0x7777.7777
        MOV   R2, #0x55555555                   ; R2 = 0x5555.5555
        MOV   R3, #0xAAAAAAAA                   ; R3 = 0xAAAA.AAAA
        MOV   R4, #0xFFFFFFFF                   ; R4 = 0xFFFF.FFFF

    ; AND (Logical AND)

        AND   R5, R2, #0                        ; R5 = R2 and 0
        ANDS  R5, R2, R4                        ; R5 = R2 and R4, actualizar APSR
        ANDS  R6, R2, #0                        ; R6 = R2 and 0, actualizar APSR

    ; ORR (Logical OR)

        ORR   R7, R0, #0x80000000               ; R7 = R0 or 0x8000.0000
        ORRS  R8, R0, #0x80000000               ; R8 = R0 or 0x8000.0000, actualizar APSR

    ; EOR (Exclusive OR)

        EOR   R9, R1, R4                        ; R9 = R1 xor R4

    ; ORN (Logical OR NOT)

        ORN   R10, R2, R1                       ; R10 = R2 or (not R1)

    ; BIC (Bit clear)

        BIC   R1, #0xFF                         ; Limpiar bits [7..0] de R1

; ***********************************************
; Operaciones de desplazamiento y rotación

        MOV   R0, #0xFF                         ; R0 = 0xFF
        MOV   R1, #0                            ; R1 = 0
        MOV   R2, #0                            ; R2 = 0
        MOV   R3, #0                            ; R3 = 0
        MOV   R4, #0                            ; R4 = 0
        MOV   R5, #0                            ; R5 = 0

    ; LSR (Logical shift right)

        LSR   R1, R0, #3                        ; R1 = R0 >> 3 (lógico)

    ; LSL (Logical shift left)

        LSL   R2, R0, #24                       ; R2 = R0 << 24 (lógico)

    ; ASR (Arithmetic shift right)

        ASR   R3, R0, #5                        ; R3 = R0 >> 5 (aritmético)
        ASR   R4, R2, #16                       ; R4 = R2 >> 16 (aritmético)

    ; ROR (Rotate right)

        ROR   R5, R0, #12                       ; R5 = R0 >> 12 (extendido)

    ; RRX (Rotate right with extend)

        RRX   R6, R0                            ; R6 = R0 >> 1 (rotación con extensión)
        RRX   R6, R6                            ; R6 = R6 >> 1 (rotación con extensión)
        RRX   R6, R6                            ; R6 = R6 >> 1 (rotación con extensión)

; ***********************************************
; Operaciones aritméticas

        MOV   R0, #0xFFFFFFFF                   ; R0 = 0xFFFF.FFFF
        MOV   R1, #1                            ; R1 = 1
        MOV   R2, #2                            ; R2 = 2
        MOV   R3, #10                           ; R3 = 10

    ; ADD (Add)

        ADD   R4, R1, R2                        ; R4 = R1 + R2
        ADDS  R4, R1, R2                        ; R4 = R1 + R2
        ADDS  R5, R0, R2                        ; R5 = R0 + R2, actualizar APSR

    ; ADC (Add with carry)

        ADC   R6, R1, R2                        ; R6 = R1 + R2  + C

    ; SUB (Subtract)

        SUB   R7, R3, R2                        ; R7 = R3 - R2
        SUBS  R8, R3, R2                        ; R8 = R3 - R2, actualizar APSR
        SUBS  R8, R2, R3                        ; R8 = R2 - R3, actualizar APSR

    ; SBC (Subtract with carry)

        SBC   R9, R3, R2                        ; R9 = R3 - R2, si C = 0 => R9 = R9 - 1

    ; CMP (Compare)

        MOV   R0, #50                           ; R0 = 50

        CMP   R0, #50                           ; actualizar APSR (R0 - 50)
        CMP   R0, #40                           ; actualizar APSR (R0 - 40)
        CMP   R0, #60                           ; actualizar APSR (R0 - 60)

end     B     end
        .end
