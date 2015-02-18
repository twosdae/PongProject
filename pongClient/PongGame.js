/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


function PongGame()
{
    var canvas = document.createElement("canvas");
    var width = 600;
    var height = 400;
    canvas.width = width;
    canvas.height = height;
    var context = canvas.getContext("2d");
    document.body.appendChild(canvas);
    
    var ball = new Ball(width/2, height/2, 250,1,1);
    var player1 = new Paddle(20,50,10,60, 250);
    var player2 = new Paddle(570,50,10,60, 250);
    
    function Ball(x, y, speed, xDir, yDir)
    {
        this.x = x;
        this.y = y;
        this.speed = speed;
        this.xDir = xDir;
        this.yDir = yDir;

        this.render = function()
        {
            context.fillStyle = "white";
            context.fillRect(this.x, this.y, 10,10);
        };

        this.move = function()
        {

            if(this.y >= height-10 || this.y < 0)
            {
                this.yDir = -this.yDir;
            }

            if(this.paddleHit())
            {
                this.xDir = -this.xDir;
            }

            //to remove later
            if(this.x >= width-10)
            {
                this.xDir = -this.xDir;
            }
            else if(this.x < 0)
            {
                this.x = width/2;
                this.y = height/2;
                this.xDir = -this.xDir;
                this.yDir = -this.yDir;
            }

            this.x = this.x + this.xDir*speed/60;
            this.y = this.y + this.yDir*speed/60;
        };

        this.paddleHit = function()
        {
            var hit = false;

            if(this.xDir < 0 
            && this.x <= player1.x+player1.width && this.x >= player1.x-5
            && this.y >= player1.y && this.y+10 <= player1.y+player1.height)
            {
                hit = true;
            }

            return hit;
        };   
    }
    
    this.setBallPos = function(x,y)
    {
        ball.x = x;
        ball.y = y;
    };
   

    function Paddle(x,y,width,height,speed)
    {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.speed = speed;

        this.render = function()
        {
            context.fillStyle = "white";
            context.fillRect(this.x, this.y, this.width, this.height);
        };
    }

    this.setPaddlePos = function(paddleNum,x,y)
    {
        if(paddleNum == 1)
        {
            player1.x = x;
            player1.y = y;
        }
        else
        {
            player2.x = x;
            player2.y = y;
        }
        
    };
    //window.addEventListener("keydown", function(event)
    //{
    //    if(event.which == 83)
    //    {
    //        player1.moveDown();
    //    }
    //});
    //
    //Renders everything - calls each object's render
    this.render = function()
    {    
        context.fillStyle = "black";
        context.fillRect(0,0,width, height);

        context.fillStyle = "white";
        context.fillText(username, 100, 10);
        context.fillText(userscore,100, 20);
        context.fillText(enemyname, 400, 10);
        context.fillText(enemyscore, 400, 20);
        
        ball.render();
        player1.render();
        player2.render();
    };


//Not used in this project since the server takes care of updating
    //Main Loop - Recursive update function

};



