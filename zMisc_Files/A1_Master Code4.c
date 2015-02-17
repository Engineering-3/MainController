printf("Done compling!\n");

/**************************************************************************
*                             D E F I N E S
* (We can't use defines in the current PicoC, so we'll just use globals)
**************************************************************************/
#define ESC_CHAR							0x1B

// Constants
#define THERMAL_THRESHOLD					1850	// Was c
#define FRONT_LEFT_ULTRASOUND_THRESHOLD		120		// Was d
#define REAR_RIGHT_ULTRASOUND_THRESHOLD		130		// Was e
#define LIGHT_SENSOR_FRONT_THRESHOLD		1725	// Was f
#define LIGHT_SENSOR_REAR_THRESHOLD			1675	// Was r
#define BUMPER_CODE_LOOP_TIME				1400	// Was g
#define WALL_FOLLOW_LEFT_TURN_TIME			2000	// Was h
#define TURN_MOTOR_SLOW_SPEED 				0x78	// For turning around corners
#define VICTIM_THERMAL_COUNT_MAX 			15		// Was m

// Constants for motor speeds
#define MOT_FORWARD_SLOW 					9		// Speed difference from 'off' for slower motor in wall following routine
#define MOT_OFF								0x7F

// For the entire robot - we're in two modes, forward or backward mode.
#define	FORWARD								0
#define REVERSE								1

// Hardware constants
#define BANK_A								0x12
#define BANK_B								0x13
#define GPIO_I2C_ADDRESS					0x27
#define MOTOR_I2C_ADDRESS					0x61

// Bit defines for each of the two GPIO ports A and B
// PortA
//   Inputs
#define FRONT_BUMPER_BIT_A					0x01
#define RIGHT_BUMPER_BIT_A	 				0x02
#define REAR_BUMPER_BIT_A					0x04
#define LEFT_BUMPER_BIT_A					0x08
//   Outputs
#define FRONT_LED_BIT_A						0x10
#define RIGHT_LED_BIT_A						0x20
#define REAR_LED_BIT_A						0x40
#define LEFT_LED_BIT_A						0x80
// PortB
//   Inputs
#define FRONT_LEFT_WALL_FOLLOWER_BIT_B		0x01
#define FRONT_RIGHT_WALL_FOLLOWER_BIT_B		0x02
#define REAR_LEFT_WALL_FOLLOWER_BIT_B		0x04
#define REAR_RIGHT_WALL_FOLLOWER_BIT_B		0x08
#define START_STOP_BUTTON_BIT_B 			0x80

// Analog input mapping
#define FRONT_LEFT_ULTRASOUND_ANALOG		11
#define REAR_RIGHT_ULTRASOUND_ANALOG		12
#define FRONT_THERMAL_ANALOG				21
#define RIGHT_THERMAL_ANALOG				22
#define REAR_THERMAL_ANALOG					23
#define LEFT_THERMAL_ANALOG	 				24
#define FRONT_LIGHT_SENSOR_ANALOG			27
#define REAR_LIGHT_SENSOR_ANALOG			28

// Enum for use with MotorsTurn()
typedef enum {
	RIGHT_FORWARD,
	RIGHT_REVERSE,
	LEFT_FORWARD,
	LEFT_REVERSE,
	RIGHT_SPIN,
	LEFT_SPIN,
	RIGHT_SLOW,
	LEFT_SLOW,
	GO_FORWARD,
	STOP,
	COAST,
	FORWARD_SLOW_RIGHT,
	FORWARD_SLOW_LEFT,
	FORWARD_SLOW,
	RIGHT_PIVOT,
	LEFT_PIVOT
} MotorsTurnType;
	
// Defines (should be enum) for use with CheckBumper()
int FRONT_BUMPER =						1
int RIGHT_BUMPER = 						2
int REAR_BUMPER = 						3
int LEFT_BUMPER = 						4
int FRONT_LEFT_BUMPER = 				5
int FRONT_RIGHT_BUMPER = 				6
int REAR_LEFT_BUMPER = 					7
int REAR_RIGHT_BUMPER = 				8

// Defines for use with ReadLightSensor()
int FRONT_LIGHT =						1
int REAR_LIGHT = 						2
int WHITE =								1
int BLACK =								2

// Defines for use with ReadUltrasoundSensor()
#define FRONT_LEFT 						1
#define REAR_RIGHT 						2

