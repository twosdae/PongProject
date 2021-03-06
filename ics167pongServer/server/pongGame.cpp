/*
 * pongGame.cpp
 *
 *  Created on: Feb 11, 2015
 *      Author: David
 */

#include "pongGame.h"

int PongGame::getScore(int player)
{
	if(player==1)
	{
		return p1Score;
	}
	else if(player==2)
	{
		return p2Score;
	}
}

void PongGame::end()
{
	GameOn=false;
	this->ball.x=WIDTH/2;
	this->ball.y=HEIGHT/2;
	p1Score = 0;
	p2Score = 0;
	
}

void PongGame::start()
{
	GameOn=true;
}

void PongGame::update()
{
	if(GameOn==true)
	{
		if(ball.paddleHit(paddle1) || ball.paddleHit(paddle2))
		{
			ball.xDir = -ball.xDir;
			playerHits++;
		}

		int goal = ball.move();

		if(goal == -1)
		{
			p2Score++;
		}
		else if(goal == 1)
		{
			p1Score++;
		}

	}
}

std::string PongGame::getGameState()
{
	char ballX[10];
	char ballY[10];
	char paddle1X[10];
	char paddle1Y[10];
	char paddle2X[10];
	char paddle2Y[10];
	itoa(ball.x, ballX, 10);
	itoa(ball.y, ballY, 10);
	itoa(paddle1.x, paddle1X, 10);
	itoa(paddle1.y, paddle1Y, 10);
	itoa(paddle2.x, paddle2X, 10);
	itoa(paddle2.y, paddle2Y, 10);
	std::string posStr = std::string(ballX) + " " + std::string(ballY) + " ";
	posStr = posStr + std::string(paddle1X) + " " + std::string(paddle1Y) + " ";
	posStr = posStr + std::string(paddle2X) + " " + std::string(paddle2Y);
	//std::cout << posStr + '\n';

	return posStr;
}

void PongGame::movePaddleUp(int paddle)
{

	if(paddle == 1)
	{
		paddle1.moveUp();
	}
	else
	{
		paddle2.moveUp();
	}

}

void PongGame::movePaddleDown(int paddle)
{
	if(paddle == 1)
	{
		paddle1.moveDown();
	}
	else
	{
		paddle2.moveDown();
	}
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
	&& this->y >= paddle.y && this->y+10 <= paddle.y+paddle.height
	&& justHit==0)
	{
		hit = true;
		justHit=10;
	}
	else if(
	   this->xDir > 0
	&& this->x+10 >= paddle.x && this->x+10 <= paddle.x+paddle.width
	&& this->y >= paddle.y && this->y+10 <= paddle.y+paddle.height
	&& justHit==0)
	{
		hit = true;
		justHit=10;
	}

	if(justHit>0)
	{
		justHit--;
	}

	return hit;
}

int PongGame::Ball::move()
{
	int goal = 0;
	if(this->y >= HEIGHT-10 || this->y < 0)
	{
		this->yDir = -this->yDir;
	}


//	if(this->x >= WIDTH-10)
//	{
//	  this->xDir = -this->xDir;
//	}
	if(this->x < 0 || this->x > 590)
	{
		if(this->x<0)
		{
			goal = -1;
		}
		if(this->x>590)
		{
			goal = 1;
		}


	  this->x = WIDTH/2;
	  this->y = HEIGHT/2;
	  this->xDir = -this->xDir;
	  this->yDir = -this->yDir;

	  return goal;
	}

	this->x = this->x + this->xDir*speed/60;
	this->y = this->y + this->yDir*speed/60;
}


