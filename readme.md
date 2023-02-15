# [alex-free.github.io](https://alex-free.github.io)

# Open95Keygen PSX

by Alex Free

Open95Keygen PSX is an open source Playstation 1 homebrew program that generates random valid Product Keys (both OEM and Retail types) for Microsoft's Windows 95 and Windows NT 4.0 operating systems. It is a port of my [Open95Keygen](https://alex-free.github.io/open95keygen) program to the PSX.

![open 95 keygen psx in pcsxr](https://alex-free.github.io/open95keygen-psx/o95kg_psx_pcsxr.png)

The Windows 95/NT 4.0 OEM/Retail Product Key algorithms have been reverse engineered by many people. Open95Keygen is a **[clean room design](https://en.wikipedia.org/wiki/Clean_room_design)** implementation not based on any existing software, it is written based on the specifications of the algorithm which is **inherently not copyright infringement**. I was inspired to write Open95Keygen after watching the YouTuber [stack smashing's](https://www.youtube.com/channel/UC3S8vxwRfqLBdIhgRlDRVzw) video [Why 111-1111111 is a valid Windows 95 key](https://www.youtube.com/watch?v=cwyH59nACzQ).

## Links

* [GitHub](https://github.com/alex-free/open95keygen-psx)
* [HomePage](https://alex-free.github.io/open95keygen-psx)

## Table Of Contents

*   [Downloads](#downloads)
*   [Usage](#usage)
*   [Install From Source](#install_source)
*   [License](#license)

## Downloads

### Version 1.0 (5/11/2021)

[Open 95 Keygen PSX for American Playstations](https://github.com/alex-free/open95keygen-psx/releases/download/1.0/open95keygen-psx_1.0_us.zip)

[Open 95 Keygen PSX for Japanese Playstations](https://github.com/alex-free/open95keygen-psx/releases/download/1.0/open95keygen-psx_1.0_jp.zip)

[Open 95 Keygen PSX .exe file](https://github.com/alex-free/open95keygen-psx/releases/download/1.0/open95keygen-psx_1.0_exe.zip)

[Source Code](https://github.com/alex-free/open95keygen-psx/archive/1.0.zip)

View [all releases](https://github.com/alex-free/open95keygen-psx/releases/).

## Usage

First, [download](#downloads) the right release for your console, or compile Open95Keygen PSX from [source](#install_source).

Burn and boot a CD-R on your PS1 or PS2 console using a method to start backup CD-Rs, or load the standalone .exe by other means.

Make sure a controller is connected, and simply press the cross button. Retail and OEM Product Keys will be displayed. You can press the cross button for even more keys as much as you want.

## Build From Source (Extremely outdated with current PSN00BSDK)

Open95Keygen PSX is made using [Lameguy64's](https://github.com/Lameguy64/) [PSn00bSDK](https://github.com/Lameguy64/PSn00bSDK) and [MKPSXISO](https://github.com/Lameguy64/mkpsxiso). This is the expected setup:

*   MKPSXISO somewhere in your `$PATH`.
*   MIPS-unknown-elf toolchain at `/usr/local/mips-unknown-elf`.
*   PSn00bSDK at `/usr/local/mips-unknown-elf/psn00bsdk`.
*   **(Optional)** the PCSX-R somewhere in your `$PATH`.

Next you need to place the file `LICENSEJ.DAT` (for building Japan bin+cue) in the same directory as the makefile to license the built images. These files can be obtained from the official PSX PSYQ SDK.

Make rules:

*   `make` - just build o95kg.exe.
*   `make jp-cd` - build o95kg.exe and create bin+cue files.
*   `make clean` - delete any files built with an above rule.
*   `make test` - Load your previously created bin+cue files with the PCSX-R emulator.

## License

Open95Keygen and Open95Keygen PSX are released under the 3-BSD license. For more info, see the file `license.txt` in each release.