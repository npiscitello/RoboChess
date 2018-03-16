/*****************************************************************************
 * Interval timer interrupt service routine
 *                                                                          
******************************************************************************/
void interval_timer_isr( )
{
	volatile int * interval_timer_ptr = (int *) 0x10002000;

	*(interval_timer_ptr) = 0; 				// Clear the interrupt

	return;
}

