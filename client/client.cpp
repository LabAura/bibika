#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <thread>
#include <math.h>
#define x_axis 0x42
#define y_axis 0x43
void error(char *msg){
	perror(msg);
	exit(0);
}
void sendData(int sockfd, int x){
	int n;
	char buffer[32];
	sprintf(buffer, "%d\n",x);
	if ((n=write(sockfd,buffer,strlen(buffer)))<0)
	error(const_cast<char *>("ERROR writing to socket"));
	buffer[n]='\0';
}
int main(){
	char serverIp[]="192.168.4.1";
	int portno=8888;
	int device=wiringPiI2CSetup(0x48),sockfd;
	int led1=31, led2=33, led3=35;
	int bth_left=18, bth_bottom=16, bth_right=15, bth_up=19;
	int speed;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	if(wiringPiSetupPhys()==-1) return 0;
	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);
	digitalWrite(led1, 0);
	digitalWrite(led2, 0);
	digitalWrite(led3, 0);
	pinMode(bth_left, INPUT);
	pinMode(bth_right, INPUT);
	pinMode(bth_bottom, INPUT);
	pinMode(bth_up, INPUT);
	printf("contacting %s on port%d\n",serverIp,portno);
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
	error(const_cast<char *>("ERROR opening socket"));
	if ((server=gethostbyname(serverIp))==NULL)
	error(const_cast<char *>("ERROR, no such host\n"));
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
	error(const_cast<char *>("ERROR connecting"));	
	}
	digitalWrite(led1,1);
	digitalWrite(led2,1);
	while(digitalRead(bth_bottom)!=0){
		wiringPiI2CReadReg8(device,y_axis);
		if((wiringPiI2CReadReg8(device,y_axis))>100 && 
		(wiringPiI2CReadReg8(device,y_axis))<200){
			wiringPiI2CReadReg8(device,x_axis);
			if((wiringPiI2CReadReg8(device,x_axis))>100 && 
			(wiringPiI2CReadReg8(device,x_axis))<200)
			sendData(sockfd,33);
		}
	
		wiringPiI2CReadReg8(device, y_axis);
		if(wiringPiI2CReadReg8(device, y_axis)==255){
			sendData(sockfd, 22);
			sendData(sockfd, 9);
			digitalWrite(led2,0);
			digitalWrite(led3,1);
			}
		if(wiringPiI2CReadReg8(device, y_axis)==0){
			sendData(sockfd, 11);
			sendData(sockfd, 9);
			digitalWrite(led2,0);
			digitalWrite(led3,1);
			}			
		wiringPiI2CReadReg8(device, x_axis);
		if(wiringPiI2CReadReg8(device, x_axis)==0 ){
			sendData(sockfd, 12);
			digitalWrite(led3,1);
			}
			wiringPiI2CReadReg8(device, x_axis);
		if(wiringPiI2CReadReg8(device, x_axis)==255){
			sendData(sockfd, 21);
			digitalWrite(led3,1);
			}
			speed=abs((wiringPiI2CReadReg8(device, x_axis))-127);
			printf("speed%i\n",speed);			
				if((wiringPiI2CReadReg8(device, x_axis)>= 70) && wiringPiI2CReadReg8(device, x_axis)<= 128){ 
					sendData(sockfd, 12);
					digitalWrite(led2,0);
					sendData(sockfd, 9);}
	if(speed<=64 && speed!=2){
		sendData(sockfd, 21);
		sendData(sockfd, 9);
		digitalWrite(led2,0);
		digitalWrite(led3,1);
		}	
	if(speed>=64){
		sendData(sockfd, 8);
		digitalWrite(led2,1);
		digitalWrite(led3,1);
		}
	if(digitalRead(bth_up)==0){
		sendData(sockfd, -1);
		digitalWrite(led3,1);
		break;
		}		
		digitalWrite(led3,0);
	}
	sendData(sockfd, -2);
	delay(100);
	close(sockfd);
	digitalWrite(led1,0);
	digitalWrite(led2,0);
	digitalWrite(led3,0);
	return 0;
}



