#include "ConsoleColor.h"


std::random_device ConsoleColor::mRandomDevice;
std::mt19937 ConsoleColor::mRandomEngine(mRandomDevice());
std::uniform_int_distribution<uint16_t> ConsoleColor::mRandomByte(0, 0xF);
std::uniform_int_distribution<uint16_t> ConsoleColor::mRandom2Bytes(0, 0xFF);


ConsoleColor::ConsoleColor()
	: mColor{ 0 }
{
}

ConsoleColor::ConsoleColor(Text textColor)
	: mColor{ static_cast<uint16_t>(textColor) }
{
}

ConsoleColor::ConsoleColor(Background backgroundColor)
	: mColor{ static_cast<uint16_t>(backgroundColor) }
{
}

ConsoleColor::ConsoleColor(Opaque opaqueColor)
	: mColor{ static_cast<uint16_t>(opaqueColor) }
{
}

ConsoleColor::ConsoleColor(Text textColor, Background backgroundColor)
	: mColor{ static_cast<uint16_t>(static_cast<uint16_t>(textColor) | static_cast<uint16_t>(backgroundColor)) }
{
}

ConsoleColor::ConsoleColor(uint16_t color)
	: mColor{ static_cast<uint16_t>(static_cast<uint16_t>(Mask::OnlyColor) & color) }
{
}

ConsoleColor::ConsoleColor(CHAR_INFO charInfo)
	: ConsoleColor(charInfo.Attributes)
{
}

ConsoleColor::ConsoleColor(Mask mask)
	: mColor{ static_cast<uint16_t>(mask) }
{
}

uint16_t ConsoleColor::color() const
{
	return mColor;
}

uint16_t ConsoleColor::color(uint16_t valueToMerge) const
{
	return mColor | (static_cast<uint16_t>(Mask::NoColor) & valueToMerge);
}

bool ConsoleColor::isValid() const
{
	return mColor != static_cast<uint16_t>(Mask::Invalid);
}

void ConsoleColor::set()
{
	mColor = 0;
}

void ConsoleColor::set(Text textColor)
{
	mColor |= static_cast<uint16_t>(Mask::Background) & static_cast<uint16_t>(textColor);
}

void ConsoleColor::set(Background backgroundColor)
{
	mColor |= static_cast<uint16_t>(Mask::Text) & static_cast<uint16_t>(backgroundColor);
}

void ConsoleColor::set(Text textColor, Background backgroundColor)
{
	mColor = static_cast<uint16_t>(textColor) | static_cast<uint16_t>(backgroundColor);
}

void ConsoleColor::set(Opaque opaqueColor)
{
	mColor = static_cast<uint16_t>(opaqueColor);
}

void ConsoleColor::setInvalid()
{
	mColor = static_cast<uint16_t>(Mask::Invalid);
}

void ConsoleColor::randomizeText(Background backgroundColor)
{
	*this = randomText(backgroundColor);
}

void ConsoleColor::randomizeBackground(Text textColor)
{
	*this = randomBackground(textColor);
}

void ConsoleColor::randomizeOpaque()
{
	*this = randomOpaque();
}

void ConsoleColor::randomize()
{
	*this = random();
}

void ConsoleColor::flipTextBrightness(ConsoleColor & color)
{
	color.mColor = (~static_cast<int>(Mask::TextBrightness) & color.mColor) | (static_cast<int>(Mask::TextBrightness) & ~color.mColor);
}

void ConsoleColor::flipBackgroundBrightness(ConsoleColor & color)
{
	color.mColor = (~static_cast<int>(Mask::BackgroundBrightness) & color.mColor) | (static_cast<int>(Mask::BackgroundBrightness) & ~color.mColor);
}

void ConsoleColor::flipOpaqueBrightness(ConsoleColor & color)
{
	flipTextBrightness(color);
	flipBackgroundBrightness(color);
}

void ConsoleColor::darkerText(ConsoleColor & color)
{
	color.mColor &= ~static_cast<int>(Mask::TextBrightness);
}

void ConsoleColor::darkerBackground(ConsoleColor & color)
{
	color.mColor &= ~static_cast<int>(Mask::BackgroundBrightness);
}

void ConsoleColor::darkerOpaque(ConsoleColor & color)
{
	darkerText(color);
	darkerBackground(color);
}

void ConsoleColor::lighterText(ConsoleColor & color)
{
	color.mColor |= static_cast<int>(Mask::TextBrightness);
}

void ConsoleColor::lighterBackground(ConsoleColor & color)
{
	color.mColor |= static_cast<int>(Mask::BackgroundBrightness);
}

void ConsoleColor::lighterOpaque(ConsoleColor & color)
{
	lighterText(color);
	lighterBackground(color);
}

void ConsoleColor::darkestText(ConsoleColor & color)
{
	if (color.mColor & static_cast<int>(Mask::TextBrightness)) {
		darkerText(color);
	} else {
		color.set(Text::Black);
	}
}

void ConsoleColor::darkestBackground(ConsoleColor & color)
{
	if (color.mColor & static_cast<int>(Mask::BackgroundBrightness)) {
		darkerBackground(color);
	} else {
		color.set(Background::Black);
	}
}

void ConsoleColor::darkestOpaque(ConsoleColor & color)
{
	darkestText(color);
	darkestBackground(color);
}

void ConsoleColor::lightessText(ConsoleColor & color)
{
	if (!(color.mColor & static_cast<int>(Mask::TextBrightness))) {
		lighterText(color);
	} else {
		color.set(Text::White);
	}
}

void ConsoleColor::lightessBackground(ConsoleColor & color)
{
	if (!(color.mColor & static_cast<int>(Mask::BackgroundBrightness))) {
		lighterBackground(color);
	} else {
		color.set(Background::White);
	}
}

void ConsoleColor::lightessOpaque(ConsoleColor & color)
{
	lightessText(color);
	lightessBackground(color);
}

ConsoleColor ConsoleColor::standard()
{
	return ConsoleColor(Text::White, Background::Black);
}

ConsoleColor ConsoleColor::randomText(Background backgroundColor)
{
	return mRandomByte(mRandomEngine);
}

ConsoleColor ConsoleColor::randomBackground(Text textColor)
{
	return mRandomByte(mRandomEngine) << 4;
}

ConsoleColor ConsoleColor::randomOpaque()
{
	uint16_t random{ mRandomByte(mRandomEngine) };
	return (random << 4)| random;
}

ConsoleColor ConsoleColor::random()
{
	return mRandom2Bytes(mRandomEngine);
}

ConsoleColor ConsoleColor::invalid()
{
	return ConsoleColor(Mask::Invalid);
}


