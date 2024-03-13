#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>


bool PointVsRect(const sf::Vector2f& sourcepoint, const sf::FloatRect& targetrect) {
	return (sourcepoint.x >= targetrect.left && sourcepoint.y >= targetrect.top && sourcepoint.x < targetrect.left + targetrect.width && sourcepoint.y < targetrect.top + targetrect.height);
}

bool RectVsRect(const sf::FloatRect& sourcerect, const sf::FloatRect& targetrect) {
	return (
		sourcerect.left < targetrect.left + targetrect.width && // Lado izquierdo del primero menor al lado derecho del segundo
		sourcerect.left + sourcerect.width >  targetrect.left && // Lado derecho del primero  mayor al lado derecho del segundo
		sourcerect.top < targetrect.top + targetrect.height && // Lado superior del primero menor al lado inferior del segundo
		sourcerect.top + sourcerect.height > targetrect.top // Lado inferior del primero mayor al lado superior del segundo
		);
}



bool RayVsRect(const sf::Vector2f& ray_origin, const sf::Vector2f& ray_direction, const sf::FloatRect& rect, sf::Vector2f& contact_point, sf::Vector2f& contact_normal, float& t_hit_near) {
	
	sf::Vector2f t_near = { ((rect.left - ray_origin.x) / ray_direction.x), ((rect.top - ray_origin.y) / ray_direction.y) };
	sf::Vector2f t_far = { ((rect.left + rect.width - ray_origin.x) / ray_direction.x), ((rect.top + rect.height - ray_origin.y) / ray_direction.y) };
	if (t_near.x > t_far.x) {
		std::swap(t_near.x, t_far.x);
	}
	if (t_near.y > t_far.y) {
		std::swap(t_near.y, t_far.y);
	}
	if (t_near.x > t_far.y || t_near.y > t_far.x) { return false; }
	t_hit_near = std::max(t_near.x, t_near.y);
	float t_hit_far = std::min(t_far.x, t_far.y);
	if (t_hit_far < 0) {
		return false;
	}

	contact_point = ray_origin + t_hit_near * ray_direction;
	if (t_near.x > t_near.y) {
		if (ray_direction.x < 0) {
			contact_normal = { 1,0 };
		}
		else {
			contact_normal = { -1, 0 };
		}
	}
	else if (t_near.x < t_near.y) {
		if (ray_direction.y < 0) {
			contact_normal = { 0, 1 };
		}
		else {
			contact_normal = { 0 , -1 };
		}
	}
	return true;
}

bool DynamicRectVsRect(const sf::FloatRect& sourcerect, const sf::Vector2f& rect_velocity, const sf::FloatRect& targetrect, sf::Vector2f& contact_point, sf::Vector2f contact_normal, float& contact_time, float elapsed_time) {
	if (rect_velocity == sf::Vector2f{ 0.0f, 0.0f }) { return false; }
	sf::FloatRect expanded_target;
	expanded_target.left = targetrect.left - sourcerect.width / 2;
	expanded_target.width = targetrect.width + sourcerect.width;
	expanded_target.top = targetrect.top - sourcerect.height / 2;
	expanded_target.height = targetrect.height + sourcerect.height;
	sf::Vector2f source_center = { sourcerect.left + sourcerect.width / 2, sourcerect.top + sourcerect.height / 2 };
	if (expanded_target.intersects(sf::FloatRect( source_center, sf::Vector2f(1,1) ))) {
		return true;
	}
	//if (RayVsRect(source_center, rect_velocity * elapsed_time, expanded_target, contact_point, contact_normal, contact_time)) {
	//	if (contact_time < 1) { return true; }
	//	else { return false; }
	//}
	return false;
}

