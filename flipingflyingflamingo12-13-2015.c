#pragma config(Sensor, in1,    match,          sensorPotentiometer)
#pragma config(Sensor, in2,    Color,          sensorPotentiometer)
#pragma config(Motor,  port1,           LeftTopW,      tmotorVex393HighSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           RightTopW,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           Feed1,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           Feed2,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,            ,             tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,            ,             tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           Launch2,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           Launch1,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           RightBottomW,  tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          LeftBottomW,   tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.

 bStopTasksBetweenModes = true;
	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

//Drive
void DriveMotor(int drivespeed)
{
	motor[LeftTopW] = drivespeed;
	motor[LeftBottomW] = drivespeed;
	motor[RightTopW] = drivespeed;
	motor[RightBottomW] = drivespeed;
}

void Rightturn(int time)
{
	motor[LeftTopW] = 127;
	motor[LeftBottomW] = 127;
	motor[RightTopW] = -127;
	motor[RightBottomW] = -127;
	wait1Msec(time);
	DriveMotor(0);
}

void Leftturn(int time)
{
	motor[LeftTopW] = -127;
	motor[LeftBottomW] = -127;
	motor[RightTopW] = 127;
	motor[RightBottomW] = 127;
	wait1Msec(time);
	DriveMotor(0);
}

//Launcher
void STOP(int Stop)
{
	motor[Launch1] = Stop;
	motor[Launch2] = Stop;
}

void Fire(int shoot, int time)
{
	motor[Launch1] = shoot;
	motor[Launch2] = shoot;
	wait1Msec(time);
	STOP(0);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
int fail = 0;
int go = 0;
int red = 0;
int blue = 0;

if(SensorValue[match] > 2047)
{
	fail = 1;
}
else
{
	go = 1;
}

if(SensorValue[Color] > 2047)
{
	red = 1;
}
else
{
	blue = 1;
}
//-----------red go------------
if (go == 1 && red == 1)
{
	DriveMotor(3000);         //Red Drive then Launch
	Fire(127,4000);
}

//-----------Blue go-----------
if (go==1 && blue ==1)
{
	DriveMotor(3000);         //Blue Drive then Launch
	Fire(127,4000);
}

//-----------red fail----------
if (fail==1 && red==1)
{
	Rightturn(2000);         //Red turn and shoot 1
	Fire(127,1200);
}

//-----------Blue fail---------
if (fail==1 && blue==1)
{
	Leftturn(2000);         //Blue turn and shoot 1
	Fire(127,1200);
}
  // .....................................................................................


}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................

	//Drive functions
	motor[LeftTopW] = vexRT[Ch3];
	motor[LeftBottomW] = vexRT[Ch3];
	motor[RightBottomW] = vexRT[Ch2];
	motor[RightTopW] = vexRT[Ch2];

	// Catapult Program
	if (vexRT[Btn5U] == 1)
	{
		motor[Launch1] = 127;
		motor[Launch2] = 127;
	}
	else if (vexRT[Btn5D] == 1)
	{
		motor[Launch1] = -127;
		motor[Launch2] = -127;
	}
	else
	{
		motor[Launch1] = 0;
		motor[Launch2] = 0;
	}

	// Feed Function
	if (vexRT[Btn6U] == 1)
	{
		motor[Feed1] = 127;
		motor[Feed2] = 127;
	}
	else if(vexRT[Btn6D] == 1)
	{
		motor[Feed1] = -127;
		motor[Feed2] = -127;
	}
	else
	{
		motor[Feed1] = 0;
		motor[Feed2] = 0;

	}
	  // .....................................................................................


	}
}
