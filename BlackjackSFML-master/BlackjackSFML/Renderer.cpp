#include "Renderer.h"

Renderer::Renderer() {
    initVariables();
    initWindow();
    m_window->setFramerateLimit(m_maxFramerate);
    initMainMenu(); // Initialize main menu at startup
}

Renderer::~Renderer() {
    delete m_window;
}

const bool Renderer::isRunning() const {
    return m_window->isOpen();
}

void Renderer::initVariables() {
    // Load resources
    m_resourceManger.loadTexture("buttonDefIdle", "Assets\\kenney_ui-pack\\PNG\\blue_button00.png");
    m_resourceManger.loadTexture("buttonDefHover", "Assets\\kenney_ui-pack\\PNG\\blue_button04.png");
    m_resourceManger.loadTexture("buttonDefClick", "Assets\\kenney_ui-pack\\PNG\\blue_button01.png");
    m_resourceManger.loadSoundBuffer("buttonDefClick", "Assets\\kenney_ui-audio\\Audio\\click1.ogg");
    m_resourceManger.loadFont("robotoSlabBlack", "Assets\\Roboto_Slab\\static\\RobotoSlab-Black.ttf");
    m_resourceManger.loadTexture("mainMenuBg", "Assets\\Background.jpg");
    m_resourceManger.loadTexture("buttonBetIdle", "Assets\\kenney_ui-pack\\PNG\\blue_button07.png");
    m_resourceManger.loadTexture("buttonBetClick", "Assets\\kenney_ui-pack\\PNG\\blue_button08.png");
    m_resourceManger.loadTexture("buttonBetHover", "Assets\\kenney_ui-pack\\PNG\\blue_button11.png");

    this->audioEnabled = true;
    this->m_gameState = mainMenu;
    this->m_maxFramerate = 60;
    this->m_window = nullptr;
    this->currentBet = 0;
    this->betConfirmed = false;  // Initialize bet confirmation flag
}

void Renderer::initWindow() {
    m_videoMode.height = 600;
    m_videoMode.width = 800;
    m_window = new sf::RenderWindow(m_videoMode, "Blackjack", sf::Style::Titlebar | sf::Style::Close);
}

void Renderer::updateMousePosition() {
    m_mousePosView = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
}

void Renderer::pollEvents() {
    while (m_window->pollEvent(m_ev)) {
        switch (m_ev.type) {
        case sf::Event::Closed:
            closeWindow();
            break;
        case sf::Event::KeyPressed:
            if (m_ev.key.code == sf::Keyboard::Escape)
                m_window->close();
            break;
        case sf::Event::MouseButtonPressed:
            for (auto x : m_activeButtons) {
                if (x && x->checkClick(m_mousePosView)) {
                    break;
                }
            }
            break;
        case sf::Event::MouseButtonReleased:
            for (auto x : m_activeButtons) {
                x->setClicked(false);
            }
            break;
        }
    }
}

void Renderer::update() {
    updateMousePosition();
    for (auto x : m_activeButtons) {
        x->updateHoverState(m_mousePosView);
    }
    pollEvents();
}

void Renderer::render() {
    m_window->clear();
    for (auto x : m_activeSprites) {
        m_window->draw(*x);
    }
    for (auto x : m_activeButtons) {
        x->render();
    }
    for (auto x : m_activeText) {
        m_window->draw(*x->getText());
    }
    m_window->display();
}

void Renderer::clearActiveElements() {
    m_activeButtons.clear();
    m_activeText.clear();
}

void Renderer::closeWindow() {
    m_window->close();
}

void Renderer::setSpriteAspectRatio(sf::Sprite* spriteRef, const sf::Texture* textureRef) {
    float textureX = textureRef->getSize().x;
    float textureY = textureRef->getSize().y;
    float windowX = m_window->getSize().x;
    float windowY = m_window->getSize().y;
    float imageAspectRatio = textureX / textureY;
    float windowAspectRatio = windowX / windowY;
    // Adjust scale based on comparison
    if (windowAspectRatio < imageAspectRatio) {
        // Window is wider than image
        float scale = windowY / textureY;
        spriteRef->setScale(scale, scale);
        spriteRef->setPosition((windowX - textureX * scale) / 2, 0);
    }
    else {
        // Window is taller than image
        float scale = windowX / textureX;
        spriteRef->setScale(scale, scale);
        spriteRef->setPosition(0, (windowY - textureY * scale) / 2);
    }
}

