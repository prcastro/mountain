    IF !DEF(HEADER_INC)
HEADER_INC SET 1

; copy x-bytes to [de]
SECTION "Copy Data",ROM0[$28]
CopyData:
  ; pop return address off stack into hl
  pop hl
  push bc

  ; here we get the number of bytes to copy
  ; hl contains the address of the bytes following the "rst $28" call

  ; put first byte into b ($00 in this context)
  ld  a,[hli]
  ld  b,a

  ; put second byte into c ($0D in this context)
  ld  a,[hli]
  ld  c,a

  ; bc now contains $000D
  ; hl now points to the first byte of our assembled subroutine (which is $F5)
  ; begin copying data
.copyDataLoop

  ; load a byte of data into a
  ld  a,[hli]

  ; store the byte in de, our destination ($FF80 in this context)
  ld  [de],a

  ; go to the next destination byte, decrease counter
  inc de
  dec bc

  ; check if counter is zero, if not repeat loop
  ld  a,b
  or  c
  jr  nz,.copyDataLoop

  ; all done, return home
  pop bc
  jp  hl
  reti

SECTION "VBlank", ROM0[$0040]
VBlank:
  ld a, [_ANIM_COUNTER]
  inc a
  cp 20
  jr nz, .endVBlank
  xor a ; ld a, 0
.endVBlank
  ld [_ANIM_COUNTER], a
	reti

SECTION "ROM_entry_point", ROM0[$0100]	; ROM is given control from boot here
	nop
	jp	Main

REPT $150 - $104
    db 0
ENDR

    ENDC ;HEADER_INC