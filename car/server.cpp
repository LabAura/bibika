#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <Aura.h>
#include <thread>
int StepPinsLeft[4] = {22,18,16,10};
int StepPinsRight[4] = {35,36,37,38};
int WaitTime = 0;
int tme=wiringPiI2CSetup(0x42);
int data;
void time1(){
	if(digitalRead(tme)==0 || digitalRead(tme)==255) WaitTime=3;
	//if(digitalRead(tme)==90 || digitalRead(tme)==140) WaitTime=3;
	}
void error(char *msg){
	perror(msg);
	exit(1);
	}
int getData(int sockfd){
	char buffer[32];
	int n;
	if((n=read(sockfd,buffer,31))<0)
	error(const_cast<char *>("ERROR reading from socket"));
	buffer[n]='\0';
	return atoi(buffer);
	}
void t_off(){
	digitalWrite(StepPinsLeft[0],0);
	digitalWrite(StepPinsLeft[1],0);
	digitalWrite(StepPinsLeft[2],0);
	digitalWrite(StepPinsLeft[3],0);
	digitalWrite(StepPinsRight[0],0);
	digitalWrite(StepPinsRight[1],0);
	digitalWrite(StepPinsRight[2],0);
	digitalWrite(StepPinsRight[3],0);
	}
void forwardLeft(){
		delay(WaitTime);
	digitalWrite(StepPinsLeft[0],1);
	digitalWrite(StepPinsLeft[1],0);
	digitalWrite(StepPinsLeft[2],0);
	digitalWrite(StepPinsLeft[3],0);
	delay(WaitTime);
		digitalWrite(StepPinsLeft[0],1);
		digitalWrite(StepPinsLeft[1],1);
		digitalWrite(StepPinsLeft[2],0);
		digitalWrite(StepPinsLeft[3],0);
		delay(WaitTime);
	digitalWrite(StepPinsLeft[0],0);
	digitalWrite(StepPinsLeft[1],1);
	digitalWrite(StepPinsLeft[2],0);
	digitalWrite(StepPinsLeft[3],0);
	delay(WaitTime);
		digitalWrite(StepPinsLeft[0],0);
		digitalWrite(StepPinsLeft[1],1);
		digitalWrite(StepPinsLeft[2],1);
		digitalWrite(StepPinsLeft[3],0);
		delay(WaitTime);
	digitalWrite(StepPinsLeft[0],0);
	digitalWrite(StepPinsLeft[1],0);
	digitalWrite(StepPinsLeft[2],1);
	digitalWrite(StepPinsLeft[3],0);
		delay(WaitTime);
	digitalWrite(StepPinsLeft[0],0);
	digitalWrite(StepPinsLeft[1],0);
	digitalWrite(StepPinsLeft[2],1);
	digitalWrite(StepPinsLeft[3],1);
		delay(WaitTime);
	digitalWrite(StepPinsLeft[0],0);
	digitalWrite(StepPinsLeft[1],0);
	digitalWrite(StepPinsLeft[2],0);
	digitalWrite(StepPinsLeft[3],1);
		delay(WaitTime);
	digitalWrite(StepPinsLeft[0],1);
	digitalWrite(StepPinsLeft[1],0);
	digitalWrite(StepPinsLeft[2],0);
	digitalWrite(StepPinsLeft[3],1);	
	}
