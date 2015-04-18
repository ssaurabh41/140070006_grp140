
//**************************************************need to run motion_pin_config(), position_encoder_init()*******************

void motion_pin_config()
{
	DDRA = DDRA | 0x0F; //set direction of the PORTA 3 to PORTA 0 pins as output
	PORTA = PORTA & 0xF0; // set initial value of the PORTA 3 to PORTA 0 pins to logic 0
	DDRL = DDRL | 0x18;   //Setting PL3 and PL4 pins as output for PWM generation
	PORTL = PORTL | 0x18; //PL3 and PL4 pins are for velocity control using PWM
}

//Function used for setting motor's direction
void motion_set (unsigned char Direction)
{
	unsigned char PortARestore = 0;

	Direction &= 0x0F; 			// removing upper nibbel as it is not needed
	PortARestore = PORTA; 			// reading the PORTA's original status
	PortARestore &= 0xF0; 			// setting lower direction nibbel to 0
	PortARestore |= Direction; 	// adding lower nibbel for direction command and restoring the PORTA status
	PORTA = PortARestore; 			// setting the command to the port
}

void forward() { motion_set(0x06); }		//both wheels forward
	
void back() { motion_set(0x09); }			//both wheels backward

void left() { motion_set(0x05); }			//Left wheel backward, Right wheel forward

void right() { motion_set(0x0A); }			//Left wheel forward, Right wheel backward

void soft_left() { motion_set(0x04); }		//Left wheel stationary, Right wheel forward

void soft_right() { motion_set(0x02); }		//Left wheel forward, Right wheel is stationary

void soft_left_2() { motion_set(0x01); }	//Left wheel backward, right wheel stationary

void soft_right_2() { motion_set(0x08); }	//Left wheel stationary, Right wheel backward

void stop() { motion_set(0x00); }			//hard stop
	
	
//PWM	
void timer5_init()      //for velocity control
{
	TCCR5B=0x00;        //stop
	TCCR5A=0xA9;
	TCNT5H=0xff;        //we only want to count upto 255 not till 65335
	TCNT5L=0x00;
	//OCR5AH=0xff;      //useless coz we have defined in TCCR that we will use 8bit mode so only OCR5AL is used
	OCR5AL=0x00;
	//OCR5BH=0xff;      //another useless fellow
	OCR5BL=0x00;
	TCCR5B=0x0B;
}

void velocity(unsigned char left_motor, unsigned char right_motor)         //sets the compare value for PWM (non-inverting mode)
{
	OCR5AL=left_motor;
	OCR5BL=right_motor;
}
//??How are PORTL and PORTA related to wheels??


volatile unsigned long int ShaftCountLeft = 0; //to keep track of left position encoder
volatile unsigned long int ShaftCountRight = 0; //to keep track of right position encoder
volatile unsigned int Degrees; //to accept angle in degrees for turning

//Function to configure INT4 (PORTE 4) pin as input for the left position encoder
void left_encoder_pin_config()
{
	DDRE  = DDRE & 0xEF;  //Set the direction of the PORTE 4 pin as input
	PORTE = PORTE | 0x10; //Enable internal pull-up for PORTE 4 pin
}

//Function to configure INT5 (PORTE 5) pin as input for the right position encoder
void right_encoder_pin_config()
{
	DDRE  = DDRE & 0xDF;  //Set the direction of the PORTE 5 pin as input
	PORTE = PORTE | 0x20; //Enable internal pull-up for PORTE 5 pin
}

void left_position_encoder_interrupt_init() //Interrupt 4 enable
{
	cli(); //Clears the global interrupt
	EICRB = EICRB | 0x02; // INT4 is set to trigger with falling edge
	EIMSK = EIMSK | 0x10; // Enable Interrupt INT4 for left position encoder
	sei();   // Enables the global interrupt
}

void right_position_encoder_interrupt_init() //Interrupt 5 enable
{
	cli(); //Clears the global interrupt
	EICRB = EICRB | 0x08; // INT5 is set to trigger with falling edge
	EIMSK = EIMSK | 0x20; // Enable Interrupt INT5 for right position encoder
	sei();   // Enables the global interrupt
}

//ISR for right position encoder
ISR(INT5_vect)
{
	ShaftCountRight++;  //increment right shaft position count
}

