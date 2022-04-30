# BACKTRACK
Backtrack algorithm in a header-only library implemented using C++ templates

Based on the work of Roger Labbe. https://github.com/rlabbe/backtracking

--------------------------------------------------

2022-04-30

problem=MapColoring, size=REDUCED, algorithm=brute force, checks=96

problem=MapColoring, size=REDUCED, algorithm=SMART, checks=18

problem=MapColoring, size=real, algorithm=brute force, checks=more than 4 x power(10,9)

problem=MapColoring, size=real, algorithm=SMART, checks=62003

problem=QueensPlacing, size=REDUCED, algorithm=brute force, checks=1380

problem=QueensPlacing, size=REDUCED, algorithm=SMART, checks=36

problem=QueensPlacing, size=real, algorithm=brute force, checks=more than 32 x power(10,6)

problem=QueensPlacing, size=real, algorithm=SMART, checks=2438


With this project you can see how the backtrack algorithm makes it possible to solve problems, which would take unbearably long time if we used brute force.

REDUCED and SMART are #define, so you can switch them off an on, and the same code to produce the above results.
