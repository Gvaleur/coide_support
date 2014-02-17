/**
 *******************************************************************************
 * @file       FlashAlgoFncs.c
 * @version    V0.3
 * @date       2010.12.02
 * @brief      Flash  Algorithm For TM4C123 with up to 256KB Flash Rom	
 *******************************************************************************
 * @copy
 *
 * INTERNAL FILE,DON'T PUBLIC.
 * 
 * <h2><center>&copy; COPYRIGHT 2009 CooCox </center></h2>
 *******************************************************************************
 */ 
 
#include <FlashAlgorithm.h>

#include "stdint.h"
#include "cpu.h"
#include "hw_flash.h"
#include "hw_types.h"

static unsigned int WRKEY;


/**
 *******************************************************************************
 * @brief      Initialize before Flash Programming/Erase Functions 
 * @param[in]  baseAddr     Flash device base address.
 * @param[in]  clk     			Flash program clock.
 * @param[in]  operateFuc   Init for what operation
 														(FLASH_OPT_ERASECHIP/FLASH_OPT_ERASESECTORS/FLASH_OPT_PROGRAMPAGE/
 														 FLASH_OPT_VERIFY/ FLASH_OPT_BLANKCHECK).
 * @param[out] None  
 * @retval     0   					All is OK.
 * @retval     others       Some error occurs.		 
 *
 * @par Description
 * @details    This function is called before flash programming/erase. 
 * @note 
 *******************************************************************************
 */
int FlashInit (unsigned long baseAddr,unsigned long clk, unsigned long operateFuc)
{
  //
  // disable interrupts on the processor 
  //
  CPUcpsid();
  
  //
  // Check which flash key the MCU is set to use
  //
  if(HWREG(FLASH_BOOTCFG) & FLASH_BOOTCFG_KEY)
  {
	WRKEY = 0xA4420000;
  }
  else
  {
	WRKEY = 0x71D50000;
  }
  
  //
  // Clear the BA bit in RMCTL to set the Flash memory at address 0x0)
  //
  HWREG(FLASH_RMCTL)  = FLASH_RMCTL_BA;
  
  return (0);
}


/**
 *******************************************************************************
 * @brief      Un-Init after Flash Programming/Erase Functions  
 * @param[in]  operateFuc   Init for what operation
 														(FLASH_OPT_ERASECHIP/FLASH_OPT_ERASESECTORS/FLASH_OPT_PROGRAMPAGE/
 														 FLASH_OPT_VERIFY/FLASH_OPT_BLANKCHECK).
 * @param[out] None  
 * @retval     0   					All is OK.
 * @retval     others       Some error occurs.		 
 *
 * @par Description
 * @details    This function is called after flash programming/erase. 
 * @note 
 *******************************************************************************
 */
int FlashUnInit(unsigned long operateFuc)
{
  
  //
  // none needed
  //
  
  return (0);
}


/**
 *******************************************************************************
 * @brief      Erase the full chip.  
 * @param[in]  None.
 * @param[out] None  
 * @retval     0   					All is OK.
 * @retval     others       Some error occurs.		 
 *
 * @par Description
 * @details     
 * @note 
 *******************************************************************************
 */
int FlashEraseChip (void)
{
  // Clear the Flash Access Interrupt
  HWREG(FLASH_FCMISC) = FLASH_FCMISC_AMISC;

  // Mass Erase
  HWREG(FLASH_FMC) = WRKEY | FLASH_FMC_MERASE;
  
  // Wait until erase is done
  while(HWREG(FLASH_FMC) & FLASH_FMC_MERASE)
  {
  }
  
  // Check Access Violation
  if (HWREG(FLASH_FCRIS) & FLASH_FCRIS_ARIS) {
    return (1);
  }
	
  return (0);
}


