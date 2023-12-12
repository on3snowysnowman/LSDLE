##############################
# LSDLE (Log's Simple DirectMedia Layer Engine) by Joel Height
##############################

LSDLE is a lightweight engine designed for rendering text and PNG images, as well as
handling basic user input. It includes various tools for creating simple menus with
modular variables and lists. For a detailed explanation, please refer to
documentation/Setup_and_Uses.txt.

##############################
## Table of Contents
##############################

1. Dependent Libraries
2. Installation
3. Usage
4. License
5. Contact


##############################
## 1. DEPENDENT LIBRARIES
##############################

This C++ engine relies on two important libraries:

- **nlohmann::json**: This library supports working with JSON data, extensively used
  for configuration and data serialization.

- **SDL2 (Simple DirectMedia Layer)**: SDL2 is essential for creating cross-platform
  applications, including graphical user interfaces, audio, and video. The engine
  utilizes SDL2 for graphics and user input handling. Ensure these libraries are
  properly installed and configured on your system before using the engine.


##############################
## 2. INSTALLATION
##############################

To use this C++ engine, follow these steps:

- Download the LSDLE Project to your system

- Ensure you have CMake installed on your computer. You can download it from
  [CMake's website](https://cmake.org/download)

- Open the "LSDLE_Path.txt" file inside the same directory as this file. 
  Then, type the path where you want the LSDLE to be installed to. Save the
  .txt file and close it. I would advise the path to your user's directory
  file, something like this : "C:/Users/{YourUserName}"

- Open the Command Prompt, and navigate to this directory (Where you downloaded
  LSDLE to)

- Run the following commands in order : 
  - "cmake -G "Ninja" -B build -S ."
  - "cmake --build build --target install"

- LSDLE is now installed on your system where you specified in the 
  LSDLE_path.txt file, and can be linked to by any of your projects. For an
  explanation on how to link to the LSDLE lib from your project, see:
  documenation/Setup_and_Uses.txt 


##############################
3. USAGE
##############################

The LSDLE can be used for a wide variety of programs or games. It provides the
basic foundation of rendering, input handling and menu simulation. See the
Documentation directory for an in-depth explanation of how to use the engine.


##############################

4. LICENSE
##############################

LSDLE is released under the MIT License.

The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

ATTRIBUTION: Users of this engine are required to provide a proper
attribution notice in any distributed or derivative works. Simply credit the
engine by including the following statement: "This engine is powered by
LSDLE".

MODIFICATIONS: Users who modify the engine must clearly mark those
modifications in any distributed versions of the engine, indicating what
changes have been made.

COMMERCIAL USE RESTRICTIONS: Commercial distribution of this engine as a
standalone product is prohibited. Users may only sell or distribute the
engine commercially if substantial modifications or value-added components
have been incorporated.

How to Apply the License:

To apply the MIT License to your project, you should:

 - Include a copy of the MIT License in your project's repository by creating
   a file named LICENSE and pasting the license text into it.

 - Make sure to include the MIT License notice in all relevant files and
   provide attribution as specified above.


##############################

5. CONTACT
##############################

email : on3snowysnowman@gmail.com

