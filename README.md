This is the project page for the EspoTek Labrador. 

http://espotek.com/labrador
https://www.crowdsupply.com/espotek/labrador

#Licence
All software files are licenced under GNU GPL v3.  https://www.gnu.org/licenses/gpl.html

All hardware files (schematics, PCB) are licenced under Creative Commons 4.0 (CC BY-NC-SA).  https://creativecommons.org/licenses/by-nc-sa/4.0/

The intention is to move to a less restrictive licence in future, where commercial hardware derivatives are allowed but the use of the Labrador name or any branding is not.  If anyone knows how to implement such a licence, please share your wisdom.

#Known bugs.
This software is very much pre-beta.
Those of you with sharp eyes will notice that there are some bugs.
A few biggies include:
 - The software is compatible with Windows (x64) only.
 - A sample is discarded every frame while the DMA resynchronises.
 - The serial decoder doesn't actually look at every sample individually.

There are planned fixes for these:
 - Port libusbK calls to libusb1.
 - Time everything from the ADC's input clock.  Send an extra "status" byte in isoBuffer[] and time this to a high-priority DMA interrupt to prevent the desktop interface and MCU code falling out of sync.  (The "drop 1 sample per frame" was a hacky solution to a synchronisation problem caused by a double buffer's state variable being stored separately, on both PC and MCU.  This should have been stomped out 6 months ago).
 - Change all calculations to be bit-based (not byte) and use a mix of divide and modulo to get exact position.

This is in addition to the dozens of small bugs that will have to be slowly squashed before launch.

#Collaboration
Collaboration will be a bit difficult at this stage since the Labrador hardware has not been distributed and the software is useless on its own.
Those who selected the "Shape the Development" reward on Crowd Supply will be sent a piece of beta hardware when the campaign ends.
Welcome to suggestions at this stage as to how you think any collaboration will proceed!

Thanks to all.

~Chris
