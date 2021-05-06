    IF !DEF(OBSTACLES_INC)
OBSTACLES_INC SET 1

SECTION "obstacles routines", ROM0

InitObstacleSprites:
    call InitObstaclesXPos
    call InitObstaclesTiles
    call InitObstaclesAttributes
    call genObstaclesY
    call setObstaclesX
    ret

InitObstaclesXPos:
    ld a, OBSTACLE_START_X
    ld [_OBSTACLE_X], a
    ret

InitObstaclesTiles:
    ld a, 2
    ld [_S_OBS_BL_TILE], a

    ld a, 14
    ld [_S_OBS_TL_TILE], a
    
    ld a, 3
    ld [_S_OBS_BR_TILE], a

    ld a, 15
    ld [_S_OBS_TR_TILE], a
    
    ld a, 12
    ld [_S_OBS_LTILE], a
    ld [_S_OBS_LTILE + (8 * 1)], a
    ld [_S_OBS_LTILE + (8 * 2)], a
    ld [_S_OBS_LTILE + (8 * 3)], a
    ld [_S_OBS_LTILE + (8 * 4)], a
    ld [_S_OBS_LTILE + (8 * 5)], a
    ld [_S_OBS_LTILE + (8 * 6)], a
    ld [_S_OBS_LTILE + (8 * 7)], a
    ld [_S_OBS_LTILE + (8 * 8)], a

    ld a, 13
    ld [_S_OBS_RTILE], a
    ld [_S_OBS_RTILE + (8 * 1)], a
    ld [_S_OBS_RTILE + (8 * 2)], a
    ld [_S_OBS_RTILE + (8 * 3)], a
    ld [_S_OBS_RTILE + (8 * 4)], a
    ld [_S_OBS_RTILE + (8 * 5)], a
    ld [_S_OBS_RTILE + (8 * 6)], a
    ld [_S_OBS_RTILE + (8 * 7)], a
    ld [_S_OBS_RTILE + (8 * 8)], a
	ret

InitObstaclesAttributes:
    ld a, OAMF_PAL1
    ld [_S_OBS_BL_ATTRIBUTES], a
    ld [_S_OBS_TL_ATTRIBUTES], a
    ld [_S_OBS_BR_ATTRIBUTES], a
    ld [_S_OBS_TR_ATTRIBUTES], a
    ld [_S_OBS_LATTRIBUTES], a
    ld [_S_OBS_LATTRIBUTES + (8 * 1)], a
    ld [_S_OBS_LATTRIBUTES + (8 * 2)], a
    ld [_S_OBS_LATTRIBUTES + (8 * 3)], a
    ld [_S_OBS_LATTRIBUTES + (8 * 4)], a
    ld [_S_OBS_LATTRIBUTES + (8 * 5)], a
    ld [_S_OBS_LATTRIBUTES + (8 * 6)], a
    ld [_S_OBS_LATTRIBUTES + (8 * 7)], a
    ld [_S_OBS_LATTRIBUTES + (8 * 8)], a
    ld [_S_OBS_RATTRIBUTES], a
    ld [_S_OBS_RATTRIBUTES + (8 * 1)], a
    ld [_S_OBS_RATTRIBUTES + (8 * 2)], a
    ld [_S_OBS_RATTRIBUTES + (8 * 3)], a
    ld [_S_OBS_RATTRIBUTES + (8 * 4)], a
    ld [_S_OBS_RATTRIBUTES + (8 * 5)], a
    ld [_S_OBS_RATTRIBUTES + (8 * 6)], a
    ld [_S_OBS_RATTRIBUTES + (8 * 7)], a
    ld [_S_OBS_RATTRIBUTES + (8 * 8)], a
	ret

