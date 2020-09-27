#pragma once
#include "Icons.h"


class BulletSpeedPowerUp:public Icons
{

private:
	bool active = true;
	std::string target;
	std::string typeOfPower="bulletSpeed";
	sf::Clock lastingClock;

public:

	void setEffect();
	std::string getTypeOfPower();
	void setup();
	void setActive(bool active_);
	bool getActive();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	float getLastingClock();
	void restartLastingClock();
    std::string getTarget();
	void setTarget(std::string target_);
	//changed virtual void to simple ones







};