#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Button.h"
#include "Text.h"
#include <vector>


class Renderer {
private:
    sf::RenderWindow* m_window;
    sf::Event m_ev;
    sf::VideoMode m_videoMode;
    sf::Vector2f m_mousePosView;
    ResourceManager m_resourceManger;
    std::vector<Text*> m_activeText;
    std::vector<sf::Sprite*> m_activeSprites;
    bool audioEnabled;
    int m_maxFramerate;
    enum GameLoopState { betting, game };
    GameLoopState m_gameLoopState;
    void initVariables();
    void initWindow();
    void initSettingsMenu();
    void updateMousePosition();
    void mainGameLoop();
    void bettingGameLoop();
    void closeWindow();
    int currentBet;
    Text* betValueText;
    bool betConfirmed;  // New flag to indicate bet confirmation
    Button* confirmBetButton;


public:
    std::vector<Button*> m_activeButtons;
    int getCurrentBet() const { return currentBet; }
    void setSpriteAspectRatio(sf::Sprite* spriteRef, const sf::Texture* textureRef);
    void initMainMenu();
    void pollEvents();
    Renderer();
    ~Renderer();
    void initGameLoop();
    enum GameState { mainMenu, settingsMenu, gameLoop };
    GameState m_gameState;
    const bool isRunning() const;
    GameState getGameState() const { return m_gameState; }
    sf::RenderWindow* getWindow() { return m_window; }
    void update();
    void render();
    bool isBetConfirmed() const { return betConfirmed; }
    void clearActiveElements();

};