genObstaclesY:
    ld a, [rDIV]
    swap a
    ld hl, PipeTable
    ld l, a
    ld a, [hl]

    cp 0
    jp z, genObstaclesY8x1
    cp 1
    jp z, genObstaclesY7x2
    cp 2
    jp z, genObstaclesY6x3
    cp 3
    jp z, genObstaclesY5x4
    cp 4
    jp z, genObstaclesY4x5
    cp 5
    jp z, genObstaclesY3x6
    cp 6
    jp z, genObstaclesY2x7
    cp 7
    jp z, genObstaclesY1x8
    ret

setObstaclesX:
    ld a, [_OBSTACLE_X]
    ld b, a
    add a, 8
    ld c, a
    
    ld d, 11
    ; b = Left X, c = Right X, d = Total "height"

    ld hl, _S_OBS_TL_X
.moveObstacleSprite
    ld [hl], b ; Set left sprite X position to b
    call NextSprite
    ld [hl], c ; Set right sprite X position to c
    call NextSprite
    dec d
    jr nz, .moveObstacleSprite
	ret

NextSprite:
    ; Move hl to the next sprite X value
    ; This is how we do "add hl, 4"
    ld a, l
    add a, 4 ; Process the low 8 bits...
    ld l, a ; Store back
    ld a, h
    adc a, 0 ; Process the upper 8 bits, counting the carry that may have stemmed from the low 8 bits
    ld h, a
    ret

MoveObstacles:
    ld hl, _OBSTACLE_X
    dec [hl]
    call setObstaclesX
    call checkResetObstacles
    ret 

checkResetObstacles:
    ld hl, _OBSTACLE_X
    ld a, [hl]
    cp 248
    ret nz
    call genObstaclesY
    ret

genObstaclesY8x1:
    ; Put sprites on the top
    ld a, 16
    ld [_S_OBS_LY ], a
    ld [_S_OBS_RY], a

    ld a, 16 + (8 * 1)
    ld [_S_OBS_LY + (8 * 1)], a
    ld [_S_OBS_RY + (8 * 1)], a

    ld a, 16 + (8 * 2)
    ld [_S_OBS_LY + (8 * 2)], a
    ld [_S_OBS_RY + (8 * 2)], a

    ld a, 16 + (8 * 3)
    ld [_S_OBS_LY + (8 * 3)], a
    ld [_S_OBS_RY + (8 * 3)], a

    ld a, 16 + (8 * 4)
    ld [_S_OBS_LY + (8 * 4)], a
    ld [_S_OBS_RY + (8 * 4)], a

    ld a, 16 + (8 * 5)
    ld [_S_OBS_LY + (8 * 5)], a
    ld [_S_OBS_RY + (8 * 5)], a

    ld a, 16 + (8 * 6)
    ld [_S_OBS_LY + (8 * 6)], a
    ld [_S_OBS_RY + (8 * 6)], a

    ld a, 16 + (8 * 7)
    ld [_S_OBS_LY + (8 * 7)], a
    ld [_S_OBS_RY + (8 * 7)], a

    ld a, 16 + (8 * 8)
    ld [_S_OBS_TL_Y], a
    ld [_S_OBS_TR_Y], a

    ; Put sprites on the bottom
    
    ld a, 152
    ld [_S_OBS_LY  + (8 * 8)], a
    ld [_S_OBS_RY  + (8 * 8)], a

    ld a, 152 - (8 * 1)
    ld [_S_OBS_BL_Y], a
    ld [_S_OBS_BR_Y], a

	ret

