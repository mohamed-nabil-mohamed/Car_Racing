#include "GPIO.h"

void PortF_Init(void){
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 1<<5;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R =1<<1 | 1<<2 | 1<<3;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R =0x00;       // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0 

	GPIO_PORTF_IS_R=0;
	GPIO_PORTF_IBE_R=0;
	GPIO_PORTF_IEV_R=0;		//0x11		
	GPIO_PORTF_ICR_R=0x11;
	GPIO_PORTF_IM_R|=0x11;
	NVIC_PRI7_R=(NVIC_PRI7_R&0xFF00FFFF)|0x00A00000;
	NVIC_EN0_R=0x40000000;
}
