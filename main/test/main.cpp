#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdlib>

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif

std::string resourcesDir() {
#ifdef SFML_SYSTEM_IOS
  return "";
#else
  return "/home/brandon/cpp-fun/cpp-fun/test/resources/";
#endif
}

int main() {
  const double pi = 3.14159265358979323846;
  const float gameWidth = 800;
  const float gameHeight = 600;
  sf::Vector2f playerSize(25, 100);
  float ballRadius = 10.f;

  sf::RenderWindow window(
      sf::VideoMode(static_cast<unsigned int>(gameWidth),
                    static_cast<unsigned int>(gameHeight), 32),
      "SFML Tennis", sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  sf::SoundBuffer ballSoundBuffer;
  if (!ballSoundBuffer.loadFromFile(resourcesDir() + "ball.wav"))
    return EXIT_FAILURE;
  sf::Sound ballSound(ballSoundBuffer);

  sf::Texture sfmlLogoTexture;
  if (!sfmlLogoTexture.loadFromFile(resourcesDir() + "sfml_logo.png"))
    return EXIT_FAILURE;
  sf::Sprite sfmlLogo;
  sfmlLogo.setTexture(sfmlLogoTexture);

  sf::RectangleShape playerOne;
  playerOne.setSize(playerSize - sf::Vector2f(3, 3));
  playerOne.setOutlineThickness(3);
  playerOne.setOutlineColor(sf::Color::Black);
  playerOne.setFillColor(sf::Color::Blue);
  playerOne.setOrigin(playerSize / 2.f);

  sf::CircleShape ball;
  ball.setRadius(ballRadius - 3);
  ball.setOutlineThickness(2);
  ball.setOutlineColor(sf::Color::Black);
  ball.setFillColor(sf::Color::White);
  ball.setOrigin(ballRadius / 2, ballRadius / 2);

  sf::Font font;
  if (!font.loadFromFile(resourcesDir() + "tuffy.ttf"))
    return EXIT_FAILURE;

  sf::Text pauseMessage;
  pauseMessage.setFont(font);
  pauseMessage.setCharacterSize(40);
  pauseMessage.setPosition(170.f, 200.f);
  pauseMessage.setFillColor(sf::Color::White);

#ifdef SFML_SYSTEM_IOS
  pauseMessage.setString(
      "Welcome to SFML Tennis!\nTouch the screen to start the game.");
#else
  pauseMessage.setString(
      "Welcome to SFML Tennis!\n\nPress space to start the game.");
#endif

  sf::Clock AITimer;
  const sf::Time AITime = sf::seconds(0.1f);
  const float playerSpeed = 300.f;
  const float ballSpeed = 400.f;
  float ballAngle = 0.f; // to be changed later

  sf::Clock clock;
  bool isPlaying = false;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if ((event.type == sf::Event::Closed) ||
          ((event.type == sf::Event::KeyPressed) &&
           (event.key.code == sf::Keyboard::Escape))) {
        window.close();
        break;
      }

      if (((event.type == sf::Event::KeyPressed) &&
           (event.key.code == sf::Keyboard::Space)) ||
          (event.type == sf::Event::TouchBegan)) {
        if (!isPlaying) {
          isPlaying = true;
          clock.restart();

          playerOne.setPosition(gameWidth / 2.f,
                                gameHeight - playerSize.y / 2.f - 10.f);
          ball.setPosition(gameWidth / 2.f, gameHeight - playerSize.y / 2);
        }
      }

      if (event.type == sf::Event::Resized) {
        sf::View view;
        view.setSize(gameWidth, gameHeight);
        view.setCenter(gameWidth / 2.f, gameHeight / 2.f);
        window.setView(view);
      }
    }

    if (isPlaying) {
      float deltaTime = clock.restart().asSeconds();
      float playerSpeedUD = playerSpeed / 2.f;
      float ballGravity = ballSpeed / 2.f;
      float playerJumpHeight = 400.f;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
          (playerOne.getPosition().x - playerSize.x / 2 > 10.f)) {
        playerOne.move(-playerSpeed * deltaTime, 0.f);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
          (playerOne.getPosition().x - playerSize.x / 2 <
           gameWidth - playerSize.x - 5)) {
        playerOne.move(playerSpeed * deltaTime, 0.f);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        // Move player upwards gradually
        float distanceToMove = -playerSpeedUD * deltaTime;

        // Check if moving won't pass the target position
        if (playerOne.getPosition().y - playerSize.y / 2 > playerJumpHeight) {
          playerOne.move(0.f, distanceToMove);
        } else {
          // Update the target y-position when reaching it
          playerJumpHeight = playerOne.getPosition().y - playerSize.y / 2;
        }
      } else {
        // Move player downwards gradually
        if (playerOne.getPosition().y < gameHeight - playerSize.y / 2.f - 10) {
          playerOne.move(0.f, playerSpeedUD * deltaTime);
        }
      }

      float factor = ballSpeed * deltaTime;
      ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);

      if (ball.getPosition().y + ballRadius > gameHeight) {
        ballSound.play();
        ballAngle = -ballAngle;
        ball.setPosition(ball.getPosition().x, gameHeight - ballRadius - 0.1f);
      }

      if (ball.getPosition().y - ballRadius < 0.f) {
        ballSound.play();
        ballAngle = -ballAngle;
        ball.setPosition(ball.getPosition().x, ballRadius - 0.1f);
      }

      if (ball.getPosition().x + ballRadius > gameWidth) {
        ballSound.play();
        ballAngle = ballAngle + 180;
        ball.setPosition(gameWidth - ballRadius - 0.1f, ball.getPosition().y);
      }

      if (ball.getPosition().x - ballRadius < 0.f) {
        ballSound.play();
        ballAngle = ballAngle - 180;
        ball.setPosition(ballRadius - 0.1f, ball.getPosition().y);
      }

      if (ball.getPosition().x - ballRadius <
              playerOne.getPosition().x + playerSize.x / 2 &&
          ball.getPosition().x - ballRadius > playerOne.getPosition().x &&
          ball.getPosition().y + ballRadius >=
              playerOne.getPosition().y - playerSize.y / 2 &&
          ball.getPosition().y - ballRadius <=
              playerOne.getPosition().y + playerSize.y / 2) {
        if (ball.getPosition().y > playerOne.getPosition().y)
          ballAngle =
              pi - ballAngle + static_cast<float>(std::rand() % 20) * pi / 180;
        else
          ballAngle =
              pi - ballAngle - static_cast<float>(std::rand() % 20) * pi / 180;

        ballSound.play();
        ball.setPosition(playerOne.getPosition().x + ballRadius +
                             playerSize.x / 2 + 0.1f,
                         ball.getPosition().y);
      }

      if (ball.getPosition().x + ballRadius >
              playerOne.getPosition().x - playerSize.x / 2 &&
          ball.getPosition().x + ballRadius < playerOne.getPosition().x &&
          ball.getPosition().y + ballRadius >=
              playerOne.getPosition().y - playerSize.y / 2 &&
          ball.getPosition().y - ballRadius <=
              playerOne.getPosition().y + playerSize.y / 2) {
        if (ball.getPosition().y > playerOne.getPosition().y)
          ballAngle =
              pi - ballAngle + static_cast<float>(std::rand() % 20) * pi / 180;
        else
          ballAngle =
              pi - ballAngle - static_cast<float>(std::rand() % 20) * pi / 180;

        ballSound.play();
        ball.setPosition(playerOne.getPosition().x - ballRadius -
                             playerSize.x / 2 - 0.1f,
                         ball.getPosition().y);
      }
    }

    window.clear(sf::Color(50, 50, 50));

    if (isPlaying) {
      window.draw(playerOne);
      window.draw(ball);
    } else {
      window.draw(pauseMessage);
      window.draw(sfmlLogo);
    }

    window.display();
  }

  return EXIT_SUCCESS;
}
