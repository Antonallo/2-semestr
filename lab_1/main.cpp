#include <SFML/Graphics.hpp>


namespace lab_1
{
    class AnimatedText 
    {
    private:

    std::string text_;
    float duration_;

    public:

        AnimatedText(const std::string& text, const float duration)
        {
            text_ = text;
            duration_ = duration;
        }
        void draw(sf::RenderWindow& window, const float deltaTime) const
        {
            static float timeElapsed = 0.0f;
            static std::string displayedText;

            timeElapsed += deltaTime;
            const float progress = timeElapsed / duration_;
            const std::size_t numChars = static_cast<std::size_t>(progress * text_.size());
            displayedText = text_.substr(0, numChars);
            
            sf::Font font;
            font.loadFromFile("Arial.ttf");
            sf::Text text(displayedText, font, 30);
            text.setFillColor(sf::Color::White);
            text.setPosition(50, 50);

            window.draw(text);
        }
    };
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Animated Text");
    lab_1::AnimatedText animatedText("Hello, World", 2.0f);

    sf::Clock clock;
    while (window.isOpen()) {
        const float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        animatedText.draw(window, deltaTime);
        window.display();
    }

    return 0;
}