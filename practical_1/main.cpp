#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

const Keyboard::Key controls[6] =
{
	//Player 1, up and down
	Keyboard::W,
	Keyboard::S,
	//Player 2, up and down
	Keyboard::Up,
	Keyboard::Down,
	//ai
	Keyboard::Num1,
	Keyboard::Num2
};

const Vector2f paddleSize(25.0f, 100.0f);
const float ballRadius = 10.0f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.0f;

Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];
int score1 = 0;
int score2 = 0;
bool ai = true;
bool otherai = true;
int scored = 0;

Font font;
Text text;

void Reset()
{
	ball.setPosition(gameWidth / 2, gameHeight / 2);
	server = !server;
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
	if (scored == 1)
	{
		score1++;
	}
	else if (scored == 2)
	{
		score2++;
	}
	text.setString(to_string(score1) + "\t-\t" + to_string(score2));
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}

void Load()
{
	for (RectangleShape &p : paddles)
	{
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.0f);
	}

	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - paddleSize.x, gameHeight / 2);
	

	font.loadFromFile("res/font/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setColor(Color::Green);
	Reset();
}

void AI(int i, float dt)
{
	float direction = ball.getPosition().y - paddles[i].getPosition().y;
	direction = direction == 0 ? 0 : direction / abs(direction);
	float topScreen = paddles[i].getPosition().y - paddleSize.y / 2;
	float bottScreen = paddles[i].getPosition().y + paddleSize.y / 2;

	if (topScreen >= 0 && bottScreen <= gameHeight)
	{
		paddles[i].move(0, direction * paddleSpeed * dt);
	}
	else if (topScreen <= 0 && direction == 1)
	{
		paddles[i].move(0, direction * paddleSpeed * dt);
	}
	else if (bottScreen >= gameHeight && direction == -1)
	{
		paddles[i].move(0, direction * paddleSpeed * dt);
	}
}

void Update(RenderWindow &window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();

	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	if (Keyboard::isKeyPressed(controls[4]))
	{
		ai = !ai;
	}
	if (Keyboard::isKeyPressed(controls[5]))
	{
		otherai = !otherai;
	}

	//Player 1
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0]) && paddles[0].getPosition().y - paddleSize.y/2 > 0 && !ai)
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]) && paddles[0].getPosition().y + paddleSize.y / 2 < gameHeight && !ai)
	{
		direction++;
	}
	paddles[0].move(0, direction * paddleSpeed * dt);

	//Player 2
	direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[2]) && paddles[1].getPosition().y - paddleSize.y / 2 > 0 && !otherai)
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[3]) && paddles[1].getPosition().y + paddleSize.y / 2 < gameHeight && !otherai)
	{
		direction++;
	}
	paddles[1].move(0, direction * paddleSpeed * dt);
	ball.move(ballVelocity * dt);

	if (ai)
	{
		AI(0, dt);
	}
	if (otherai)
	{
		AI(1, dt);
	}

	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

	if (by > gameHeight)
	{
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0)
	{
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth)
	{
		scored = 1;
		Reset();
	}
	else if (bx < 0)
	{
		scored = 2;
		Reset();
	}
	else if (
		bx < paddleSize.x &&
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
	{
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(10, 0);
	}
	else if (
		bx > gameWidth - paddleSize.x &&
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5))
	{
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(-10, 0);
	}
}

void Render(RenderWindow &window)
{
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}