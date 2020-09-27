#pragma once
#include  "Icons.h"

class BulletSizeIncrease : public Icons
{
private:
	bool active = true;
	bool wasShot = false;
	std::string target;
	std::string typeOfPower = "bulletSizeIncrease";
	sf::Clock lastingClock;

public:
	std::string getTypeOfPower();
	void setPos();
	void setActive(bool active_);
	bool getActive();
	bool getIfWasShot();
	void setWasShot(bool shot_);
	virtual std::string getTarget();
	virtual void setTarget(std::string target_);
	float getLastingClock();
	void restartLastingClock();
	void setup();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;




};