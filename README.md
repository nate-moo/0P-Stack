# Project 0P-Stack

This document is written in Markdown.  If you are not familiar with markdown and/or would like to view a more "human readable" version in VS Code, look for a button in the upper right corner that says "Open Preview to the Side" when hovered over.

**Be sure to read through the assignment prompt on Canvas before starting on this project!**

## To Compile/Run
1. `cmake . -B build` (on Windows native, use `cmake . -B build -G "MinGW Makefiles"` instead). *This step only needs to be done once for each project.*
2. `cd build`
3. `make stage#` (on Windows native, use `mingw32-make stage#` instead), replacing \# with the number 1, 2, or 3 for each respective stage.
4. `./run-stage#-tests` or `./run-stage#-main`

## Notes:
You do not need to modify the `stage1-tests/` or `stage2-3-tests/` folders.  While you are welcome to add your own tests, you will probably find it easier to do your testing using the provided `main-stage1.cpp` and `main-stage3.cpp`.  Note that you will be tested on the tests *as provided in the repo*, ignoring any edits you make.

