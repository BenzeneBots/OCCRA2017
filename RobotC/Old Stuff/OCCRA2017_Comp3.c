
task main()
{

	if( drivemotor ) {
			if( tmVal < time1[ timer1 ] ) {
				tmVal = time1[timer1] + 500;		// ReSchedule time value into the future.
				if( SensorValue[ ledCLAW ] )		// If the LEDs are on, turn them off.
					SensorValue[ ledCLAW ] = 0;
				else														// Else, turn them on.
					SensorValue[ ledCLAW ] = 1;
			}
		}
		else {															// Init LEDs and timer when claw is off.
				SensorValue[ ledCLAW ] = 0;
				tmVal = 0;
		}

}
