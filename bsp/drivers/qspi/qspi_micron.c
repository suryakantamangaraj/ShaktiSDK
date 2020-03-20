/***************************************************************************
 * Project           	        : shakti devt board
 * Name of the file	     	    : qspi_micron.c
 * Brief Description of file    : source file for qspi_micron  
 * Name of Author    	        : visvesh
 * Email ID                     : vishu.vivek@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ****************************************************************************/

#include "qspi.h"
#include "utils.h"
#include "log.h"
#define MEM_TYPE_N25Q256_ID 0x9d189d18

char fail_bit = 0;
int status = 0;

int* cr       =      (const int*) CR;
int* dcr      =      (const int*) DCR;
int* sr       =      (const int*) SR;
int* fcr      =      (const int*) FCR;
int* ccr      =      (const int*) CCR;
int* ar       =      (const int*) AR;
int* abr      =      (const int*) ABR;
int* dr       =      (const int*) DR;
int* dlr      =      (const int*) DLR;
int* psmkr    =      (const int*) PSMKR;
int* pir      =      (const int*) PIR;
int* lprt     =      (const int*) LPRT;
int* startmm  =      (const int*) STARTMM;
int* endmm    =      (const int*) ENDMM;

/** @fn set_qspi_shakti32
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] No output parameter
 */
void set_qspi_shakti32(int* addr, int val)
{
    *addr = val;
}

/** @fn set_qspi_shakti16
 * @brief 
 * @details
 * @warning 
 * @param[in] 
 * @param[Out] No output parameter
 */
void set_qspi_shakti16(int16_t* addr, int16_t val)
{
    *addr = val;
}

/** @fn set_qspi_shakti8
 * @brief 
 * @details
 * @warning 
 * @param[in] char
 * @param[Out] No output parameter
 */
void set_qspi_shakti8(char* addr, char val)
{
    *addr= val;
}

/** @fn get_qspi_shakti
 * @brief 
 * @details
 * @warning 
 * @param[in] int   
 * @param[Out] int
 */
int get_qspi_shakti(int* addr)
{
 return *addr;
}

/** @fn qspi_init
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] No output parameter
 */
void qspi_init(int fsize, int csht, int prescaler, int enable_interrupts, int fthreshold, int ck_mode){
    int int_vector = enable_interrupts? (CR_TOIE|CR_SMIE|CR_FTIE|CR_TCIE|CR_TEIE) : 0; 
    set_qspi_shakti32(dcr,(DCR_FSIZE(fsize)|DCR_CSHT(csht)|DCR_CKMODE(ck_mode))); 
    set_qspi_shakti32(cr,(CR_PRESCALER(prescaler)|int_vector|CR_FTHRES(fthreshold)|CR_EN));
}

/** @fn reset_interrupt_flags
 * @brief 
 * @details
 * @warning 
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
void reset_interrupt_flags(){
    set_qspi_shakti32(fcr,(FCR_CTOF|FCR_CSMF|FCR_CTCF|FCR_CTEF)); //Resetting all the flags
}

/** @fn wait_for_tcf
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int wait_for_tcf(int status){
    int timeout = DEF_TIMEOUT; 

    status = get_qspi_shakti(sr);
     
//    printf("status : %d looping?\n",status);
    
    while(!( status & 0x02 ) && --timeout){
        waitfor(1000);
        status=get_qspi_shakti(sr);
        printf("status: %08x in loop %d \n",status, !(status & 0x02));
    }
    if(timeout==0){
        printf("Request Timed out\n");
        return -1;
    }
    return 0;
}

/** @fn check_fail_bit
 * @brief 
 * @details
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */
int check_fail_bit(){
  if(fail_bit){
        fail_bit = 0;
        return -1;
  }
    else{
        fail_bit = 0;
        return 0;
    }
}

