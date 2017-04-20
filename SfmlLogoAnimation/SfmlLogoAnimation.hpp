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

#ifndef SFMLLOGOANIMATION_HPP
#define SFMLLOGOANIMATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

// SFML Logo Animation v1.1
class SfmlLogoAnimation
{
public:
	sf::Texture texture;
	sf::Sprite logo, theS, theF, theM, theL;
	sf::SoundBuffer soundBuffer;
	std::vector<sf::Keyboard::Key> exitKeys;
	std::vector<sf::Keyboard::Key> skipKeys;

	float volume; // multiplier (range 0 - 1)
	float shakeStrength;
	float letterScale;
	sf::Time shakeLength;
	sf::Time fadeStart;
	sf::Time length;

	SfmlLogoAnimation(sf::RenderWindow& window);
	bool play();
	bool isSoundFinished() const;
	void stopSound();



private:
	const sf::Vector2f widescreenSize;
	const sf::View startingView;
	const sf::Time shakeStart;
	sf::RenderWindow& window;
	sf::Clock clock;
	sf::Sound sound;
	sf::Time currentTime;
	sf::View view;
	struct KeyFrame
	{
		sf::Time time;
		sf::Vector2f position;
		float scale{ 1.f };
	};
	struct Animation
	{
		KeyFrame start;
		KeyFrame end;
	};
	Animation animationLogo;
	Animation animationTheS;
	Animation animationTheF;
	Animation animationTheM;
	Animation animationTheL;

	void priv_prepareSound();
	void priv_prepareSprites();
	void priv_prepareAnimations();
	void priv_updateObject(sf::Sprite& sprite, const Animation& animation);
	void priv_updateFade();
	void priv_updateShake(const sf::View& startingView);
};

#endif // SFMLLOGOANIMATION_HPP
