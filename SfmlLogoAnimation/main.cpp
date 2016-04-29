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

#include <SFML/Graphics.hpp>

#include "SfmlLogoAnimation.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Logo Animation", sf::Style::None);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	// create animation
	SfmlLogoAnimation logoAnim(window);

	// load sound and texture
	if (!logoAnim.soundBuffer.loadFromFile("sfml-logo-animation.wav") ||
		!logoAnim.texture.loadFromFile("sfml-logo-big.png"))
		return EXIT_FAILURE;

	// set texture rects
	logoAnim.logo.setTextureRect({ 0, 0, 313, 304 });
	logoAnim.theS.setTextureRect({ 360, 101, 153, 170 });
	logoAnim.theF.setTextureRect({ 520, 101, 137, 170 });
	logoAnim.theM.setTextureRect({ 664, 101, 186, 170 });
	logoAnim.theL.setTextureRect({ 865, 101, 136, 170 });

	// add keys
	logoAnim.exitKeys.emplace_back(sf::Keyboard::Key::Escape);
	logoAnim.exitKeys.emplace_back(sf::Keyboard::Key::Q);
	logoAnim.skipKeys.emplace_back(sf::Keyboard::Key::Space);
	logoAnim.skipKeys.emplace_back(sf::Keyboard::Key::Return);

	// play animation
	if (!logoAnim.play())
		window.close();

	// (a normal window loop could go here)

	return EXIT_SUCCESS;
}
