## IMPORTANT NOTICE

The batch of Labrador boards produced in February 2020 were configured incorrectly at the factory and **will not be detected** by older releases of the Labrador software interface.

There is a fix in the latest version of the software (July 2020 Continuous release) that will automatically reconfigure the board upon connection.

Please update your software if you are having any issues!

# What is it?
The EspoTek Labrador is an open-source board that converts your PC, Raspberry Pi or Android Smartphone and into a full-featured electronics lab bench, complete with oscilloscope, signal generator and more.

More information available at:
http://espotek.com/labrador

This repo hosts all of the software and hardware that makes Labrador possible.

# Documentation and Software
To download binary (executable) versions of the software, go to:  
https://github.com/espotek/labrador/releases

The software is re-built automatically each time I make a change to the source code.  I recommend always downloading the latest win32, osx-dmg or linux-appimage version, depending on whether you're on Windows, macOS or Linux.  Raspberry Pi downloads are not currently automatically built, but an older version is provided at the link above.

For the documentation, please visit:  
https://github.com/espotek/labrador/wiki

# Additional Extras
There is also a 3D printable case available at Thingiverse, courtesy of SpaceBex:
https://www.thingiverse.com/thing:3188243

# Licence
All software files are licenced under GNU GPL v3.  https://www.gnu.org/licenses/gpl.html

All hardware files (schematics, PCB) are licenced under Creative Commons 4.0 (CC BY-NC-SA).  https://creativecommons.org/licenses/by-nc-sa/4.0/

# Building from Source
I use Qt Creator to build the software interface.  
https://www.qt.io/download-open-source/  
Open Desktop_Interface/Labrador.pro, then Clean All -> Run qmake -> Build All.  

If you're on Linux (including Raspberry Pi), then you can also build the software from source by cloning the repo, cd'ing to the Desktop_Interface directory then running:  
```
qmake
make
sudo make install
```
Then, to launch, just type `labrador` into the terminal.  

To build the AVR software, I use Atmel Studio 7.  Just load up the .atsln and push F7.  You can use `avr-gcc` if you don't want to install a full IDE.

The PCB files can be edited in KiCAD 4.0.

# Known bugs.
Most of the main bugs from the pre-launch period have now been fixed, including synchronisation issues.  
Please open an issue if you're aware of any in particular.

# Collaboration
If you want to make any suggestions, or better yet, submit some code, please do so here at GitHub.

Suggestions and feature requests belong on the "Issues" page.

For code submissions, look into Pull Requests.

If you just want to say hello and remind me that people are actually using my product (or if you just don't want to make a GitHub account), please email admin@espotek.com

Thanks to all.  
~Chris