/************************************
* G L O B A L   V A R I A B L E S
************************************/

// Define and intialize all global variables
int i = 15;			//vid time loop front
int j = 15;			//vid time loop left
int k = 15;			//vid time loop rear
int l = 15;			//vid time loop right
int n = 0; 			//vid turn delay front
int o = 0; 			//vid turn delay left
int p = 0; 			//vid turn delay rear
int q = 0; 			//vid turn delay right
int Direction = 0;	// 0 = Forward, 1 = Backward
int LastLeft = 0;

/********************************
*       F U N C T I O N S 
********************************/

/**** Sensor Helper Functions ****/

// Read's a byte from BANK_A or BANK_B and returns true
// or false if Bit is set in the resulting byte
int ReadBank(char Bank, char Bit)
{
	delay(2);
	if (readi2c(GPIO_I2C_ADDRESS, Bank) & Bit)
	{
		delay(2);
		return(1);
	}
	else
	{
		delay(2);
		return(0);
	}
}

// Writes a value to PortA (for now, just the top LEDs)
void WriteBankA(int Value)
{
	writei2c(GPIO_I2C_ADDRESS, BANK_A, Value);
	delay(2);
}

/****** B U M P E R   H E L P E R   F U N C T I O N S ***************/

// Return true (1) or false (0) based upon bumper state. If a wall is
// present, then return true. This function honors the Direction variable
// so that the actual bumpers used will change based upon direction.
// TODO: Refactor this using an array to save code
int CheckBumper(int WhichBumper)
{
	int ReturnVal = 0;
	
	if (Direction == FORWARD)
	{
		switch (WhichBumper)
		{
		case FRONT_BUMPER:
			ReturnVal = ReadBank(BANK_A, FRONT_BUMPER_BIT_A);
			break;
		case RIGHT_BUMPER:
			ReturnVal = ReadBank(BANK_A, RIGHT_BUMPER_BIT_A);
			break;
		case REAR_BUMPER:
			ReturnVal = ReadBank(BANK_A, REAR_BUMPER_BIT_A);
			break;
		case LEFT_BUMPER:
			ReturnVal = ReadBank(BANK_A, LEFT_BUMPER_BIT_A);
			break;
		case FRONT_LEFT_BUMPER:
			ReturnVal = ReadBank(BANK_B, FRONT_LEFT_WALL_FOLLOWER_BIT_B);
			break;
		case FRONT_RIGHT_BUMPER:
			ReturnVal = ReadBank(BANK_B, FRONT_RIGHT_WALL_FOLLOWER_BIT_B);
			break;
		case REAR_LEFT_BUMPER:
			ReturnVal = ReadBank(BANK_B, REAR_LEFT_WALL_FOLLOWER_BIT_B);
			break;
		case REAR_RIGHT_BUMPER:
			ReturnVal = ReadBank(BANK_B, REAR_RIGHT_WALL_FOLLOWER_BIT_B);
			break;
		default:
		}
	}
	else
	{
		switch (WhichBumper)
		{
		case FRONT_BUMPER:
			ReturnVal = ReadBank(BANK_A, REAR_BUMPER_BIT_A);
			break;
		case RIGHT_BUMPER:
			ReturnVal = ReadBank(BANK_A, LEFT_BUMPER_BIT_A);
			break;
		case REAR_BUMPER:
			ReturnVal = ReadBank(BANK_A, FRONT_BUMPER_BIT_A);
			break;
		case LEFT_BUMPER:
			ReturnVal = ReadBank(BANK_A, RIGHT_BUMPER_BIT_A);
			break;
		case FRONT_LEFT_BUMPER:
			ReturnVal = ReadBank(BANK_B, REAR_RIGHT_WALL_FOLLOWER_BIT_B);
			break;
		case FRONT_RIGHT_BUMPER:
			ReturnVal = ReadBank(BANK_B, REAR_LEFT_WALL_FOLLOWER_BIT_B);
			break;
		case REAR_LEFT_BUMPER:
			ReturnVal = ReadBank(BANK_B, FRONT_RIGHT_WALL_FOLLOWER_BIT_B);
			break;
		case REAR_RIGHT_BUMPER:
			ReturnVal = ReadBank(BANK_B, FRONT_LEFT_WALL_FOLLOWER_BIT_B);
			break;
		default:
		}
	}
	// This works around a bug in PicoC that doesn't allow us to return
	// from within a case statement properly.
	return(ReturnVal);
}

