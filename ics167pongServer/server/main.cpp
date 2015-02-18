#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include "websocket.h"
#include "pongGame.h"

using namespace std;
struct PlayerInfo
	{
		std::string playerName;
		int clientID;
		int score;
	};

	PlayerInfo player1;
	PlayerInfo player2;

webSocket server;
PongGame pongGame;

int numPlayers;

/* called when a client connects */
void openHandler(int clientID){
    ostringstream os;
    os << "Stranger " << clientID << " has joined.";
	numPlayers++;
	if(numPlayers>2)
	{
		cout<<"Too many People. I'm kicking this guy." << endl;
		server.wsSend(clientID, "There are too many people on the server.");
		server.wsClose(clientID);
	}

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
	numPlayers--;
    vector<int> clientIDs = server.getClientIDs();
    for (int i = 0; i < clientIDs.size(); i++){
        if (clientIDs[i] != clientID)
            server.wsSend(clientIDs[i], os.str());
    }
}

/* called when a client sends a message to the server */
void messageHandler(int clientID, string message){
	cout << message << endl;

	if(message.compare("paddleUp") == 0)
    {
		pongGame.movePaddleUp(clientID+1);
    }
	else if(message.compare("paddleDown") == 0)
	{
		pongGame.movePaddleDown(clientID+1);
	}
	else
	{
		cout << "I got user nickname" << endl;
		std::istringstream ss(message);
		std::string token;
		std::getline(ss, token, ' ');

		if(token.compare("username")==0)
		{
			std::getline(ss, token, ' ');
			if(clientID == 0)
			{
				player1.playerName = token;
				player1.clientID = clientID;
				std::cout << "Player1: " + player1.playerName << '\n';
			}
			else if(clientID == 1)
			{
				player2.playerName = token;
				player2.clientID = clientID;
				std::cout << "Player2: " + player2.playerName << '\n';
			}
		}
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
		
		if(numPlayers==2 && pongGame.GameOn==false)
		{
			pongGame.start();
			ostringstream oh;
			ostringstream ohh;
			oh << "enemyname " << player2.playerName;
			server.wsSend(0, oh.str());
			ohh << "enemyname " << player1.playerName;
			server.wsSend(1, ohh.str());
		}
		if(numPlayers<2 && pongGame.GameOn==true)
		{
			pongGame.end();
		}
		if(pongGame.GameOn==true)
		{
			pongGame.update();
			int newscore1 = pongGame.getScore(1);
			int newscore2 = pongGame.getScore(2);

			if(player1.score != newscore1 || player2.score != newscore2)
			{
				player1.score = newscore1;
				player2.score = newscore2;
				char score1[10];
    			itoa(newscore1,score1,10);
				char score2[10];
				itoa(newscore2,score2,10);

				ostringstream oh;
				oh << "score " << std::string(score1) << ' ' << std::string(score2);
				server.wsSend(0, oh.str());
				server.wsSend(1, oh.str());

			}


		}
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
	numPlayers = 0;
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
