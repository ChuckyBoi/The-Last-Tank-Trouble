#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(sf::Texture& t, float x, float y, float w, float h, float count, float speed_)
{
	frame = 0;
	speed = speed_;
	for (int i = 0; i < count; i++)
	{
		frames.push_back(sf::IntRect(x + i * w, y, w, h));

		sprite.setTexture(t);
		sprite.setOrigin(w / 2, h / 2);
		sprite.setTextureRect(frames[0]);
	}
}
void Animation::update()
{
	frame += speed;
	int n = frames.size();
	if (frame >= n)
	{
		frame -= n;
	}
	if (n > 0)
	{
		sprite.setTextureRect(frames[int(frame)]);
	}
}

bool Animation::isEnd()
{
		return frame + speed >= frames.size();
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(sprite);
}