/**
 *******************************************************************************
 * @brief      Erase the select Sector. 
 * @param[in]  sectorAddr   Sector's start address.
 * @param[out] None  
 * @retval     0   					All is OK.
 * @retval     others       Some error occurs.		 
 *
 * @par Description
 * @details     
 * @note 
 *******************************************************************************
 */
int FlashEraseSector (unsigned long sectorAddr)
{

  // Address must be Block aligned
  if (sectorAddr & (FLASH_ERASE_SIZE - 1)) {
    return (1);
  }

  // Clear the Flash Access Interrupt
  HWREG(FLASH_FCMISC) = FLASH_FCMISC_AMISC;

  // Erase the Block
  HWREG(FLASH_FMA) = sectorAddr;
  HWREG(FLASH_FMC) = WRKEY | FLASH_FMC_ERASE;

  // Wait until Erase is done
  while (HWREG(FLASH_FMC) & FLASH_FMC_ERASE);

  // Check Access Violation
  if (HWREG(FLASH_FCRIS) & FLASH_FCRIS_ARIS) {
    return (1);
  }
  
  return (0);                 
}



/**
 *******************************************************************************
 * @brief      Proram a page. 
 * @param[in]  pageAddr     Page's start address.
 * @param[in]  size			    Page size
 * @param[in]  buf   			  Source buf point.
 * @param[out] None  
 * @retval     0   					All is OK.
 * @retval     others       Some error occurs.		 
 *
 * @par Description
 * @details     
 * @note 
 *******************************************************************************
 */ 
int FlashProgramPage (unsigned long pageAddr, unsigned long size, unsigned char *buf)
{

  // Address and Size must be Word aligned
  if ((pageAddr & 3) || (size & 3)) {
    return (1);
  }

  // Clear the Flash Access Interrupt
  HWREG(FLASH_FCMISC) = FLASH_FCMISC_AMISC;

  // Loop over the Words to be programmed
  while (size) {

    // Program Word
    HWREG(FLASH_FMA) = pageAddr;
    HWREG(FLASH_FMD) = *((unsigned long *)buf);
    HWREG(FLASH_FMC) = WRKEY | FLASH_FMC_WRITE;

    // Wait unitl Word has been programmed
    while (HWREG(FLASH_FMC) & FLASH_FMC_WRITE);

    // Prepeare Next Word
    pageAddr += 4;
    buf += 4;
    size  -= 4;

  }

  // Check Access Violation
  if (HWREG(FLASH_FCRIS) & FLASH_FCRIS_ARIS) {
    return (1);
  }

  return (0);   // Success
}


/**
 *******************************************************************************
 * @brief      Page Verify Function. 
 * @param[in]  verifyAddr   Verify Start Address(Usually page start address).
 * @param[in]  size			    Verify size
 * @param[in]  buf   			  Source buf point.
 * @param[out] None  
 * @retval     0   					Verify pass.
 * @retval     others       Some error occurs or verify failed..		 
 *
 * @par Description
 * @details   Optional function. When this function is absence, 
 *            the link will read flash memory directly to do verify.  
 * @note 
 *******************************************************************************
 */ 
//int FlashVerify(unsigned long verifyAddr,unsigned long size,unsigned char *buf)
//{
//  // TODO: your code for the page verify
//  return (0);
//}


/**
 *******************************************************************************
 * @brief      Page Blank Check Function. 
 * @param[in]  checkAddr    Check Start Address(Usually page start address).
 * @param[in]  size			    Check size
 * @param[out] None  
 * @retval     0   					Check pass.
 * @retval     others       Some error occurs or check failed.		 
 *
 * @par Description
 * @details   Optional function. When this function is absence, 
 *            the link will read flash memory directly to do verify.  
 * @note      Sector can be significant.We check the page rather than the sector,
 *            having regard to the actual size of the ram.
 *******************************************************************************
 */ 
//int FlashBlankCheck (unsigned long checkAddr,unsigned long size)
//{
//  // TODO: your code for the page check
//  return (0);
//}