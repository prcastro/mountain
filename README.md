# Abigos' Mountain - Batata's Adventure

FlappyBird clone for the original Game Boy, fully written in assembly

![Mountain's Gameplay](img/mountain.gif)

## How to play

Download the latest version of the game (`mountain.gb`) from the [releases page](https://github.com/prcastro/mountain/releases) and open it on any Game Boy emulator.

### From source

You will need to [install RGBDS](https://rgbds.gbdev.io/install). On windows you can run `build.bat` from the repository root folder. On other platforms run:

```
rgbasm -o build/mountain.o mountain.asm
rgblink -o build/mountain.gb build/mountain.o
rgbfix -v -p 0 build/mountain.gb
```

Your rom will be available on `build/mountain.gb`. You can open it on any Game Boy emulator.