/****** M O T O R   H E L P E R    F U N C T I O N S ***************/
/* Motor 1 is left hand motor:
	0xFF = forward
	0x80 = stop (locked)
	0x01 = reverse
	0x00 = coast
   Motor 2 is right hand motor:
    0xFF = reverse
	0x80 = stop (locked)
	0x01 = forward
	0x00 = coast
*/

// Low level motor command - set each motor to a specified speed
// This routine honors the global Direction mode
void Motors(unsigned char Motor1Speed, unsigned char Motor2Speed)
{
	if (Direction == FORWARD)
	{
		// First the right motor
		writei2c(MOTOR_I2C_ADDRESS, 1, Motor1Speed);
		delay(2);
		// Then the left motor
		writei2c(MOTOR_I2C_ADDRESS, 2, Motor2Speed);
		delay(2);
	}
	else
	{
		// First the right motor
		writei2c(MOTOR_I2C_ADDRESS, 1, Motor2Speed);
		delay(2);
		// Then the left motor
		writei2c(MOTOR_I2C_ADDRESS, 2, Motor1Speed);
		delay(2);
	}
}

// High level function for telling the motors what direction to go
// The function respects the Direction mode of the robot
// TODO: Refactor this using a big 2-dimensional array to keep code shorter
void MotorsTurn(unsigned char TurnDirection)
{
	switch(TurnDirection)
	{
	case RIGHT_PIVOT:
		Motors(0xFF, MOT_OFF);
		break;
	case LEFT_PIVOT:
		Motors(MOT_OFF, 0x01);
		break;
	case RIGHT_FORWARD:
		Motors(0xFF, 0x00);
		break;
	case RIGHT_REVERSE:
		Motors(0x01, 0x00);
		break;
	case LEFT_FORWARD:
		Motors(0x00, 0x01);
		break;
	case LEFT_REVERSE:
		Motors(0x00, 0xFF);
		break;
	case RIGHT_SPIN:
		Motors(0xFF, 0xFF);
		break;
	case LEFT_SPIN:
		Motors(0x01, 0x01);
		break;
	case RIGHT_SLOW:
		Motors(0xFF, TURN_MOTOR_SLOW_SPEED);
		break;
	case LEFT_SLOW:
		Motors(TURN_MOTOR_SLOW_SPEED, 0x01);
		break;
	case GO_FORWARD:
		Motors(0xFF, 0x01);
		break;
	case STOP:
		Motors(MOT_OFF, MOT_OFF);
		break;
	case COAST:
		Motors(0x00, 0x00);
		break;
	case FORWARD_SLOW_LEFT:
		Motors(MOT_OFF + MOT_FORWARD_SLOW, 0x01);
		break;
	case FORWARD_SLOW_RIGHT:
		Motors(0xFF, MOT_OFF - MOT_FORWARD_SLOW);
		break;
	case FORWARD_SLOW:
		Motors(MOT_OFF + MOT_FORWARD_SLOW, MOT_OFF - MOT_FORWARD_SLOW);
		break;
	default:
		printf("ERROR Unknown motor command.\n");
		break;
	}
}

/****** A N A L O G   S E N S O R    F U N C T I O N S ***************/

// This function returns BLACK or WHITE
// Pass it either FRONT_LIGHT or REAR_LIGHT
// It honors the global Direction mode
int ReadLightSensor(int WhichSensor)
{
	if (Direction == FORWARD)
	{
		if (WhichSensor == FRONT_LIGHT)
		{
			if (analog(FRONT_LIGHT_SENSOR_ANALOG) > LIGHT_SENSOR_FRONT_THRESHOLD)
			{
				return(BLACK);
			}
			else
			{
				return(WHITE);
			}
		}
		else
		{
			if (analog(REAR_LIGHT_SENSOR_ANALOG) > LIGHT_SENSOR_REAR_THRESHOLD)
			{
				return(BLACK);
			}
			else
			{
				return(WHITE);
			}
		}
	}
	else
	{
		if (WhichSensor == FRONT_LIGHT)
		{
			if (analog(REAR_LIGHT_SENSOR_ANALOG) > LIGHT_SENSOR_REAR_THRESHOLD)
			{
				return(BLACK);
			}
			else
			{
				return(WHITE);
			}
		}
		else
		{
			if (analog(FRONT_LIGHT_SENSOR_ANALOG) > LIGHT_SENSOR_FRONT_THRESHOLD)
			{
				return(BLACK);
			}
			else
			{
				return(WHITE);
			}
		}
	}
}

