cd dfu prog
dfu-programmer atxmega32a4u erase --force
dfu-programmer atxmega32a4u flash labrafirm_0001_01.hex
dfu-programmer atxmega32a4u launch
timeout 2
dfu-programmer atxmega32a4u launch
PAUSE