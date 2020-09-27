#pragma once
#include  "Icons.h"

class SpeedPowerUp : public Icons
{
private:
	bool active = true;
	std::string target;
	std::string typeOfPower = "speed";
	sf::Clock lastingClock;

public:
	std::string getTypeOfPower();
	void setPos();
	void setEffect();
	void setActive(bool active_);
	bool getActive();
    std::string getTarget();
    void setTarget(std::string target_);
	float getLastingClock();
	void restartLastingClock();
	void setup();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;




};