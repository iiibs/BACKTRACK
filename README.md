# BACKTRACK
Backtrack algorithm in a header-only library implemented using C++ templates

Based on the work of Roger Labbe. https://github.com/rlabbe/backtracking

2022-04-30

problem       size    algorithm     checks
------------- ------- ----------- --------
MapColoring   REDUCED brute force       96
MapColoring   REDUCED SMART             18
MapColoring   real    brute force  >4*10^9
MapColoring   real    SMART          62003
QueensPlacing REDUCED brute force     1380
QueensPlacing REDUCED SMART             36
QueensPlacing real    brute force >32*10^6
QueensPlacing real    SMART           2438

With this project you can see how the backtrack algorithm makes it possible to solve problems, which would take unbearably long time if we used brute force.

REDUCED and SMART are #define, so you can switch them off an on, and the same code to produce the above results.
