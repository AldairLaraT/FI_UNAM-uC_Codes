; -------------------------------------------------------------------------------------------------
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
;
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        26 de agosto de 2025
;
; Tema 03:      Modos de direccionamiento y conjunto de instrucciones
; Código 05:    Instrucciones del procesador ARM Cortex-M4F | Acceso a memoria
; Descripción:  Uso de las instrucciones de acceso a memoria del ARM Cortex-M4F.
;               NOTA: El código no inicializa el contenido de la memoria, por lo que es necesario
;                     utilizar la herramienta "Memory Browser" para observar el comportamiento de
;                     las instrucciones.
;
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; -------------------------------------------------------------------------------------------------

        .global main


; -------------------------------------------------------------------------------------------------
; Sección de código ejecutable
; -------------------------------------------------------------------------------------------------

main:

    ; --- LDR (Load register) -----------------

        MOV     R0, #0x20000000                 ; R0 = 0x2000_0000

        LDR     R1, [R0]                        ; R1 = [R0]
        LDR     R2, [R0, #4]                    ; R2 = [R0+4]
        LDR     R3, [R0, #8]!                   ; R3 = [R0+8], R0 = R0+8
        LDR     R4, [R0], #4                    ; R4 = [R0], R0 = R0+4

        MOV     R0, #0x20000000                 ; R0 = 0x2000_0000
        MOV     R1, #0                          ; R1 = 0
        MOV     R2, #0                          ; R2 = 0
        MOV     R3, #0                          ; R3 = 0
        MOV     R4, #0                          ; R4 = 0

        LDRB    R1, [R0], #1                    ; R1(7..0) = [R0], R0 = R0+1
        LDRB    R2, [R0], #1                    ; R2(7..0) = [R0], R0 = R0+1
        LDRSB   R3, [R0], #1                    ; R3(7..0) = [R0] con extensión de signo a 32 bits, R0 = R0+1
        LDRSB   R4, [R0], #1                    ; R4(7..0) = [R0] con extensión de signo a 32 bits, R0 = R0+1

        MOV     R0, #0x20000000                 ; R0 = 0x2000_0000

        LDRH    R1, [R0], #2                    ; R1(15..0) = [R0], R0 = R0+2
        LDRH    R2, [R0], #2                    ; R2(15..0) = [R0], R0 = R0+2
        LDRSH   R3, [R0], #2                    ; R3(15..0) = [R0] con extensión de signo a 32 bits, R0 = R0+2
        LDRSH   R4, [R0], #2                    ; R4(15..0) = [R0] con extensión de signo a 32 bits, R0 = R0+2


    ; --- STR (Store register) ----------------

        MOV     R0, #0x20000000                 ; R0 = 0x2000_0000
        MOV     R1, #0x11111111                 ; R1 = 0x1111_1111
        MOV     R2, #0x22222222                 ; R2 = 0x2222_2222
        MOV     R3, #0x33333333                 ; R3 = 0x3333_3333
        MOV     R4, #0x44444444                 ; R4 = 0x4444_4444

        STR     R1, [R0]                        ; [R0] = R1
        STR     R2, [R0, #4]                    ; [R0+4] = R2
        STR     R3, [R0, #8]!                   ; [R0+8] = R3, R0 = R0+8
        STR     R4, [R0], #4                    ; [R0] = R4, R0 = R0+4

        MOV     R0, #0x20000000                 ; R0 = 0x2000_0000

        STRB    R1, [R0], #1                    ; [R0] = Rn(7..0), R0 = R0+1
        STRB    R2, [R0], #1                    ; [R0] = Rn(7..0), R0 = R0+1
        STRH    R3, [R0], #2                    ; [R0] = Rn(15..0), R0 = R0+2
        STRH    R4, [R0], #2                    ; [R0] = Rn(15..0), R0 = R0+2


    ; --- LDM (Load multiple registers) -------

        MOV     R0, #0x20000000                 ; R0 = 0x2000_0000
        MOV     R1, #0                          ; R1 = 0
        MOV     R2, #0                          ; R2 = 0
        MOV     R3, #0                          ; R3 = 0
        MOV     R4, #0                          ; R4 = 0

        LDM     R0, {R1}                        ; R1 = [R0]
        LDM     R0, {R2-R6}                     ; Cargar R2-R6 desde direcciones consecutivas a partir de [R0]
        LDM     R0, {R7, R9}                    ; Cargar R7 y R9 desde direcciones consecutivas a partir de [R0]
        LDM     R0!, {R1-R7}                    ; Cargar R1-R7 desde direcciones consecutivas a partir de [R0]
                                                ; Actualizar R0 con la dirección resultante

        LDMIA   R0, {R1-R3}                     ; Cargar R1-R3 desde direcciones consecutivas a partir de [R0] (orden ascendente)
        LDMDB   R0, {R4-R6}                     ; Cargar R4-R6 desde direcciones consecutivas a partir de [R0] (orden descendente)


    ; --- STM (Store multiple registers) ------

        MOV     R0, #0x20000000                 ; R0 = 0x2000_0000
        MOV     R1, #0x11111111                 ; R1 = 0x1111_1111
        MOV     R2, #0x22222222                 ; R2 = 0x2222_2222
        MOV     R3, #0x33333333                 ; R3 = 0x3333_3333
        MOV     R4, #0x44444444                 ; R4 = 0x4444_4444
        MOV     R5, #0x55555555                 ; R5 = 0x5555_5555
        MOV     R6, #0x66666666                 ; R6 = 0x6666_6666

        STM     R0!, {R1-R3}                    ; Guardar R1-R3 en direcciones consecutivas a partir de [R0]
                                                ; Actualizar R0 con la dirección resultante

        STMIA   R0, {R1-R3}                     ; Guardar R1-R3 en direcciones consecutivas a partir de [R0] (orden ascendente)
        STMDB   R0, {R4-R6}                     ; Guardar R4-R6 en direcciones consecutivas a partir de [R0] (orden descendente)


    ; --- PUSH (Push registers onto stack) ----

        MOV     R1, #0x11111111                 ; R1 = 0x1111_1111
        MOV     R2, #0x22222222                 ; R2 = 0x2222_2222
        MOV     R3, #0x33333333                 ; R3 = 0x3333_3333
        MOV     R4, #0x44444444                 ; R4 = 0x4444_4444

        PUSH    {R1}                            ; Guardar R1 en el stack
        PUSH    {R1-R4}                         ; Guardar R1-R4 en el stack
        PUSH    {R1, R3}                        ; Guardar R1 y R3 en el stack


    ; --- POP (Pop registers from stack) ------

        POP     {R5}                            ; Cargar R5 desde el stack
        POP     {R6-R9}                         ; Cargar R6-R9 desde el stack
        POP     {R10, R12}                      ; Cargar R10 y R12 desde el stack


halt    B       halt

        .end
