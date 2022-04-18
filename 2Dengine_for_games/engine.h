/*
 * engine.h
 *
 * Created: 13.04.2022 23:52:40
 *  Author: Mikhail
 */ 


#ifndef ENGINE_H_
#define ENGINE_H_
#include <stdint.h>
#define Collision4 0
#define Collision8 1
#define Collision16 3
#define VerticalCollision 2
class engine2D
{
	public:
	uint8_t getVerticalRadius();
	uint8_t getGorizontalRadius();
	void setCenter(uint8_t x, uint8_t y);
	void setVerticalRadius(uint8_t radius);
	void setGorizontalRadius(uint8_t radius);
	void setCollisions(uint8_t Collision);
	uint8_t getX0();
	uint8_t getY0();
	uint8_t getX1();
	uint8_t getY1();
	uint8_t getCenterX();
	uint8_t getCenterY();
	uint8_t getCollision();
	bool CheckIntersection(engine2D ob);
	bool CheckIntersectionPlatform(engine2D ob);
	uint8_t Collisons[16][2];
	private:
	uint8_t x_center, y_center, gor_radius, ver_radius;
	uint8_t Coll;
	
};

#endif /* ENGINE_H_ */