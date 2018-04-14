#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <errno.h>

typedef uint8_t SESSID[16];
typedef uint32_t KEY[16];

char running;

int sock;

uint16_t portAuth;
uint16_t portComm;

struct sockaddr_in local;
struct sockaddr_in remote;
socklen_t remoteLen;

//Buffer
#define PKTSZ 1024
char pktbuf[PKTSZ];

//Current session infos
struct in_addr curRemote;
SESSID curSessId;
KEY curKey;

//Error helper
void fterror(char* str){
	perror(str);
	exit(-8);
}

int main(){
	int rslt;

	//Make socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock == -1)fterror("Unable to create socket");
	//So we don't need to wait every time we restart the program
	int reuseaddr = 1;
	rslt = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
	if(rslt)perror("Unable to set option SO_REUSEADDR");
	
	//Create our name
	memset((void*)&local, sizeof(struct sockaddr_in), 0);

	local.sin_family = AF_INET;
	local.sin_port = htons(344);
	local.sin_addr.s_addr = INADDR_ANY;
	
	//Bind name
	rslt = bind(sock, (struct sockaddr*)&local, sizeof(struct sockaddr));
	if(rslt)fterror("Unable to bind");

	//Good to go
	running = 1;

	while(running){
		remoteLen = sizeof(remote);
		rslt = recvfrom(sock, pktbuf, PKTSZ, 0, &remote, &remoteLen);

	}	

	//Close evrything
	close(sock);

	return 0;

}