void backwardLeft(){
			delay(WaitTime);
	digitalWrite(StepPinsLeft[0],1);
	digitalWrite(StepPinsLeft[1],0);
	digitalWrite(StepPinsLeft[2],0);
	digitalWrite(StepPinsLeft[3],1);
	delay(WaitTime);
		digitalWrite(StepPinsLeft[0],0);
		digitalWrite(StepPinsLeft[1],0);
		digitalWrite(StepPinsLeft[2],0);
		digitalWrite(StepPinsLeft[3],1);
		delay(WaitTime);
	digitalWrite(StepPinsLeft[0],0);
	digitalWrite(StepPinsLeft[1],0);
	digitalWrite(StepPinsLeft[2],1);
	digitalWrite(StepPinsLeft[3],1);
	delay(WaitTime);
		digitalWrite(StepPinsLeft[0],0);
		digitalWrite(StepPinsLeft[1],0);
		digitalWrite(StepPinsLeft[2],1);
		digitalWrite(StepPinsLeft[3],0);
		delay(WaitTime);
	digitalWrite(StepPinsLeft[0],0);
	digitalWrite(StepPinsLeft[1],1);
	digitalWrite(StepPinsLeft[2],1);
	digitalWrite(StepPinsLeft[3],0);
		delay(WaitTime);
	digitalWrite(StepPinsLeft[0],0);
	digitalWrite(StepPinsLeft[1],1);
	digitalWrite(StepPinsLeft[2],0);
	digitalWrite(StepPinsLeft[3],0);
		delay(WaitTime);
	digitalWrite(StepPinsLeft[0],1);
	digitalWrite(StepPinsLeft[1],1);
	digitalWrite(StepPinsLeft[2],0);
	digitalWrite(StepPinsLeft[3],0);
		delay(WaitTime);
	digitalWrite(StepPinsLeft[0],1);
	digitalWrite(StepPinsLeft[1],0);
	digitalWrite(StepPinsLeft[2],0);
	digitalWrite(StepPinsLeft[3],0);
	}
void forwardRight(){
		delay(WaitTime);
	digitalWrite(StepPinsRight[0],1);
	digitalWrite(StepPinsRight[1],0);
	digitalWrite(StepPinsRight[2],0);
	digitalWrite(StepPinsRight[3],0);	
		delay(WaitTime);
	digitalWrite(StepPinsRight[0],1);
	digitalWrite(StepPinsRight[1],1);
	digitalWrite(StepPinsRight[2],0);
	digitalWrite(StepPinsRight[3],0);	
			delay(WaitTime);
	digitalWrite(StepPinsRight[0],0);
	digitalWrite(StepPinsRight[1],1);
	digitalWrite(StepPinsRight[2],0);
	digitalWrite(StepPinsRight[3],0);	
			delay(WaitTime);
	digitalWrite(StepPinsRight[0],0);
	digitalWrite(StepPinsRight[1],1);
	digitalWrite(StepPinsRight[2],1);
	digitalWrite(StepPinsRight[3],0);	
			delay(WaitTime);
	digitalWrite(StepPinsRight[0],0);
	digitalWrite(StepPinsRight[1],0);
	digitalWrite(StepPinsRight[2],1);
	digitalWrite(StepPinsRight[3],0);	
			delay(WaitTime);
	digitalWrite(StepPinsRight[0],0);
	digitalWrite(StepPinsRight[1],0);
	digitalWrite(StepPinsRight[2],1);
	digitalWrite(StepPinsRight[3],1);	
			delay(WaitTime);
	digitalWrite(StepPinsRight[0],0);
	digitalWrite(StepPinsRight[1],0);
	digitalWrite(StepPinsRight[2],0);
	digitalWrite(StepPinsRight[3],1);	
			delay(WaitTime);
	digitalWrite(StepPinsRight[0],1);
	digitalWrite(StepPinsRight[1],0);
	digitalWrite(StepPinsRight[2],0);
	digitalWrite(StepPinsRight[3],1);		
	}
