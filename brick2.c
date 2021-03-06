#pragma config(Sensor, S1,     touch,          sensorEV3_Touch)
#pragma config(Sensor, S2,     sonic,          sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define PULL_STATE 0
#define FEAR_STATE 1


#include "shared.c"

int state=PULL_STATE;
bool startSong=false, startScream=false;
task drive(){
	while(1){
		switch(state){
		case PULL_STATE:
			startScream=true;
			if(startSong){
			startTask(playSong);
			startSong=false;
		}
			setMotorSpeed(left,100);
			setMotorSpeed(right, 100);
			break;
		case FEAR_STATE:
			stopTask(playSong);
			startSong=true;
			setMotorSpeed(left,-25);
			setMotorSpeed(right, -25);
			if(startScream){
			scream();
			startScream=false;
		}
			break;

			sleep(100);
		}
	}
}
task sense(){
	while(true){

		state=PULL_STATE;
		if (getUSDistance(sonic)<60)
			state=FEAR_STATE;

		sleep(100);
	}
}

task main()
{
	setSoundVolume(100);
	startTask(blinkLights);
	startTask(playSong);
	while(!getTouchValue(touch))sleep(300);
	startTask(sense);
	startTask(drive);
	while(true) sleep(100000);
}