genObstaclesY7x2:
    ; Put sprites on the top
    ld a, 16
    ld [_S_OBS_LY ], a
    ld [_S_OBS_RY], a

    ld a, 16 + (8 * 1)
    ld [_S_OBS_LY + (8 * 1)], a
    ld [_S_OBS_RY + (8 * 1)], a

    ld a, 16 + (8 * 2)
    ld [_S_OBS_LY + (8 * 2)], a
    ld [_S_OBS_RY + (8 * 2)], a

    ld a, 16 + (8 * 3)
    ld [_S_OBS_LY + (8 * 3)], a
    ld [_S_OBS_RY + (8 * 3)], a

    ld a, 16 + (8 * 4)
    ld [_S_OBS_LY + (8 * 4)], a
    ld [_S_OBS_RY + (8 * 4)], a

    ld a, 16 + (8 * 5)
    ld [_S_OBS_LY + (8 * 5)], a
    ld [_S_OBS_RY + (8 * 5)], a

    ld a, 16 + (8 * 6)
    ld [_S_OBS_LY + (8 * 6)], a
    ld [_S_OBS_RY + (8 * 6)], a

    ld a, 16 + (8 * 7)
    ld [_S_OBS_TL_Y], a
    ld [_S_OBS_TR_Y], a

    ; Put sprites on the bottom
    
    ld a, 152
    ld [_S_OBS_LY  + (8 * 8)], a
    ld [_S_OBS_RY  + (8 * 8)], a

    ld a, 152 - (8 * 1)
    ld [_S_OBS_LY + (8 * 7)], a
    ld [_S_OBS_RY + (8 * 7)], a

    ld a, 152 - (8 * 2)
    ld [_S_OBS_BL_Y], a
    ld [_S_OBS_BR_Y], a

	ret

genObstaclesY6x3:
    ; Put sprites on the top
    ld a, 16
    ld [_S_OBS_LY ], a
    ld [_S_OBS_RY], a

    ld a, 16 + (8 * 1)
    ld [_S_OBS_LY + (8 * 1)], a
    ld [_S_OBS_RY + (8 * 1)], a

    ld a, 16 + (8 * 2)
    ld [_S_OBS_LY + (8 * 2)], a
    ld [_S_OBS_RY + (8 * 2)], a

    ld a, 16 + (8 * 3)
    ld [_S_OBS_LY + (8 * 3)], a
    ld [_S_OBS_RY + (8 * 3)], a

    ld a, 16 + (8 * 4)
    ld [_S_OBS_LY + (8 * 4)], a
    ld [_S_OBS_RY + (8 * 4)], a

    ld a, 16 + (8 * 5)
    ld [_S_OBS_LY + (8 * 5)], a
    ld [_S_OBS_RY + (8 * 5)], a

    ld a, 16 + (8 * 6)
    ld [_S_OBS_TL_Y], a
    ld [_S_OBS_TR_Y], a

    ; Put sprites on the bottom
    
    ld a, 152
    ld [_S_OBS_LY  + (8 * 8)], a
    ld [_S_OBS_RY  + (8 * 8)], a

    ld a, 152 - (8 * 1)
    ld [_S_OBS_LY + (8 * 7)], a
    ld [_S_OBS_RY + (8 * 7)], a

    ld a, 152 - (8 * 2)
    ld [_S_OBS_LY + (8 * 6)], a
    ld [_S_OBS_RY + (8 * 6)], a

    ld a, 152 - (8 * 3)
    ld [_S_OBS_BL_Y], a
    ld [_S_OBS_BR_Y], a

	ret

genObstaclesY5x4:
    ; Put sprites on the top
    ld a, 16
    ld [_S_OBS_LY ], a
    ld [_S_OBS_RY], a

    ld a, 16 + (8 * 1)
    ld [_S_OBS_LY + (8 * 1)], a
    ld [_S_OBS_RY + (8 * 1)], a

    ld a, 16 + (8 * 2)
    ld [_S_OBS_LY + (8 * 2)], a
    ld [_S_OBS_RY + (8 * 2)], a

    ld a, 16 + (8 * 3)
    ld [_S_OBS_LY + (8 * 3)], a
    ld [_S_OBS_RY + (8 * 3)], a

    ld a, 16 + (8 * 4)
    ld [_S_OBS_LY + (8 * 4)], a
    ld [_S_OBS_RY + (8 * 4)], a

    ld a, 16 + (8 * 5)
    ld [_S_OBS_TL_Y], a
    ld [_S_OBS_TR_Y], a

    ; Put sprites on the bottom
    
    ld a, 152
    ld [_S_OBS_LY  + (8 * 8)], a
    ld [_S_OBS_RY  + (8 * 8)], a

    ld a, 152 - (8 * 1)
    ld [_S_OBS_LY + (8 * 7)], a
    ld [_S_OBS_RY + (8 * 7)], a

    ld a, 152 - (8 * 2)
    ld [_S_OBS_LY + (8 * 6)], a
    ld [_S_OBS_RY + (8 * 6)], a

    ld a, 152 - (8 * 3)
    ld [_S_OBS_LY + (8 * 5)], a
    ld [_S_OBS_RY + (8 * 5)], a

    ld a, 152 - (8 * 4)
    ld [_S_OBS_BL_Y], a
    ld [_S_OBS_BR_Y], a

	ret


