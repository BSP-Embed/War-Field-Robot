/*	Main.c: Application program for War Filed Robot		*/
/*	Written By	: Prashanth BS (info@bspembed.com)		*/
/*	Demo at		: www.youtube.com/c/bspembed			*/

#include "main.h"

struct App Flags;
extern	lcdptr;
char	sbuf[10];
int8u	CtlSig;

char *CtlMsg[] = {" Moving Forward", "Moving Backward", "  Moving Left", "  Moving Right", " ROBOT STOPPED"};
void (*RobotCtlFun[]) (void) = {Forward, Backward, Left, Right, Stop};
	
int main(void) {
	init();
	while (TRUE) {
		if (Flags.Serial)
			CtlBot();
		if (Flags.Meas) {
			ChkFire();
			ChkMtl();
		}
		sleep_cpu();
	}
	return 0;
}
static void init(void) {
	buzinit();
	ledinit();
	motorinit();
	beep(2,100);
	lcdinit();
	uartinit();
	tmr1init();
	SensorInit();
	disptitl(); 
	EnUARTInt();
	sei();
	sleep_enable();
	sleep_cpu();
}
static void CtlBot(void) {
	int8u Ctl = sbuf[0] - 'A';
	lcdclrr(1);
	lcdws(CtlMsg[Ctl]);
	RobotCtlFun[Ctl]();
	if (Ctl >= 0 && Ctl <= 3)
		Flags.Moving = TRUE;
	Flags.Serial = FALSE;
	EnUARTInt();
}
static void ChkFire(void) {
	if ((SENSOR_PPIN & _BV(FIRE_PIN)) == 0) {
		if (!Flags.FireDet) {
			putchar(FIRE_SIGNAL);
			if (Flags.Moving)
				RobotStop();
			lcdclrr(1);
			lcdws(" FIRE DETECTED");
			beep(3,150);
			Flags.FireDet = TRUE;
		}
	} else 
		if (Flags.FireDet) {
			lcdclrr(1);
			Flags.FireDet = FALSE;
		}
	
}
static void ChkMtl(void) {
	if ((SENSOR_PPIN & _BV(METAL_PIN)) == 0) { 
		if (!Flags.MetalDet) {
			putchar(METAL_SIGNAL);
			if (Flags.Moving)
			RobotStop();
			lcdclrr(1);
			lcdws(" METAL DETECTED");
			beep(3,150);
			Flags.MetalDet = TRUE;
		}
	}else
		if (Flags.MetalDet) {
			lcdclrr(1);
			Flags.MetalDet = FALSE;
		}
}
static void disptitl(void) { 
	lcdclr();
	lcdws(" WAR FIELD ROBOT");
}
static void RobotStop(void) {
	Stop();
	lcdclrr(1);
	lcdws(CtlMsg[4]);
	dlyms(1000);
	Flags.Moving = FALSE;
}

static void tmr1init(void) {
	TCNT1H   = 225;					/* overflows at every 250msec */
	TCNT1L   = 123;
	TIMSK   |= _BV(TOIE1);			/* ENABLE OVERFLOW INTERRUPT */
	TCCR1A   = 0x00;					
	TCCR1B  |= _BV(CS12);			 /* PRESCALAR BY 256 */
}
static void SensorInit(void){
	SENSOR_DDR 	&= ~((_BV(FIRE_PIN)) | (_BV(METAL_PIN))); 
	SENSOR_PORT |= _BV(FIRE_PIN) | _BV(METAL_PIN);
}
ISR(TIMER1_OVF_vect) { 
	static int8u i,j,k;
	TCNT1H = 225;
	TCNT1L = 123;
	if (++i >= 20) i = 0;
	switch(i) {
		case 0: case 2: ledon();  break;
		case 1: case 3: ledoff(); break;
	} 
	if (++j >= 2) {
		j = 0;
		Flags.Meas = TRUE;
	}
}
ISR (USART_RXC_vect) {
	static int8u msgcnt;
	static int8u state = MSG_WAIT_MSG;
		
	switch (state) {
		case MSG_WAIT_MSG:
					if (UDR == '*') state = MSG_PH_NUM;
					break;
		case MSG_PH_NUM:
				if ((sbuf[msgcnt++] = UDR) == '#') {
					sbuf[msgcnt-1] = '\0';
					state = MSG_WAIT_MSG;
					msgcnt = 0;
					Flags.Serial = TRUE;
					DisUARTInt();
				}
	}
} 