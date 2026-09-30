; ==============================================================================
; Practica 01: Semaforo en Ensamblador (AVR / ATmega328P)
; Practice 01: Traffic Light Controller in Assembly (AVR / ATmega328P)
;
; Descripcion / Description:
; [ES] Control de secuencia de dos semaforos vehiculares con parpadeo de luz verde,
;      transicion a amarillo y rojo usando puertos I/O y subrutinas de retardo.
; [EN] Dual traffic light sequence controller with flashing green light, yellow
;      transition, and red light using I/O ports and nested delay subroutines.
; ==============================================================================

; ------------------------------------------------------------------------------
; Configuracion de Puertos I/O / I/O Ports Configuration
; ------------------------------------------------------------------------------
                    LDI     R16, 0B00111111     ; [ES] Configurar pines 0-5 del Puerto B como salidas
                                                ; [EN] Set Port B pins 0-5 as outputs
                    OUT     DDRB, R16

                    LDI     R16, 0B11111111     ; [ES] Configurar Puerto D como salidas
                                                ; [EN] Set Port D as outputs
                    OUT     DDRD, R16

; ==============================================================================
; Ciclo Principal del Semaforo / Main Traffic Light Loop
; ==============================================================================
SEMAFORO:
    ; --------------------------------------------------------------------------
    ; Fase 1: Semaforo 1 en Verde, Semaforo 2 en Rojo (10 segundos)
    ; Phase 1: Traffic Light 1 Green, Traffic Light 2 Red (10 seconds)
    ; --------------------------------------------------------------------------
                    LDI     R16, 0B00001100     ; S1: Verde ON | S2: Rojo ON
                    OUT     PORTB, R16
                    CALL    RET_DIEZ            ; Retardo de 10 segundos / 10-second delay

    ; --------------------------------------------------------------------------
    ; Parpadeo de Luz Verde en Semaforo 1 / Flashing Green Light on Traffic Light 1
    ; --------------------------------------------------------------------------
                    LDI     R16, 0B00000100     ; S1: Verde OFF | S2: Rojo ON
                    OUT     PORTB, R16
                    CALL    RET_MEDIO           ; Retardo 0.5 seg / 0.5s delay

                    LDI     R16, 0B00001100     ; S1: Verde ON | S2: Rojo ON
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

                    LDI     R16, 0B00000100     ; S1: Verde OFF | S2: Rojo ON
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

                    LDI     R16, 0B00001100     ; S1: Verde ON | S2: Rojo ON
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

                    LDI     R16, 0B00000100     ; S1: Verde OFF | S2: Rojo ON
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

                    LDI     R16, 0B00001100     ; S1: Verde ON | S2: Rojo ON
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

                    LDI     R16, 0B00000100     ; S1: Verde OFF | S2: Rojo ON
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

    ; --------------------------------------------------------------------------
    ; Transicion a Amarillo en Semaforo 1 / Yellow Transition on Traffic Light 1
    ; --------------------------------------------------------------------------
                    LDI     R16, 0B00010100     ; S1: Amarillo ON | S2: Rojo ON
                    OUT     PORTB, R16
                    CALL    RET_TRES            ; Retardo de 3 segundos / 3-second delay

    ; --------------------------------------------------------------------------
    ; Fase 2: Semaforo 1 en Rojo, Semaforo 2 en Verde (10 segundos)
    ; Phase 2: Traffic Light 1 Red, Traffic Light 2 Green (10 seconds)
    ; --------------------------------------------------------------------------
                    LDI     R16, 0B00100001     ; S1: Rojo ON | S2: Verde ON
                    OUT     PORTB, R16
                    CALL    RET_DIEZ            ; Retardo de 10 segundos / 10-second delay

    ; --------------------------------------------------------------------------
    ; Parpadeo de Luz Verde en Semaforo 2 / Flashing Green Light on Traffic Light 2
    ; --------------------------------------------------------------------------
                    LDI     R16, 0B00100000     ; S1: Rojo ON | S2: Verde OFF
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

                    LDI     R16, 0B00100001     ; S1: Rojo ON | S2: Verde ON
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

                    LDI     R16, 0B00100000     ; S1: Rojo ON | S2: Verde OFF
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

                    LDI     R16, 0B00100001     ; S1: Rojo ON | S2: Verde ON
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

                    LDI     R16, 0B00100000     ; S1: Rojo ON | S2: Verde OFF
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

                    LDI     R16, 0B00100001     ; S1: Rojo ON | S2: Verde ON
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

                    LDI     R16, 0B00100000     ; S1: Rojo ON | S2: Verde OFF
                    OUT     PORTB, R16
                    CALL    RET_MEDIO

    ; --------------------------------------------------------------------------
    ; Transicion a Amarillo en Semaforo 2 / Yellow Transition on Traffic Light 2
    ; --------------------------------------------------------------------------
                    LDI     R16, 0B00100010     ; S1: Rojo ON | S2: Amarillo ON
                    OUT     PORTB, R16
                    CALL    RET_TRES            ; Retardo de 3 segundos / 3-second delay

                    RJMP    SEMAFORO            ; Repetir ciclo / Loop infinitely

; ==============================================================================
; Subrutinas de Retardo / Delay Subroutines
; ==============================================================================

; --- Retardo de 10 Segundos / 10 Seconds Delay ---
RET_DIEZ:
                    LDI     R17, 10             ; Contador exterior: 10 iteraciones de 1s
LOOP_1:             LDI     R18, 100
LOOP_2:             LDI     R19, 250
LOOP_3:             LDI     R20, 213
RETARDO:            DEC     R20
                    BRNE    RETARDO
                    DEC     R19
                    BRNE    LOOP_3
                    DEC     R18
                    BRNE    LOOP_2
                    DEC     R17
                    BRNE    LOOP_1
                    RET

; --- Retardo de Medio Segundo (500 ms) / 0.5 Second Delay ---
RET_MEDIO:
                    LDI     R21, 50             ; 50 iteraciones para medio segundo
LOOP_4:             LDI     R22, 250
LOOP_5:             LDI     R23, 213
LOOP_6:             DEC     R23
                    BRNE    LOOP_6
                    DEC     R22
                    BRNE    LOOP_5
                    DEC     R21
                    BRNE    LOOP_4
                    RET

; --- Retardo de Tres Segundos / 3 Seconds Delay ---
RET_TRES:
                    LDI     R24, 3              ; Contador exterior: 3 iteraciones de 1s
LOOP_7:             LDI     R25, 100
LOOP_8:             LDI     R26, 250
LOOP_9:             LDI     R27, 213
LOOP_10:            DEC     R27
                    BRNE    LOOP_10
                    DEC     R26
                    BRNE    LOOP_9
                    DEC     R25
                    BRNE    LOOP_8
                    DEC     R24
                    BRNE    LOOP_7
                    RET

; ==============================================================================
; Fin del Programa / End of Program
; ==============================================================================