#include <iostream>
#include <fstream>
#include <cmath>
#include <conio.h>
#include "Config.h"

using namespace std;

int main() //main function
{
	while (true) //loop
	{
		InitValues(); //call function and passing address object
		ReadInputs(); //call function and passing address object
	}
	return 0;
}

void WelcomeMessasge() //Welcome Message for user
{
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                           WELCOME                              |" << endl;
	cout << "------------------------------------------------------------------" << endl;
}



void InitValues () //function for Initialization the variables are used in this project
{
	vy         = INIT;  //velocity in y direction
	vx         = INIT;  //velocity in  x direction
	ay         = INIT;  //acceleration in y direction
	ax         = INIT;  //acceleration in x direction
	delta_vy   = INIT;  //delta_vy in y direction
	delta_vx   = INIT;  //delta vx in x direction
	M          = INIT;  //Mass of GeneralStructure
	d          = INIT;  //diameter of your GeneralStructure
	v          = INIT;  //Initial velocity of your GeneralStructure
	b          = INIT;  //fraction
	e          = INIT;  //parameter
	mu         = INIT;  //parameter
	y      	   = INIT;  //distance in y
	x     	   = INIT;  //distance in x
	theta 	   = INIT;  //angle of GeneralStructure
	t     	   = INIT;  //time of projectile
	i     	   = INIT;  //variable for looping
	j     	   = INIT;  //variable for looping
	k     	   = INIT;  //variable for looping
	delta_y    = INIT;  //difference between distance y
	delta_x    = INIT;  //difference between distance x
	arr_x[Max] = INIT;  //array to saving x distance values
	arr_y[Max] = INIT;  //array for saving y distance values
	arr_t[Max] = INIT;  //array for saving t values
	delta_t    = delta; //difference time (end - start time )
	counter    = END;   //constant
}


void ChooseModes() //choose your mode
{
    cout << "------------------------------------------------------------------" << endl;
	cout << "|                ModeA : Enter Your Values Without Control       |" << endl;
	cout << "|                ModeB : Load Existing Values With Control       |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                       please Enter Your Mode !                 |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                         For ModeA Enter 1                      |"<< endl;
	cout << "|                         For ModeB Enter 2                      |"<< endl;
	cout << "------------------------------------------------------------------" << endl;
	cin >> i ; // i for store int values

	switch (i) //switch between case 1 and case 2
	{
	case   1 : ModeA() ;                       break ; //press 1 to call ModeA function
	case   2 : ModeB() ;                       break ; //press 2 to call ModeB function
	}
}



void ReadInputs() //this function passing pointers to choose Modes
{
	WelcomeMessasge(); //display the Welcome Message
	ChooseModes(); //CallFunction
}


void EnterValues() //function for user to enter the parameters
{
    cout << "------------------------------------------------------------------" << endl;
	cout << "|                 please Enter Your Parameters !                 |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "please Enter Your Parameters !"<<endl ; //display User's message
	cout << "M"<<"\t"<< "D"<<"\t"<< "Angle"<<"\t"<< "V"<<"\t"<< "B"<<"\t"<< "E"<<"\t"<< "MU"<<"\t"<< "H"<<"\n"<<endl ; //display User's message
	cin >> M >> d >> v >> theta >> b >> e >> mu >> y;//Enter the values
}

//Mode A Input parameters by user and Do simulate
void ModeA() //ModeA Function call WriteOutputs Function for Saving values that input by user and Do simulation
{
	WriteOutputs(); //call function and passing pointer address
}


void ModeB() //ModeB Function loaded constants values from parameters.txt file
{

	ifstream inputFile; //create input file GeneralStructure
	//Open a file for reading
	inputFile.open("parameters.txt");//open the existing file
	//Read file until end of file (eof)
	i = 0 ; //variable i for incrementing array's index
	//Check that the file is opened
    cout << "----------------------------------- " << endl;
	cout << "|       Mass        |          e   |" << endl;
	cout << "----------------------------------- " << endl;
    cout << "------------------------------------" << endl;
	cout << "|       Diameter    |          b   |" << endl;
	cout << "------------------------------------" << endl;
    cout << "------------------------------------" << endl;
	cout << "|       Velocity    |          mu  |" << endl;
	cout << "------------------------------------" << endl;
    cout << "------------------------------------" << endl;
	cout << "|       angle       |           h  |" << endl;
	cout << "----------------------------------- " << endl;
	        cout <<"---------"<<endl ;
	if(inputFile.is_open()){ //make sure the file is open
		while (!(inputFile.eof())){ //
			inputFile >> data[i] ;//load the data into data file
			printf("| %15.5lf|\n",data[i]);
			//cout << data[i] <<endl;//display the values
			i++ ;
		}
		   cout <<"---------"<<endl ;
		//close the file
		inputFile.close();//close the file
	}
	else{
		cout<<"can't open the file " <<endl;
	}
	//load the values into parameters

	M=data[0]; d=data[1] ;v=data[2] ;
	theta=data[3]; y=data[7]; b=data[4] ;
	e=data[5];mu=data[6];
	Control(); //call function
}



