#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <optional>

int main() {
    // SFML 3.0 syntax: VideoMode ab Vector2u use karta hai
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My Custom CLI Window");
    
    sf::Font font;
    // SFML 3.0 mein loadFromFile ab openFromFile ho gaya hai
    if (!font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf")) {
        std::cerr << "Font nahi mila!" << std::endl;
        return -1;
    }

    // Text constructor ab font mangta hai
    sf::Text text(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Green);
    
    std::string currentInput = "Hasrat@MyDevBox:~$ ";
    std::string history = "";

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        // SFML 3.0 pollEvent loop
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Text Input Handling
            if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
                uint32_t unicode = textEvent->unicode;
                if (unicode == 8) { // Backspace
                    if (currentInput.length() > 19)
                        currentInput.pop_back();
                } else if (unicode == 13 || unicode == 10) { // Enter
                    history += currentInput + "\n[Command executed...]\n";
                    currentInput = "Hasrat@MyDevBox:~$ ";
                } else if (unicode < 128) { // Regular characters
                    currentInput += static_cast<char>(unicode);
                }
            }
        }

        window.clear(sf::Color::Black);
        text.setString(history + currentInput);
        window.draw(text);
        window.display();
    }

    return 0;
}