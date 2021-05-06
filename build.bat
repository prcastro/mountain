rgbasm -o build\mountain.o mountain.asm
rgblink -o build\mountain.gb build\mountain.o
rgbfix -v -p 0 build\mountain.gb
