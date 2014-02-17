/**
 *******************************************************************************
 * @file       FlashAlgoInfo.c
 * @version    V0.3
 * @date       2010.12.02
 * @brief      Flash  Algorithm and Flash Device Description.	
 *******************************************************************************
 * @copy
 *
 * INTERNAL FILE,DON'T PUBLIC.
 * 
 * <h2><center>&copy; COPYRIGHT 2009 CooCox </center></h2>
 *******************************************************************************
 */
#include <FlashAlgorithm.h>

#define FLASH_ALGORITHM_VERSION 0x01


#if defined TM4C123_32
#if defined ( __GNUC__   )
__attribute__ ((section(".driver_info")))
#endif
struct FlashAlgorithm const FlashDriver = {
	((FLASH_FRAMEWORK_VERSION << 16) | FLASH_ALGORITHM_VERSION),
	"Flash Algorithm Template",
	{
		FLASH_TYPE_ONCHIP,          // Special the Flash Device Type
		0x00000000,                 // Special the Device Start Address
		0x00008000,                 // Special the Device Size in Bytes (32kB)
		1024,                       // Special the Programming Page Size in Bytes
		0xFF,                       // Special the Initial Content of Erased Memory
		// Sector Array
		{
			{ 0x0400, 0x00000000 },	  
			{ FLASH_SECTOR_END   },   // As a sign of the end of the array
		},
	},
	5000,												// Time Out of FlashInit/FlashUnInit/FlashVerify/FlashBlankCheck function (in msec)
	5000,    											// Time Out of FlashProgramage  Function (in msec)
	5000,  												// Time Out of FlashEraseSector Function (in msec)
	5000, 												// Time Out of FlashEraseChip   Function (in msec)

};
#endif


#if defined TM4C123_64
#if defined ( __GNUC__   )
__attribute__ ((section(".driver_info")))
#endif
struct FlashAlgorithm const FlashDriver = {
	((FLASH_FRAMEWORK_VERSION << 16) | FLASH_ALGORITHM_VERSION),
	"Flash Algorithm Template",
	{
		FLASH_TYPE_ONCHIP,          // Special the Flash Device Type
		0x00000000,                 // Special the Device Start Address
		0x00010000,                 // Special the Device Size in Bytes (64kB)
		1024,                       // Special the Programming Page Size in Bytes
		0xFF,                       // Special the Initial Content of Erased Memory
		// Sector Array
		{
			{ 0x0400, 0x00000000 },	  
			{ FLASH_SECTOR_END   },   // As a sign of the end of the array
		},
	},
	5000,												// Time Out of FlashInit/FlashUnInit/FlashVerify/FlashBlankCheck function (in msec)
	5000,    											// Time Out of FlashProgramage  Function (in msec)
	5000,  												// Time Out of FlashEraseSector Function (in msec)
	5000, 												// Time Out of FlashEraseChip   Function (in msec)

};
#endif

#if defined TM4C123_128
#if defined ( __GNUC__   )
__attribute__ ((section(".driver_info")))
#endif
struct FlashAlgorithm const FlashDriver = {
	((FLASH_FRAMEWORK_VERSION << 16) | FLASH_ALGORITHM_VERSION),
	"Flash Algorithm Template",
	{
		FLASH_TYPE_ONCHIP,          // Special the Flash Device Type
		0x00000000,                 // Special the Device Start Address
		0x00020000,                 // Special the Device Size in Bytes (128kB)
		1024,                       // Special the Programming Page Size in Bytes
		0xFF,                       // Special the Initial Content of Erased Memory
		// Sector Array
		{
			{ 0x0400, 0x00000000 },	  
			{ FLASH_SECTOR_END   },   // As a sign of the end of the array
		},
	},
	5000,												// Time Out of FlashInit/FlashUnInit/FlashVerify/FlashBlankCheck function (in msec)
	5000,    											// Time Out of FlashProgramage  Function (in msec)
	5000,  												// Time Out of FlashEraseSector Function (in msec)
	5000, 												// Time Out of FlashEraseChip   Function (in msec)

};
#endif


#if defined TM4C123_256
#if defined ( __GNUC__   )
__attribute__ ((section(".driver_info")))
#endif
struct FlashAlgorithm const FlashDriver = {
	((FLASH_FRAMEWORK_VERSION << 16) | FLASH_ALGORITHM_VERSION),
	"Flash Algorithm Template",
	{
		FLASH_TYPE_ONCHIP,          // Special the Flash Device Type
		0x00000000,                 // Special the Device Start Address
		0x00040000,                 // Special the Device Size in Bytes (256kB)
		1024,                       // Special the Programming Page Size in Bytes
		0xFF,                       // Special the Initial Content of Erased Memory
		// Sector Array
		{
			{ 0x0400, 0x00000000 },	  
			{ FLASH_SECTOR_END   },   // As a sign of the end of the array
		},
	},
	5000,												// Time Out of FlashInit/FlashUnInit/FlashVerify/FlashBlankCheck function (in msec)
	5000,    											// Time Out of FlashProgramage  Function (in msec)
	5000,  												// Time Out of FlashEraseSector Function (in msec)
	5000, 												// Time Out of FlashEraseChip   Function (in msec)

};
#endif


