; -------------------------------------------------------------------------------------------------
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
;
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        31 de agosto de 2025
;
; Tema 03:      Modos de direccionamiento y conjunto de instrucciones
; Código 08:    Instrucciones del procesador ARM Cortex-M4F | Salto y control
; Descripción:  Uso de las instrucciones de salto y control del ARM Cortex-M4F.
;
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; -------------------------------------------------------------------------------------------------

        .global main


; -------------------------------------------------------------------------------------------------
; Sección de código ejecutable
; -------------------------------------------------------------------------------------------------


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


    ; -----------------------------------------
    ; Subrutina:    add_array
    ; Descripción:  Suma de los elementos de un arreglo.
    ; Parámetros:
    ;   R1  : Puntero al arreglo
    ;   R2  : Número de elementos del arreglo
    ; Registros reservados (variables locales):
    ;   R4  : Acumulador de la suma
    ;   R5  : Elemento del arreglo
    ; Retorno:
    ;   R0  : Suma de los elementos del arreglo
    ; -----------------------------------------

add_array:

    ; Inicializar variables locales
        MOV     R4, #0                          ; R4 = 0

    ; Suma de los elementos del arreglo
array   LDR     R5, [R1], #4                    ; R5 = [R1], R1 = R1 + 4
        ADD     R4, R5                          ; R4 = R4 + R5
        SUBS    R2, #1                          ; R2 = R2 - 1
        BNE     array                           ; Si (Z = 0), saltar a array
        MOV     R0, R4                          ; R0 = R4

    ; Retorno de subrutina
        BX      LR                              ; Salto indirecto a LR (link register)


; -------------------------------------------------------------------------------------------------
; Código principal

main:

    ; --- B (Branch) --------------------------
    ; --- BL (Branch with link) ---------------
    ; --- BX (Branch indirect) ----------------

        MOV     R0, #50                         ; R0 = 50
        BL      twos_complement                 ; Salto con liga a twos_complement

        MOV     R0, #0                          ; R0 = 0
        MOV     R1, #0x20000000                 ; R1 = 0x2000_0000
        MOV     R2, #5                          ; R2 = 5
        BL      add_array                       ; Salto con liga a add_array

        MOV     R0, #0                          ; R0 = 0
        MOV     R2, #3                          ; R2 = 3


    ; --- BLX (Branch indirect with link) -----

        MOV     R5, #0x0222                     ; R5 = 0x0222 (dirección de la primera instrucción
                                                ; del código principal)
        ORR     R5, #1                          ; R5[0] = 1
        BLX     R5                              ; Salto indirecto con liga a R5


    ; --- IT (If-Then) ------------------------

        MOV     R0, #0x000F                     ; R0 = 0x000F

        ORRS    R1, R0, #0x00F0                 ; R1 = R0 or 0x00F0, actualizar APSR (Z = 0)

        IT      NE                              ; Bloque IT (Z = 0)
        ADDNE   R1, #1                          ; TRUE (Z = 0), R1 = R1 + 1

        IT      EQ                              ; Bloque IT (Z = 1)
        ADDEQ   R1, #2                          ; TRUE (Z = 1), R1 = R1 + 2

        ANDS    R2, R0, #0                      ; R2 = R0 and 0, actualizar APSR (Z = 1)

        ITT     EQ                              ; Bloque IT (Z = 1)
        ADDEQ   R2, #1                          ; Si TRUE (Z = 1), R2 = R2 + 1
        ADDEQ   R2, #2                          ; Si TRUE (Z = 1), R2 = R2 + 2

        ITTE    EQ                              ; Bloque IT (Z = 1)
        ADDEQ   R2, #1                          ; Si TRUE (Z = 1), R2 = R2 + 1
        ADDEQ   R2, #2                          ; Si TRUE (Z = 1), R2 = R2 + 2
        ADDNE   R2, #3                          ; Si FALSE (Z != 1), R2 = R2 + 3

        ITETE   EQ                              ; Bloque IT (Z = 1)
        ADDEQ   R2, #1                          ; Si TRUE (Z = 1), R2 = R2 + 1
        ADDNE   R2, #2                          ; Si FALSE (Z != 1), R2 = R2 + 2
        ADDEQ   R2, #3                          ; Si TRUE (Z = 1), R2 = R2 + 3
        ADDNE   R2, #4                          ; Si FALSE (Z != 1), R2 = R2 + 4


halt    B       halt

        .end