/** @fn pageProgramSingleSPI
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int pageProgramSingleSPI(int value1, int value2, int value3, int value4, int address){
    if(micron_write_enable(status)){
        printf("Panic: Write Enable Command Failed to execute");
        return -1;
    }
    reset_interrupt_flags(); 
   
    set_qspi_shakti32(dlr,DL(16));
//  set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12)));
	set_qspi_shakti32(ar, address);                                                                 
	printf(" Address written %d \n",address); 
    set_qspi_shakti32(dr,value1);
	printf(" Value 1 written %d \n",value1);
    set_qspi_shakti32(dr,value2);
	printf(" Value 2 written %d \n",value2);
	set_qspi_shakti32(dr,value3);
	printf(" Value 3 written %d \n",value3);
    set_qspi_shakti32(dr,value4);
	printf(" Value 4 written %d \n",value4);
    waitfor(150); 
    wait_for_tcf(status);
    reset_interrupt_flags();
    return wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn pageProgramQuadSPI
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int pageProgramQuadSPI(int value1, int value2, int value3, int value4, int address){
    if(micron_write_enable(status)){
        printf("Panic: Write Enable Command Failed to execute");
        return -1;
    }
    reset_interrupt_flags(); 
   
    set_qspi_shakti32(dlr,DL(16));
//  set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(QUAD)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x34))); 
    set_qspi_shakti32(ar, address);
    set_qspi_shakti32(dr,value1);
    set_qspi_shakti32(dr,value2);
    set_qspi_shakti32(dr,value3);
    set_qspi_shakti32(dr,value4);
    waitfor(150); 
    wait_for_tcf(status);
    reset_interrupt_flags();
    return wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn flashIdentificationDevice
 * @brief 
 * @details
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */
int flashIdentificationDevice(){
	log_debug("\tReading the ID register and discovering the Flash Device\n");
	set_qspi_shakti32(dlr,4);
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x90)|CCR_ADSIZE(THREEBYTE)|CCR_ADMODE(SINGLE)|CCR_DMODE(SINGLE)));
    set_qspi_shakti32(ar, 0);
    status = 0; // Useless Variable but still!!!!
    int ret = wait_for_tcf(status);
    int value = get_qspi_shakti(dr);
	log_info("\t device id %x\n",value);
    reset_interrupt_flags();
    if(value == MEM_TYPE_N25Q256_ID){
    	printf("\tN25Q256 Device Detected \n");
    	return 0;
    }
    else{
    	log_fatal("\t Device Not Detected - Diagnose %08x\n",value);
    	return -1;
    }
}

/** @fn flashMemInit
 * @brief 
 * @details
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */
int flashMemInit(){   //Supposedly a set of routines to check if the memory/interface or whatever is proper
	int ret = flashIdentificationDevice();
	if(ret==-1){
		log_fatal("Flash Mem Init Failed -- Quitting Program, Diagnose");
		return ret;
	}
	else log_debug("Flash Mem Init Success\n");
    return 0;
	//to fill in code
}

/** @fn flashReadstatusRegister
 * @brief 
 * @details
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */
int flashReadStatusRegister(){
//    printf("\tReading the Status bits of the Flash\n");
    set_qspi_shakti32(dlr,4);
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x05)|CCR_DMODE(SINGLE)));
 	status = 0;
	waitfor(1000);
    int ret = wait_for_tcf(status);
    waitfor(100);
    int value = get_qspi_shakti(dr);
//	printf("Read status register value %08x \n", value);
    reset_interrupt_flags();
    if(ret){
        printf("\tRead Status Register Failed\n");
		fail_bit = 1;
        return -1;
        }
    else 
    	return value;
}

/** @fn flashReadFlagRegister
 * @brief 
 * @details
 * @warning 
 * @param[in] No input parameter 
 * @param[Out] int
 */
int flashReadFlagRegister(){
	return 0;
}

