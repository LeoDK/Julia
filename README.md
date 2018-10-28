# Julia sets
A handy CLI tool to generate beautiful Julia sets

# julia
Usage : ./julia x1 y1 x2 y2 Re(c) Im(c) width height limit save.
Use it to create a classic image of a Julia set, and save it if you want.

# evol
Usage : ./evol x1 y1 x2 y2 Re(c) Im(c) width height limit.
Use it to see which value of "limit" fits the most to your set.
The number of max iterations will take values from 1 to "limit".

# move
Usage : ./evol x1 y1 x2 y2 |c| arg(c) width height limit range_arg steps.
Make it move!
Choose an initial value of c (with "|c|" and "arg(c)") and change its argument with "range_arg".
There will "steps" produced frames.

# Note
All the executables were compiled on a Linux v4.9.0-6-amd64 machine.
To compile the source code, you need a standard C compiler (like gcc) and SDL v1.2.