// Read the FRONT_LEFT or RIGHT_REAR ultrasound sensor
// Returns true (1) if something is closer than threshold
// Returns false (0) otherwise
// It honors the global Direction mode
int ReadUltrasoundSensor(int WhichSensor)
{
	if (Direction == FORWARD)
	{
		if (WhichSensor == FRONT_LEFT)
		{
			return(analog(FRONT_LEFT_ULTRASOUND_ANALOG) < FRONT_LEFT_ULTRASOUND_THRESHOLD);
		}
		else
		{
			return(analog(REAR_RIGHT_ULTRASOUND_ANALOG) < REAR_RIGHT_ULTRASOUND_THRESHOLD);
		}
	}
	else
	{
		if (WhichSensor == FRONT_LEFT)
		{
			return(analog(REAR_RIGHT_ULTRASOUND_ANALOG) < REAR_RIGHT_ULTRASOUND_THRESHOLD);
		}
		else
		{
			return(analog(FRONT_LEFT_ULTRASOUND_ANALOG) < FRONT_LEFT_ULTRASOUND_THRESHOLD);
		}
	}
}

// Helper function to print current front and rear downward facing light sensors
void PrintSensors()
{
	// First print the light sensors
	if (ReadLightSensor(FRONT_LIGHT) == WHITE)
	{
		printf("Front Light Sensor = WHITE      %d\n", analog(FRONT_LIGHT_SENSOR_ANALOG));
	}
	else
	{
		printf("Front Light Sensor = BLACK      %d\n", analog(FRONT_LIGHT_SENSOR_ANALOG));
	}
	if (ReadLightSensor(REAR_LIGHT) == WHITE)
	{
		printf("Rear Light Sensor = WHITE       %d\n", analog(REAR_LIGHT_SENSOR_ANALOG));
	}
	else
	{
		printf("Rear Light Sensor = BLACK\n     %d", analog(REAR_LIGHT_SENSOR_ANALOG));
	}
	
	// Then ultrasound sensors
	if (ReadUltrasoundSensor(FRONT_LEFT))
	{
		printf("Front Left Ultrasound is TRUE   %d\n", analog(FRONT_LEFT_ULTRASOUND_ANALOG));
	}
	else
	{
		printf("Front Left Ultrasound is FALSE  %d\n", analog(FRONT_LEFT_ULTRASOUND_ANALOG));
	}
	if (ReadUltrasoundSensor(REAR_RIGHT))
	{
		printf("Rear Right Ultrasound is TRUE   %d\n", analog(REAR_RIGHT_ULTRASOUND_ANALOG));
	}
	else
	{
		printf("Rear Right Ultrasound is FALSE  %d\n", analog(REAR_RIGHT_ULTRASOUND_ANALOG));
	}
}

/**********************************************/
/*               S Y S T E M                  */
/*      H E L P E R    F U N C T I O N S      */
/**********************************************/
// Set up hardware on boot
void SystemInitalize()
{
	//initialize and define
	//initialize ports

	//SD 20
	writei2c(0x61, 21, 0x00);
	delay(2);

	//MCD Bank A
	writei2c(0x27, 0x00, 0x00);
	delay(2);
	writei2c(0x27, 0x0c, 0x00);
	delay(2);
	writei2c(0x27, 0x02, 0x00);
	delay(2);
	
	//MCD Bank B
	writei2c(0x27, 0x01, 0x00);
	delay(2);
	writei2c(0x27, 0x0d, 0x00);
	delay(2);
	writei2c(0x27, 0x03, 0x00);
	delay(2);

	//define ports
	writei2c(0x27, 0x00, 0x0f); //set A ports 1-4 as inputs 
	delay(2);
	writei2c(0x27, 0x02, 0x0f); //set A ports 1-4 as inverse
	delay(2);
	writei2c(0x27, 0x01, 0x8f); //set B ports 1-4 & 8 as inputs
	delay(2);
	writei2c(0x27, 0x03, 0x8f); //set B ports 1-4 & 8 inverse
	delay(2);
	writei2c(0x27, 0x0d, 0x80); //pull up resister on port 8
	delay(2);
}

