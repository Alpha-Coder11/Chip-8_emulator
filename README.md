# Chip8 Interpreter

A lightweight and efficient Chip8 emulator built to run classic Chip8 programs and games. This project is perfect for understanding the fundamentals of emulation, low-level programming, and retro gaming.

## Table of Contents

1. [Introduction](#introduction)
2. [Getting Started](#getting-started)
3. [Usage](#usage)
4. [Supported Instructions](#supported-instructions)


## Introduction

The Chip8 is a simple, interpreted programming language that was used on early computers in the 1970s. Its simplicity makes it a great project for learning about emulation and the inner workings of classic systems.

This emulator replicates the behavior of the Chip8 system, allowing you to load and play ROMs for educational or entertainment purposes.

## Getting Started

### Prerequisites for Windows
- MinGW 32-GCC-G++ version 6.3.0-1
- MinGW32-Make, it is installed by installing mingw32-base package.
- SDL2 (Simple DirectMedia Layer) library for graphics and input handling. I am using version [SDL2-devel-2.30.11-mingw](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.11) . 
- ![alt text](images/mingw32.png)

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/Alpha-Coder11/Chip-8_emulator.git
   ```

2. Configure the build:

   ```
   Navigate to the Project Folder
   ```

3. Build the project:

   Type <b>mingw32-make</b> in Command Line and hit enter
   
   ![alt text](images/build.png)

   For Linux, we need to install sdl separately, and after that, we just type <b> make</b>

4. Download the ROM File 

    Go to [Zophar's Domain](https://www.zophar.net/pdroms/chip8/chip-8-games-pack.html)
    Download and Extract the ROMS.
    Copy the INVADERS to bin folder of our repo.

5. Run the emulator:

   ```bash
   Navigate to bin folder
   ```
   Type main.exe INVADERS shift load
   ![alt text](images/Invader_Screen.png)

   Alternatively, you can stay in the root folder and use <b>mingw32-make run</b>. It will build the code and run the INVADER automatically. If you want to change the game you want to play,
   you can just change the game in the bin directory and update <b>ROM</b> variable. <b>shift </b> and <b> load </b> are flags which enable the quirks in the interpreter, more detail on them is mentioned below.

## Usage

1. Place your Chip8 ROM files in the `bin` directory.
3. Use the keyboard to interact with the program. Default key mappings correspond to the Chip8 hex keypad:
   ```
   1 2 3 C       -->   1 2 3 4
   4 5 6 D       -->   Q W E R
   7 8 9 E       -->   A S D F
   A 0 B F       -->   Z X C V
   ```

## Supported Instructions

This emulator supports the entire Chip8 instruction set, including:

- Arithmetic operations
- Conditional and unconditional jumps
- Timer management
- Display and input handling

Refer to [Cowgod's Chip-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) for detailed information about the instruction set.

Flags: 
* shift - enable shift_quirk 
* load  - enable load_quirk

## Load_quirk and Shift_quirk

### Explanation of the flags

Load/Store quirks - Instructions 0xFX55 and 0xFX65 increments value of Index register but some CHIP-8 programs assume that they don't. Enabling this quirk causes I register to become unchanged after the instruction.

Shift quirks - Shift instructions 0x8XY6 and 0x8XYE originally shift register VY and store results in register VX. Some CHIP-8 programs incorrectly assume that the VX register is shifted by this instruction, and VY remains unmodified. Enabling this quirk causes VX to become shifted and VY remain untouched.


Refer to [Yet Another CHIP-8 Emulator](https://blog.khutchins.com/posts/chip-8-emulation/) and [Chromatophore-HP48](https://github.com/Chromatophore/HP48-Superchip/tree/master/investigations) for detailed information about the quirks.
### List of games needing those flags

Enabling ***load_quirk*** is recommended for:
* Astro Dodge [Revival Studios, 2008]
* Tic-Tac-Toe [David Winter]
* Stars [Sergey Naydenov, 2010]
* Connect 4 [David Winter]
* Hidden [David Winter, 1996]

Enabling ***shift_quirk*** is recommended for:
* BMP Viewer - Hello (C8 example) [Hap, 2005]
* Space Invaders [David Winter]
* Keypad Test [Hap, 2006]

Enabling both ***shift_quirk*** AND ***load_quirk*** is recommended for:
* Blinky [Hans Christian Egeberg, 1991]

## Contributing

Contributions are welcome! Feel free to fork the repository, submit issues, or create pull requests. 

### Notes to Self
- Two things I learned while building this project, one is forward declaration and the other is memset on 2D array. Current problem is invaders is not working properly with thi emulator version.


