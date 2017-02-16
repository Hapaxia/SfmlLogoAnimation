//////////////////////////////////////////////////////////////////////////////
//
// SFML Logo Animation (https://github.com/Hapaxia/SfmlLogoAnimation)
//
// Copyright(c) 2016 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#include "SfmlLogoAnimation.hpp"

namespace
{

template <class T>
inline T linearInterpolation(const T& start, const T& end, const float alpha)
{
	return static_cast<T>(start * (1.f - alpha) + end * alpha);
}

} // namespace

SfmlLogoAnimation::SfmlLogoAnimation(sf::RenderWindow& theWindow)
	: window(theWindow)
	, sound(soundBuffer)
	, widescreenSize(960.f, 540.f)
	, startingView({ 0.f, 0.f }, { widescreenSize.y * (theWindow.getView().getSize().x / theWindow.getView().getSize().y), widescreenSize.y })
	, shakeStart(sf::seconds(1.944f))
	, volume(1.f)
	, shakeStrength(50.f)
	, letterScale(0.7f)
	, shakeLength(sf::seconds(0.6f))
	, fadeStart(sf::seconds(11.f))
	, length(sf::seconds(13.f))
{
	logo.setTexture(texture);
	theS.setTexture(texture);
	theF.setTexture(texture);
	theM.setTexture(texture);
	theL.setTexture(texture);
}

bool SfmlLogoAnimation::play()
{
	srand(static_cast<unsigned int>(time(NULL)));
	priv_prepareSound();
	priv_prepareSprites();
	priv_prepareAnimations();
	sound.play();
	clock.restart();
	const sf::Time syncOffset{ sound.getPlayingOffset() - clock.getElapsedTime() };
	bool inAnim{ true };
	while (inAnim)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				sound.stop();
				return false;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				for (auto& key : exitKeys)
				{
					if (event.key.code == key)
					{
						sound.stop();
						return false;
					}
				}
				for (auto& key : skipKeys)
				{
					if (event.key.code == key)
						inAnim = false;
				}
			}
		}

		currentTime = clock.getElapsedTime() + syncOffset;
		if (currentTime > length)
			inAnim = false;
		
		priv_updateObject(logo, animationLogo);
		priv_updateObject(theS, animationTheS);
		priv_updateObject(theF, animationTheF);
		priv_updateObject(theM, animationTheM);
		priv_updateObject(theL, animationTheL);
		priv_updateFade();
		priv_updateShake(startingView);

		window.setView(view);
		window.clear();
		window.draw(logo);
		window.draw(theS);
		window.draw(theF);
		window.draw(theM);
		window.draw(theL);
		window.display();
	}
	return true;
}

bool SfmlLogoAnimation::isSoundFinished() const
{
	return (sound.getStatus() == sf::Sound::Status::Stopped);
}

void SfmlLogoAnimation::stopSound()
{
	sound.stop();
}

void SfmlLogoAnimation::priv_prepareSound()
{
	sound.setVolume(volume * 100.f);
}

void SfmlLogoAnimation::priv_prepareSprites()
{
	// centralise all origins
	logo.setOrigin(logo.getTextureRect().width / 2.f, logo.getTextureRect().height / 2.f);
	theS.setOrigin(theS.getTextureRect().width / 2.f, theS.getTextureRect().height / 2.f);
	theF.setOrigin(theF.getTextureRect().width / 2.f, theF.getTextureRect().height / 2.f);
	theM.setOrigin(theM.getTextureRect().width / 2.f, theM.getTextureRect().height / 2.f);
	theL.setOrigin(theL.getTextureRect().width / 2.f, theL.getTextureRect().height / 2.f);
}

