#include "engine.h"
void engine2D::setCenter(uint8_t x, uint8_t y)
{
	engine2D::x_center = x;
	engine2D::y_center = y;
}

void engine2D::setGorizontalRadius(uint8_t radius)
{
	engine2D::gor_radius = radius;
}

void engine2D::setVerticalRadius(uint8_t radius)
{
	engine2D::ver_radius = radius;
}

void engine2D::setCollisions(uint8_t Collision)
{
	engine2D::Coll = Collision;
	switch(Collision)
	{
		case 0:
		engine2D::Collisons[0][0] = engine2D::getCenterX()-engine2D::getGorizontalRadius();
		engine2D::Collisons[0][1] = engine2D::getCenterY();
		
		engine2D::Collisons[1][0] = engine2D::getCenterX();
		engine2D::Collisons[1][1] = engine2D::getCenterY()-engine2D::getVerticalRadius();
		
		engine2D::Collisons[2][0] = engine2D::getCenterX()+engine2D::getGorizontalRadius();
		engine2D::Collisons[2][1] = engine2D::getCenterY();
		
		engine2D::Collisons[3][0] = engine2D::getCenterX();
		engine2D::Collisons[3][1] = engine2D::getCenterY()+engine2D::getVerticalRadius();
		break;
		case 1:
		engine2D::Collisons[0][0] = engine2D::getCenterX()-engine2D::getGorizontalRadius();
		engine2D::Collisons[0][1] = engine2D::getCenterY();
		
		engine2D::Collisons[1][0] = engine2D::getCenterX()-engine2D::getGorizontalRadius();
		engine2D::Collisons[1][1] = engine2D::getCenterY()-engine2D::getVerticalRadius();
		
		engine2D::Collisons[2][0] = engine2D::getCenterX();
		engine2D::Collisons[2][1] = engine2D::getCenterY()-engine2D::getVerticalRadius();
		
		engine2D::Collisons[3][0] = engine2D::getCenterX()+engine2D::getGorizontalRadius();
		engine2D::Collisons[3][1] = engine2D::getCenterY()-engine2D::getVerticalRadius();
		
		engine2D::Collisons[4][0] = engine2D::getCenterX()+engine2D::getGorizontalRadius();
		engine2D::Collisons[4][1] = engine2D::getCenterY();
		
		engine2D::Collisons[5][0] = engine2D::getCenterX()+engine2D::getGorizontalRadius();
		engine2D::Collisons[5][1] = engine2D::getCenterY()+engine2D::getVerticalRadius();
		
		engine2D::Collisons[6][0] = engine2D::getCenterX();
		engine2D::Collisons[6][1] = engine2D::getCenterY()+engine2D::getVerticalRadius();
		
		engine2D::Collisons[7][0] = engine2D::getCenterX()-engine2D::getGorizontalRadius();
		engine2D::Collisons[7][1] = engine2D::getCenterY()+engine2D::getVerticalRadius();
		break;
		case 3:
		engine2D::Collisons[0][0] = engine2D::getCenterX()-engine2D::getGorizontalRadius();
		engine2D::Collisons[0][1] = engine2D::getCenterY()+engine2D::getVerticalRadius();
		
		engine2D::Collisons[1][0] = engine2D::getCenterX()-engine2D::getGorizontalRadius();
		engine2D::Collisons[1][1] = engine2D::getCenterY()+(engine2D::getVerticalRadius()/2);
		
		engine2D::Collisons[2][0] = engine2D::getCenterX()-engine2D::getGorizontalRadius();
		engine2D::Collisons[2][1] = engine2D::getCenterY();
		
		engine2D::Collisons[3][0] = engine2D::getCenterX()-engine2D::getGorizontalRadius();
		engine2D::Collisons[3][1] = engine2D::getCenterY()-(engine2D::getVerticalRadius()/2);
		
		engine2D::Collisons[4][0] = engine2D::getCenterX()-engine2D::getGorizontalRadius();
		engine2D::Collisons[4][1] = engine2D::getCenterY()-engine2D::getVerticalRadius();
		
		engine2D::Collisons[5][0] = engine2D::getCenterX()-(engine2D::getGorizontalRadius()/2);
		engine2D::Collisons[5][1] = engine2D::getCenterY()-engine2D::getVerticalRadius();
		
		engine2D::Collisons[6][0] = engine2D::getCenterX();
		engine2D::Collisons[6][1] = engine2D::getCenterY()-engine2D::getVerticalRadius();
		
		engine2D::Collisons[7][0] = engine2D::getCenterX()+(engine2D::getGorizontalRadius()/2);
		engine2D::Collisons[7][1] = engine2D::getCenterY()-engine2D::getVerticalRadius();
		
		engine2D::Collisons[8][0] = engine2D::getCenterX()+engine2D::getGorizontalRadius();
		engine2D::Collisons[8][1] = engine2D::getCenterY()-engine2D::getVerticalRadius();
		
		engine2D::Collisons[9][0] = engine2D::getCenterX()+engine2D::getGorizontalRadius();
		engine2D::Collisons[9][1] = engine2D::getCenterY()-(engine2D::getVerticalRadius()/2);
		
		engine2D::Collisons[10][0] = engine2D::getCenterX()+engine2D::getGorizontalRadius();
		engine2D::Collisons[10][1] = engine2D::getCenterY();
		
		engine2D::Collisons[11][0] = engine2D::getCenterX()+engine2D::getGorizontalRadius();
		engine2D::Collisons[11][1] = engine2D::getCenterY()+(engine2D::getVerticalRadius()/2);
		
		engine2D::Collisons[12][0] = engine2D::getCenterX()+engine2D::getGorizontalRadius();
		engine2D::Collisons[12][1] = engine2D::getCenterY()+engine2D::getVerticalRadius();
		
		engine2D::Collisons[13][0] = engine2D::getCenterX()+(engine2D::getGorizontalRadius()/2);
		engine2D::Collisons[13][1] = engine2D::getCenterY()+engine2D::getVerticalRadius();
		
		engine2D::Collisons[14][0] = engine2D::getCenterX();
		engine2D::Collisons[14][1] = engine2D::getCenterY()+engine2D::getVerticalRadius();
		
		engine2D::Collisons[15][0] = engine2D::getCenterX()-(engine2D::getGorizontalRadius()/2);
		engine2D::Collisons[15][1] = engine2D::getCenterY()+engine2D::getVerticalRadius();
		break;
		case 2:
		uint8_t x_ = 0;
		for(uint8_t b = engine2D::getCenterX()-engine2D::getGorizontalRadius(); b < engine2D::getCenterX()+engine2D::getGorizontalRadius(); b+=2*engine2D::getGorizontalRadius()/16)
		{
			engine2D::Collisons[x_][0]=b;
			x_++;
		}
		for(uint8_t c = 0; c < 16; c++)
		{
			engine2D::Collisons[c][1]=engine2D::getCenterY()-engine2D::getVerticalRadius();
		}
		break;
	}
}

