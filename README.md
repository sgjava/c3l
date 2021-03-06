![C3L is the Commodore 128 CP/M C Library](images/title.png)

C3L is an ANSI C based API to access C128 specific features under CP/M.
Currently there are two abstraction layers. One for bitmap graphics and one for
character mode. This allows you to set the target (VIC or VDC) at runtime and use
the same functions. You only need to initialize which display chip you would like
to use or use both at the same time! This allows you to switch between VIC and VDC
with minimal effort. One cool feature of the VIC is that you can use the PETSCII
character ROM without having to worry about translation. Then if you change to
ASCII character set (CP/M default) there is only one simple change to make.

## Running demos
You can run the demo applications using the [disk images](https://github.com/sgjava/c3l/tree/master/disks).
* Unzip disk images
* `x128 -80col`
* In VICE configure drives
* Boot boot.d81 as device 8
* Attach c3l.d71 as device 9
* `b`:
* `vicdemo1`
* To list all the demos just `dir *.com`

## Set up development environment
You have a few ways to develop C code for C128 CP/M. You could use a cross
compiler, but I haven't found a way to do this with Hitech C 3.09. You could
use MyZ80 which is pretty darn fast or lastly you could use the VICE emulator.
Of course a real C128 system would work, but it will not be as productive as
the above mentioned methods. I've chosen the Eclipse/MyZ80/ctools method
because the flow is easier and build times are fast. You can use an Ubuntu VM
on VirtualBox to run under Linux/Windows/Mac if that works for you.

Build [VICE 3.3](http://vice-emu.sourceforge.net) on Ubuntu 18.04 x64.
* `sudo apt-get install build-essential byacc texi2html flex xa65 libreadline-dev libxaw7-dev libgtkmm-3.0-dev libpulse-dev`
* [Download](http://vice-emu.sourceforge.net/index.html#download) latest VICE source and extract.
* `cd vice-3.x` (use actual directory name)
* `./configure --enable-native-gtk3ui`
* `make`
* `sudo make install`
* `x128 -80col`

Build ctools:
* `git clone https://github.com/mist64/ctools`
* `cd ctools/src`
* `make`
* `make install`

Install [Eclipse](https://linuxize.com/post/how-to-install-the-latest-eclipse-ide-on-ubuntu-18-04/).

## Building
I'm using MyZ80, but you could use VICE or a real C128 with two drives.
Drive a: (1581) boots CP/M and has Hitech C, turbo editor, etc. Drive b: (1571)
contains the source that ctools can write to from your Eclipse src folder. The
[src](https://github.com/sgjava/c3l/tree/master/src) directory should be
considered the latest source. The [disk images](https://github.com/sgjava/c3l/tree/master/disks) may go out of date. To build
latest source from scratch on VICE or real C128:
* `x128 -80col`
* In VICE configure drives.
* Boot boot.d81 as device 8.
* Attach c3l.d71 as device 9.
* `b`:
* `era *.*`
* Detach device 9.
* Copy eclipse src to disk image. Change paths as needed.
* `~/ctools/bin/ctools ~/cpm/c3l.d71 p ~/eclipse-workspace/c3l/src/*.*`
* Attach c3l.d71 as device 9.
* Build c3l library.
* `submit lib`
* Alt+W (VICE warp mode) and answer prompts.
* Build demos.
* `submit compile`
* Alt+W (VICE warp mode).
* Run a demo.
* `vicdemo1`

If you skip the VICE stuff the build works on MyZ80, so it's cross platform from
a build perspective. MyZ80 has IMPORT and EXPORT commands to move source files
in and com files out to DOS which is also a Linux dir. Then just use ctools to
copy exported files to d71 image.

## Programming considerations
* No range checks are performed by most functions for performance sake. It is
incumbent upon the programmer to handle range checks. If you go out of range
and corrupt the program or OS memory it will most likely lock the machine.
* If the linker gives an "Undefined symbol" message for some symbol which you know
nothing about, it is possible that it is a library routine which was not found
during the library search due to incorrect library ordering.  In this case you
can search the library twice, e.g. for the standard library add a -LC to the end
of the C command line, or -LF for the floating library.  If you have specified
the library by name simply repeat its name.

## 8564/8566 VIC-IIe

![VIC](images/vic.png)

### Features
* Easy to configure VIC mode and memory layout
* 16 bit operations used where possible
* Character and bitmap mode options galore

### VIC memory management in CP/M
By default CP/M uses the VIC in MMU bank 0. This makes it difficult to access
from your CP/M program because the TPA is in bank 1. You could try to switch
banks like CP/M does, but this is very inefficient. Plus there is very little
free RAM in bank 0 that you could leverage. For C3L programs MMU bank 1 is
used and your program manages the VIC's memory.

You can use [allocVicMem()](https://github.com/sgjava/c3l/blob/be5396dbebb6b99084f3128bf62baf0d6e4c1427/src/vicmem.c#L19)
function to handle reserving memory for the VIC and
protect it from the running program. There are several configurations you can
use based on program size and VIC features you want to use. The simplest
configuration is to have your program and VIC memory in VIC bank 0 with
allocVicMem(0). With this configuration your program can reside from
0x100-0x2fff (almost 8K) and VIC memory is used starting at 0x3000 for character
set and 0x3800 for first screen. 0x1000-0x1fff is viewed by the VIC as
character ROM, but your program can use this memory, so it's not wasted.

allocVicMem() reserves a contiguous block of memory, thus allocVicMem(1) reserves
VIC bank 0 and VIC bank 1. VIC bank 3 is in the gray area since some of it is
reserved for CP/M. It's a good idea to allocate memory in bank 3 manually if
you have a large program. Remember to free() memory allocated by allocVicMem()
when you are done with the VIC.

### Return to CP/M mode
You should return to CP/M like nothing happened to the VIC. Color memory is restored
when you exit back to CP/M, so no code is required for that. To restore VIC for CP/M
use:

```
/* CPM default */
setVicChrMode(0, 0, 11, 3);
```

### Limitations
As I mentioned above 0x1000 is always read by the VIC as character ROM. Your
program will still use this memory normally. See [vicdemo1](https://github.com/sgjava/c3l/blob/master/src/vicdemo1.c)
for an example of using the ROM character set and the ASCII to PETSCII translation
of printVicPet.

### Character mode
I pretty much include everything you need to take control of character mode. I
also included PETSCII print functions, so you can use the ROM character set
at 0x1800. To keep things consistent I like to use the VDC's character set since
that's what you use in normal CP/M mode. You have to think a little different
using C3L since stdout is no longer visible. stdout still goes to the screen in
VIC bank 0, so that could be used for debugging, etc.

![VIC Demo 1](images/vicdemo1.png)

#### Features
* Use ROM character set at 0x1800 for the smallest memory footprint
* Fast print uses existing background color
* Fast color printing too
* PETSCII print functions convert from ASCII strings to PETSCII
* Custom character sets (can be copied from VDC or loaded from disk)
* Scroll any area of screen

### Bitmap graphics
I put some thought in how to share the same graphics functions across the VIC
and VDC (DRY principle). In an OOP language like Java you'd just use an
interface and create various implementations. Since I'm using ANSI C I had to
go with function pointers. This basically allows runtime polymorphism, thus I
can set the pixel routines, etc. at runtime and share the graphics functions.

I took a fresh look at implementing lines, rectangles, ellipses and circles.
setVicPix sets a pixel and clearVicPix clears a pixels. I added a parameter to
the graphics function to tell it to set or clear pixels. This is pretty cool,
since you can easily erase parts of your drawing using the same parameters except
the last one called setPix. Set it to 1 to set and 0 to clear pixels.

I optimized drawVicLine by detecting horizontal and vertical lines. drawVicLineH
can draw horizontal lines about 15x faster than Bresenham's algorithm based on
the bitmap memory layout and not having to read/write the pixel byte 8 times like
setVicPix and clearVicPix. drawVicLineV is optimized also, but not nearly as much
as drawVicLineH. You can still call drawVicLineH and drawVicLineV directly as
needed.

Enough bitmap graphic basics are provided to build applications that can graph
data, build out game screens, annotate with text that can have unique foreground
and background colors, etc.

![VIC Demo 3](images/vicdemo3.png)

#### Features
* Set and clear pixel functions
* Fast color and bitmap clearing
* All drawing functions can set or clear pixels
* Optimized line drawing uses accelerated horizontal and vertical line functions
before using Bresenham's algorithm
* Rectangle uses optimized horizontal and vertical line functions
* Square
* Bézier curve
* Ellipse
* Circle 
* Use existing character set to print to bitmap

## 6581/8580 SID
All the required functions are there to drive the SID.

### Features
* Clear SID
* Set master volume
* Set envelopes
* Set attack/release cycles
* Set pulse wave

## Keyboard scan and decode
The 8502 is responsible for most of the low-level I/O functions in CP/M mode and
the key scan routine is no exception. The whole idea behind C3L is to stay in
native Z80 mode as much as possible. This required writing low level key scan
and decode functions. [Keyboard Scan](https://sites.google.com/site/h2obsession/CBM/C128/keyboard-scan)
describes the concept. You end up with complex weirdness like the shift and
another key being on the scan row. The formula is 255-2^k1-2^k2, but I
calculated the values for the left and right shift using a lookup table, so no
calculation or bit fiddling is needed with these combinations.

[getKey](https://github.com/sgjava/c3l/blob/75755335d3a512c2b535649a376d46523dc98814/src/ciakey.c#L101)
allows you to read a single key row. This can be used for video games or other
time sensitive applications. In order to read standard and extended rows requires
18 out and 16 in operations. getKey only requires 2 out and 1 in operations. Plus
you do not need to decode the row saving that time as well.

[readVicLine](https://github.com/sgjava/c3l/blob/9ef99675463c5abf3eff9b8dda75937cb114f464/src/vicscr.c#L169)
is a simple line editor that takes advantage of screen memory to allow input
from the keyboard to be displayed and saved. Debounce logic makes sure the input
is smooth while still allowing for auto repeat. Only Backspace is allowed to
edit the line. Insert and delete can be added later. 

![Key Demo](images/keydemo.png)

### Features
* Read single row for performance
* Read all standard and extended rows at once
* Decode key press as ASCII including shifted characters
* Simple line editor for VIC
* CP/M key scan routine disabled for performance

### Limitations
* Shift lock not accessible in Z80 mode
* Polling frequency is important, so long running processes between key presses
may cause missed key strokes.

## DS12C887 Real Time Clock

I have been spoiled using NodeMCU (ESP8266) micro controllers. NodeMcu has a
NTP module for getting network time. I thought why not try a RTC on the C128?
[DS12C887 - Real Time Clock for C64/128](https://github.com/ytmytm/c64-ds12c887.git)
covers how it's done on a real C128.
[DS12887 RTC INTERFACING](http://what-when-how.com/8051-microcontroller/ds12887-rtc-interfacing)
gives you more detailed information on how to program the DS12C887.

### Features
* Read and write data register.
* Get time in hh:mm:ss format.
* Get date in mm/dd/yyyy format.

Under VICE Settings, I/O extensions, DS12C887 Real Time Clock click Enable
DS12C887 Real Time Clock, Start with running oscillator, Enable RTC Saving.
Make sure to save your configuration.

![VIC Demo 2](images/vicdemo2.png)
