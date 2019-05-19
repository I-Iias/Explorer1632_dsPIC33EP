/*
 * File:   types.h
 * Author: Matthias Leeb
 *
 * Created on 22. April 2019, 13:44
 */

#ifndef TYPES_H
#define	TYPES_H

#ifndef   TRUE
    #define TRUE  1             ///< constant for TRUE
 #endif
 #ifndef   FALSE
    #define FALSE 0             ///< constant for FALSE
 #endif 

#ifndef	NULL
#define NULL (0)
#endif	/* NULL */

 typedef unsigned char      uint8;       ///< for unsigned 8-Bit variables
 typedef unsigned short     uint16;      ///< for unsigned 16-Bit variables
 typedef unsigned long      uint32;      ///< for unsigned32-Bit variables
 typedef unsigned long long uint64;      ///< for unsigned 64-Bit variables
 typedef signed   char      int8;        ///< for signed 8-Bit variables
 typedef signed   short     int16;       ///< for signed 16-Bit variables
 typedef signed   long      int32;       ///< for signed 32-Bit variables
 typedef signed   long long int64;       ///< for unsigned 64-Bit variables
 typedef          char      boolean;     ///< for TRUE/FALSE variables
 typedef          float     float32;     ///< for 32-Bit floating point
 typedef long     double    float64;     ///< for 64-Bit floating point
 
#endif // TYPES_H