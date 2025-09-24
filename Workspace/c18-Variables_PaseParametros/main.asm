; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        17 de septiembre de 2025
; 
; Tema 05:      Programación estructurada en lenguaje ensamblador
; Código 18:    Variables y pase de parámetros
; Descripción:  Declaración y uso de variables globales, locales y arreglos de datos.
;               Pase de parámetros siguiendo la convención AAPCS.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************

        .global main


; *************************************************************************************************
; Sección de datos
; ***********************************************

        .data

arrayA  .word 1, 3, 5, 7, 9                     ; Arreglo de 5 datos enteros (impares)
arrayB  .word 2, 4, 6, 8, 10                    ; Arreglo de 5 datos enteros (pares)
N       .word 5                                 ; Tamaño de los arreglos (variable global)
sumA    .word 0                                 ; Suma del arreglo A (variable global)
sumB    .word 0                                 ; Suma del arreglo B (variable global)


; *************************************************************************************************
; Sección de código ejecutable
; ***********************************************

        .text


; ***********************************************
; Apuntadores


; ***********************************************
; Subrutinas

    ; ********************   ********************
    ; Subrutina:    add_array
    ;
    ; Descripción:
    ;   Suma de los elementos de un arreglo.
    ;
    ; Parámetros:
    ;   R0  : Puntero a los elementos del arreglo
    ;   R1  : Tamaño del arreglo (N)
    ;
    ; Retorno:
    ;   R0  : Resultado de la suma del arreglo
    ;
    ; Registros reservados (variables locales):
    ;   R4  : Elemento del arreglo (array[i])
    ;   R5  : Suma acumulada (ACC)
    ;   R6  : Índice (i)
    ; ********************   ********************

add_array:
        ; PUSH  {R4, R5, R6}                      ; Preservar contexto (registros usados como variables locales)
        MOV   R5, #0                            ; ACC = 0
        MOV   R6, #0                            ; i = 0
array   LDR   R4, [R0], #4                      ; R4 = array[i], actualización del puntero
        ADD   R5, R4                            ; ACC = ACC + array[i]
        ADD   R6, #1                            ; i++
        CMP   R6, R1                            ; Comparar i con N
        BNE   array                             ; Repetir ciclo si (i < N)

        ; PUSH  {LR}                              ; Preservar contexto (LR)
        ; BL    delay                             ; Llamado a subrutina anidada delay
        ; POP   {LR}                              ; Restaurar contexto (LR)

        MOV   R0, R5                            ; Retorno en R0 (suma del arreglo)
        ; POP   {R4, R5, R6}                      ; Restaurar contexto (registros usados como variables locales)
        BX    LR                                ; Retorno de subrutina


    ; ********************   ********************
    ; Subrutina:    delay
    ;
    ; Descripción:
    ;   Retardo utilizado para ejemplificar el anidamiento de subrutinas.
    ;
    ; Parámetros:
    ;
    ; Retorno:
    ;
    ; Registros reservados (variables locales):
    ; ********************   ********************

delay:
        NOP
        NOP
        NOP
        NOP

        BX    LR                                ; Retorno de subrutina


; ***********************************************
; Código principal

main:
        ; Datos ficticios en R4, R5 y R6 (para verificar la preservación del contexto)
        MOV   R4, #0x44444444
        MOV   R5, #0x55555555
        MOV   R6, #0x66666666

        ; Parámetros para subrutina add_array
        MOVW  R0, arrayA
        MOVT  R0, arrayA                        ; R0 = [arrayA]
        MOVW  R1, N
        MOVT  R1, N                             ; R1 = [N]
        LDR   R1, [R1]                          ; R1 = N
        BL    add_array                         ; Llamado a subrutina add_array

        MOVW  R1, sumA
        MOVT  R1, sumA                          ; R1 = [sumA]
        STR   R0, [R1]                          ; [sumA] = Suma de los elementos arrayA

        ; Parámetros para subrutina add_array
        MOVW  R0, arrayB
        MOVT  R0, arrayB                        ; R0 = [arrayB]
        MOVW  R1, N
        MOVT  R1, N                             ; R1 = [N]
        LDR   R1, [R1]                          ; R1 = N
        BL    add_array                         ; Llamado a subrutina add_array

        MOVW  R1, sumB
        MOVT  R1, sumB                          ; R1 = [sumB]
        STR   R0, [R1]                          ; [sumB] = Suma de los elementos arrayB


end     B     end
        .end
