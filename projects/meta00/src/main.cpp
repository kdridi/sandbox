#include <SFML/Graphics.hpp>
#include <fmt/core.h>

#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

class Context {
public:
    template <typename T>
    void put(const std::string &key, std::shared_ptr<T> object)
    {
        fmt::print("put: {}\n", key);
        std::type_index type = std::type_index(typeid(T));
        data_.emplace(key, std::make_pair(type, std::static_pointer_cast<void>(object)));
    }

    template <typename T>
    std::shared_ptr<T> get(const std::string &key)
    {
        fmt::print("get: {}\n", key);
        auto it = data_.find(key);
        if (it != data_.end() && it->second.first == std::type_index(typeid(T))) {
            return std::static_pointer_cast<T>(it->second.second);
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::pair<std::type_index, std::shared_ptr<void>>> data_;
};

class Program {
public:
    void push(std::function<void(Context &)> task)
    {
        m_tasks.push(task);
    }

    template <class _T>
    void pushWith(const std::string &_name, const std::function<void(_T &)> &_func)
    {
        auto name{std::make_shared<std::string>(_name)};
        auto func{std::make_shared<std::function<void(_T &)>>(_func)};
        push([=](Context &_ctx) {
            auto obj = _ctx.get<_T>(*name);
            if (obj)
                (*func)(*obj);
        });
    }

    template <class _Ty, class... _Types>
    void pushSet(const std::string &_key, _Types &&..._args)
    {
        auto key{std::make_shared<std::string>(_key)};
        auto object{std::make_shared<_Ty>(std::forward<_Types>(_args)...)};
        push([=](Context &_ctx) { _ctx.put(*key, object); });
    }

    void run()
    {
        while (!m_tasks.empty()) {
            m_tasks.front()(m_ctx);
            m_tasks.pop();
        }
    }

public:
    Context m_ctx;
    std::queue<std::function<void(Context &)>> m_tasks;
};

int main()
{
    Program program;
    program.pushSet<sf::RenderWindow>("window", sf::VideoMode(640, 480), "SFML works!");
    program.pushSet<sf::CircleShape>("shape", 100.f);
    program.pushWith<sf::CircleShape>("shape", [](sf::CircleShape &_shape) { _shape.setFillColor(sf::Color::Green); });

    program.push([](Context &_ctx) {
        _ctx.put("mainLoop", std::make_shared<std::function<void()>>([&_ctx]() {
                     _ctx.put("event", std::make_shared<sf::Event>());

                     while (_ctx.get<sf::RenderWindow>("window")->pollEvent(*_ctx.get<sf::Event>("event"))) {
                         if (_ctx.get<sf::Event>("event")->type == sf::Event::Closed)
                             _ctx.get<sf::RenderWindow>("window")->close();

                         if (_ctx.get<sf::Event>("event")->type == sf::Event::KeyPressed) {
                             if (_ctx.get<sf::Event>("event")->key.code == sf::Keyboard::Escape)
                                 _ctx.get<sf::RenderWindow>("window")->close();
                         }
                     }

                     _ctx.get<sf::RenderWindow>("window")->clear();
                     _ctx.get<sf::RenderWindow>("window")->draw(*_ctx.get<sf::CircleShape>("shape"));
                     _ctx.get<sf::RenderWindow>("window")->display();
                 }));
    });

    program.push([](Context &_ctx) {
        while (true) {
            if (!_ctx.get<sf::RenderWindow>("window")->isOpen())
                break;
            _ctx.get<std::function<void()>>("mainLoop")->operator()();
        }
    });

    program.run();

    return 0;
}
