#pragma config(Sensor, dgtl1,  PSIOut1,        sensorDigitalOut)
#pragma config(Sensor, dgtl3,  PSIOut2,        sensorDigitalOut)
#pragma config(Motor,  port2,           motor1,        tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port3,           motor2,        tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port4,           motor3,        tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           motor4,        tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port6,           motor5,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           motor6,        tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define STOP			0                   	// Motor Stop Speed
#define MOTOR_NUM			2		// First two motors
#define MOTOR_MAX_VALUE			(127)
#define MOTOR_MIN_VALUE			(-127)

// Macros
#define max( A, B )				A > B ? A : B
#define min( A, B )				A < B ? A : B
#define LimitVal( L, T, H)		max( min( T, H ), L)

bool flag = false;
int mot[ MOTOR_NUM ];			// Array to hold requested speed for the motors
int scale = -1;				   // Multiplies by the scale value flag = 0;
int joy_flag;

task main () {

	wait1Msec( 400 );


	while ( true ) {

		int joy_speed, joy_turn;


		if ( vexRT[1] > 0 ) {
			joy_flag = 1;
		}
		else if ( vexRT[1] < 0 ) {
			joy_flag = -1;
		}

		joy_speed = sqrt(127*127 - vexRT[2]*vexRT[2])*joy_flag;	// Grab a copy of the values from the system vars.
		joy_turn = sqrt(127*127 - vexRT[1]*vexRT[1]) + (127);
		joy_speed= vexRT[1] * -1;
		 joy_turn = vexRT[2];

		// Compute movement based on a foward / reverse knob and a steering knob.
		mot[ 0 ] = LimitVal( MOTOR_MIN_VALUE, (joy_speed)/2, MOTOR_MAX_VALUE );
		mot[ 1 ] = LimitVal( MOTOR_MIN_VALUE, (joy_turn)/2, MOTOR_MAX_VALUE );

		//Flip Functionality

		if ( vexRT[Btn7UXmtr2] ) {
			if ( flag ) {
				flag = false;
			}
			else {
				flag = true;
			}
		}
		if ( flag ) {
			scale = -1;
		}
		else {
			scale = 1;
		}

		//Motor Drive

		motor[motor1] = mot[0] * scale;
		motor[motor2] = mot[0] * scale;
		motor[motor3] = mot[1] * scale;
		motor[motor4] = mot[1] * scale;

		//Pneumatic System Output Control

		if ( vexRT[Btn6UXmtr2] ) {
			SensorValue[PSIOut1]=0;
			SensorValue[PSIOut2]=1;
		}
		if ( vexRT[Btn6DXmtr2] ) {
			SensorValue[PSIOut1]=1;
			SensorValue[PSIOut2]=0;
		}

		//Intake Motors

		if ( vexRT[Btn5UXmtr2] ) {
			motor[motor5] = 127;
		}
		else {
			motor[motor5] = 0;
		}

		if ( vexRT[Btn5UXmtr2] ) {
			motor[motor6] = 127;
		}
		else {
			motor[motor6] = 0;
		}

		if ( vexRT[Btn5DXmtr2] ) {
			motor[motor5] = -127;
		}
		else {
			motor[motor5] = 0;

			if ( vexRT[Btn5DXmtr2] ) {
				motor[motor6] = -127;
			}
			else {
				motor[motor6] = 0;
			}

		}
	}
}