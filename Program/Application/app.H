#ifndef _APP_H
#define _APP_H

/* Main settings */

/*comment below line for release*/

//#define TESTING

#define EEPROM_DISPLAY				0

/******** MAIN CONFIGURATION ENDS ****************/

/* LCD CONFIGURATION */
#define LCD_DDR           	   		DDRC 
#define LCD_DATA_PORT          		PORTC
#define LCD_ENABLE_PIN        		PC3 
#define LCD_REGISTER_SELECT_PIN     PC2
#define DISPLAY_INIT				1
#define LCD_NSCRL					1
#define FLOAT_T0_STRING				1
#define DECIMAL_PRECISION			100

/******** LCD CONFIGURATION ENDS ****************/

/* BUZZER: CONFIGURATION */
#define	BUZ_DDR						DDRC
#define	BUZ_PORT					PORTC
#define	BUZ_PIN						PC1
#define OFF_TIME					100
/******** BUZZER CONFIGURATION ENDS ****************/

/* LED: CONFIGURATION */

#define	LED_DDR			DDRC
#define	LED_PORT		PORTC
#define	LED_PIN			PC0

#define OFF_TIME		100
/******** LED CONFIGURATION ENDS ****************/

/* GSM: CONFIGURATION */
#define OPhNum	"7899249682"


#define MSG_START					""
#define MSG_END						". Automated SMS By: CBB."

/******** GSM CONFIGURATION ENDS ****************/

/******** MOTOR CONFIGURATION   ****************/
#define MOT_PORT			PORTA
#define MOT_DDR				DDRA
#define MOT1_AN				PA3
#define MOT1_CA				PA4
#define MOT2_AN				PA5
#define MOT2_CA				PA6
/******** MOTOR CONFIGURATION ENDS  ****************/

/******** PWM CONFIGURATION  *******************/
#define PWM_DDR				DDRD
#define PWM_PIN				PD7
/********  PWM CONFIGURATION ENDS **************/

/******** ALCOHOL SENSOR PIN  *******************/
#define ALSENS_DDR			DDRB
#define ALSENS_PORT			PORTB
#define ALSENS_IPIN			PINB
#define ALSENS_PIN			PB7
/******** PWM CONFIGURATION  *******************/

/******** ULTRASONIC SENSOR PIN  *******************/
#define	ULTSEN_DDR			DDRB
#define	ULTSEN_PORT			PORTB
#define	ULTSEN_PIN			PINB
#define ECHO_PIN			PB1
#define TRIG_PIN			PB0
/******** ULTRASONIC SENSOR PIN  *******************/

#endif
