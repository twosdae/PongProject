/*
 * pongGame.cpp
 *
 *  Created on: Feb 11, 2015
 *      Author: David
 */

#include "pongGame.h"

void PongGame::end()
{
	GameOn=false;
	this->ball.x=WIDTH/2;
	this->ball.y=HEIGHT/2;
	
}

void PongGame::start()
{
	GameOn=true;
}

void PongGame::update()
{
	if(GameOn==true)
	{
		if(ball.paddleHit(paddle))
		{
			ball.xDir = -ball.xDir;
			playerHits++;
		}

		ball.move();
	}
}

std::string PongGame::getGameState()
{
	char ballX[10];
	char ballY[10];
	char paddleX[10];
	char paddleY[10];
	itoa(ball.x, ballX, 10);
	itoa(ball.y, ballY, 10);
	itoa(paddle.x, paddleX, 10);
	itoa(paddle.y, paddleY, 10);
	std::string posStr = std::string(ballX) + " " + std::string(ballY) + " "+ std::string(paddleX) + " " + std::string(paddleY);
	//std::cout << posStr + '\n';

	return posStr;
}

void PongGame::movePaddleUp()
{
	paddle.moveUp();
}

void PongGame::movePaddleDown()
{
	paddle.moveDown();
}

void PongGame::Paddle::moveUp()
{
	this->y = this->y - speed/60;
}

void PongGame::Paddle::moveDown()
{
	this->y = this->y + speed/60;
}

//PRIVATE
bool PongGame::Ball::paddleHit(PongGame::Paddle paddle)
{
	bool hit = false;

	if(this->xDir < 0
	&& this->x <= paddle.x+paddle.width && this->x >= paddle.x
	&& this->y >= paddle.y && this->y+10 <= paddle.y+paddle.height)
	{
		hit = true;
	}

	return hit;
}

void PongGame::Ball::move()
{
	if(this->y >= HEIGHT-10 || this->y < 0)
	{
		this->yDir = -this->yDir;
	}


	if(this->x >= WIDTH-10)
	{
	  this->xDir = -this->xDir;
	}
	else if(this->x < 0)
	{
	  this->x = WIDTH/2;
	  this->y = HEIGHT/2;
	  this->xDir = -this->xDir;
	  this->yDir = -this->yDir;
	}

	this->x = this->x + this->xDir*speed/60;
	this->y = this->y + this->yDir*speed/60;
}


