#ifndef SERVER_H
#define SERVER_H


#define LOGMSGLENGTH 100
#define OUTPUTLENGTH 100000
#define MAXTIMEOUTSECS 0
#define MAXTIMEOUTUSECS 100000
#define MAXTIMEOUTPING 0
#define MAXTIMEOUTPINGU 100000
#define DELAYUSECS 1
#define GRAPHICSDELAY 10000
#define MAXLOGSIZE 20
#define MAXIDLECLIENT 5
#define MAX_CLIENTS_HARD_LIMIT 1000

typedef struct serverState{
	
	char logBuff[LOGMSGLENGTH*100];
	char addressContainer[INET_ADDRSTRLEN];
	char *pathToFile;
	u_int64_t serverRunning;
	u_int64_t idle;
	u_int64_t adminsActive,clientsActive,maxNumOfClients;
	DListW* listOfClients;
	DListW* listOfAdmins;
	stackList* logs;
	int server_socket;
	struct sockaddr_in server_address;
	u_int64_t totalSent;
	u_int64_t timeActive;
	double trafficRate;
	stackList* kickedClientPtrs;
	stackList* kickedAdminPtrs;
	queueList* cmdQueue;
	u_int64_t dataSize;
	u_int16_t pingSize;

}serverState;

typedef struct clientStruct{
	struct	sockaddr_in clientAddress;
	int client_socket;
	socklen_t addrLength;
	u_int64_t numOfBytesSent;
	u_int64_t done;
	u_int64_t bytesToRead;
	int fd;
	char login[FIELDLENGTH+1];
}clientStruct;

typedef struct adminStruct{
	struct	sockaddr_in clientAddress;
	int admin_socket;
	u_int32_t addrLength;
	u_int64_t numOfBytesSent;
	int fd;
}adminStruct;
typedef struct command{

	char string[LINESIZE];
	clientStruct* whoItWas;


}command;
void initEverything(u_int16_t port,char* pathToFile,u_int16_t startPingSize,u_int64_t startDataSize,u_int16_t startMaxNumOfClients);

void sigint_handler(int signal);

void cleanup(void);

#endif