/** @fn flashWriteEnable
 * @brief 
 * @details
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */
int flashWriteEnable(){
    printf("\tWrite Enable\n");
    set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
    int ret = wait_for_tcf(0); //Indicating the completion of command -- Currently polling
    reset_interrupt_flags();
    return ret; 
}


/** @fn flashEnable4ByteAddressingMode
 * @brief 
 * @details
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */
int flashEnable4ByteAddressingMode(){  //Enable 4-byte addressing Mode and read the status to verify that it has happened correctly

    if(flashWriteEnable()){
        printf("\t Write Enable Failed \n");
        return -1;
    }
    waitfor(100);
    set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
  //  int status =0; 
    status = 0;
    int ret = wait_for_tcf(status);
    reset_interrupt_flags();
    waitfor(100);
    //Checking Phase
    status = flashReadStatusRegister();
    printf("\t Status Value: %08x\n",status);
    if(status & 1)
        printf("\t 4-Byte Addressing Mode is Enabled\n");
    else
        printf("\t 4-byte Addressing mode not Enabled\n");
}

/** @fn flashReadSingleSPI
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int flashReadSingleSPI(int dummy_cycles, int read_address, int instruction, int data_words, int adsize){
    set_qspi_shakti32(dlr,data_words);
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DCYC(dummy_cycles)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_ADSIZE(adsize)|CCR_INSTRUCTION(instruction)));
    set_qspi_shakti32(ar,read_address);
    status = 0;
    int ret = wait_for_tcf(status);
    int value = get_qspi_shakti(dr);
    printf("\tThe Read Value: %08x\n",value);
//    printf("\tThe Read Value: %08x\n",value);
    if(ret){
        printf("\t Read Value Failed \n");
        return -1;
    }
    reset_interrupt_flags();
    return value;
}

/** @fn flashReadDualSPI
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int flashReadDualSPI(int address, int data_length){
    set_qspi_shakti32(dlr,data_length); //DLR
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
    set_qspi_shakti32(ar,address); 
//    printf("Status : %08x dcr : %08x cr : %08x ccr : %08x dlr: %08x ar: %08x\n",status,*dcr,*cr,*ccr,*dlr,*ar);
    int ret = wait_for_tcf(status);
	int value = get_qspi_shakti(dr);
    printf("\tThe Read Value: %08x\n",value);	
    if(ret){
        printf("\t QSPI: Read Value failed\n");
        return -1;
    }
    //*config_string = get_qspi_shakti(dr);
    //printf("\t Read Data is %08x\n",read_data);
    reset_interrupt_flags();
    return value;
}

/** @fn flashReadQuadSPI
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int flashReadQuadSPI(int dummy_cycles, int read_address, int instruction, int data_words, int adsize){
     set_qspi_shakti32(dlr,data_words);
     set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DCYC(dummy_cycles)|CCR_ADSIZE(adsize)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(instruction)));
     set_qspi_shakti32(ar,read_address);
     status = 0;
     int ret = wait_for_tcf(status);
     int value_1 = get_qspi_shakti(dr);
	 int value_2 = get_qspi_shakti(dr);
	 int value_3 = get_qspi_shakti(dr);
	 int value_4 = get_qspi_shakti(dr);
     printf("\tThe Read Value: %08x, %08x, %08x and %08x \n",value_1,value_2,value_3,value_4);
     if(ret){
         printf("\t Read Value Failed \n");
         return -1; 
     }   
     reset_interrupt_flags();
     return value_1;
 }

/** @fn flashSingleSPIXip 
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int flashSingleSPIXip(int addr, int* dest_addr){
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
    set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1)));
    set_qspi_shakti32(dlr,0x4);
    set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
    status=0;
    wait_for_tcf(status);
    waitfor(100); 
    *dest_addr = get_qspi_shakti(dr);
	printf("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
    reset_interrupt_flags(); 
    printf("\t Trying XIP now\n");
    set_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
    set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1))); 
    waitfor(25);
	return 0;
}

/** @fn flashSingleSPIDDRXip 
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int flashSingleSPIDDRXip(int addr, int* dest_addr){
    set_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(15)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
    set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1)));
    set_qspi_shakti32(dlr,0x4);
    set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
    status=0;
    wait_for_tcf(status);
    waitfor(100); 
    *dest_addr = get_qspi_shakti(dr);
    reset_interrupt_flags(); 
    printf("\t Trying XIP now\n");
    set_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(14)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
    set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1))); 
    waitfor(25);
	return 0;
}

/** @fn flashDualSPIXip 
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int flashDualSPIXip(int addr, int* dest_addr){
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
    set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1)));
    set_qspi_shakti32(dlr,0x4);
    set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
    status=0;
    wait_for_tcf(status);
    waitfor(100); 
    *dest_addr = get_qspi_shakti(dr);
	printf("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
    reset_interrupt_flags(); 
   printf("\t Trying XIP now\n");
   set_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
   set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
   waitfor(25);
	return 0;
}

/** @fn flashDualSPIDDRXip
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int flashDualSPIDDRXip(int addr, int* dest_addr){
    set_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)));
    set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1)));
    set_qspi_shakti32(dlr,0x4);
    set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
    status=0;
    wait_for_tcf(status);
    waitfor(100); 
    *dest_addr = get_qspi_shakti(dr);
    reset_interrupt_flags(); 
    printf("\t Trying XIP now\n");
    set_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
    set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
    waitfor(25);
	return 0;
}

/** @fn flashQuadSPIXip
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int flashQuadSPIXip(int addr, int* dest_addr){
    if(flashWriteVolatileConfigReg(0x40404040)){
        printf("\t Volatile Configuration Register not Set -- Diagnose\n");
        return -1;
    }
	status = wait_for_wip();
	printf("\t qspi status register %08x\n",status);
    reset_interrupt_flags();
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEC)));
    set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1)));
    set_qspi_shakti32(dlr,0x4);
    set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
    status=0;
    wait_for_tcf(status);
    waitfor(100); 
    *dest_addr = get_qspi_shakti(dr);
    reset_interrupt_flags(); 
    printf("\t Trying XIP now\n");
    set_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
    set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
    waitfor(25);
	return 0;
}

/** @fn flashQuadSPIDDRXip 
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int flashQuadSPIDDRXip(int addr, int* dest_addr){
    if(flashWriteVolatileConfigReg(0x40404040)){
        printf("\t Volatile Configuration Register not Set -- Diagnose\n");
        return -1;
    }
	status = wait_for_wip();
	printf("\t qspi status register %08x\n",status);
    reset_interrupt_flags();
    set_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEE)));
    set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1)));
    set_qspi_shakti32(dlr,0x4);
    set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
    status=0;
    wait_for_tcf(status);
    waitfor(100); 
    *dest_addr = get_qspi_shakti(dr);
    reset_interrupt_flags(); 
    printf("\t Trying XIP now\n");
    set_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
    set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
    waitfor(25);
	return 0;
}

/** @fn flashWriteVolatileConfigReg 
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int flashWriteVolatileConfigReg(int value){
    printf("\t Setting Volatile Configuration Register with the Value: %08x\n",value);
	if(micron_write_enable(status)){
        printf("Panic: Write Enable Command Failed to execute\n");
        return -1;
	}
     reset_interrupt_flags();
//	flashReadStatusRegister();
    set_qspi_shakti32(dlr,DL(1));
    set_qspi_shakti8(dr,value);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x01)));
    waitfor(50);
    status=0;
    int ret = wait_for_tcf(status);
//    printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
    reset_interrupt_flags();
    waitfor(50);  //Giving Micron time to store the data
    return ret;
}

/** @fn flash_Write_disable
 * @brief 
 * @details
 * @warning 
 * @param[in] No iput parameter
 * @param[Out] int
 */
 
