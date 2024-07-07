# **ASCII Renderer Project**

# Description
Created for my C++ course, this project allows you to draw muliple figures on an ASCII canvas.

# Usage
### Installation and execution
1. Clone the repository: `git clone https://github.com/JedrzejKwinta/ASCII-Renderer`.
2. Adjust the configuration file "cfg.txt" to your needs - see the [Configuration File](#Configuration-File) paragraph.
3. Execute the `make run` command in terminal in the repository folder.
4. Use the `make clean` command to clean unused files.
> [!WARNING]
> Do not delete or rename the configuration file!

# Configuration File
### Basic format of the file: 
```
[output_file.txt] [canvas_size] [shape1_name] [shape1_size] [shape1_distinctive_point] [shape1_symbol] [shape2_name] [shape2_size] [shape2_distinctive_point] [shape2_symbol] ...
```
### Format of each part:
1. Output file: choose the name you'd like to use - in an ASCII format, preferably ".txt".
2. Canvas size: specify the size for both of the canvas' dimensions in a `[dim1]x[dim2]` format.
3. Shape names: choose from "Rectangle", "Square" and "Circle".
4. Shape size: exactly as canvas size - `[dim1]x[dim2]`.
5. Shape distinctive point: specify a characteristic point of your shape determining its position on the canvas - the center of a circle and the top-left corner for rectangles and squares - in a `([x],[y])` format.
6. Shape symbol: specify a symbol that will be representing a certain figure (ideally not "|" and "=", for those are used as the border) - a symbol not belonging to any figure is a blank space.
> [!NOTE]
> Remember that any coordinates or dimensions lower than 0 won't show up on the canvas.

# Files in the repository
1. `art.cpp` - the main file containing the code.
2. `Makefile` - makefile for the project.
3. `cfg.txt` - the [configuration file](#configuration-file).
4. `output.txt` - an example output file.