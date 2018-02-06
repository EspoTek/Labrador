Welcome to the GitHub page for the EspoTek Labrador!

# What is it?
The EspoTek Labrador is an open-source board that converts your PC, Raspberry Pi or Android Smartphone and into a full-featured electronics lab bench, complete with oscilloscope, signal generator and more.

More information available at:
http://espotek.com/labrador

This repo hosts all of the software and hardware that makes Labrador possible.

# Licence
All software files are licenced under GNU GPL v3.  https://www.gnu.org/licenses/gpl.html

All hardware files (schematics, PCB) are licenced under Creative Commons 4.0 (CC BY-NC-SA).  https://creativecommons.org/licenses/by-nc-sa/4.0/

The intention is to move to a less restrictive licence in future, where commercial hardware derivatives are allowed but the use of the Labrador name or any branding is not.  If anyone knows how to implement such a licence, I'm all ears.

# Documentation and Binary
To download binary (executable) versions of the software, go to:

https://github.com/espotek/labrador/releases

For the documentation, please visit:

https://github.com/espotek/labrador/wiki


# Build Instructions
I use Qt Creator to build the software interface.
https://www.qt.io/download-open-source/
Open Desktop Interface/Labrador.pro, then Clean All -> Run qmake -> Build All.
Others have built it through qmake and the terminal, though (I have no idea how, specifically).
Just make sure you have Qt 5.6 or later.

For the AVR software, I use Atmel Studio 7.  Just load up the .atsln and push F7.
Again, you can use avr-gcc if you don't want to install a full IDE.

The PCB files were designed in KiCAD 4.0.

# Known bugs.
Most of the main bugs have now been fixed, including all synchronisation issues.
Please open an issue if you're aware of any in particular.

# Collaboration
If you want to make any suggestions, or better yet, submit some code, please do so here at GitHub.
Suggestions and feature requests belong on the "Issues" page.
For code submissions, look into Pull Requests.  Or you can open an issue.  I'm not picky.  :)

# Cleanup Notice
Please note that this repository was cleaned up on 21/10/17.
This significantly reduced the size - from over 200MB to about 3MB, but I was fairly aggressive and it's possible that something was deleted that shouldn't have been.
For this reason, the old, unclean repo has been preserved at:

https://github.com/EspoTek/Labrador_backup


Thanks to all.

~Chris
