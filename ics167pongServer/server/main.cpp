#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include "websocket.h"
#include "pongGame.h"

using namespace std;

webSocket server;
PongGame pongGame;
bool gameInprogress = false;

/* called when a client connects */
void openHandler(int clientID){
    ostringstream os;
    os << "Stranger " << clientID << " has joined.";

    vector<int> clientIDs = server.getClientIDs();
    for (int i = 0; i < clientIDs.size(); i++){
        if (clientIDs[i] != clientID)
            server.wsSend(clientIDs[i], os.str());
    }

    server.wsSend(clientID, "Welcome!");
}

/* called when a client disconnects */
void closeHandler(int clientID){
    ostringstream os;
    os << "Stranger " << clientID << " has leaved.";

    vector<int> clientIDs = server.getClientIDs();
    for (int i = 0; i < clientIDs.size(); i++){
        if (clientIDs[i] != clientID)
            server.wsSend(clientIDs[i], os.str());
    }
}

/* called when a client sends a message to the server */
void messageHandler(int clientID, string message){

	if(message.compare("paddleUp") == 0)
    {
		pongGame.movePaddleUp();
    }
	else if(message.compare("paddleDown") == 0)
	{
		pongGame.movePaddleDown();
	}
	else
	{

	}


	//ostringstream os;
    //os << "Stranger " << clientID << " says: " << message;
//    vector<int> clientIDs = server.getClientIDs();
//    for (int i = 0; i < clientIDs.size(); i++){
//        if (clientIDs[i] != clientID)
//            server.wsSend(clientIDs[i], os.str());
//    }
}

/* called once per select() loop */
void periodicHandler(){
	static DWORD next = GetTickCount() + 15;
	static int hitCount = 0;
	DWORD currentTime = GetTickCount();
    if (currentTime >= next ){

    	vector<int> clientIDs = server.getClientIDs();
    	if(hitCount != pongGame.playerHits)
		{
    		hitCount = pongGame.playerHits;
    		ostringstream oh;
    		char hitChars[10];
    		itoa(hitCount,hitChars,10);
    		oh << "hit" << " " << std::string(hitChars);
    		for (int i = 0; i < clientIDs.size(); i++)
    		            server.wsSend(clientIDs[i], oh.str());
		}

        pongGame.update();
        ostringstream os;


        os << "pong" << " " <<  pongGame.getGameState();
        for (int i = 0; i < clientIDs.size(); i++)
            server.wsSend(clientIDs[i], os.str());

       // next = time(NULL) + 1;
        next = GetTickCount() + 15;
    }
}

int main(int argc, char *argv[]){
    int port;

    cout << "Please set server port: ";
    cin >> port;

    /* set event handler */
    server.setOpenHandler(openHandler);
    server.setCloseHandler(closeHandler);
    server.setMessageHandler(messageHandler);
    server.setPeriodicHandler(periodicHandler);

    std::cout << '\n';
    /* start the chatroom server, listen to ip '127.0.0.1' and port '8000' */
    server.startServer(port);

    return 1;
}
