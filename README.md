# Conway's Game of Life, in RGB
Original Website: [CS61C](https://inst.eecs.berkeley.edu/~cs61c/fa20/projects/proj1/)
## Personal Modification
This project is using `csh` for command execution, `build-essential`, `cgdb` for debuging, `valgrind` for memocheck. 
Also we have an open source library `imagemagick` for users can use it for converting `.ppm` file to `.png` file or `.gif` file.
For that students cannot use HIVE, I prepared `Dockerfile` for proper environment.
## Key Requirements (FROM ORIGINAL WEBSITE)
### Usage
Your program must be usable in the following way:

```
$ ./gameOfLife [file] [rule]
```
…where <font color="red">[file]</font> is a PPM ASCII file, and <font color="red">[rule]</font> is a hexadecimal encoding of the generalized Game of Life rules. If you do not receive the correct number of input arguments, you should print the following usage string:
```
$ ./gameOfLife
    usage: ./gameOfLife filename rule
    filename is an ASCII PPM file (type P3) with maximum value 255.
    rule is a hex number beginning with 0x; Life is 0x1808.
```
Otherwise, you may assume that the rule is a hexadecimal number between 0x00000 and 0x3FFFF, and that the input file exists and is valid.
### Making An Animation
Since the Game of Life is designed to run for many generations, we have provided a shell script that will run GameOfLife repeatedly over multiple generations. To use the script, run:
```
$ ./frames.csh [prefix of ppm file in testInputs] [rule in hex] [number of frames]
```
### debugging and check
`make gameoflife` will compile your code into the executable gameOfLife. This does not run any tests, though, so you will need to run them yourself, either directly, or through frames.csh. We have provided with the starter code the result of running GliderGuns with rule `0x1808` over 100 generations, but it is important to note that this test is not comprehensive (for example, it doesn’t check if your code works on the boundary); you will thus need to make your own tests to confirm that your code works. `make gameoflifememcheck` runs a quick memory check on gameoflife; for the exact commands run, you can open the Makefile with any text editor and see what lines of UNIX commands are being performed.
