#ifndef CONSOLE_IMAGE_H
#define CONSOLE_IMAGE_H


#include "ConsoleColor.h"
#include <vector>
#include <utility>


class ConsoleWriter;


class ConsoleImage
{
	ConsoleImage(ConsoleWriter & consoleWriter, char outputChar = ' ', ConsoleColor color = ConsoleColor::standard()); // ATTENTION DOIT ÊTRE PRIVEE

public:
	ConsoleImage& operator=(ConsoleImage const & im);

	int width() const;
	int height() const;

	char character(int x, int y) const;
	ConsoleColor color(int x, int y) const;
	std::pair<char, ConsoleColor> pixel(int x, int y) const;

	void fill(char outputChar, ConsoleColor color);
	void fill(int x1, int y1, int width, int height, char outputChar, ConsoleColor color);
	void fill(double x1, double y1, double width, double height, char outputChar, ConsoleColor color);

	void drawPoint(int x, int y, char outputChar, ConsoleColor color);
	void drawPoint(double x, double y, char outputChar, ConsoleColor color);
	void drawPoint(int x, int y, size_t size, char outputChar, ConsoleColor color);
	void drawPoint(double x, double y, size_t size, char outputChar, ConsoleColor color);

	void drawLine(int x1, int y1, int x2, int y2, char outputChar, ConsoleColor color);
	void drawLine(double x1, double y1, double x2, double y2, char outputChar, ConsoleColor color);

	void drawRect(int x1, int y1, int width, int height, char outputChar, ConsoleColor color);
	void drawRect(double x1, double y1, double width, double height, char outputChar, ConsoleColor color);
	void drawRect(int x1, int y1, int width, int height, char borderOutputChar, ConsoleColor borderColor, char fillOutputChar, ConsoleColor fillColor);
	void drawRect(double x1, double y1, double width, double height, char borderOutputChar, ConsoleColor borderColor, char fillOutputChar, ConsoleColor fillColor);

	void drawCircle(int x, int y, int radius, char outputChar, ConsoleColor color);

	void drawText(int x, int y, std::string const & text, ConsoleColor color, bool horizontal = true);
	void drawCenteredText(int pos, std::string const & text, ConsoleColor color, bool horizontal = true);
	void drawCenteredTextBox(int height, std::string const & text, ConsoleColor textColor, int horSpacer, int verSpacer, char borderOutputChar, ConsoleColor borderColor, char fillOutputChar, ConsoleColor fillColor);

	void randomize();
	void calib();

private:
	ConsoleWriter & mConsoleWriter;
	std::vector<CHAR_INFO> mBuffer;

	CHAR_INFO* get(int x, int y) const;
	CHAR_INFO charInfo(char outChar, ConsoleColor color);
	void drawPoint(int x, int y, CHAR_INFO const & pix);
	void drawPoint(double x, double y, CHAR_INFO const & pix);
	void drawLine(int x1, int y1, int x2, int y2, CHAR_INFO const & pix);
	void drawLine(double x1, double y1, double x2, double y2, CHAR_INFO const & pix);
	void drawRect(int x1, int y1, int width, int height, CHAR_INFO const & pix);
	void drawRect(double x1, double y1, double width, double height, CHAR_INFO const & pix);
	void drawCircle(int x, int y, int radius, CHAR_INFO const & pix);

	int round(double value) const;

	friend class ConsoleWriter;
};

#endif // CONSOLE_IMAGE_H