void Renderer::initMainMenu() {
    clearActiveElements(); // Clear active elements

    float centerX = m_window->getSize().x / 2;
    float BcenterX = (m_window->getSize().x - m_resourceManger.getTexture("buttonDefIdle").getSize().x) / 2;

    Text* title = new Text("BLACKJACK", 32, &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(centerX, 100), sf::Color::White, true);
    Button* play = new Button(&m_resourceManger.getTexture("buttonDefIdle"), &m_resourceManger.getTexture("buttonDefHover"), &m_resourceManger.getTexture("buttonDefClick"), "Play", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(BcenterX, 200), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));
    Button* settings = new Button(&m_resourceManger.getTexture("buttonDefIdle"), &m_resourceManger.getTexture("buttonDefHover"), &m_resourceManger.getTexture("buttonDefClick"), "Settings", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(BcenterX, 300), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));
    Button* exit = new Button(&m_resourceManger.getTexture("buttonDefIdle"), &m_resourceManger.getTexture("buttonDefHover"), &m_resourceManger.getTexture("buttonDefClick"), "Exit", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(BcenterX, 400), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));

    settings->setCallbackFunction([this] { initSettingsMenu(); });
    exit->setCallbackFunction([this] { closeWindow(); });
    play->setCallbackFunction([this] { initGameLoop(); });

    m_activeButtons.push_back(play);
    m_activeButtons.push_back(settings);
    m_activeButtons.push_back(exit);
    m_activeText.push_back(title);

    sf::Sprite* backgroundSprite = new sf::Sprite;
    backgroundSprite->setTexture(m_resourceManger.getTexture("mainMenuBg"));

    setSpriteAspectRatio(backgroundSprite, &m_resourceManger.getTexture("mainMenuBg"));
    m_activeSprites.push_back(backgroundSprite);

    m_gameState = mainMenu;
}

void Renderer::initSettingsMenu() {
    clearActiveElements(); // Clear active elements

    float centerX = m_window->getSize().x / 2;
    float BcenterX = (m_window->getSize().x - m_resourceManger.getTexture("buttonDefIdle").getSize().x) / 2;

    Text* settings = new Text("SETTINGS", 16, &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(centerX, 100), sf::Color::White, true);
    Text* audioT = new Text("Audio:", 16, &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(centerX, 200), sf::Color::White, true);
    Button* audioB = new Button(&m_resourceManger.getTexture("buttonDefIdle"), &m_resourceManger.getTexture("buttonDefHover"), &m_resourceManger.getTexture("buttonDefClick"), audioEnabled == true ? "ON" : "OFF", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(BcenterX, 225), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));
    Button* backB = new Button(&m_resourceManger.getTexture("buttonDefIdle"), &m_resourceManger.getTexture("buttonDefHover"), &m_resourceManger.getTexture("buttonDefClick"), "Back", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(BcenterX, 400), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));

    audioB->setCallbackFunction([this, audioB] {
        if (audioEnabled == true) {
            audioEnabled = false;
            sf::Listener::setGlobalVolume(0);
            audioB->setText("OFF");
        }
        else {
            audioEnabled = true;
            sf::Listener::setGlobalVolume(100);
            audioB->setText("ON");
        }
        });

    backB->setCallbackFunction([this] { initMainMenu(); });

    m_activeText.push_back(settings);
    m_activeText.push_back(audioT);
    m_activeButtons.push_back(audioB);
    m_activeButtons.push_back(backB);

    m_gameState = settingsMenu;
}

void Renderer::initGameLoop() {
    clearActiveElements(); // Clear active elements

    m_gameState = gameLoop;
    m_gameLoopState = betting;
    betConfirmed = false;  // Reset bet confirmation flag
    currentBet = 0;  // Reset current bet amount

    float centerX = m_window->getSize().x / 2;
    float BcenterX = (m_window->getSize().x - m_resourceManger.getTexture("buttonBetIdle").getSize().x) / 2;

    Text* you = new Text("YOU", 16, &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(centerX, 575), sf::Color::White, true);
    Text* dealer = new Text("DEALER", 16, &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(centerX, 25), sf::Color::White, true);

    m_activeText.push_back(you);
    m_activeText.push_back(dealer);

    // Set background for game loop
    sf::Sprite* backgroundSprite = new sf::Sprite;
    backgroundSprite->setTexture(m_resourceManger.getTexture("mainMenuBg"));
    setSpriteAspectRatio(backgroundSprite, &m_resourceManger.getTexture("mainMenuBg"));
    m_activeSprites.push_back(backgroundSprite);

    mainGameLoop();
}

