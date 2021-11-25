# AG - ASCII Graphics
![Work In Progress](https://www.repostatus.org/badges/latest/wip.svg)

AG is a graphics library for consoles. It uses text as pixels
and bases colour values on how many pixels each character
takes.

# How to Setup
At the time of writing there is no pre-compiled linker files,
so just download the source and use the C files in src to
compile. In the future I'll setup library files and linker
files and such.

# Some Quick Documenation
### Setting up a window
Windows store pixel data and are what is shown in the console.
The following creates a 50x50 window at 0, 0 in the console, then 
kills the window. It's important to always kill a window to
prevent memory leaks.
```c
AGWindow window = agCreateWindow(0, 0, 50, 50);
agKillWindow(&window);
```

### Filling a window with a colour
This example will fill all the pixels in a window with a
colour value of 255.
```c
AGWindow window = agCreateWindow(0, 0, 50, 50);
agFillWindow(&window, 255);
agKillWindow(&window);
```

### Drawing a box
You can use the `agDrawBox` function to draw a box. Below
is an example of drawing a 8x3 box at 15, 15 that has a
colour value of 172.
```c
AGWindow window = agCreateWindow(0, 0, 50, 50);
agFillWindow(&window, 255);
agDrawBox(&window, 15, 15, 8, 3, 172);
agKillWindow(&window);
```

### Resizing and repositioning a window
The example below will resize the window from 50x50 to
35x35, then will reposition the window to 3, 6 in the
console.
```c
AGWindow window = agCreateWindow(0, 0, 50, 50);
agFillWindow(&window, 255);
agDrawBox(&window, 15, 15, 8, 3, 172);
agResizeWindow(&window, 35, 35);
agRepositionWindow(&window, 3, 6);
agKillWindow(&window);
```

**You can go to reference.md in the github root for a reference to all functions and library options**