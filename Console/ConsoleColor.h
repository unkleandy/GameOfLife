#ifndef CONSOLE_COLOR_H
#define CONSOLE_COLOR_H


#define NOMINMAX
#include <Windows.h>
#include <cstdint>
#include <random>


class ConsoleColor
{
public:
	enum class Text : uint16_t {
		Black			= 0,
		Red				= FOREGROUND_RED,
		Green			= FOREGROUND_GREEN,
		Blue			= FOREGROUND_BLUE,
		Yellow			= Red | Green,
		Magenta			= Red | Blue,
		Cyan			= Green | Blue,
		White			= Red | Green | Blue,
		BrightRed		= Red | FOREGROUND_INTENSITY,
		BrightGreen		= Green | FOREGROUND_INTENSITY,
		BrightBlue		= Blue | FOREGROUND_INTENSITY,
		BrightYellow	= Yellow | FOREGROUND_INTENSITY,
		BrightMagenta	= Magenta | FOREGROUND_INTENSITY,
		BrightCyan		= Cyan | FOREGROUND_INTENSITY,
		BrightWhite		= White | FOREGROUND_INTENSITY
	};
	enum class Background : uint16_t {
		Black			= 0,
		Red				= BACKGROUND_RED,
		Green			= BACKGROUND_GREEN,
		Blue			= BACKGROUND_BLUE,
		Yellow			= Red | Green,
		Magenta			= Red | Blue,
		Cyan			= Green | Blue,
		White			= Red | Green | Blue,
		BrightRed		= Red | BACKGROUND_INTENSITY,
		BrightGreen		= Green | BACKGROUND_INTENSITY,
		BrightBlue		= Blue | BACKGROUND_INTENSITY,
		BrightYellow	= Yellow | BACKGROUND_INTENSITY,
		BrightMagenta	= Magenta | BACKGROUND_INTENSITY,
		BrightCyan		= Cyan | BACKGROUND_INTENSITY,
		BrightWhite		= White | BACKGROUND_INTENSITY
	};
	enum class Opaque : uint16_t {
		Black			= static_cast<uint16_t>(Text::Black)		 | static_cast<uint16_t>(Background::Black),
		Red				= static_cast<uint16_t>(Text::Red)			 | static_cast<uint16_t>(Background::Red),
		Green			= static_cast<uint16_t>(Text::Green)		 | static_cast<uint16_t>(Background::Green),
		Blue			= static_cast<uint16_t>(Text::Blue)			 | static_cast<uint16_t>(Background::Blue),
		Yellow			= static_cast<uint16_t>(Text::Yellow)		 | static_cast<uint16_t>(Background::Yellow),
		Magenta			= static_cast<uint16_t>(Text::Magenta)		 | static_cast<uint16_t>(Background::Magenta),
		Cyan			= static_cast<uint16_t>(Text::Cyan)			 | static_cast<uint16_t>(Background::Cyan),
		White			= static_cast<uint16_t>(Text::White)		 | static_cast<uint16_t>(Background::White),
		BrightRed		= static_cast<uint16_t>(Text::BrightRed)	 | static_cast<uint16_t>(Background::BrightRed),
		BrightGreen		= static_cast<uint16_t>(Text::BrightGreen)	 | static_cast<uint16_t>(Background::BrightGreen),
		BrightBlue		= static_cast<uint16_t>(Text::BrightBlue)	 | static_cast<uint16_t>(Background::BrightBlue),
		BrightYellow	= static_cast<uint16_t>(Text::BrightYellow)	 | static_cast<uint16_t>(Background::BrightYellow),
		BrightMagenta	= static_cast<uint16_t>(Text::BrightMagenta) | static_cast<uint16_t>(Background::BrightMagenta),
		BrightCyan		= static_cast<uint16_t>(Text::BrightCyan)	 | static_cast<uint16_t>(Background::BrightCyan),
		BrightWhite		= static_cast<uint16_t>(Text::BrightWhite)	 | static_cast<uint16_t>(Background::BrightWhite)
	};

	static constexpr Text tk{ Text::Black };
	static constexpr Text tw{ Text::White };
	static constexpr Text tr{ Text::Red };
	static constexpr Text tg{ Text::Green };
	static constexpr Text tb{ Text::Blue };
	static constexpr Text ty{ Text::Yellow };
	static constexpr Text tm{ Text::Magenta };
	static constexpr Text tc{ Text::Cyan };
	static constexpr Text tK{ Text::Black };
	static constexpr Text tW{ Text::BrightWhite };
	static constexpr Text tR{ Text::BrightRed };
	static constexpr Text tG{ Text::BrightGreen };
	static constexpr Text tB{ Text::BrightBlue };
	static constexpr Text tY{ Text::BrightYellow };
	static constexpr Text tM{ Text::BrightMagenta };
	static constexpr Text tC{ Text::BrightCyan };

