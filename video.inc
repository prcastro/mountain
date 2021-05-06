    IF !DEF(VIDEO_INC)
VIDEO_INC SET 1

SECTION "video routines", ROM0

EnableVBlankInterrupt:
	ld	a, IEF_VBLANK
	ld	[rIE], a	; Set only Vblank interrupt flag
	ei	; enable interrupts, so that vblank triggers
	ret

WaitVBlank:
	halt	; halts cpu until interrupt triggers (vblank)
 	; by halting, we ensure that .loop only runs only each screen-refresh,
	; so only 60fps. That makes the background movement here manageable
	ret

TurnOffLCD:
	xor a         ; ld a, 0 ; We only need to reset a value with bit 7 reset, but 0 does the job
    ld [rLCDC], a ; We will have to write to LCDC again later, so it's not a bother, really.
	ret

TurnOnLCD:
    ld a, LCDCF_ON|LCDCF_BGON|LCDCF_OBJON
    ld [rLCDC], a
	ret

ClearSpriteAttributes:
	ld hl, _SPRITES
    ld bc, _SPRITES_END - _SPRITES
    call MemClear
	ret

ResetWindowPosition:
	xor a ; ld a, 0
    ld [rSCY], a
    ld [rSCX], a
	ret

    ENDC ;VIDEO_INC