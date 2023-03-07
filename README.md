# What is it?
The [EspoTek Labrador](http://espotek.com/labrador) is an open-source board that turns your PC, Raspberry Pi or Android Smartphone and into a full-featured electronics lab bench, complete with oscilloscope, signal generator and more.

This repo hosts all of the software and hardware that makes Labrador possible.

# Tutorial
If you're new to Labrador or oscilloscopes in general, I strongly recommend checking out the fantastic tutorial series produced by Lief Koepsel:   
https://www.wellys.com/posts/courses_electronics/  
It features well-written, rich articles as well as video content that explains everything more clearly than I ever could!  

# Getting Started
To download binary (executable) versions of the software, go to:  
https://github.com/espotek/labrador/releases

For the documentation, please visit:  
https://github.com/espotek/labrador/wiki 

# Raspberry Pi Build
***Please note that the 32-bit version of Raspbian version 9 (Stretch) or later is required to install this software.***

To install Labrador on the Raspberry Pi, open a terminal and paste the following command:  
`wget -O /tmp/labrador_bootstrap_pi https://raw.githubusercontent.com/EspoTek/Labrador/master/labrador_bootstrap_pi && sudo chmod +x /tmp/labrador_bootstrap_pi && sudo /tmp/labrador_bootstrap_pi`

This will automatically download, compile and install the latest version of the Labrador software from source.  The whole process will take around 20-30 minutes, so don't forget to pack a snack!  
After running it, a desktop entry will appear for the Labrador software (under Education), and running the `labrador` command from the terminal will launch the software interface.

# Additional Extras
There are community contributed 3D printable cases available at Thingiverse, courtesy of SpaceBex and Bostwickenator:
* https://www.thingiverse.com/thing:3188243
* https://www.thingiverse.com/thing:4705392

# Building from Source
If you're looking to build from source but don't know where to start, Qt Creator is the easiest way to get your toes wet!  
https://www.qt.io/download-open-source/  
When installing, make sure you tick the box to install Qt 5.15 or later.

Once it's installed, open Desktop_Interface/Labrador.pro, then Clean All -> Run qmake -> Build All.

If you're on Linux (including Raspberry Pi), then you can also build the software from source by cloning the repo, cd'ing to the Desktop_Interface directory then running:  
```
qmake
make
sudo make install
```
Then, to launch, just type `labrador` into the terminal.

On Macos, additional steps may be required.  See issue https://github.com/EspoTek/Labrador/issues/238

To build the AVR software, I use Atmel Studio 7.  Just load up the .atsln and push F7.  You can use `avr-gcc` if you don't want to install a full IDE.

The PCB files can be edited in KiCAD 5.0 or later.

# Licence
All Dekstop software files are licenced under GNU GPL v3.  https://www.gnu.org/licenses/gpl.html

All Microcontroller software files, with the exception of those provided by Atmel, are licenced under the 3-Clause BSD License.  https://opensource.org/licenses/BSD-3-Clause

All hardware files (schematics, PCB) are licenced under Creative Commons 4.0 (CC BY-NC-SA).  https://creativecommons.org/licenses/by-nc-sa/4.0/

# Collaboration
If you want to submit a Pull Request, bug report or feature request please feel free to do so here at GitHub.  
If you just want to say hello and remind me that people are actually using my product (or if you just don't want to make a GitHub account), please email admin@espotek.com

Thanks to all.  
~Chris