uint8_t engine2D::getCenterX()
{
	return engine2D::x_center;
}

uint8_t engine2D::getCenterY()
{
	return engine2D::y_center;
}

uint8_t engine2D::getCollision()
{
	return engine2D::Coll;
}

uint8_t engine2D::getGorizontalRadius()
{
	return engine2D::gor_radius;
}

uint8_t engine2D::getVerticalRadius()
{
	return engine2D::ver_radius;
}

bool engine2D::CheckIntersection(engine2D ob)
{
	for(int i = 0; i < (engine2D::getCollision()+1)*4; i++)
	{
		for(int b = 0; b < (ob.getCollision()+1)*4; b++)
		{
			if(engine2D::Collisons[i][0]==ob.Collisons[b][0] && engine2D::Collisons[i][1]==ob.Collisons[b][1])return 1;
		}
	}
	return 0;
}

bool engine2D::CheckIntersectionPlatform(engine2D ob)
{
	for(int i = 0; i < (engine2D::getCollision()+1)*4; i++)
	{
		for(int b = 0; b < 16; b++)
		{
			if(engine2D::Collisons[i][0]==ob.Collisons[b][0] && engine2D::Collisons[i][1]==ob.Collisons[b][1])return 1;
		}
	}
	return 0;
}


uint8_t engine2D::getX0()
{
	return engine2D::getCenterX()-engine2D::getGorizontalRadius();
}

uint8_t engine2D::getY0()
{
	return engine2D::getCenterY()+engine2D::getVerticalRadius();
}

uint8_t engine2D::getX1()
{
	return engine2D::getCenterX()+engine2D::getGorizontalRadius();
}

uint8_t engine2D::getY1()
{
	return engine2D::getCenterY()-engine2D::getVerticalRadius();
}