// Check to see if user has pressed a key, and if so
// bail and return to SRV firmware command line.
// Because the input() command seems to need to be called
// once before it begins to work properly, call this 
// function with Real = 0 on startup of your application,
// then after that use Real = 1.
void CheckForUserEscape(int Real)
{
	int c;
	if (signal())
	{
		c = input();
		if (Real)
		{
			MotorsTurn(COAST);
			exit(0);
		}
	}
}

// Simple hang until user presses the button
void WaitForButtonPress()
{
	// Wait until it's Pressed
	while (!ReadBank(BANK_B, START_STOP_BUTTON_BIT_B))
	{
		delay(50);
		CheckForUserEscape(1);
	}
	delay(50);
	printf("Robot is now running\n");
	// Wait until it's released
	while (ReadBank(BANK_B, START_STOP_BUTTON_BIT_B))
	{
		delay(50);
	}
	delay(50);
}

// Check to see if user has pressed the little yellow button
// If so, sit and wait for them to press it again. As long as 
// this function gets called often enough, this will allow the 
// user to puase operation at any time and resuem it with a 
// button press. 
void ButtonCheck()
{
	// Also check to see if user typed a character on the terminal
	CheckForUserEscape(1);

	// If the button is pushed down
	if (ReadBank(BANK_B, START_STOP_BUTTON_BIT_B))
	{
		MotorsTurn(COAST);
		printf("Robot is now paused\n");
		
		delay(50);
		// Wait until it's released
		while (ReadBank(BANK_B, START_STOP_BUTTON_BIT_B))
		{
			delay(50);
		}
		delay(50);
		
		WaitForButtonPress();
	}
}

// TODO: Document
void VictimCountReset()
{
	if (i < VICTIM_THERMAL_COUNT_MAX + 1)
	{
		i++;
	}
	if (j < VICTIM_THERMAL_COUNT_MAX + 1)
	{
		j++;
	}
	if (k < VICTIM_THERMAL_COUNT_MAX + 1)
	{
		k++;
	}
	if (l < VICTIM_THERMAL_COUNT_MAX + 1)
	{
		l++;
	}
}

// Blink one of the four LEDs 10 times (100ms on, 100ms off)
void BlinkTheLight(char Light)
{
	int LightBlinkCount;
	
	for (LightBlinkCount = 0; LightBlinkCount < 10; LightBlinkCount++)
	{
		WriteBankA(Light);
		delay(100);
		WriteBankA(0x00);
		delay(100);
	}
}

// TODO: Document
void VictimIDHelper(int * Var1, int * Var2, int BitPos, int Sensor, int Light)
{
	if (*Var1 > VICTIM_THERMAL_COUNT_MAX)
	{
		// Is there a victim here?
		// Only count this sigting if there is also a wall here
		if (
			(analog(Sensor) > THERMAL_THRESHOLD)
			&&
			(ReadBank(BANK_A, BitPos))
		)
		{
			// Zero out the victim counter for this direction
			*Var1 = 0;
			*Var2++;
			BlinkTheLight(Light);
		}
	}
}

// TODO: Document
void VictimID()
{
	VictimIDHelper(&i, &n, FRONT_BUMPER_BIT_A, FRONT_THERMAL_ANALOG, FRONT_LED_BIT_A);
	VictimIDHelper(&j, &o, RIGHT_BUMPER_BIT_A, RIGHT_THERMAL_ANALOG, RIGHT_LED_BIT_A);
	VictimIDHelper(&k, &p, REAR_BUMPER_BIT_A, REAR_THERMAL_ANALOG, REAR_LED_BIT_A);
	VictimIDHelper(&l, &q, LEFT_BUMPER_BIT_A, LEFT_THERMAL_ANALOG, LEFT_LED_BIT_A);
}

// It looks like we're blinking the directional LEDs
// based on if we've seen a victim on that side,
// then reseting the count for that side
void BlinkForVictims()
{
	if (n > 0)
	{
		MotorsTurn(COAST);
		BlinkTheLight(FRONT_LED_BIT_A);
		n = 0;
	}
	
	if (o > 0)
	{
		MotorsTurn(COAST);
		BlinkTheLight(RIGHT_LED_BIT_A);
		o = 0;
	}
	
	if (p > 0)
	{
		MotorsTurn(COAST);
		BlinkTheLight(REAR_LED_BIT_A);
		p = 0;
	}

	if (q > 0)
	{
		MotorsTurn(COAST);
		BlinkTheLight(LEFT_LED_BIT_A);
		q = 0;
	}
}

