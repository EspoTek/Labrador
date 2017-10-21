/*
 * tiny_eeprom.h
 *
 * Created: 22/04/2017 12:37:34 PM
 *  Author: Esposch
 */ 


#ifndef TINY_EEPROM_H_
#define TINY_EEPROM_H_

#define EEPROM_CURRENT_PAGE 1

void eeprom_safe_read();
void eeprom_safe_write();
extern volatile unsigned char eeprom_buffer_write[EEPROM_PAGE_SIZE];
extern volatile unsigned char eeprom_buffer_read[EEPROM_PAGE_SIZE];


#endif /* TINY_EEPROM_H_ */