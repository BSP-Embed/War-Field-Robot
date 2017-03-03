#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define SENSOR_DDR			DDRD
#define SENSOR_PORT			PORTD
#define SENSOR_PPIN			PIND
#define METAL_PIN			PD3
#define FIRE_PIN			PD2

//DEFINE CONSTANT
#define FIRE_SIGNAL			1
#define METAL_SIGNAL		2
	
/* STRUCTURE DEFINITION FOR FLAGS */
struct App{
	volatile int8u	Serial	: 1;
	volatile int8u	Meas	: 1;
	volatile int8u	FireDet	: 1;
	volatile int8u	MetalDet: 1;
	volatile int8u	Moving	: 1;
};

//FUNCTION PROTOTYPES
static void	init		(void);
static void disptitl 	(void);
static void tmr1init	(void);
static void	CtlBot		(void);
static void ChkFire		(void);
static void ChkMtl		(void);
static void SensorInit	(void);
static void RobotStop	(void);
#endif
