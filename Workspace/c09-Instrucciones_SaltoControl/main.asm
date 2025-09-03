; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        31 de agosto de 2025
; 
; Tema 03:      Modos de direccionamiento y conjunto de instrucciones
; Código 09:    Instrucciones del procesador ARM Cortex-M4F | Salto y control
; Descripción:  Uso de las instrucciones de salto y control del ARM Cortex-M4F.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************

        .global main


; *************************************************************************************************
; Sección de código ejecutable
; ***********************************************


; ***********************************************
; Subrutinas

twos_complement:
        MVN   R0, R0                            ; R0 = not R0
        ADD   R0, #1                            ; R0 = R0 + 1

        BX    LR                                ; Salto indirecto a LR (link register)


add_array:
        MOV   R3, #0                            ; R3 = 0
array   LDR   R0, [R1], #4                      ; R0 = [R1], R1 = R1 + 4
        ADD   R3, R0                            ; R3 = R3 + R0
        SUBS  R2, #1                            ; R2 = R2 - 1
        BNE   array                             ; Si (Z = 0), saltar a array

        BX    LR                                ; Salto indirecto a LR (link register)


; ***********************************************
; Código principal

main:

    ; B (Branch)
    ; BL (Branch with link)
    ; BX (Branch indirect)
    ; BLX (Branch indirect with link)

        MOV   R0, #50                           ; R0 = 50
        BL    twos_complement                   ; Salto con liga hacía twos_complement

        MOV   R0, #0                            ; R0 = 0
        MOV   R1, #0x20000000                   ; R1 = 0x2000.0000
        MOV   R2, #5                            ; R2 = 5
        BL    add_array                         ; Salto con liga a add_array

        MOV   R0, #0                            ; R0 = 0
        MOV   R2, #3                            ; R2 = 3

        MOV   R5, #0x0212                       ; R5 = 0x0212
        ORR   R5, #1                            ; R5 = 1
        BLX   R5                                ; Salto indirecto con liga a R5

    ; IT (If-Then)

        MOV   R0, #0x000F                       ; R0 = 0x000F

        ORRS  R1, R0, #0x00F0                   ; R1 = R0 or 0x00F0, actualizar APSR (Z = 0)

        IT    NE                                ; Bloque IT (Z = 0)
        ADDNE R1, #1                            ; Si (Z = 0), R1 = R1 + 1

        IT    EQ                                ; Bloque IT (Z = 1)
        ADDEQ R1, #2                            ; Si (Z = 1), R1 = R1 + 2

        ANDS  R2, R0, #0                        ; R2 = R0 and 0, actualizar APSR (Z = 1)

        ITT   EQ                                ; Bloque IT (Z = 1)
        ADDEQ R2, #1                            ; Si (Z = 1), R2 = R2 + 1
        ADDEQ R2, #2                            ; Si (Z = 1), R2 = R2 + 2

        ITTE  EQ                                ; Bloque IT (Z = 1)
        ADDEQ R2, #1                            ; Si (Z = 1), R2 = R2 + 1
        ADDEQ R2, #2                            ; Si (Z = 1), R2 = R2 + 2
        ADDNE R2, #3                            ; Si (Z != 1), R2 = R2 + 3

        ITETE EQ                                ; Bloque IT (Z = 1)
        ADDEQ R2, #1                            ; Si (Z = 1), R2 = R2 + 1
        ADDNE R2, #2                            ; Si (Z != 1), R2 = R2 + 2
        ADDEQ R2, #3                            ; Si (Z = 1), R2 = R2 + 3
        ADDNE R2, #4                            ; Si (Z != 1), R2 = R2 + 4

end     B     end
        .end