	static constexpr Background bk{ Background::Black };
	static constexpr Background bw{ Background::White };
	static constexpr Background br{ Background::Red };
	static constexpr Background bg{ Background::Green };
	static constexpr Background bb{ Background::Blue };
	static constexpr Background by{ Background::Yellow };
	static constexpr Background bm{ Background::Magenta };
	static constexpr Background bc{ Background::Cyan };
	static constexpr Background bK{ Background::Black };
	static constexpr Background bW{ Background::BrightWhite };
	static constexpr Background bR{ Background::BrightRed };
	static constexpr Background bG{ Background::BrightGreen };
	static constexpr Background bB{ Background::BrightBlue };
	static constexpr Background bY{ Background::BrightYellow };
	static constexpr Background bM{ Background::BrightMagenta };
	static constexpr Background bC{ Background::BrightCyan };

	static constexpr Opaque black{	Opaque::Black };
	static constexpr Opaque red{	Opaque::Red };
	static constexpr Opaque green{	Opaque::Green };
	static constexpr Opaque blue{	Opaque::Blue };
	static constexpr Opaque yellow{ Opaque::Yellow };
	static constexpr Opaque magenta{Opaque::Magenta };
	static constexpr Opaque cyan{	Opaque::Cyan };
	static constexpr Opaque white{	Opaque::White };
	static constexpr Opaque Black{	Opaque::Black };
	static constexpr Opaque Red{	Opaque::BrightRed };
	static constexpr Opaque Green{	Opaque::BrightGreen };
	static constexpr Opaque Blue{	Opaque::BrightBlue };
	static constexpr Opaque Yellow{	Opaque::BrightYellow };
	static constexpr Opaque Magenta{Opaque::BrightMagenta };
	static constexpr Opaque Cyan{	Opaque::BrightCyan };
	static constexpr Opaque White{	Opaque::BrightWhite };

	ConsoleColor();
	ConsoleColor(Text textColor);
	ConsoleColor(Background backgroundColor);
	ConsoleColor(Opaque opaqueColor);
	ConsoleColor(Text textColor, Background backgroundColor);
	ConsoleColor(uint16_t value);
	ConsoleColor(CHAR_INFO charInfo);

	uint16_t color() const;
	uint16_t color(uint16_t valueToMerge) const;
	bool isValid() const;

	void set();
	void set(Text textColor);
	void set(Background backgroundColor);
	void set(Text textColor, Background backgroundColor);
	void set(Opaque opaqueColor);
	void setInvalid();

	void randomizeText(Background backgroundColor = bk);
	void randomizeBackground(Text textColor = tk);
	void randomizeOpaque();
	void randomize();

	static void flipTextBrightness(ConsoleColor & color);
	static void flipBackgroundBrightness(ConsoleColor & color);
	static void flipOpaqueBrightness(ConsoleColor & color);
	static void darkerText(ConsoleColor & color);
	static void darkerBackground(ConsoleColor & color);
	static void darkerOpaque(ConsoleColor & color);
	static void lighterText(ConsoleColor & color);
	static void lighterBackground(ConsoleColor & color);
	static void lighterOpaque(ConsoleColor & color);
	static void darkestText(ConsoleColor & color);
	static void darkestBackground(ConsoleColor & color);
	static void darkestOpaque(ConsoleColor & color);
	static void lightessText(ConsoleColor & color);
	static void lightessBackground(ConsoleColor & color);
	static void lightessOpaque(ConsoleColor & color);

	static ConsoleColor standard();
	static ConsoleColor randomText(Background backgroundColor = bk);
	static ConsoleColor randomBackground(Text textColor = tk);
	static ConsoleColor randomOpaque();
	static ConsoleColor random();
	static ConsoleColor invalid();

private:
	uint16_t mColor;

	static std::random_device mRandomDevice;
	static std::mt19937 mRandomEngine;
	static std::uniform_int_distribution<uint16_t> mRandomByte;
	static std::uniform_int_distribution<uint16_t> mRandom2Bytes;

	enum class Mask : uint16_t {
		Text					= 0b1111'1111'0000'1111,
		Background				= 0b1111'1111'1111'0000,
		NoColor					= Text & Background,
		OnlyColor				= static_cast<uint16_t>(~NoColor),
		TextBrightness			= FOREGROUND_INTENSITY,
		BackgroundBrightness	= BACKGROUND_INTENSITY,
		Invalid					= 0b1111'1111'1111'1111				// <=-- to do : bad strategy to do otherwise
	};
	ConsoleColor(Mask mask);
};

inline ConsoleColor operator+(ConsoleColor::Text tColor, ConsoleColor::Background bColor) {
	return ConsoleColor(tColor, bColor);
}
inline ConsoleColor operator+(ConsoleColor::Background bColor, ConsoleColor::Text tColor) {
	return ConsoleColor(tColor, bColor);
}


#endif // CONSOLE_COLOR_H