void backwardRight(){
			delay(WaitTime);
	digitalWrite(StepPinsRight[0],1);
	digitalWrite(StepPinsRight[1],0);
	digitalWrite(StepPinsRight[2],0);
	digitalWrite(StepPinsRight[3],1);
			delay(WaitTime);
	digitalWrite(StepPinsRight[0],0);
	digitalWrite(StepPinsRight[1],0);
	digitalWrite(StepPinsRight[2],0);
	digitalWrite(StepPinsRight[3],1);
				delay(WaitTime);
	digitalWrite(StepPinsRight[0],0);
	digitalWrite(StepPinsRight[1],0);
	digitalWrite(StepPinsRight[2],1);
	digitalWrite(StepPinsRight[3],1);
				delay(WaitTime);
	digitalWrite(StepPinsRight[0],0);
	digitalWrite(StepPinsRight[1],0);
	digitalWrite(StepPinsRight[2],1);
	digitalWrite(StepPinsRight[3],0);
			delay(WaitTime);
	digitalWrite(StepPinsRight[0],0);
	digitalWrite(StepPinsRight[1],1);
	digitalWrite(StepPinsRight[2],1);
	digitalWrite(StepPinsRight[3],0);
				delay(WaitTime);
	digitalWrite(StepPinsRight[0],0);
	digitalWrite(StepPinsRight[1],1);
	digitalWrite(StepPinsRight[2],0);
	digitalWrite(StepPinsRight[3],0);
				delay(WaitTime);
	digitalWrite(StepPinsRight[0],1);
	digitalWrite(StepPinsRight[1],1);
	digitalWrite(StepPinsRight[2],0);
	digitalWrite(StepPinsRight[3],0);
				delay(WaitTime);
	digitalWrite(StepPinsRight[0],1);
	digitalWrite(StepPinsRight[1],0);
	digitalWrite(StepPinsRight[2],0);
	digitalWrite(StepPinsRight[3],0);		
	}	
void left_side(){
	while(1){
		if (data == 11){
			forwardLeft();
			delay(1);
			t_off();
			}
		if (data == 22){
			backwardLeft();
			delay(1);
			t_off();
			}
		if (data == 21){
			backwardLeft();
			delay(1);
			t_off();
			}
		if (data == 12){
			forwardLeft();
			delay(1);
			t_off();
			}
		if (data<0)	break;									
		}
	}
void right_side(){
	while(1){
		if (data == 11){
			backwardRight();
			delay(1);
			t_off();
			}
		if (data == 22){
			forwardRight();
			delay(1);
			t_off();
			}
		if (data == 21){
			backwardRight();
			delay(1);
			t_off();
			}
		if (data == 12){
			forwardRight();
			delay(1);
			t_off();
			}
		if (data == 8){
			WaitTime=1;
			}			
		if (data == 9){
			WaitTime=3;
			}			
		if (data<0)	break;									
		}
	}	
int main(){
	int sockfd, newsockfd, clilen, portno=8888;
	struct sockaddr_in serv_addr, cli_addr;
	int timeout=0;
	if (wiringPiSetupPhys()== -1) return 0;
	pinMode(StepPinsLeft[0], OUTPUT);
	pinMode(StepPinsLeft[1], OUTPUT);
	pinMode(StepPinsLeft[2], OUTPUT);
	pinMode(StepPinsLeft[3], OUTPUT);
	pinMode(StepPinsRight[0], OUTPUT);
	pinMode(StepPinsRight[1], OUTPUT);
	pinMode(StepPinsRight[2], OUTPUT);
	pinMode(StepPinsRight[3], OUTPUT);
	system("/home/pi/mjpg-streamer/mjpg-streamer.sh start");
	std::thread thr1(left_side);
	std::thread thr2(right_side);
	thr1.detach();
	thr2.detach();
	printf("using port #%d\n", portno);
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	error(const_cast<char *>("ERROR opening socket"));
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
	sizeof(serv_addr)) < 0)
	error( const_cast<char *>("ERROR on binding"));
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	while(1){
	printf("waiting for new client...\n");
	if((newsockfd=accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen))<0)
	error(const_cast <char *>("ERROR on accept"));
	printf("client connected\n");
	while (1){
		if (timeout>10000){
			timeout=0;
			break;
		}
	data = getData(newsockfd);
	printf("%i\n", data);
	if (data<0) break;
	if (data==0) timeout++;	
	}
	if(data==-2||data==-1)
	break;
}
t_off();
close(newsockfd);
printf("Connection closed\n");
system("/home/pi/mjpg-streamer/mjpg-streamer.sh stop");
if(data==-1){
	printf("\nGonka konchilas");
	system("sudo shutdown -h now");
}
system("sudo fuser -k 8888/tcp");
return 0;
}						

	
