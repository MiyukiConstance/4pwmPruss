
/** Basic PRU C program to flash an LED that is attached to P9_27 at a
*   frequency of 10 Hz, until a button that is attached to P9_28 is pressed
**/



/* the registers for I/O and interrupts */
//volatile register unsigned int __R31, __R30;
volatile register unsigned int __R31,  __R30;
unsigned int i;                  // the counter in the time delay
//unsigned int delay =769000;     // the delay (manually determined)
unsigned int delay = 153.8;
unsigned int cycle = 0;
unsigned int pcnt01 = 50;
unsigned int pcnt02 = 75;
unsigned int pcnt03 = 50;
unsigned int pcnt04 = 25;
unsigned int off = 0;
unsigned int off1 = 0;
unsigned int off2 = 0;
unsigned int off3 = 0;
unsigned int dbnc = 0;
unsigned int gotHigh = 0;
unsigned int gotLow = 0;

int main()
{

   // keep looping forever
   while(1) {

      if(off == 0) {
      __R30 = __R30 | 1<<5;         // turn on the LED r30.5
	}
      if(off1 == 0) {
      __R30 = __R30 | 1<<3;
	}
      if(off2 == 0) {
      __R30 = __R30 |  1<<1;
        }
      if(off3 ==0) {
      __R30 = __R30  |  1<<2;
	}

      cycle = cycle + 1;
      for(i=0; i<delay; i++) {}     // sleep for the delay
// maintenant evaluer si pcnt01 est a cycle
      if(pcnt01 == cycle) {
      __R30 = __R30 & 0<<5;	   // turn off the LED r30.5 
      off = 1;        
      }

      if(pcnt02 == cycle) {
      __R30 = __R30 & 0<<3;       // turn off the LED r30.3
      off1 = 1;
      }
      if(pcnt03 == cycle) {
      __R30 = __R30 &  0<<1;
      off2 = 1;
      } 
      if(pcnt04 == cycle) {
      __R30 = __R30 & 0<<2;
      off3 = 1;
      }
	



if(gotHigh == 0) {

	if(!(__R31 & 0<<0)) {  // pour si zero
	dbnc = dbnc + 1;
	}

	if(dbnc == 100) {
	pcnt01 = 28;	//set pcnt01 a 10 si 28 condition met
	dbnc = 0;
// sortir du high (low pour linstant)
	gotHigh = 1;
 
	}
}
if(gotHigh == 1) {
	if(!(__R31 & 1<<0)) {
	dbnc = dbnc + 1;
	}
	if(dbnc == 100) {
	pcnt01 = 55;
	gotLow = 1;	
	gotHigh = 0;
	dbnc = 0;
	}
}




	if(cycle == 99) {
	off = 0;
        off1 = 0;
	off2 = 0;
	off3 = 0;
	cycle = 0;

	}

   }

   // Exiting the application - send the interrupt
//   __R31 = 35;                      // PRUEVENT_0 on PRU0_R31_VEC_VALID
//   __halt();                        // halt the PRU
}