void Bouncing () //Function to solve Bouncing Equations
{
	vy = - (e * vy);                           //vy : velocity in Y direction
	vx = vx + (mu *(e-1)*vx);        //vx : velocity in x direction
	delta_y = vy + delta_t ;                   //delta_y:difference between
	y = y +delta_y ;
	delta_x = vx + delta_x ;           //delta_x for difference distance in x direction
	x = x +delta_x ; //distance of GeneralStructure in x direction
}



void Projectile() //Function to solve Projectile Equations
{
	ay = ((-M*g)-(b*vy))/M;  //acceleration in y direction
	ax = -(b*vx)/M; //acceleration in x direction
	delta_vy = ay * delta_t ;//difference values in y direction
	delta_vx = ax * delta_t ;//difference values in x direction
	vy = vy + delta_vy ;//velocity in y direction
	vx = vx + delta_vx ;//velocity in x direction
	delta_y = vy + delta_t ;
	delta_x = vx + delta_x ;
	y = y +delta_y ;
	x = x +delta_x ;
}



void Display () //Function to display the values
{
	// Displaying values of Time and (x, y) position of the ball
	printf("| %15.5lf    | %15.5lf     | %15.5lf     |\n", t, x, y);
}

void Simulate() //Function for simulation
{
	vy = v * sin(theta * pi /180); //by using initial velocity and theta value to calculate the Vy
	vx = v * cos(theta * pi/180); ////by using initial velocity and theta value to calculate the Vx

  // make nice distance for display the values
	cout << "------------------------------------------------------------------" << endl;
	cout << "|       Time(sec)    |          X(cm)      |          Y(cm)      |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	int j = 0; //this variable for helping to increment the array space for storing
	do
	{

		Projectile();//call projectile function
		if ( y <= 0)
		{
			Bouncing(); //call Bouncing function
		}
		else {}

		t = t+delta_t ;

		Display(); //call Display Function

		arr_x[j] = x;//we used array_x to store values of x to help us for stroed into parameters.csv file
		arr_y[j] = y;////we used array_x to store values of x to help us for stroed into parameters.csv file
		j++;

	}
	while (t <= END); // loop till T= 20.01
	cout << "------------------------------------------------------------------" << endl;
}



void WriteOutputs()  //Write function thats save parameters from user
{

	ofstream savefile ; //create GeneralStructure
	savefile.open ("projectile.csv"); //create fie .csv

	EnterValues() ; //call parameters from users
	savefile <<"MASS (kg),Diameter(m),Initial velocity(m/s),Initial angle(degrees),b(N.s/m), e ,mu,h(m) \n" ;

	savefile <<M << ","<< d<< ","<<v<< ","<<theta<< ","; //Save parameters values to file
	savefile <<b<< ","<<e<< ","<<mu<< ","<<y<<"\n"; //Save parameters values to file
	savefile.close(); //close file

	ofstream outputFile; //open Newfile for take the reading and save it
	outputFile.open("Readings.csv");//open Reading.csv
	Simulate();//call function to Do simulation
	i = 0 ;//index array increment
	for (t = 0.0 ; t<=END ; t+=delta) //loop 0:20.01
	{
		outputFile << arr_x[i] <<","<< arr_y[i] <<","<< t <<endl;//saving into file
	}
	outputFile.close();//close file
    cout << "------------------------------------------------------------------" << endl;
	cout << "|                           GoodBye!                             |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << endl ;
}



void Control()
{
        cout <<endl ;
    	cout << "---------------------------------------------------------------------------------------------------"<< endl;
	    cout << "|       ESC        ||    You will exist from Control Program                                     |" << endl;
        cout << "|       Enter      ||    You will entering to Simulation program                                 |" << endl;
        cout << "|      Space       ||    You Will Control for increasing Initial Velocity Value                  |" << endl;
        cout << "|      BackSpace   ||    You will exist from Control for increasing Acceleration Value           |" << endl;
        cout << "|      Tab         ||    You will exist from Control for dncreasing Acceleration Value           |" << endl;
	    cout << "---------------------------------------------------------------------------------------------------"<< endl;
	while (!kbhit())
	{
		char ch = getch();
		switch (ch)
		{
		case 27:      goto exist;                       break ;     // press ESC to exit
		case 32:     VelocityIncrearse();               break ;     // press SPACE to clear screen
		case 13 :    Simulate();                        break ;    //Entrer press to simulate
		case 8  :    ThetaIncrearse();                  break ;    //Backspace
		case 9  :    Thetadecrearse();                  break ;     //Tab
		}

	}
	exist :
    cout << "------------------------------------------------------------------" << endl;
	cout << "|                           GoodBye!                             |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << endl ;
}



void VelocityIncrearse()
{
	v++;
	cout << v << endl;
}

void ThetaIncrearse()
{
	++theta;
	cout << theta << endl;
}




void Thetadecrearse()
{
	--theta;
	cout << theta << endl ;
}

