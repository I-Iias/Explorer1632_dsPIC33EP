/* 
 * File:   EEPROM_emulation.h
 * Author: Matthias
 *
 * Created on 21. Mai 2019, 21:09
 */

#ifndef EEPROM_EMULATION_H
#define	EEPROM_EMULATION_H

#include "libs\DEE_Emulation_16-bit.h"
#include "types.h"

#define EEPROM_addr_Pot 10

void Init_EEPROM (void);
boolean EEPROM_write(uint16 data, uint16 addr);
uint16 EEPROM_read(uint16 addr);


#endif	/* EEPROM_EMULATION_H */

