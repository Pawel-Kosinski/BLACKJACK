#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::unordered_map<std::string, sf::Font> fonts;

public:
    // Load a texture and store it with a key
    void loadTexture(const std::string& key, const std::string& filePath) {
        sf::Texture texture;
        if (texture.loadFromFile(filePath)) {
            textures[key] = texture;
        }
    }

    // Get a reference to a stored texture
    sf::Texture& getTexture(const std::string& key) {
        return textures.at(key);
    }

    // Load a sound buffer and store it with a key
    void loadSoundBuffer(const std::string& key, const std::string& filePath) {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(filePath)) {
            soundBuffers[key] = buffer;
        }
    }

    // Get a reference to a stored sound buffer
    sf::SoundBuffer& getSoundBuffer(const std::string& key) {
        return soundBuffers.at(key);
    }

    // Load a font and store it with a key
    void loadFont(const std::string& key, const std::string& filePath) {
        sf::Font buffer;
        if (buffer.loadFromFile(filePath)) {
            fonts[key] = buffer;
        }
    }

    // Get a reference to a stored font
    sf::Font& getFont(const std::string& key) {
        return fonts.at(key);
    }
};
