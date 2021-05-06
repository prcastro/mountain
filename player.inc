    IF !DEF(PLAYER_INC)
PLAYER_INC SET 1

SECTION "player routines", ROM0


InitPlayerYPos:
    ld a, PLAYER_START_Y
    ld [_PLAYER_Y], a
    ret

InitPlayerSprite:
    ld a, 54
    ld [_S_PLAYER_TL_X], a

    ld a, 4
    ld [_S_PLAYER_TL_TILE], a

    ld a, 62
    ld [_S_PLAYER_TR_X], a

    ld a, 5
    ld [_S_PLAYER_TR_TILE], a

    ld a, 54
    ld [_S_PLAYER_BL_X], a

    ld a, 7
    ld [_S_PLAYER_BL_TILE], a
    
    ld a, 62
    ld [_S_PLAYER_BR_X], a

    ld a, 6
    ld [_S_PLAYER_BR_TILE], a

	ret

SetPlayerSpriteY:
    ld a, [_PLAYER_Y]
    ld b, a
    add a, 8
    ld c, a
    ; b = Top Y, c = Bottom Y

    ld a, b
    ld [_S_PLAYER_TL_Y], a
    ld [_S_PLAYER_TR_Y], a

    ld a, c
    ld [_S_PLAYER_BL_Y], a
    ld [_S_PLAYER_BR_Y], a

	ret

MovePlayer:
    call ReadPad
    call CheckImpulse
    call ApplyGravity
    call ApplyBreak
    call CapPlayerVelocity
    call ApplyPlayerVelocity
    call MovePlayerPos
    call SetPlayerSpriteY
    ret

CheckImpulse:
    ld a, [_PAD]
    and %00000001
    ret z

    ld a, [_IS_PRESSING_A]
    cp 1
    ret z

    call ApplyImpulse
    ret

ApplyImpulse:
    ld a, -PLAYER_IMPULSE_VEL
    ld [_PLAYER_VEL_Y], a
    ret

ApplyBreak:
    ; TODO: remove this
    ; Reset velocity with B pressed
    ld a, [_PAD]
    and %00000010
    ret z

    xor a ; ld a, 0
    ld [_PLAYER_VEL_Y], a
    ret

ApplyGravity:
    ld hl, _PLAYER_VEL_Y
    inc [hl]
    ret

CapPlayerVelocity:
    ; Return if velocity is less than max
    ld a, [_PLAYER_VEL_Y]
    cp PLAYER_MAX_VEL
    ret c

    ; Return if velocity is less than zero
    ; above comparison doesn't work for negative velocities
    bit 7, a
    ret nz

    ld a, PLAYER_MAX_VEL
    ld [_PLAYER_VEL_Y], a
    ret

ApplyPlayerVelocity:
    ld a, [_PLAYER_VEL_Y]
    ld b, a
    ld a, [_PLAYER_Y]
    add b
    ld [_PLAYER_Y], a
    ret

MovePlayerPos:
    ld a, [_PAD]
    and %10000000
    call nz, MoveDown

    ld a, [_PAD]
    and %01000000
    call nz, MoveUp

    ret

MoveDown:
    ld a, [_PLAYER_Y]
    inc a
    ld [_PLAYER_Y], a
    ret

MoveUp:
    ld a, [_PLAYER_Y]
    dec a
    ld [_PLAYER_Y], a
    ret

SetPlayerInactive:
    ld a, 0
    ld [_PLAYER_ACTIVE], a
    ret

SetPlayerActive:
    ld a, 1
    ld [_PLAYER_ACTIVE], a
    ret

AnimatePlayerSprite:
    ld a, [_ANIM_COUNTER]
    cp 19
    ret nz
    
    ld a, [_S_PLAYER_TL_TILE]
    cp 4
    jp z, .squish

    ld a, 4
    ld [_S_PLAYER_TL_TILE], a
    ld a, 5
    ld [_S_PLAYER_TR_TILE], a
    ld a, 7
    ld [_S_PLAYER_BL_TILE], a
    ld a, 6
    ld [_S_PLAYER_BR_TILE], a
    ret

.squish
    ld a, 8
    ld [_S_PLAYER_TL_TILE], a
    ld a, 9
    ld [_S_PLAYER_TR_TILE], a
    ld a, 11
    ld [_S_PLAYER_BL_TILE], a
    ld a, 10
    ld [_S_PLAYER_BR_TILE], a
    ret

ActivatePlayer:
    call ReadPad

    ld a, [_PAD]
    and %00000001
    ret z

    ld a, [_IS_PRESSING_A]
    cp 1
    ret z

    call SetPlayerActive
    call ApplyImpulse ; Set the first impulse as soon as you activate the player
    ret

ResetPlayerVelocity:
    xor a
    ld [_PLAYER_VEL_Y], a
    ret

    ENDC ;PLAYER_INC