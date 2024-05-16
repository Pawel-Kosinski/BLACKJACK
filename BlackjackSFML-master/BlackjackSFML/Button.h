#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Text.h"

class Button {
private:
    sf::Sprite m_sprite;
    sf::Texture* m_idleTexture;
    sf::Texture* m_hoverTexture;
    sf::Texture* m_clickedTexture;
    sf::Text m_text;
    sf::Sound m_clickSound;
    sf::SoundBuffer* m_clickSoundBuffer;
    sf::RenderWindow* m_window;
    bool m_enabled;
    bool m_hovered;
    bool m_clicked;
    std::function<void()> callbackFunction;
public:
    Button(sf::Texture* idleTexture, sf::Texture* hoverTexture, sf::Texture* clickedTexture, const std::string text, const sf::Font* font, const sf::Vector2f& position, sf::RenderWindow* window, sf::SoundBuffer* clickSoundBuffer = nullptr);
    ~Button();
    sf::Sprite* getSprite();
    const sf::Texture* getIdleTexture();
    void setClicked(bool state);
    void setEnabled(bool enable);
    bool checkClick(const sf::Vector2f& mousePos);
    void setCallbackFunction(std::function<void()> actionFunc);
    void trigger();
    void render();
    void setText(const std::string& text);
    void setTextSize(unsigned int size);
    void setTextColor(const sf::Color& color);
    void setPosition(const sf::Vector2f& position);
    void setTextAlignment(const sf::Vector2f& alignment = sf::Vector2f(0, 0));
    void setSoundBuffer(sf::SoundBuffer* soundBuffer);
    void updateHoverState(const sf::Vector2f& mousePosition);
};