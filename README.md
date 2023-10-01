# RenGen: summary
A game engine used for 2D games used as a .lib file. An example game of Pacman has been provided.

# Pros
An simple engine for simple 2D games. Easy use, provides plenty of flexibility and perfect for optimal memory management.

# Cons
The only compatible language is C++.

# Instructions
Download the latest release of this project and compile/run in visual studio on the correct platform. A folder should appear with as name the chosen platform (being either win32 or 64). In there, you can find Rengen.lib. Put that file wherever in your game's folder and add it to your project. To do so in Visual studio, go to your project's properties > Configuration properties > Linker > Input > Additional dependencies. Also, make sure your project knows where to find this .lib file. You can set this up in your project's properties > Configuration properties > Linker > General > Additional Library Directories. 
