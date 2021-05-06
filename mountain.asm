INCLUDE "hardware.inc"
INCLUDE "constants.inc"
INCLUDE "header.inc"
INCLUDE "memory.inc"
INCLUDE "video.inc"
INCLUDE "others.inc"
INCLUDE "menu.inc"
INCLUDE "game.inc"

SECTION "Main", ROM0[$0151]

Main:
	call EnableVBlankInterrupt
	call TurnOffSound
	call CopyDMAToHRAM
	call ResetPressingA
	jp Menu

Menu:
	call TurnOffLCD
	call LoadMenu
	call TurnOnLCD
.menuLoop
	call WaitVBlank
	call UpdateMenu

	ld a, [_GAME_OVER]
	cp 0
	jp z, Game
	jp .menuLoop

Game:
	call TurnOffLCD
	call LoadGame
	call TurnOnLCD
.gameLoop
	call WaitVBlank 
	call UpdateGame

	; Jump to menu if we got a game over
	ld a, [_GAME_OVER]
	cp 0
	jp nz, Menu
	jp	.gameLoop