#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

bool isCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
    return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Galactic Rescue");

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("background.png");
    sf::Sprite background(backgroundTexture);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("player.png");
    sf::Sprite player(playerTexture);
    player.setPosition(400, 300); 

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("enemy.png");
    std::vector<sf::Sprite> enemies;
    for (int i = 0; i < 5; ++i) {
        sf::Sprite enemy(enemyTexture);
        enemy.setPosition(100 * i + 50, 100);
        enemies.push_back(enemy);
    }

    sf::SoundBuffer buffer;
    buffer.loadFromFile("explosion.wav");
    sf::Sound explosionSound;
    explosionSound.setBuffer(buffer);

    int score = 0;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-3, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(3, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0, -3);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0, 3);

        for (auto& enemy : enemies) {
            if (isCollision(player, enemy)) {
                explosionSound.play();
                score -= 100;
                enemy.setPosition(rand() % 700 + 50, rand() % 400 + 50);
            }
        }

        score += 10;

        window.clear();
        window.draw(background);
        window.draw(player);
        for (auto& enemy : enemies) {
            window.draw(enemy);
        }

        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);

        window.display();
    }

    return 0;
}