//ISR for left position encoder
ISR(INT4_vect)
{
	ShaftCountLeft++;  //increment left shaft position count
}

void position_encoder_init()			//Initialize the position encoder
{
	left_encoder_pin_config();
	right_encoder_pin_config();
	left_position_encoder_interrupt_init();
	right_position_encoder_interrupt_init();
}

const int rotation_resolution=4.090*5.44/5.338; //default 4.090 given
//Function used for turning robot by specified degrees
void angle_rotate(unsigned int Degrees)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = float(Degrees)/ float(rotation_resolution); // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned int) ReqdShaftCount;
	ShaftCountRight = 0;
	ShaftCountLeft = 0;

	while (1)
	{
		if((ShaftCountRight >= ReqdShaftCountInt) | (ShaftCountLeft >= ReqdShaftCountInt))
		break;
	}
	stop(); //Stop robot
}

//Function used for moving robot forward by specified distance
void linear_distance_mm(unsigned int DistanceInMM)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = DistanceInMM / 5.44; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned long int) ReqdShaftCount;
	
	ShaftCountRight = 0;
	while(1)
	{
		if(ShaftCountRight > ReqdShaftCountInt)
		{
			break;
		}
	}
	stop(); //Stop robot
}

void forward_mm(unsigned int DistanceInMM)
{
	forward();
	linear_distance_mm(DistanceInMM);
}

void back_mm(unsigned int DistanceInMM)
{
	back();
	linear_distance_mm(DistanceInMM);
}

void left_degrees(unsigned int Degrees)
{
	// 88 pulses for 360 degrees rotation 4.090 degrees per count
	left(); //Turn left
	angle_rotate(Degrees);
}

void right_degrees(unsigned int Degrees)
{
	// 88 pulses for 360 degrees rotation 4.090 degrees per count
	right(); //Turn right
	angle_rotate(Degrees);
}

void soft_left_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_left(); //Turn soft left
	Degrees=Degrees*2;
	angle_rotate(Degrees);
}

void soft_right_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_right();  //Turn soft right
	Degrees=Degrees*2;
	angle_rotate(Degrees);
}

void soft_left_2_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_left_2(); //Turn reverse soft left
	Degrees=Degrees*2;
	angle_rotate(Degrees);
}

void soft_right_2_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_right_2();  //Turn reverse soft right
	Degrees=Degrees*2;
	angle_rotate(Degrees);
}

//functions for motion between two coordinates
struct Point
{
	volatile float x;
	volatile float y;
};


float calc_rotate_angle(Point current_point, Point next_point, float current_angle)
{
	float x;
	if(next_point.x==current_point.x)
	{
		if (next_point.y==current_point.y) return 0;
		else if(next_point.y>current_point.y) x=90;
		else if(next_point.y<current_point.y)x=-90;
	}
	else x=atan2(next_point.y-current_point.y, next_point.x-current_point.x)*180/3.1416;

	float angle_to_rotate = current_angle-x;

	if(angle_to_rotate<(-180)) angle_to_rotate+=360.0;
	if(angle_to_rotate>180)    angle_to_rotate-=360.0;                                              //angle is in clockwise direction

	return angle_to_rotate;
}

float calc_distance(Point current_point, Point next_point)				//Returns the distance between two points
{
	return sqrt(pow(current_point.x-next_point.x,2)+pow(current_point.y-next_point.y,2));
}

void update_current_angle(Point current_point, Point next_point, float &current_angle)		//Updates the current orientation of the bot
{
	if(next_point.x==current_point.x)
	{
		if(next_point.y==current_point.y) return;
		if(next_point.y-current_point.y>0) current_angle=90;
		else current_angle=-90;
	}
	else current_angle=atan2(next_point.y-current_point.y, next_point.x-current_point.x)*180/3.1416;
}

void move(Point current_point, Point next_point, float current_angle)                           //moves the bot from one point to another,pass current angle by reference
{
	if(calc_rotate_angle(current_point,next_point,current_angle)>0)                             //i.e to move clockwise i.e. right
		right_degrees(calc_rotate_angle(current_point,next_point,current_angle));
	else 
		left_degrees(-calc_rotate_angle(current_point,next_point,current_angle));
		
	_delay_ms(200);
	
	forward_mm(calc_distance(current_point,next_point));
}

