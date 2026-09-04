; -------------------------------------------------------------------------------------------------
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
;
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        26 de agosto de 2025
;
; Tema 03:      Modos de direccionamiento y conjunto de instrucciones
; Código 06:    Instrucciones del procesador ARM Cortex-M4F | Procesamiento de datos
; Descripción:  Uso de las instrucciones de procesamiento de datos del ARM Cortex-M4F.
;
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ---------------------------------------------

        .global main


; -------------------------------------------------------------------------------------------------
; Sección de código ejecutable

main:

    ; ---------------------------------------------------------------------------------------------
    ; Operaciones de transferencia de datos

    ; --- MOV (Move) --------------------------

        MOV     R0, #0x7777                     ; R0 = 0x7777
        MOV     R1, #0x20000000                 ; R1 = 0x2000_0000
        MOV     R2, R1                          ; R2 = R1


    ; --- MVN (Move NOT) ----------------------

        MVN     R3, #0x77777777                 ; R3 = not(0x7777_7777)
        MVN     R4, #0x20000000                 ; R4 = not(0x2000_0000)
        MVN     R5, R4                          ; R5 = not(R4)


    ; --- MOVW (Move wide) --------------------

        MOVW    R1, #0x0010                     ; R1(31..16) = 0x0000,      R1(15..0) = 0x0010


    ; --- MOVT (Move top) ---------------------

        MOVT    R1, #0x2000                     ; R1(31..16) = 0x2000

        ; MOV     R6, #0x20000010                 ; Dato no codificable por estar fuera de rango
        MOV     R6, #0x00AB00AB                 ; R6 = 0x00AB_00AB
        MOV     R6, #0xAB00AB00                 ; R6 = 0xAB00_AB00
        MOV     R6, #0xABABABAB                 ; R6 = 0xABAB_ABAB

        MOVW    R7, #0x1234                     ; R7(31..16) = 0x0000,      R7(15..0) = 0x1234
        MOVT    R7, #0x5678                     ; R7(31..16) = 0x5678

        MOVT    R8, #0x5678                     ; R8(31..16) = 0x5678
        MOVW    R8, #0x1234                     ; R8(31..16) = 0x0000,      R8(15..0) = 0x1234


    ; ---------------------------------------------------------------------------------------------
    ; Operaciones lógicas

        MOVS    R0, #0x44444444                 ; R0 = 0x4444_4444
        MOV     R1, #0x77777777                 ; R1 = 0x7777_7777
        MOV     R2, #0x55555555                 ; R2 = 0x5555_5555
        MOV     R3, #0xAAAAAAAA                 ; R3 = 0xAAAA_AAAA
        MOV     R4, #0xFFFFFFFF                 ; R4 = 0xFFFF_FFFF


    ; --- AND (Logical AND) -------------------

        AND     R5, R2, #0                      ; R5 = R2 and 0
        ANDS    R5, R2, #0                      ; R5 = R2 and 0, actualizar APSR
        ANDS    R6, R2, R4                      ; R6 = R2 and R4, actualizar APSR


    ; --- ORR (Logical OR) --------------------

        ORR     R7, R0, #0x80000000             ; R7 = R0 or 0x8000_0000
        ORRS    R8, R0, #0x80000000             ; R8 = R0 or 0x8000_0000, actualizar APSR


    ; --- EOR (Exclusive OR) ------------------

        EOR     R9, R1, #0x60                   ; R9 = R1 xor 0x60
        EOR     R10, R1, R4                     ; R10 = R1 xor R4


    ; --- ORN (Logical OR NOT) ----------------

        ORN     R11, R3, #0x30                  ; R11 = R3 or not(0x30)
        ORN     R12, R0, R1                     ; R12 = R0 or not(R1)


    ; --- BIC (Bit clear) ---------------------

        BIC     R1, #0x01                       ; R1 = R1 and not(0x01), limpiar bit 0 de R1
        BIC     R1, #0x02                       ; R1 = R1 and not(0x02), limpiar bit 1 de R1
        BIC     R1, #0xE0                       ; R1 = R1 and not(0xE0), limpiar bits (7..5) de R1


    ; ---------------------------------------------------------------------------------------------
    ; Operaciones de desplazamiento y rotación

        MOV     R0, #0xFF                       ; R0 = 0xFF
        MOV     R1, #800                        ; R1 = 800 (0x320)

        MVN     R2, R1
        ADD     R2, #1                          ; R2 = C2(R1) = -800 (0xFFFF_FCE0)

        MOV     R3, #5                          ; R3 = 5


    ; --- LSR (Logical shift right) -----------

        LSR     R4, R0, #3                      ; R4 = R0 >> 3 (lógico)
        LSR     R5, R0, R3                      ; R5 = R0 >> R3 (lógico)


    ; --- LSL (Logical shift left) ------------

        LSL     R6, R0, #24                     ; R6 = R0 << 24 (lógico)
        LSL     R7, R0, R3                      ; R7 = R0 << R3 (lógico)


    ; --- ASR (Arithmetic shift right) --------

        LSR     R8, R1, #5                      ; R8 = R1 >> 5 (lógico)
        ASR     R9, R1, #5                      ; R9 = R1 >> 5 con extensión de signo (aritmético)

        LSR     R10, R2, #5                     ; R10 = R2 >> 5 (lógico)
        ASR     R11, R2, #5                     ; R11 = R2 >> 5 con extensión de signo (aritmético)


    ; --- ROR (Rotate right) ------------------

        ROR     R12, R0, #12                    ; R12 = R0 >> 12 (rotación)
        ROR     R12, R12, R3                    ; R12 = R12 >> R3 (rotación)
        ROR     R12, R12, R3                    ; R12 = R12 >> R3 (rotación)


    ; --- RRX (Rotate right with extend) ------

        RRXS    R3, R3                          ; R3 = R3 >> 1 (rotación con extensión)
        RRXS    R3, R3                          ; R3 = R3 >> 1 (rotación con extensión)
        RRXS    R3, R3                          ; R3 = R3 >> 1 (rotación con extensión)
        RRXS    R3, R3                          ; R3 = R3 >> 1 (rotación con extensión)
        RRXS    R3, R3                          ; R3 = R3 >> 1 (rotación con extensión)


    ; ---------------------------------------------------------------------------------------------
    ; Operaciones aritméticas

        MOV     R0, #0xFFFFFFFF                 ; R0 = 0xFFFF_FFFF
        MOVW    R1, #0xFFFF
        MOVT    R1, #0x7FFF                     ; R1 = 0x7FFF_FFFF
        MOV     R2, #1                          ; R2 = 1, actualizar APSR
        MOV     R3, #2                          ; R3 = 2

        ; (R5, R4) = 150,000,000,000 (0x22_ECB2_5C00)
        MOVW    R4, #0x5C00
        MOVT    R4, #0xECB2                     ; R4 = 0xECB2_5C00
        MOVW    R5, #0x0022                     ; R5 = 0x0000_0022

        ; (R7, R6) = 50,000,000,000 (0xB_A43B_7400)
        MOVW    R6, #0x7400
        MOVT    R6, #0xA43B                     ; R6 = 0xA43B_7400
        MOVW    R7, #0x000B                     ; R7 = 0x0000_000B


    ; --- ADD (Add) ---------------------------

        ADD     R8, R2, #5                      ; R8 = R2 + 5

        ADD     R8, R1, R2                      ; R8 = R1 + R2
        ADDS    R8, R1, R2                      ; R8 = R1 + R2, actualizar APSR

        ADD     R9, R0, R2                      ; R9 = R0 + R2
        ADDS    R9, R0, R2                      ; R9 = R0 + R2, actualizar APSR

        ADD     R10, R0, R3                     ; R10 = R0 + R3
        ADDS    R10, R0, R3                     ; R10 = R0 + R3, actualizar APSR


    ; --- ADC (Add with carry) ----------------

        ; (R9, R8) = (R5, R4) + (R7, R6) = 150,000,000,000 + 50,000,000,000
        ;                                = 200,000,000,000 (0x2E_90ED_D000)
        ADDS    R8, R4, R6                      ; R8 = R4 + R6, actualizar APSR
        ADC     R9, R5, R7                      ; R9 = R5 + R7 + C


    ; --- SUB (Subtract) ----------------------

        SUB     R8, R0, #0x0F                   ; R8 = R0 - 0x0F

        SUB     R8, R3, R2                      ; R7 = R3 - R2
        SUBS    R8, R3, R2                      ; R8 = R3 - R2, actualizar APSR

        SUB     R8, R2, R3                      ; R8 = R2 - R3
        SUBS    R8, R2, R3                      ; R8 = R2 - R3, actualizar APSR


    ; --- SBC (Subtract with carry) -----------

        ; (R9, R8) = (R5, R4) - (R7, R6) = 150,000,000,000 - 50,000,000,000
        ;                                = 100,000,000,000 (0x17_4876_E800)
        SUBS    R8, R4, R6                      ; R8 = R4 - R6, actualizar APSR
        SBC     R9, R5, R7                      ; R9 = R5 - R7 - (1 - C)


    ; --- CMP (Compare) -----------------------

        MOV     R0, #50                         ; R0 = 50

        CMP     R0, #50                         ; Actualizar APSR (R0 - 50)
        CMP     R0, #40                         ; Actualizar APSR (R0 - 40)
        CMP     R0, #60                         ; Actualizar APSR (R0 - 60)


halt    B       halt

        .end
