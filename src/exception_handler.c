#include "nios2_ctrl_reg_macros.h"

/* function prototypes */
void interrupt_handler(void);
void interval_timer_isr(void);

/* global variables */
extern int	key_pressed;

/* The assembly language code below handles CPU reset processing */
void the_reset (void) __attribute__ ((section (".reset")));
void the_reset (void)
/************************************************************************************
 * Reset code. By giving the code a section attribute with the name ".reset" we     *
 * allow the linker program to locate this code at the proper reset vector address. *
 * This code just calls the main program.                                           *
 ***********************************************************************************/
{
__asm (".set		noat");					// Magic, for the C compiler
__asm (".set		nobreak");				// Magic, for the C compiler
__asm ("movia		r2, main");				// Call the C language main program
__asm ("jmp		r2"); 
}

/* The assembly language code below handles CPU exception processing. This
 * code should not be modified; instead, the C language code in the function
 * interrupt_handler() can be modified as needed for a given application.
*/
void the_exception (void) __attribute__ ((section (".exceptions")));
void the_exception (void)
/*******************************************************************************
 * Exceptions code. By giving the code a section attribute with the name       *
 * ".exceptions" we allow the linker program to locate this code at the proper *
 * exceptions vector address.                                                  *
 * This code calls the interrupt handler and later returns from the exception. *
 ******************************************************************************/
{
__asm ( ".set		noat" );						// Magic, for the C compiler
__asm ( ".set		nobreak" );					// Magic, for the C compiler
__asm ( "subi		sp, sp, 128" );
__asm ( "stw		et, 96(sp)" );
__asm ( "rdctl	et, ctl4" );
__asm ( "beq		et, r0, SKIP_EA_DEC" );	// Interrupt is not external         
__asm ( "subi		ea, ea, 4" );				/* Must decrement ea by one instruction  
												 	 * for external interupts, so that the 
												 	 * interrupted instruction will be run */

__asm ( "SKIP_EA_DEC:" );
__asm (	"stw	r1,  4(sp)" );					// Save all registers 
__asm (	"stw	r2,  8(sp)" );
__asm (	"stw	r3,  12(sp)" );
__asm (	"stw	r4,  16(sp)" );
__asm (	"stw	r5,  20(sp)" );
__asm (	"stw	r6,  24(sp)" );
__asm (	"stw	r7,  28(sp)" );
__asm (	"stw	r8,  32(sp)" );
__asm (	"stw	r9,  36(sp)" );
__asm (	"stw	r10, 40(sp)" );
__asm (	"stw	r11, 44(sp)" );
__asm (	"stw	r12, 48(sp)" );
__asm (	"stw	r13, 52(sp)" );
__asm (	"stw	r14, 56(sp)" );
__asm (	"stw	r15, 60(sp)" );
__asm (	"stw	r16, 64(sp)" );
__asm (	"stw	r17, 68(sp)" );
__asm (	"stw	r18, 72(sp)" );
__asm (	"stw	r19, 76(sp)" );
__asm (	"stw	r20, 80(sp)" );
__asm (	"stw	r21, 84(sp)" );
__asm (	"stw	r22, 88(sp)" );
__asm (	"stw	r23, 92(sp)" );
__asm (	"stw	r25, 100(sp)" );				// r25 = bt (skip r24 = et, because it is saved above)
__asm (	"stw	r26, 104(sp)" );				// r26 = gp
// skip r27 because it is sp, and there is no point in saving this
__asm (	"stw	r28, 112(sp)" );				// r28 = fp
__asm (	"stw	r29, 116(sp)" );				// r29 = ea
__asm (	"stw	r30, 120(sp)" );				// r30 = ba
__asm (	"stw	r31, 124(sp)" );				// r31 = ra
__asm (	"addi	fp,  sp, 128" );

__asm (	"call	interrupt_handler" );		// Call the C language interrupt handler

__asm (	"ldw	r1,  4(sp)" );					// Restore all registers
__asm (	"ldw	r2,  8(sp)" );
__asm (	"ldw	r3,  12(sp)" );
__asm (	"ldw	r4,  16(sp)" );
__asm (	"ldw	r5,  20(sp)" );
__asm (	"ldw	r6,  24(sp)" );
__asm (	"ldw	r7,  28(sp)" );
__asm (	"ldw	r8,  32(sp)" );
__asm (	"ldw	r9,  36(sp)" );
__asm (	"ldw	r10, 40(sp)" );
__asm (	"ldw	r11, 44(sp)" );
__asm (	"ldw	r12, 48(sp)" );
__asm (	"ldw	r13, 52(sp)" );
__asm (	"ldw	r14, 56(sp)" );
__asm (	"ldw	r15, 60(sp)" );
__asm (	"ldw	r16, 64(sp)" );
__asm (	"ldw	r17, 68(sp)" );
__asm (	"ldw	r18, 72(sp)" );
__asm (	"ldw	r19, 76(sp)" );
__asm (	"ldw	r20, 80(sp)" );
__asm (	"ldw	r21, 84(sp)" );
__asm (	"ldw	r22, 88(sp)" );
__asm (	"ldw	r23, 92(sp)" );
__asm (	"ldw	r24, 96(sp)" );
__asm (	"ldw	r25, 100(sp)" );				// r25 = bt
__asm (	"ldw	r26, 104(sp)" );				// r26 = gp
// skip r27 because it is sp, and we did not save this on the stack
__asm (	"ldw	r28, 112(sp)" );				// r28 = fp
__asm (	"ldw	r29, 116(sp)" );				// r29 = ea
__asm (	"ldw	r30, 120(sp)" );				// r30 = ba
__asm (	"ldw	r31, 124(sp)" );				// r31 = ra

__asm (	"addi	sp,  sp, 128" );

__asm (	"eret" );
}

/*****************************************************************************
 * Interrupt Service Routine                                                 
 *  Determines what caused the interrupt and calls the appropriate          
 *  subroutine.                                                              
 *                                                                           
 * ipending - Control register 4 which has the pending external interrupts  
 *****************************************************************************/
void interrupt_handler(void)
{
	int ipending;
	NIOS2_READ_IPENDING(ipending);
  // interval timer is interrupt level 0
	if ( ipending & 0x1 )
	{
		interval_timer_isr( );
	}
	// else, ignore the interrupt
	return;
}
