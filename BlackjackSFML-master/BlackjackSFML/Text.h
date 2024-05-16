#pragma once
#include <SFML/Graphics.hpp>

class Text {
private:
    sf::Text m_text;

public:
    Text(std::string string, int size, sf::Font* font, sf::Vector2f position, sf::Color color, bool outline = false, sf::Color outlineColor = sf::Color::Black);
    ~Text();

    void setText(const std::string& string);
    sf::Text* getText();
};
