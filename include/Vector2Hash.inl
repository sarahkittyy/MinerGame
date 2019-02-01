#include <SFML/Graphics.hpp>

// sf::Vector2f hash.
struct Vector2Hash {
    template <class T>
    std::size_t operator () (const sf::Vector2<T> &p) const {
        auto h1 = std::hash<T>{}(p.x);
        auto h2 = std::hash<T>{}(p.y);

        // A little overly simple, but it works.
        return h1 ^ h2;  
    }
};