void Renderer::mainGameLoop() {
    switch (m_gameLoopState) {
    case betting:
        bettingGameLoop();
        break;
    case game:
        // (game logic)
        break;
    default:
        break;
    }
}

void Renderer::bettingGameLoop() {
    clearActiveElements(); // Clear active elements

    float centerX = m_window->getSize().x / 2;
    float BcenterX = (m_window->getSize().x - m_resourceManger.getTexture("buttonBetIdle").getSize().x) / 2;

    betValueText = new Text("BET: $0", 16, &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(centerX, 100), sf::Color::White, true);
    Text* moneyT = new Text("YOUR MONEY HERE", 16, &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(centerX, 500), sf::Color::White, true);

    Button* betadd1 = new Button(&m_resourceManger.getTexture("buttonBetIdle"), &m_resourceManger.getTexture("buttonBetHover"), &m_resourceManger.getTexture("buttonBetClick"), "+1$", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(BcenterX - 100, 350), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));
    Button* betadd10 = new Button(&m_resourceManger.getTexture("buttonBetIdle"), &m_resourceManger.getTexture("buttonBetHover"), &m_resourceManger.getTexture("buttonBetClick"), "+10$", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(BcenterX, 350), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));
    Button* betadd50 = new Button(&m_resourceManger.getTexture("buttonBetIdle"), &m_resourceManger.getTexture("buttonBetHover"), &m_resourceManger.getTexture("buttonBetClick"), "+50$", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(BcenterX + 100, 350), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));
    Button* betsub1 = new Button(&m_resourceManger.getTexture("buttonBetIdle"), &m_resourceManger.getTexture("buttonBetHover"), &m_resourceManger.getTexture("buttonBetClick"), "-1$", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(BcenterX - 100, 420), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));
    Button* betsub10 = new Button(&m_resourceManger.getTexture("buttonBetIdle"), &m_resourceManger.getTexture("buttonBetHover"), &m_resourceManger.getTexture("buttonBetClick"), "-10$", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(BcenterX, 420), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));
    Button* betsub50 = new Button(&m_resourceManger.getTexture("buttonBetIdle"), &m_resourceManger.getTexture("buttonBetHover"), &m_resourceManger.getTexture("buttonBetClick"), "-50$", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(BcenterX + 100, 420), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));

    confirmBetButton = new Button(&m_resourceManger.getTexture("buttonDefIdle"), &m_resourceManger.getTexture("buttonDefHover"), &m_resourceManger.getTexture("buttonDefClick"), "Confirm Bet", &m_resourceManger.getFont("robotoSlabBlack"), sf::Vector2f(centerX - 75, 500), m_window, &m_resourceManger.getSoundBuffer("buttonDefClick"));
    confirmBetButton->setCallbackFunction([this] {
        betConfirmed = true;
        m_gameLoopState = game;  // Change state to game after bet is confirmed
        clearActiveElements(); // Clear betting elements
        });

    betadd1->setCallbackFunction([this] { currentBet += 1; betValueText->setText("BET: $" + std::to_string(currentBet)); });
    betadd10->setCallbackFunction([this] { currentBet += 10; betValueText->setText("BET: $" + std::to_string(currentBet)); });
    betadd50->setCallbackFunction([this] { currentBet += 50; betValueText->setText("BET: $" + std::to_string(currentBet)); });
    betsub1->setCallbackFunction([this] { currentBet = std::max(0, currentBet - 1); betValueText->setText("BET: $" + std::to_string(currentBet)); });
    betsub10->setCallbackFunction([this] { currentBet = std::max(0, currentBet - 10); betValueText->setText("BET: $" + std::to_string(currentBet)); });
    betsub50->setCallbackFunction([this] { currentBet = std::max(0, currentBet - 50); betValueText->setText("BET: $" + std::to_string(currentBet)); });

    m_activeButtons.push_back(betadd1);
    m_activeButtons.push_back(betadd10);
    m_activeButtons.push_back(betadd50);
    m_activeButtons.push_back(betsub1);
    m_activeButtons.push_back(betsub10);
    m_activeButtons.push_back(betsub50);
    m_activeButtons.push_back(confirmBetButton);  // Add confirm button

    m_activeText.push_back(betValueText);
    m_activeText.push_back(moneyT);
}
