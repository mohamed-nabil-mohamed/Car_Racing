#include <stdint.h>
#define TIMER4_CFG_R            (*((volatile unsigned long *)0x40034000))
#define TIMER4_TAMR_R           (*((volatile unsigned long *)0x40034004))
#define TIMER4_TBMR_R           (*((volatile unsigned long *)0x40034008))
#define TIMER4_CTL_R            (*((volatile unsigned long *)0x4003400C))
#define TIMER4_SYNC_R           (*((volatile unsigned long *)0x40034010))
#define TIMER4_IMR_R            (*((volatile unsigned long *)0x40034018))
#define TIMER4_RIS_R            (*((volatile unsigned long *)0x4003401C))
#define TIMER4_MIS_R            (*((volatile unsigned long *)0x40034020))
#define TIMER4_ICR_R            (*((volatile unsigned long *)0x40034024))
#define TIMER4_TAILR_R          (*((volatile unsigned long *)0x40034028))
#define TIMER4_TBILR_R          (*((volatile unsigned long *)0x4003402C))
#define TIMER4_TAMATCHR_R       (*((volatile unsigned long *)0x40034030))
#define TIMER4_TBMATCHR_R       (*((volatile unsigned long *)0x40034034))
#define TIMER4_TAPR_R           (*((volatile unsigned long *)0x40034038))
#define TIMER4_TBPR_R           (*((volatile unsigned long *)0x4003403C))
#define TIMER4_TAPMR_R          (*((volatile unsigned long *)0x40034040))
#define TIMER4_TBPMR_R          (*((volatile unsigned long *)0x40034044))
#define TIMER4_TAR_R            (*((volatile unsigned long *)0x40034048))
#define TIMER4_TBR_R            (*((volatile unsigned long *)0x4003404C))
#define TIMER4_TAV_R            (*((volatile unsigned long *)0x40034050))
#define TIMER4_TBV_R            (*((volatile unsigned long *)0x40034054))
#define TIMER4_RTCPD_R          (*((volatile unsigned long *)0x40034058))
#define TIMER4_TAPS_R           (*((volatile unsigned long *)0x4003405C))
#define TIMER4_TBPS_R           (*((volatile unsigned long *)0x40034060))
#define TIMER4_TAPV_R           (*((volatile unsigned long *)0x40034064))
#define TIMER4_TBPV_R           (*((volatile unsigned long *)0x40034068))
#define TIMER4_PP_R             (*((volatile unsigned long *)0x40034FC0))

void Timer4_Init(uint32_t period){
  SYSCTL_RCGCTIMER_R |= 0x10;   // enable Timer4 module clock
  TIMER4_CTL_R = 0x00;          // disable Timer4A
  TIMER4_CFG_R = 0x00;          // configure Timer4A as a 32-bit timer
  TIMER4_TAMR_R = 0x02;         // configure Timer4A in periodic mode
  TIMER4_TAILR_R = period - 1;  // set the Timer4A interval
  TIMER4_ICR_R = 0x01;          // clear Timer4A timeout flag
  TIMER4_CTL_R |= 0x01;         // enable Timer4A
  NVIC_PRI17_R = (NVIC_PRI17_R&0xFF00FFFF)|0x00A00000; // set Timer4A interrupt priority to 5
  NVIC_EN2_R |= 0x10000000;     // enable interrupt 86 (Timer4A) in NVIC
}

void Timer4A_Handler(void){
  TIMER4_ICR_R = 0x01;          // clear Timer4A timeout flag
  // add your interrupt code here
}

void Timer4_EnableInterrupt(void){
  TIMER4_IMR_R |= 0x01;         // enable Timer4A timeout interrupt
}

void Timer4_DisableInterrupt(void){
  TIMER4_IMR_R &= ~0x01;        // disable Timer4A timeout interrupt
}
