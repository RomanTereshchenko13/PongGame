#pragma once

class State
{
public:
    //Constructors
    State(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, bool mp);
    virtual ~State() = default;
    
    //Functions
    sf::Text SetupText(sf::Text& text, int fontSize, sf::Color color, sf::Vector2f position);
    float RandomFloat(float min, float max);
    void UpdateMousePos();

    //Ending State functions
    void EndState();
    bool GetQuit() const;

    //Pure virtual functions
    virtual void Update(const float& deltaTime) = 0;
    virtual void Render(sf::RenderTarget* target = nullptr) = 0;

protected:
    sf::RenderWindow* m_window;
    std::stack<std::unique_ptr<State>>* m_states;
    sf::Vector2i m_mousePosScreen;
    sf::Vector2i m_mousePosWindow;
    sf::Vector2f m_mousePosView;
    sf::Font m_font;

    bool b_multiplayer;
    bool b_quit;
};