genObstaclesY4x5:
    ; Put sprites on the top
    ld a, 16
    ld [_S_OBS_LY ], a
    ld [_S_OBS_RY], a

    ld a, 16 + (8 * 1)
    ld [_S_OBS_LY + (8 * 1)], a
    ld [_S_OBS_RY + (8 * 1)], a

    ld a, 16 + (8 * 2)
    ld [_S_OBS_LY + (8 * 2)], a
    ld [_S_OBS_RY + (8 * 2)], a

    ld a, 16 + (8 * 3)
    ld [_S_OBS_LY + (8 * 3)], a
    ld [_S_OBS_RY + (8 * 3)], a

    ld a, 16 + (8 * 4)
    ld [_S_OBS_TL_Y], a
    ld [_S_OBS_TR_Y], a

    ; Put sprites on the bottom
    
    ld a, 152
    ld [_S_OBS_LY  + (8 * 8)], a
    ld [_S_OBS_RY  + (8 * 8)], a

    ld a, 152 - (8 * 1)
    ld [_S_OBS_LY + (8 * 7)], a
    ld [_S_OBS_RY + (8 * 7)], a

    ld a, 152 - (8 * 2)
    ld [_S_OBS_LY + (8 * 6)], a
    ld [_S_OBS_RY + (8 * 6)], a

    ld a, 152 - (8 * 3)
    ld [_S_OBS_LY + (8 * 5)], a
    ld [_S_OBS_RY + (8 * 5)], a

    ld a, 152 - (8 * 4)
    ld [_S_OBS_LY + (8 * 4)], a
    ld [_S_OBS_RY + (8 * 4)], a

    ld a, 152 - (8 * 5)
    ld [_S_OBS_BL_Y], a
    ld [_S_OBS_BR_Y], a

	ret

genObstaclesY3x6:
    ; Put sprites on the top
    ld a, 16
    ld [_S_OBS_LY ], a
    ld [_S_OBS_RY], a

    ld a, 16 + (8 * 1)
    ld [_S_OBS_LY + (8 * 1)], a
    ld [_S_OBS_RY + (8 * 1)], a

    ld a, 16 + (8 * 2)
    ld [_S_OBS_LY + (8 * 2)], a
    ld [_S_OBS_RY + (8 * 2)], a

    ld a, 16 + (8 * 3)
    ld [_S_OBS_TL_Y], a
    ld [_S_OBS_TR_Y], a

    ; Put sprites on the bottom
    
    ld a, 152
    ld [_S_OBS_LY  + (8 * 8)], a
    ld [_S_OBS_RY  + (8 * 8)], a

    ld a, 152 - (8 * 1)
    ld [_S_OBS_LY + (8 * 7)], a
    ld [_S_OBS_RY + (8 * 7)], a

    ld a, 152 - (8 * 2)
    ld [_S_OBS_LY + (8 * 6)], a
    ld [_S_OBS_RY + (8 * 6)], a

    ld a, 152 - (8 * 3)
    ld [_S_OBS_LY + (8 * 5)], a
    ld [_S_OBS_RY + (8 * 5)], a

    ld a, 152 - (8 * 4)
    ld [_S_OBS_LY + (8 * 4)], a
    ld [_S_OBS_RY + (8 * 4)], a

    ld a, 152 - (8 * 5)
    ld [_S_OBS_LY + (8 * 3)], a
    ld [_S_OBS_RY + (8 * 3)], a

    ld a, 152 - (8 * 6)
    ld [_S_OBS_BL_Y], a
    ld [_S_OBS_BR_Y], a

	ret

