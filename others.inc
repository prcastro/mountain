    IF !DEF(OTHERS_INC)
OTHERS_INC SET 1

SECTION "other routines", ROM0

TurnOffSound:
	xor a ; ld a, 0
	ld [rNR52], a ; Shut sound down
	ret

ReadPad:
	; we will read the dpad:
	ld a, %00100000	; bit 4-0, 5-1 bit (on dpad, no buttons)
	ld [rP1], a
 
	; now we read the status of the dpad, to avoid bouncing
	; We do several readings
	ld a, [rP1]
	ld a, [rP1]
	ld a, [rP1]
	ld a, [rP1]
 
	and	$0F			; only care about the bottom 4 bits.
	swap a			; lower and upper exchange. 
	ld b, a			; We keep dpad status in b
 
	; we go for the buttons
    ld a, %00010000    	; bit 4 to 1, bit 5 to 0 (enabled buttons, not dpad)
    ld [rP1], a
 
	; We read several times to avoid bouncing
    ld a, [rP1]
    ld a, [rP1]
    ld a, [rP1]
    ld a, [rP1]
 
	; we at A, the state of the buttons
    and $0F         ; only care about the bottom 4 bits.
	or b			; or make a to b, to "meter" in Part
					; A superior, dpad status.
 
	; we now have at A, the state of all, we complement and
	; store it in the variable
	cpl
	ld [_PAD], a
	ret

CopyDMAToHRAM:
    ld  de, StartDMA
    rst CopyData
    DB  $00,$0D
    DB  $F5, $3E, $C1, $EA, $46, $FF, $3E, $28, $3D, $20, $FD, $F1, $D9
    ret

UpdatePressingA:
    ld a, [_PAD]
    and %00000001
    jp z, .notPressing
    call SetPressingA
    ret
.notPressing
    call ResetPressingA
    ret

SetPressingA:
    ld a, 1
    ld [_IS_PRESSING_A], a
    ret

ResetPressingA:
    xor a ; ld a, 0
    ld [_IS_PRESSING_A], a
    ret

SetGameOver:
    ld a, 1
    ld [_GAME_OVER], a
    ret

ResetGameOver:
    xor a ; ld a, 0
    ld [_GAME_OVER], a
    ret

    ENDC ;OTHERS_INC