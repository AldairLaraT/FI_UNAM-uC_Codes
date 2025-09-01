; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        26 de agosto de 2025
; 
; Tema 03:      Modos de direccionamiento y conjunto de instrucciones
; Código 06:    Instrucciones del procesador ARM Cortex-M4F | Acceso a memoria
; Descripción:  Uso de las instrucciones de acceso a memoria del ARM Cortex-M4F.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************

        .global main


; *************************************************************************************************
; Sección de código ejecutable
; ***********************************************

main:

    ; LDR (Load register)

        MOV   R0, #0x20000000                   ; R0 = 0x2000.0000

        LDR   R1, [R0]                          ; R1 = [R0]
        LDR   R2, [R0, #4]                      ; R2 = [R0+4]
        LDR   R3, [R0, #8]!                     ; R3 = [R0+8], R0 = R0+8
        LDR   R4, [R0], #4                      ; R4 = [R0], R4 =  R4+4

        MOV   R0, #0x20000000                   ; R0 = 0x2000.0000
        MOV   R1, #0                            ; R1 = 0
        MOV   R2, #0                            ; R2 = 0
        MOV   R3, #0                            ; R3 = 0
        MOV   R4, #0                            ; R4 = 0

        LDRB  R1, [R0], #1                      ; R1(7..0) = [R0], R0 = R0+1
        LDRB  R2, [R0], #1                      ; R2(7..0) = [R0], R0 = R0+1
        LDRSB R3, [R0], #1                      ; R3(7..0) = [R0] con extensión de signo a 32 bits, R0 = R0+1
        LDRSB R4, [R0], #1                      ; R4(7..0) = [R0] con extensión de signo a 32 bits, R0 = R0+1

        MOV   R0, #0x20000000                   ; R0 = 0x2000.0000

        LDRH  R1, [R0], #2                      ; R1(15..0) = [R0], R0 = R0+2
        LDRH  R2, [R0], #2                      ; R2(15..0) = [R0], R0 = R0+2
        LDRSH R3, [R0], #2                      ; R3(15..0) = [R0] con extensión de signo a 32 bits, R0 = R0+2
        LDRSH R4, [R0], #2                      ; R4(15..0) = [R0] con extensión de signo a 32 bits, R0 = R0+2

    ; STR (Store register)

        MOV   R0, #0x20000000                   ; R0 = 0x2000.0000
        MOV   R1, #0x11111111                   ; R1 = 0x1111.1111
        MOV   R2, #0x22222222                   ; R2 = 0x2222.2222
        MOV   R3, #0x33333333                   ; R3 = 0x3333.3333
        MOV   R4, #0x44444444                   ; R4 = 0x4444.4444

        STR   R1, [R0]                          ; [R0] = R1
        STR   R2, [R0, #4]                      ; [R0+4] = R2
        STR   R3, [R0, #8]!                     ; [R0+8] = R3, R0 = R0+8
        STR   R4, [R0], #4                      ; [R0] = R4, R0 = R0+4

        MOV   R0, #0x20000000                   ; R0 = 0x2000.0000

        STRB  R1, [R0], #1                      ; [R0] = Rn(7..0), R0 = R0+1
        STRB  R2, [R0], #1                      ; [R0] = Rn(7..0), R0 = R0+1
        STRH  R3, [R0], #2                      ; [R0] = Rn(15..0), R0 = R0+2
        STRH  R4, [R0], #2                      ; [R0] = Rn(15..0), R0 = R0+2

    ; LDM (Load multiple registers)

        MOV   R0, #0x20000000                   ; R0 = 0x2000.0000
        MOV   R1, #0                            ; R1 = 0
        MOV   R2, #0                            ; R2 = 0
        MOV   R3, #0                            ; R3 = 0
        MOV   R4, #0                            ; R4 = 0

        LDM   R0, {R1}                          ; R1 = [R0]
        LDM   R0, {R2-R6}                       ; Cargar los registros R2, R3, R4, R5 y R6 con el contenido de memoria, a partir de [R0]
        LDM   R0, {R7, R9}                      ; Cargar los registros R7 y R9 con el contenido de memoria, a partir de [R0]
        LDM   R0!, {R1-R7}                      ; Cargar los registros R2, R3, R4, R5 y R6 con el contenido de memoria, a partir de [R0]
                                                ; Actualizar R0 con la última dirección de memoria apuntada

        LDMIA R0, {R1-R3}                       ; Cargar los registros R1, R2 y R3 con el contenido de memoria, a partir de [R0] en orden ascendente
        LDMDB R0, {R4-R6}                       ; Cargar los registros R1, R2 y R3 con el contenido de memoria, a partir de [R0] en orden descendente

    ; STM (Load multiples registers)

        MOV   R0, #0x20000000                   ; R0 = 0x2000.0000
        MOV   R1, #0x11111111                   ; R1 = 0x1111.1111
        MOV   R2, #0x22222222                   ; R2 = 0x2222.2222
        MOV   R3, #0x33333333                   ; R3 = 0x3333.3333
        MOV   R4, #0x44444444                   ; R4 = 0x4444.4444
        MOV   R5, #0x55555555                   ; R5 = 0x5555.5555
        MOV   R6, #0x66666666                   ; R6 = 0x6666.6666

        STM   R0!, {R1-R3}                      ; Guardar el contenido de R1 y R3, a partir de la dirección [R0]
                                                ; Actualizar R0 con la última dirección de memoria apuntada

        STMIA R0, {R1-R3}                       ; Guardar el contenido de R1, R2 y R3 a partir de la dirección [R0], en orden ascendente
        STMDB R0, {R4-R6}                       ; Guardar el contenido de R4, R5 y R6 a partir de la dirección [R0], en orden descendente

    ; PUSH (Push registers onto stack)

        MOV   R1, #0x11111111                   ; R1 = 0x1111.1111
        MOV   R2, #0x22222222                   ; R2 = 0x2222.2222
        MOV   R3, #0x33333333                   ; R3 = 0x3333.3333
        MOV   R4, #0x44444444                   ; R4 = 0x4444.4444

        PUSH  {R1}                              ; Guardar R1 en la pila
        PUSH  {R1-R4}                           ; Guardar R1, R2, R3 y R4 en la pila
        PUSH  {R1, R3}                          ; Guardar R1 y R3 en la pila

    ; POP (Pop registers from stack)

        POP   {R5}                              ; Cargar en R5 el último valor de la pila
        POP   {R6-R9}                           ; Cargar en R6, R7, R8 y R9 los últimos valores de la pila
        POP   {R10, R12}                        ; Cargar en R10 y R12 los últimos valores de la pila

end     B     end
        .end
