/* 
 * File:   EEPROM_emulation.c
 * Author: Matthias
 *
 * Created on 21. Mai 2019, 21:09
 */

#include "EEPROM_emulation.h"

void Init_EEPROM (void)
{
    DataEEInit();
    dataEEFlags.val = 0;
}

boolean EEPROM_write(uint16 data, uint16 addr)
{
    DataEEWrite(data,addr);
    uint16 value;
    value = DataEERead(addr);
    if (value == data)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

uint16 EEPROM_read(uint16 addr)
{
    return DataEERead(addr);
}
