    IF !DEF(MEMORY_INC)
MEMORY_INC SET 1

SECTION "memory routines", ROM0

MemClear:
    ld a, 0
    ld [hli], a
    dec bc
    ld a, b
    or c
    jr nz, MemClear
    ret

MemCpy:
    ld a, [de] ; Grab 1 byte from the source
    ld [hli], a ; Place it at the destination, incrementing hl
    inc de ; Move to next byte
    dec bc ; Decrement count
    ld a, b ; Check if count is 0, since `dec bc` doesn't update flags
    or c
    jr nz, MemCpy
    ret

    ENDC ;MEMORY_INC