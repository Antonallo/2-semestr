#include <SFML/Graphics.hpp>
#include <cmath>
#include <SFML/Window.hpp>
#include <iostream>

class KinematicSolver {
public:
    KinematicSolver(double link1, double link2) : L1(link1), L2(link2) {}

    // Функция для решения задачи обратной кинематики
    // Принимает координаты точки M(x,y) и возвращает углы alpha и beta
    std::pair<double, double> Solve(double x, double y) {
        double r = std::sqrt(x * x + y * y); // расстояние от начала координат до точки M
        double phi = std::atan2(y, x); // угол между осью X и линией от начала координат до точки M

        // Рассчитываем угол alpha с помощью закона косинусов
        double cos_alpha = (r * r + L1 * L1 - L2 * L2) / (2 * r * L1);
        double sin_alpha = std::sqrt(1 - cos_alpha * cos_alpha);
        double alpha = std::atan2(sin_alpha, cos_alpha) + phi;

        // Рассчитываем угол beta с помощью закона косинусов
        double cos_beta = (L1 * L1 + L2 * L2 - r * r) / (2 * L1 * L2);
        double sin_beta = std::sqrt(1 - cos_beta * cos_beta);
        double beta = std::acos(cos_beta) - std::atan2(sin_beta, cos_beta);

        // Преобразуем углы в градусы и возвращаем результат
        return std::make_pair(alpha * 180 / 3.14, beta * 180 / 3.14);
    }

private:
    double L1; // Длина первого звена
    double L2; // Длина второго звена
};

int main() {
    double L1 = 200; // Длина первого звена
    double L2 = 200; // Длина второго звена

    KinematicSolver solver(L1, L2);

    sf::RenderWindow window(sf::VideoMode(800, 600), "KinematicSolver");

    sf::RectangleShape link1(sf::Vector2f(L1, 5)); // Создаем первое звено
    link1.setOrigin(0, link1.getSize().y / 2);
    link1.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    link1.setFillColor(sf::Color::Black);

    sf::RectangleShape link2(sf::Vector2f(L2, 5)); // Создаем второе звено
    link2.setOrigin(0, link2.getSize().y / 2);
    link2.setPosition(link1.getTransform().transformPoint(link1.getSize()));
    link2.setFillColor(sf::Color::Black);

    sf::CircleShape endpoint(5); // Создаем точку M
    endpoint.setOrigin(endpoint.getRadius(), endpoint.getRadius());
    endpoint.setPosition(link2.getTransform().transformPoint(link2.getSize()));
    endpoint.setFillColor(sf::Color::Red);

    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)); // Создаем вид
    view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    window.setView(view);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Получаем мировые координаты мыши
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        sf::Vector2f world_mouse_position = window.mapPixelToCoords(mouse_position);

        // Проверяем, находится ли мировая позиция мыши внутри окна
        if (sf::FloatRect(0, 0, window.getSize().x, window.getSize().y).contains(world_mouse_position)) {

            auto angles = solver.Solve(world_mouse_position.x - link1.getPosition().x, world_mouse_position.y - link1.getPosition().y);

            link1.setRotation(angles.first);
            link2.setRotation(angles.second);

            link2.setPosition(link1.getTransform().transformPoint(link1.getSize()));
            endpoint.setPosition(link2.getTransform().transformPoint(link2.getSize()));

            window.clear(sf::Color::White);

            window.draw(link1);
            window.draw(link2);
            window.draw(endpoint);

            window.display();
        }
    }

    return 0;
}