// Check bumpers
// If the front (direction dependant) bumper is 'pressed', then
// TODO: Document
void BumperCheck(
	char Bumper1, 
	char Bumper2,	
	char Motor1, 
	char Motor2, 
	int BlockNumber, 
	int IterationNumber
)
{
	int t0;
	
	// Check to see if we detect anything
	if (CheckBumper(FRONT_BUMPER))
	{
printf("Found something in front\n");
		MotorsTurn(COAST);
		
		// Check to see if something is in this direction
		if (ReadBank(BANK_A, Bumper2))
		{
printf("Found something in a direction\n");
			t0 = time();
			while (time() < t0 + BUMPER_CODE_LOOP_TIME)
			{
//				VictimID();
				ButtonCheck();
				// Then turn this way 
//				Motors(Motor1, Motor2);
			}
			MotorsTurn(COAST);
		}
	}
}

void MoveRobot();
/*********************************************
* This is the big block of code
* We need to move either forward or backward
**********************************************/
void MoveRobot()
{
	int t0;

//	VictimCountReset();
	ButtonCheck();
//	VictimID();	
	
	// bumperCode_forward
	// While there is a wall in front of us, keep turning until
	// there ISN'T a wall in front of us.	
	if(CheckBumper(FRONT_BUMPER))
	{
		// If we are left wall following, and there's a wall in 
		// front of us, then figure out if we should turn right
		// or just reverse direction (i.e. spin 180 without spinning)
		if (CheckBumper(FRONT_RIGHT_BUMPER))
		{
			// There is a wall to our right, so just reverse direction
			if (Direction == FORWARD)
			{
				Direction = REVERSE;
			}
			else
			{
				Direction = FORWARD;
			}
			MotorsTurn(STOP);
			delay(1000);
			// Display which direction we're going (just for testing)
			if (Direction == FORWARD)
			{
				WriteBankA(FRONT_LED_BIT_A);
			}
			else
			{
				WriteBankA(REAR_LED_BIT_A);
			}
			
		}
		else
		{
			// There is no wall to our right, so turn right
			MotorsTurn(RIGHT_SPIN);
			delay(1000);
			MotorsTurn(STOP);
		}
	}



//		ButtonCheck();
//printf("Checking front bumper\n");
//		BumperCheck(
//			BumperToCheckBit1, 
//			BumperToCheckBit2,
//			0xFF, 
//			0xFF,
//			BlockNumber,
//			1
//		);
//		BumperCheck(
//			BumperToCheckBit1, 
//			BumperToCheckBit3,		// RIGHT
//			0x01, 					// LEFT TURN
//			0x01,
//			BlockNumber,
//			2
//		);
//		BumperCheck(
//			BumperToCheckBit1, 
//			BumperToCheckBit4,		// FRONT
//			0xFF, 					// RIGHT TURN
//			0xFF,
//			BlockNumber,
//			3
//		);
//	}

	// wallfollowleft
	// Drive forward and keep distance from left wall
	// If the front ultrasound sensor isn't seeing anything to the front left of us
//	if (!ReadUltrasoundSensor(FRONT_LEFT))
	if (0)
	{
		// Then it's time to turn
		// But first, drive until the left rear bumper stops seeing the wall
printf("Front left ultrasound does not see a wall.\n");
		// If there is a wall to our left rear
		if (CheckBumper(REAR_LEFT_BUMPER))
		{
printf("There is a wall to my rear left. Continuing wall following.\n");
			// Then just keep chuging along forward
			if (CheckBumper(LEFT_BUMPER))
			{
printf("Wall following straight - right forward\n");
				MotorsTurn(FORWARD_SLOW_RIGHT);
			}
			else
			{
printf("Wall following straight - left forward\n");
				MotorsTurn(FORWARD_SLOW_LEFT);
			}
		}
		else 
		{
printf("No wall to my rear left! Turning left.\n");
			// There is no wall to our left, and we have passed the edge of the wall to our left
			// So turn to the left, slowly, for long enough for us to do 90 degrees
			MotorsTurn(LEFT_SLOW);
			t0 = time();
			while (time() < t0 + WALL_FOLLOW_LEFT_TURN_TIME)
			{
//				VictimID();
				ButtonCheck();
			}

//			BlinkForVictims();
printf("Stop.\n");

			MotorsTurn(STOP);
			delay(500);

			// Now move forward for a little bit to move the left rear sensor past the wall (if there is one)
			MotorsTurn(GO_FORWARD);
			t0 = time();
printf("Forward a bit.\n");
			while (time() < t0 + 500)
			{
//				VictimID();
				ButtonCheck();
			}
printf("Coast.\n");
			
//			BlinkForVictims();
			MotorsTurn(COAST);
			delay(500);
		
			// If we still don't see anything in front of us, then
			// move forward for 300ms.
//			if (!ReadUltrasoundSensor(FRONT_LEFT))
//			{
//printf("Still nothing in front after turn, moving forward for 300ms.\n");
//				t0 = time();
//				while (time() < t0 + 300) 
//				{
//					VictimID();
//					ButtonCheck();
//					MotorsTurn(GO_FORWARD);
//				}
//				BlinkForVictims();
//			}
printf("Done with turn.\n");
		}
	}
	else 
	{
		// The front left ultrasound sensor sees a wall
		// So drive forward, but turn left/right based
		// on status of the front left bumper
		if (CheckBumper(FRONT_LEFT_BUMPER))
		{
			MotorsTurn(RIGHT_PIVOT);
			delay(25);
		}
		else
		{
			MotorsTurn(LEFT_PIVOT);
			delay(25);
		}
	}
}


