#include "Text.h"

Text::Text(std::string string, int size, sf::Font* font, sf::Vector2f position, sf::Color color, bool outline, sf::Color outlineColor)
{
    m_text = sf::Text();
    m_text.setString(string);
    m_text.setCharacterSize(size);
    m_text.setFont(*font);
    // Center Text
    m_text.setPosition(position - sf::Vector2f(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2));
    m_text.setFillColor(color);
    outline == 1 ? m_text.setOutlineThickness(1) : m_text.setOutlineThickness(0);
    m_text.setOutlineColor(outlineColor);
}

Text::~Text() {}

sf::Text* Text::getText() {
    return &m_text;
}

void Text::setText(const std::string& string) {
    m_text.setString(string);
    // Center Text again after updating the string
    m_text.setPosition(m_text.getPosition() - sf::Vector2f(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2));
}
