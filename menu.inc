    IF !DEF(MENU_INC)
MENU_INC SET 1

SECTION "menu routines", ROM0

LoadMenu:
	call LoadMenuBackground
	call LoadMenuObjects
	call SetGameOver
	ret

LoadMenuBackground:
	call LoadMenuBackgroundTiles
	call LoadMenuBackgroundMap
	call SetMenuBackgroundPalette
	call ResetWindowPosition
	ret

LoadMenuBackgroundTiles:
	ld hl, _VRAM9000
    ld de, MenuTileSet
    ld bc, MenuTileSetEnd - MenuTileSet
    call MemCpy
	ret

LoadMenuBackgroundMap:
    ld hl, _SCRN0
    ld de, MenuTileMap
    ld bc, MenuTileMapEnd - MenuTileMap
    call MemCpy
	ret

LoadMenuObjects:
	call ClearSpriteAttributes
	call StartDMA
	ret

SetMenuBackgroundPalette:
	ld a, %11100100 ; 3 B, 2 LG, 1 DG, 0 W
    ld [rBGP], a
	ret

UpdateMenu:
	call ReadPad
	call StartGame
	call UpdatePressingA
	ret

StartGame:
	ld a, [_PAD]
	and %00000001 ; Press A
	ret z

	ld a, [_IS_PRESSING_A]
    cp 1
    ret z

	call SetPressingA
	call ResetGameOver
	ret

SECTION "MenuTileSet", ROM0
MenuTileSet:
INCBIN "menutile.bin"
MenuTileSetEnd:

SECTION "MenuTileMap", ROM0
MenuTileMap:
INCBIN "menumap.bin"
MenuTileMapEnd:

    ENDC ;MENU_INC