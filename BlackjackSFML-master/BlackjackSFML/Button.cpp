#include "Button.h"
#include <iostream>

#include "Button.h"

Button::Button(sf::Texture* idleTexture, sf::Texture* hoverTexture, sf::Texture* clickedTexture, const std::string text, const sf::Font* font, const sf::Vector2f& position, sf::RenderWindow* window, sf::SoundBuffer* clickSoundBuffer)
    : m_idleTexture(idleTexture),m_clicked(false), m_hoverTexture(hoverTexture), m_clickedTexture(clickedTexture), m_window(window), m_enabled(true), m_hovered(false), m_clickSoundBuffer(clickSoundBuffer) {
    m_sprite.setTexture(*m_idleTexture);
    m_sprite.setPosition(position);

    //m_sprite.setScale(sf::Vector2f(2,1));

    //SET UP TEXT
    m_text.setFont(*font);
    m_text.setString(text);
    m_text.setCharacterSize(16);
    setTextAlignment();
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color());
    m_text.setOutlineThickness(1);

    if (m_clickSoundBuffer) {
        m_clickSound.setBuffer(*m_clickSoundBuffer);
    }
}

void Button::updateHoverState(const sf::Vector2f& mousePosition) {
    if (m_clicked == true || m_enabled == false) {
        return;
    }
    if (m_sprite.getGlobalBounds().contains(mousePosition)) {
        m_sprite.setTexture(*m_hoverTexture,true);
        m_hovered = true;
    }
    else {
        m_sprite.setTexture(*m_idleTexture,true);
        m_hovered = false;
    }
}

void Button::setPosition(const sf::Vector2f& position) {
    m_sprite.setPosition(position);
    setTextAlignment();
}

void Button::setTextAlignment(const sf::Vector2f& alignment) {
    sf::Vector2f position = m_sprite.getPosition();
    m_text.setPosition(sf::Vector2f(position.x + ((m_idleTexture->getSize().x - m_text.getGlobalBounds().width) / 2), position.y + (m_idleTexture->getSize().y - m_text.getGlobalBounds().height) / 2 - 5));
    m_text.setPosition(m_text.getPosition() + alignment);
}

void Button::render() {
    m_window->draw(m_sprite);
    m_window->draw(m_text);
}

Button::~Button() {
    std::cout << "Button destructor" << std::endl;
}

sf::Sprite* Button::getSprite()
{
    return &m_sprite;
}

const sf::Texture* Button::getIdleTexture()
{
    return m_idleTexture;
}

void Button::setClicked(bool state)
{
        m_clicked = state;

}

void Button::setEnabled(bool enable) {
    m_enabled = enable;
    m_sprite.setColor(enable ? sf::Color::White : sf::Color(150,150,150,255));
    m_text.setFillColor(enable ? sf::Color::White : sf::Color(150, 150, 150, 255));
}

bool Button::checkClick(const sf::Vector2f& mousePos) {
    if (this->m_enabled && this->m_sprite.getGlobalBounds().contains(mousePos)) {
        m_sprite.setTexture(*m_clickedTexture,true);
        trigger();
        setClicked(true);
        return true;
    }
    return false;
}

void Button::setCallbackFunction(std::function<void()> actionFunc) {
    callbackFunction = actionFunc;  // Store the callback, don't call it here
}

void Button::trigger()
{
    if (m_clickSoundBuffer) {
        m_clickSound.play();
    }
    if (callbackFunction) {
        callbackFunction();  // Execute the stored function
    }
}


void Button::setText(const std::string& text) {
    m_text.setString(text);
    setTextAlignment();
}

void Button::setTextSize(unsigned int size) {
    m_text.setCharacterSize(size);
}

void Button::setTextColor(const sf::Color& color) {
    m_text.setFillColor(color);
}

void Button::setSoundBuffer(sf::SoundBuffer* soundBuffer) {
    m_clickSoundBuffer = soundBuffer;
    if (m_clickSoundBuffer) {
        m_clickSound.setBuffer(*m_clickSoundBuffer);
    }
}