// Test function - returns the states of all bumpers
void PrintBumpers()
{	int x;
	Direction = FORWARD;
	printf("Bumper Status:\n");
	printf(" Front      = %d\n",CheckBumper(FRONT_BUMPER));
	printf(" Right      = %d\n",CheckBumper(RIGHT_BUMPER));
	printf(" Rear       = %d\n",CheckBumper(REAR_BUMPER));
	printf(" Left       = %d\n",CheckBumper(LEFT_BUMPER));
	printf(" FrontLeft  = %d\n",CheckBumper(FRONT_LEFT_BUMPER));
	printf(" FrontRight = %d\n",CheckBumper(FRONT_RIGHT_BUMPER));
	printf(" RearLeft   = %d\n",CheckBumper(REAR_LEFT_BUMPER));
	printf(" RearRight = %d\n",CheckBumper(REAR_RIGHT_BUMPER));
}

/**********************************************
*
* M A I N     P R O G R A M     S T A R T
* 
***********************************************/

// Perform all board and hardware intialization
SystemInitalize();

// ready light
//WriteBankA(0xF0);		// To turn them all on
WriteBankA(0x00);		// To turn them all off

// Must call this with an argument of 0 one time on startup
CheckForUserEscape(0);

// Wait until user presses yellow start button
printf("Press yellow button to start robot.\n"); 
WaitForButtonPress();

// Main forever loop
while(1)
{
	// Reset the victim counts
	VictimCountReset();
//while(1) {
	// Check for a pause
	ButtonCheck();

	// Assume we're going forward by default
	Direction = FORWARD;		// Forward

//Motors(MOT_OFF + 5, MOT_OFF - 5);	
	PrintSensors();
//delay(100);
//}	
	// While front is white and rear is white go forward
//	while (
//		ReadLightSensor(FRONT_LIGHT) == WHITE
//		&&
//		ReadLightSensor(REAR_LIGHT) == WHITE
//	)
//	{
//printf("Front= white Rear= white : Forward\n");
ButtonCheck();
//		delay(100);
		MoveRobot();
//	}

	// While front is black and rear is black go forward
//	while (
//		ReadLightSensor(FRONT_LIGHT) == BLACK
//		&&
//		ReadLightSensor(REAR_LIGHT) == BLACK
//	)
//	{
//printf("Front= black Rear= black : Forward\n");
//ButtonCheck();
//		MoveRobot(FORWARD);
//	}	
	
	// While front is black and rear is white go backward
//	while(
//		ReadLightSensor(FRONT_LIGHT) == BLACK
//		&&
//		ReadLightSensor(REAR_LIGHT) == WHITE
//	)
//	{
//printf("Front= black Rear= white : Reverse\n");
//ButtonCheck();
//		MoveRobot(REVERSE);
//	}

	// While front is white and rear is black go forward
//	while (
//		ReadLightSensor(FRONT_LIGHT) == WHITE
//		&&
//		ReadLightSensor(REAR_LIGHT) == BLACK
//	)
//	{
//printf("Front= white Rear= black : Forward\n");
//ButtonCheck();
//		MoveRobot(FORWRD);
//	}
}
