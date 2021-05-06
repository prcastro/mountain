    IF !DEF(GAME_INC)
GAME_INC SET 1

INCLUDE "player.inc"
INCLUDE "obstacles.inc"

SECTION "game routines", ROM0

LoadGame:
	call LoadBackground
	call LoadObjects
    call SetPlayerInactive
    call ResetAnimCounter
    call ResetPlayerVelocity
	ret

LoadBackground:
	call LoadBackgroundTiles
	call LoadBackgroundMap
	call SetBackgroundPalette
	call ResetWindowPosition
	ret

LoadBackgroundTiles:
	ld hl, _VRAM9000
    ld de, TileSet
    ld bc, TileSetEnd - TileSet
    call MemCpy
	ret

LoadBackgroundMap:
    ld hl, _SCRN0
    ld de, TileMap
    ld bc, TileMapEnd - TileMap
    call MemCpy
	ret

SetBackgroundPalette:
	ld a, %11100100 ; 3 B, 2 LG, 1 DG, 0 W
    ld [rBGP], a
	ret

LoadObjects:
    call ClearSpriteAttributes
	call LoadSpriteTiles
	call InitPlayerSprite
    call InitPlayerYPos
    call SetPlayerSpriteY
    call InitObstacleSprites
    call SetObjectPalette
    call StartDMA
	ret

LoadSpriteTiles:
	ld hl, _VRAM
    ld de, Sprites
    ld bc, SpritesEnd - Sprites
    call MemCpy
	ret

SetObjectPalette:
	; Change OBJ 0 palette
    ld a, %11010000 ; 3 B, 2 LG, 1 W 
    ld [rOBP0], a 

    ; Change OBJ 1 palette
    ld a, %11100100 ; 3 B, 2 DG, 1 LG 
    ld [rOBP1], a 
	ret

ResetAnimCounter:
    xor a
    ld [_ANIM_COUNTER], a
    ret

UpdateGame:
    ld a, [_PLAYER_ACTIVE]
    cp 1
    jp z, .updateGameActive 
.updateGameInactive:
    call MoveBackground
    call AnimatePlayerSprite
    call ActivatePlayer
    call StartDMA
    call UpdatePressingA
    ret
.updateGameActive:
	call MoveBackground
    call AnimatePlayerSprite
	call MovePlayer
    call MoveObstacles
    call StartDMA
    call CheckCollisions
    call UpdatePressingA
	ret

MoveBackground:
	ld	a, [rSCX]
	inc	a
	ld	[rSCX], a
	ret

CheckCollisions:
    call CheckPipeCollision
    call CheckCeilingCollision
    call CheckFloorCollision
    ret

CheckCeilingCollision:
    ld a, [_S_PLAYER_TL_Y]
    cp 16
    call c, SetGameOver
    ret

CheckFloorCollision:
    ld a, [_S_PLAYER_BL_Y]
    add 8
    cp 160
    call nc, SetGameOver
    ret

CheckPipeCollision:
    ; Check if player is to the right of the beggining of the obstacle
    ld a, [_OBSTACLE_X]
    ld b, a
    ld a, [_S_PLAYER_TR_X]
    add a, 8
    cp b
    ret c

    ; Check if player is to the left of the end of the obstacle
    ld a, [_OBSTACLE_X]
    add a, 16
    ld b, a
    ld a, [_S_PLAYER_TL_X]
    cp b
    ret nc

    ; We know the player is in between the pipes

    ld a, [_S_OBS_TL_Y]
    add a, 8
    ld b, a
    ld a, [_S_PLAYER_TL_Y]
    cp b
    jp nc, .checkBottom
    call SetGameOver
    ret

.checkBottom
    ld a, [_S_OBS_BL_Y]
    ld b, a
    ld a, [_S_PLAYER_BL_Y]
    add a, 8
    cp b
    call nc, SetGameOver
    ret


SECTION "TileSet", ROM0
TileSet:
INCBIN "tile.bin"
TileSetEnd:

SECTION "TileMap", ROM0
TileMap:
    INCBIN "map.bin"
TileMapEnd:

SECTION "Sprites", ROM0
Sprites:
    INCBIN "sprites.bin"
SpritesEnd:

    ENDC ;GAME_INC