genObstaclesY2x7:
    ; Put sprites on the top
    ld a, 16
    ld [_S_OBS_LY ], a
    ld [_S_OBS_RY], a

    ld a, 16 + (8 * 1)
    ld [_S_OBS_LY + (8 * 1)], a
    ld [_S_OBS_RY + (8 * 1)], a

    ld a, 16 + (8 * 2)
    ld [_S_OBS_TL_Y], a
    ld [_S_OBS_TR_Y], a

    ; Put sprites on the bottom
    
    ld a, 152
    ld [_S_OBS_LY  + (8 * 8)], a
    ld [_S_OBS_RY  + (8 * 8)], a

    ld a, 152 - (8 * 1)
    ld [_S_OBS_LY + (8 * 7)], a
    ld [_S_OBS_RY + (8 * 7)], a

    ld a, 152 - (8 * 2)
    ld [_S_OBS_LY + (8 * 6)], a
    ld [_S_OBS_RY + (8 * 6)], a

    ld a, 152 - (8 * 3)
    ld [_S_OBS_LY + (8 * 5)], a
    ld [_S_OBS_RY + (8 * 5)], a

    ld a, 152 - (8 * 4)
    ld [_S_OBS_LY + (8 * 4)], a
    ld [_S_OBS_RY + (8 * 4)], a

    ld a, 152 - (8 * 5)
    ld [_S_OBS_LY + (8 * 3)], a
    ld [_S_OBS_RY + (8 * 3)], a

    ld a, 152 - (8 * 6)
    ld [_S_OBS_LY + (8 * 2)], a
    ld [_S_OBS_RY + (8 * 2)], a

    ld a, 152 - (8 * 7)
    ld [_S_OBS_BL_Y], a
    ld [_S_OBS_BR_Y], a

	ret

genObstaclesY1x8:
    ; Put sprites on the top
    ld a, 16
    ld [_S_OBS_LY ], a
    ld [_S_OBS_RY], a

    ld a, 16 + (8 * 1)
    ld [_S_OBS_TL_Y], a
    ld [_S_OBS_TR_Y], a

    ; Put sprites on the bottom
    
    ld a, 152
    ld [_S_OBS_LY  + (8 * 8)], a
    ld [_S_OBS_RY  + (8 * 8)], a

    ld a, 152 - (8 * 1)
    ld [_S_OBS_LY + (8 * 7)], a
    ld [_S_OBS_RY + (8 * 7)], a

    ld a, 152 - (8 * 2)
    ld [_S_OBS_LY + (8 * 6)], a
    ld [_S_OBS_RY + (8 * 6)], a

    ld a, 152 - (8 * 3)
    ld [_S_OBS_LY + (8 * 5)], a
    ld [_S_OBS_RY + (8 * 5)], a

    ld a, 152 - (8 * 4)
    ld [_S_OBS_LY + (8 * 4)], a
    ld [_S_OBS_RY + (8 * 4)], a

    ld a, 152 - (8 * 5)
    ld [_S_OBS_LY + (8 * 3)], a
    ld [_S_OBS_RY + (8 * 3)], a

    ld a, 152 - (8 * 6)
    ld [_S_OBS_LY + (8 * 2)], a
    ld [_S_OBS_RY + (8 * 2)], a

    ld a, 152 - (8 * 7)
    ld [_S_OBS_LY + (8 * 1)], a
    ld [_S_OBS_RY + (8 * 1)], a

    ld a, 152 - (8 * 8)
    ld [_S_OBS_BL_Y], a
    ld [_S_OBS_BR_Y], a

	ret

SECTION "pipes_rand_table", ROMX[$6000]

PipeTable:
    DB 0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6
    
    ENDC ;OBSTACLES_INC