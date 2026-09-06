; -------------------------------------------------------------------------------------------------
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
;
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        17 de septiembre de 2025
;
; Tema 05:      Programación estructurada en lenguaje ensamblador
; Código 17:    Variables y pase de parámetros
; Descripción:  Declaración y uso de variables globales, locales y arreglos de datos.
;               Pase de parámetros siguiendo la convención AAPCS.
;               NOTA: Por fines didácticos, las instrucciones necesarias para preservar el contexto
;               y llamado a subrutinas anidadas se encuentran comentadas en un inicio.
;
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; -------------------------------------------------------------------------------------------------

        .global main


; -------------------------------------------------------------------------------------------------
; Sección de datos
; -------------------------------------------------------------------------------------------------

        .data

array_A .word   1, 3, 5, 7, 9                   ; Arreglo de 5 datos enteros impares (variable global)
array_B .word   2, 4, 6, 8, 10                  ; Arreglo de 5 datos enteros pares (variable global)
N       .word   5                               ; Tamaño de los arreglos (variable global)
sum_A   .word   0                               ; Suma del arreglo A (variable global)
sum_B   .word   0                               ; Suma del arreglo B (variable global)


; -------------------------------------------------------------------------------------------------
; Sección de código ejecutable
; -------------------------------------------------------------------------------------------------

        .text


; -------------------------------------------------------------------------------------------------
; Apuntadores


; -------------------------------------------------------------------------------------------------
; Subrutinas

    ; -----------------------------------------
    ; Subrutina:    add_array
    ; Descripción:  Suma de los elementos de un arreglo.
    ; Parámetros:
    ;   R0  : Puntero a los elementos del arreglo
    ;   R1  : Tamaño del arreglo (N)
    ; Registros reservados (variables locales):
    ;   R4  : Elemento del arreglo (array[i])
    ;   R5  : Suma acumulada (ACC)
    ;   R6  : Índice (i)
    ; Retorno:
    ;   R0  : Resultado de la suma del arreglo
    ; -----------------------------------------

add_array:

    ; Preservar contexto (registros usados como variables locales)
        ; PUSH    {R4, R5, R6}

    ; Inicializar variables locales
        MOV     R5, #0                            ; ACC = 0
        MOV     R6, #0                            ; i = 0

    ; Suma de los elementos del arreglo
array   LDR     R4, [R0], #4                    ; R4 = array[i], actualización del puntero
        ADD     R5, R4                          ; ACC = ACC + array[i]
        ADD     R6, #1                          ; i++
        CMP     R6, R1                          ; Comparar i con N
        BNE     array                           ; Repetir ciclo si (i < N)

    ; Llamado a subrutina anidada
        ; PUSH    {LR}                            ; Preservar contexto (LR)
        ; BL      delay                           ; Llamado a subrutina delay
        ; POP     {LR}                            ; Restaurar contexto (LR)

    ; Retorno del resultado
        MOV     R0, R5                          ; Retorno en R0 (suma del arreglo)

    ; Restaurar contexto (registros usados como variables locales)
        ; POP     {R4, R5, R6}

    ; Retorno de subrutina
        BX      LR


    ; -----------------------------------------
    ; Subrutina:    delay
    ; Descripción:  Retardo utilizado para ejemplificar el anidamiento de subrutinas.
    ; -----------------------------------------

delay:

        NOP
        NOP
        NOP
        NOP

    ; Retorno de subrutina
        BX      LR


; -------------------------------------------------------------------------------------------------
; Código principal

main:

    ; Datos dummy en R4, R5 y R6 para ejemplificar la preservación del contexto
        MOV     R4, #0x44444444
        MOV     R5, #0x55555555
        MOV     R6, #0x66666666

    ; Parámetros para subrutina add_array
        MOVW    R0, array_A
        MOVT    R0, array_A                     ; R0 = puntero(array_A)
        MOVW    R1, N
        MOVT    R1, N                           ; R1 = puntero(N)
        LDR     R1, [R1]                        ; R1 = N

        BL      add_array                       ; Llamado a subrutina add_array

    ; Almacenamiento del resultado de la suma del arreglo A
        MOVW    R1, sum_A
        MOVT    R1, sum_A                       ; R1 = puntero(sum_A)
        STR     R0, [R1]                        ; [sum_A] = Suma de los elementos de array_A

    ; Parámetros para subrutina add_array
        MOVW    R0, array_B
        MOVT    R0, array_B                     ; R0 = puntero(array_B)
        MOVW    R1, N
        MOVT    R1, N                           ; R1 = puntero(N)
        LDR     R1, [R1]                        ; R1 = N

        BL      add_array                       ; Llamado a subrutina add_array

    ; Almacenamiento del resultado de la suma del arreglo B
        MOVW    R1, sum_B
        MOVT    R1, sum_B                       ; R1 = puntero(sum_B)
        STR     R0, [R1]                        ; [sum_B] = Suma de los elementos de array_B


halt    B       halt

        .end
