/*
 *  ======== gtz.c ========
 */    

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "gtz.h"

void clk_SWI_Generate_DTMF(UArg arg0);
void clk_SWI_GTZ_0697Hz(UArg arg0);

extern void task0_dtmfGen(void);
extern void task1_dtmfDetect(void);

extern char digit;
extern int sample, mag1, mag2, freq1, freq2, gtz_out[8];
extern short coef[8];



/*
 *  ======== main ========
 */
void main(void)
{


	System_printf("\n I am in main :\n");
	System_flush();
	/* Create a Clock Instance */
    Clock_Params clkParams;

    /* Initialise Clock Instance with time period and timeout (system ticks) */
    Clock_Params_init(&clkParams);
    clkParams.period = 1;
    clkParams.startFlag = TRUE;

    /* Instantiate ISR for tone generation  */
	Clock_create(clk_SWI_Generate_DTMF, TIMEOUT, &clkParams, NULL);

    /* Instantiate 8 parallel ISRs for each of the eight Goertzel coefficients */
	Clock_create(clk_SWI_GTZ_0697Hz, TIMEOUT, &clkParams, NULL);

	mag1 = 32768.0; mag2 = 32768.0; freq1 = 697; // I am setting freq1 = 697Hz to test my GTZ algorithm with one frequency.
	//mag1 = 32768.0; mag2 = 32768.0; freq1 = 1500; // I am setting freq1 = 697Hz to test my GTZ algorithm with one frequency.


	/* Start SYS_BIOS */
    BIOS_start();
}

/*
 *  ====== clk0Fxn =====
 *  Dual-Tone Generation
 *  ====================
 */
void clk_SWI_Generate_DTMF(UArg arg0)
{
	static int tick;


	tick = Clock_getTicks();

//	sample = (int) 32768.0*sin(2.0*PI*freq1*TICK_PERIOD*tick) + 32768.0*sin(2.0*PI*freq2*TICK_PERIOD*tick);
	sample = (int) 32768.0*sin(2.0*PI*freq1*TICK_PERIOD*tick) + 32768.0*sin(2.0*PI*0*TICK_PERIOD*tick);
	sample = sample >>12; //scales its down
}

/*
 *  ====== clk_SWI_GTZ =====
 *  gtz sweep
 *  ====================
 */
void clk_SWI_GTZ_0697Hz(UArg arg0)
{
	/* */
   	static int iteration_num = 0;
   	static int Goertzel_Output = 0;

   	static short Q;
   	static short Q1 = 0;
   	static short Q2 = 0;

   	int maths1, maths2, maths3;

   	short input;
   	short coef_1 = 0x6D02; //hex for 697

   	input = (short) sample >> 12;

   	// first part
    maths1 = (Q1*coef_1)>>14;
   	Q = input + (short)maths1 - Q2;
   	//

   	if (iteration_num==206)
   	{
   		maths1 = (Q * Q);
   		maths2 = (Q1 * Q1);
   		maths3 = (Q * Q1 * coef_1) >> 14;

   		Goertzel_Output = (maths1 + maths2 - maths3);// >> 15;
   		Goertzel_Output <<= 1;  // scale up for sensitivity
   		iteration_num = 0;
   		Q = Q1 = Q2 = 0;
   	}

   	//update delayed variables
   	Q2 = Q1;
   	Q1 = Q;
   	iteration_num++;
   	//

    gtz_out[0] = Goertzel_Output;


}
