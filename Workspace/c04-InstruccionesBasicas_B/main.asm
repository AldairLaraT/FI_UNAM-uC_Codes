; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        24 de agosto de 2025
; 
; Tema 03:      Modos de direccionamiento y conjunto de instrucciones
; Código 04:    Instrucciones básicas del ARM Cortex-M | B
; Descripción:  Uso básico de la instrucción B.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************

        .global main


; *************************************************************************************************
; Sección de código ejecutable
; ***********************************************

main:

        MOV   R0, #0                            ; R0 = 0
        MOV   R1, #0x20000000                   ; R1 = 0x2000.0000
loop    LDR   R2, [R1], #4                      ; R2 = [R1]
                                                ; R1 = R1 + 4
        ADD   R0, R0, R2                        ; R0 = R0 + R2
        B     loop                              ; Saltar a la etiqueta loop

end     B     end
        .end
