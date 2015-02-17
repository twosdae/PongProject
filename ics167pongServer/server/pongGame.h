/*
 * pongGame.h
 *
 *  Created on: Feb 11, 2015
 *      Author: David
 */

#ifndef PONGGAME_H_
#define PONGGAME_H_

#include <string>
#include <stdlib.h>
#include <iostream>

const int WIDTH = 600;
const int HEIGHT = 400;


class PongGame
{
public:
	int playerHits;
	bool GameOn;
	PongGame()
	{
		playerHits = 0;
		ball = Ball(WIDTH/2, HEIGHT/2, 250,1,1);
		paddle1 = Paddle(20,50,10,60, 250);
		paddle2 = Paddle(570,50,10,60, 250);
		GameOn = false;
	}
	
	void update();
	std::string getGameState();
	void movePaddleUp(int paddle);
	void movePaddleDown(int paddle);
	void start();
	void end();
private:
	class Paddle
	{
	public:
		int x;
		int y;
		int width;
		int height;
		int speed;

		Paddle()
		{
			Paddle(20,50,10,60, 250);
		};
		Paddle(int x, int y, int width, int height, int speed)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->speed = speed;
		}

		void moveUp();
		void moveDown();
	};

	class Ball
	{
	public:
		int x;
		int y;
		int speed;
		int xDir;
		int yDir;
		int justHit;

		Ball()
		{
			Ball(WIDTH/2, HEIGHT/2, 250,1,1);
		};

		Ball(int x, int y, int speed, int xDir, int yDir)
		{
			this->x = x;
			this->y = y;
			this->speed = speed;
			this->xDir = xDir;
			this->yDir = yDir;

			justHit = 0;
		}

		bool paddleHit(Paddle p);
		void move();
	};


	Ball ball;
	Paddle paddle1;
	Paddle paddle2;

};


#endif /* PONGGAME_H_ */