int flash_Write_disable(){
    printf("\tWrite disable\n");
    set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x04)));
    int ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
    printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	reset_interrupt_flags();
	return wait_for_wip();
}

/** @fn eraseSector 
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int eraseSector(int command, int address){
    if(micron_write_enable(status)){
        printf("Panic: Write Enable Command Failed to execute");
        return -1;
    }
    reset_interrupt_flags();
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(command)));
    set_qspi_shakti32(ar,address);
    waitfor(150);
    int ret = wait_for_tcf(status);
    reset_interrupt_flags();
    return wait_for_wip(); //For sector erase maybe estat should be checked
}

/** @fn wait_for_wip
 * @brief 
 * @details
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */
int wait_for_wip(){
    int status1;
    do{
 //       printf("\t Waiting for Wip \n");
        status1 = flashReadStatusRegister(0x05);
        if(check_fail_bit())
            return -1;
        if(status1 & 0x0){
            printf("\tQSPI: Programming Error - Diagnose\n");
            return -1;
        }
        waitfor(20000);
    }while(status1 & 0x01);
//    printf("\t QSPI: Page Program/Erase Command Successfully Completed\n");
    return 0;
}	

/** @fn micron_write_enable
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int micron_write_enable(int status){
//    printf("\tWrite Enable\n");
    set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
    int ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
//    printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
    return ret;
}

/** @fn micron_volatile_write_enable 
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int micron_volatile_write_enable(int status){
    printf("\tVolatile Write Enable\n");
    set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x50)));
    int ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
    printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
    return ret;
}

/** @fn micron_enable_4byte_addressing 
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int micron_enable_4byte_addressing(int status){
    printf("\t Enable 4 byte address \n");
    set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
    int ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
    printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
    return ret;
}

/** @fn micron_configure_xip_volatile
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int micron_configure_xip_volatile(int status, int value){
    log_debug("\tWrite Volatile Configuration Register\n");
    set_qspi_shakti32(dlr,DL(1));
    set_qspi_shakti8(dr,value);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x81)));
    waitfor(50);
    int ret = wait_for_tcf(status);
    printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
    waitfor(50);  //Giving Micron time to store the data
    return ret;
}

/** @fn micron_disable_xip_volatile
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int micron_disable_xip_volatile(int status, int value){
    log_debug("\tWrite Volatile Configuration Register to exit XIP\n");
    set_qspi_shakti32(cr,(CR_PRESCALER(0x3)|CR_TOIE|CR_TCIE|CR_TEIE|CR_SMIE|CR_FTIE|CR_ABORT|CR_EN));
    waitfor(30);
    qspi_init(27,0,3,1,15,1);
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_BIT|CCR_DUMMY_CONFIRMATION|CCR_DCYC(8)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
    set_qspi_shakti32(ar,0x00000); //Dummy address 
    set_qspi_shakti32(dlr,1);
    int ret = wait_for_tcf(status);
   int temp_data = get_qspi_shakti(dr);
    waitfor(50);
    reset_interrupt_flags();
    return ret;
}

/** @fn micron_read_id_cmd
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int micron_read_id_cmd(int status, int value){
    log_debug("\tRead ID Command to see if the Protocol is Proper\n");
    set_qspi_shakti32(dlr,4);
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x9E)|CCR_DMODE(SINGLE)));
    int ret = wait_for_tcf(status);
    value = get_qspi_shakti(dr);
    printf("Read ID: %08x",value);
    return ret;
}

/** @fn micron_read_configuration_register
 * @brief 
 * @details
 * @warning 
 * @param[in] int
 * @param[Out] int
 */
int micron_read_configuration_register(int status, int value){
    printf("\tRead ID Command to see if the Protocol is Proper\n");
    set_qspi_shakti32(dlr,4);
    set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)|CCR_DMODE(SINGLE)));
    int ret = wait_for_tcf(status);
    value = get_qspi_shakti(dr);
    log_debug("Configuration Register Value: %08x",value);
    return ret;
}