void SfmlLogoAnimation::priv_prepareAnimations()
{
	// s 160 f 144 m 201 l
	// s = 0 + 153 / 2 = 77
	// f = 160 + 137 / 2 = 229
	// m = 160 + 144 + 186 / 2 = 304 + 93 = 397
	// l = 304 + 201 + 136 / 2 = 505 + 68 = 573

	const sf::Vector2f size{ widescreenSize };
	const float letterTextureScale{ letterScale };

	animationLogo.start.time = sf::seconds(1.7f);
	animationLogo.end.time = sf::seconds(1.944f);
	animationLogo.start.position = { size.x * 0.3f, -size.y * 0.4f };
	animationLogo.end.position = { 0.f, -size.y * 0.15f };
	animationLogo.start.scale = 0.f;
	animationLogo.end.scale = 1.f;

	animationTheS.start.time = sf::seconds(2.8f);
	animationTheS.end.time = sf::seconds(3.f);
	animationTheS.start.position = { 0.f, -size.y * 0.15f };
	animationTheS.end.position = { -243.f * letterTextureScale, size.y * 0.3f };
	animationTheS.start.scale = 0.f;
	animationTheS.end.scale = letterScale;

	animationTheF.start.time = sf::seconds(3.2f);
	animationTheF.end.time = sf::seconds(3.4f);
	animationTheF.start.position = { 0.f, -size.y * 0.1f };
	animationTheF.end.position = { -91.f * letterTextureScale, size.y * 0.3f };
	animationTheF.start.scale = 0.f;
	animationTheF.end.scale = letterScale;

	animationTheM.start.time = sf::seconds(3.6f);
	animationTheM.end.time = sf::seconds(3.8f);
	animationTheM.start.position = { 0.f, -size.y * 0.1f };
	animationTheM.end.position = { 77.f * letterTextureScale, size.y * 0.3f };
	animationTheM.start.scale = 0.f;
	animationTheM.end.scale = letterScale;

	animationTheL.start.time = sf::seconds(4.f);
	animationTheL.end.time = sf::seconds(4.2f);
	animationTheL.start.position = { 0.f, -size.y * 0.1f };
	animationTheL.end.position = { 253.f * letterTextureScale, size.y * 0.3f };
	animationTheL.start.scale = 0.f;
	animationTheL.end.scale = letterScale;
}

void SfmlLogoAnimation::priv_updateObject(sf::Sprite& sprite, const Animation& animation)
{
	if (currentTime <= animation.start.time)
	{
		sprite.setPosition(animation.start.position);
		sprite.setScale({ animation.start.scale, animation.start.scale });
	}
	else if (currentTime >= animation.end.time)
	{
		sprite.setPosition(animation.end.position);
		sprite.setScale({ animation.end.scale, animation.end.scale });
	}
	else
	{
		const float ratio{ (currentTime - animation.start.time) / (animation.end.time - animation.start.time) };
		sprite.setPosition(linearInterpolation(animation.start.position, animation.end.position, ratio));
		const float scale{ linearInterpolation(animation.start.scale, animation.end.scale, ratio) };
		sprite.setScale({ scale, scale });
	}
}

void SfmlLogoAnimation::priv_updateFade()
{
	if (currentTime > fadeStart)
	{
		const float ratio{ (currentTime - fadeStart) / (length - fadeStart) };
		const sf::Color color(255, 255, 255, static_cast<sf::Uint8>(255.f * (1.f - ratio)));
		logo.setColor(color);
		theS.setColor(color);
		theF.setColor(color);
		theM.setColor(color);
		theL.setColor(color);
	}
}

void SfmlLogoAnimation::priv_updateShake(const sf::View& startingView)
{
	view = startingView;
	if ((currentTime >= shakeStart) && (currentTime <= (shakeStart + shakeLength)))
	{
		const float ratio{ (currentTime - shakeStart) / shakeLength };
		const float strength{ shakeStrength * (1.f - ratio) };
		view.move({ (static_cast<float>(rand() % 200) / 100.f - 1.f) * strength, (static_cast<float>(rand() % 200) / 100.f - 1.f) * strength });
	}
}