sf::Vector2f NormalizeV2f(const sf::Vector2f& vector) {
	float lenght = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
	if (lenght != 0) {
		return sf::Vector2f({ vector.x / lenght, vector.y / lenght });
	}
	else {
		return vector;
	}
}
int main() {
	srand((unsigned)time(0)); // inicializar números aleatorios
	sf::RenderWindow window(sf::VideoMode(800, 600), "jueguito");
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Vertex lines[] = {
		sf::Vertex({50, 50}),
		sf::Vertex({100,100})
	};
	sf::Vertex lines2[] = {
		sf::Vertex({50, 50}),
		sf::Vertex({100,100})
	};
	sf::Vertex normal[] = {
		sf::Vertex({50,100}),
		sf::Vertex({100,100})
	};
	sf::RectangleShape line({ 150,5 });
	sf::RectangleShape rectangle;
	sf::RectangleShape enemy1;
	sf::RectangleShape player;
	sf::Vector2f ray_direction;
	rectangle.setSize({ 100,100 });
	rectangle.setPosition({ 250,250 });
	rectangle.setOutlineColor(sf::Color::White);
	line.setOutlineColor(sf::Color::White);
	//enemy1.setOutlineColor(sf::Color::Magenta);
	enemy1.setSize({ 100,100 });
	enemy1.setPosition({ 400,400 });
	enemy1.setOrigin(50, 50);
	//enemy1.setOutlineColor(sf::Color::White);
	player.setSize({ 50,50 });
	player.setPosition({ 500,300 });
	player.setOutlineColor(sf::Color::White);
	sf::Vector2f velocity;
	sf::Vector2f speed = { 5,5 };
	sf::Vector2f contactpoint, contactnormal;
	sf::CircleShape circle;
	circle.setRadius(5);
	circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
	sf::CircleShape circle2;
	circle2.setRadius(5);
	circle2.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
	float t = 0;
	bool upsize = true;
	sf::Vector2f RayDirection1;
	sf::Vector2f RayDirection2;
	sf::Vector2f MousePos;
	sf::Clock d_clock;
	sf::Time d_time;
	sf::Vector2f finalspeed;
	while (window.isOpen()) {
		static bool left = false;
		static bool right = false;
		static bool up = false;
		static bool down = false;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		lines[0].position = player.getPosition();
		lines2[0].position = player.getPosition() + sf::Vector2f{ 0, 50 };
		MousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		RayDirection1 = MousePos - lines[0].position;
		RayDirection2 = MousePos + sf::Vector2f{ 0, 50 } - lines2[0].position;
		lines[1].position = MousePos;
		lines2[1].position = MousePos + sf::Vector2f{ 0, 50 };
		if (RayVsRect(lines[0].position, RayDirection1, enemy1.getGlobalBounds(), contactpoint, contactnormal, t) && t <= 1.0f) {
			enemy1.setFillColor(sf::Color::Red);
			circle.setPosition(contactpoint);
			circle.setFillColor(sf::Color::Yellow);
		}
		else {
			circle.setFillColor(sf::Color::Transparent);
		}
		if (RayVsRect(lines2[0].position, RayDirection2, enemy1.getGlobalBounds(), contactpoint, contactnormal, t) && t <= 1.0f) {
			enemy1.setFillColor(sf::Color::Red);
			circle2.setPosition(contactpoint);
			circle2.setFillColor(sf::Color::Yellow);
			normal[0].position = contactpoint;
			normal[1].position = contactpoint + (contactnormal * 50.0f);
			normal[0].color = sf::Color::White;
			normal[1].color = sf::Color::White;
		}
		else {
			//enemy1.setOutlineColor(sf::Color::Cyan);
			//enemy1.setOutlineThickness(3);
			enemy1.setFillColor(sf::Color::White);
			circle2.setFillColor(sf::Color::Transparent);
			normal[0].color = sf::Color::Transparent;
			normal[1].color = sf::Color::Transparent;
		}



		//rectangle.move(velocity);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !right) {
			left = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				velocity.x += speed.x * d_time.asSeconds();
			}
			else {
				velocity.x += -speed.x * d_time.asSeconds();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !left) {
			right = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				velocity.x += -speed.x * d_time.asSeconds();
			}
			else {
				velocity.x += speed.x * d_time.asSeconds();
			}
		}
		else {
			//velocity.x = 0;
			right = left = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !up) {
			down = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				velocity.y += -speed.y * d_time.asSeconds();
			}
			else {
				velocity.y += speed.y * d_time.asSeconds();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !down) {
			up = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				velocity.y += speed.y * d_time.asSeconds();
			}
			else {
				velocity.y += -speed.y * d_time.asSeconds();
			}
		}
		else {
			//velocity.y = 0;
			up = down = false;
		}
		
		if (DynamicRectVsRect(player.getGlobalBounds(), velocity, enemy1.getGlobalBounds(), contactpoint, contactnormal, t, d_time.asSeconds())) {
			//if (contactnormal.x != 0) {
			//	velocity.x = std::abs(velocity.x) * contactnormal.x;
			//}
			//if (contactnormal.y != 0) {
			//	velocity.y = std::abs(velocity.y) * contactnormal.y;
			//}
			//if (velocity.x != 0) {
			//	player.move(-velocity.x, 0);
			//	//velocity.x = -velocity.x;
			//}
			//if (velocity.y != 0) {
			//	player.move(0, -velocity.y);
			//}
			velocity = sf::Vector2f{ contactnormal.x * std::abs(velocity.x) , contactnormal.y * std::abs(velocity.y)};
		}
		//0, 0;
		if (velocity.x > speed.x) {
			velocity.x = speed.x;
		}
		if (velocity.x < -speed.x) {
			velocity.x = -speed.x;
		}
		if (velocity.y > speed.y) {
			velocity.y = speed.y;
		}
		if (velocity.y < -speed.y) {
			velocity.y = -speed.y;
		}
		

		player.move(velocity);



		//lines[1].position = { rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2 };
		//lines2[0].position = player.getPosition();
		//lines2[1].position = { rectangle.getPosition().x + rectangle.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y / 2 };

	//Clear

		window.clear();
		//Draw
		//window.draw(rectangle);
		window.draw(lines, 2, sf::Lines);
		window.draw(lines2, 2, sf::Lines);
		window.draw(normal, 2, sf::Lines);
		window.draw(enemy1);
		window.draw(player);
		window.draw(circle);
		window.draw(circle2);
		//window.draw(tile, 4, sf::Quads);
		//Display
		window.display();
		//clock.restart();
		d_time = d_clock.restart();
	}
	return 0;
}