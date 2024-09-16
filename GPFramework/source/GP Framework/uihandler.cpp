#include "uihandler.h"
#include "renderer.h"
#include "sprite.h"
#include <string>

UiHandler::UiHandler()
{
    m_pNumberElements.resize(11, nullptr); // Resize the vector to hold 11 pointers
}

UiHandler::~UiHandler()
{
    for (Sprite* sprite : m_pNumberElements)
    {
        delete sprite; // Safely delete the sprite
    }
}

bool UiHandler::Initialise(Renderer& renderer)
{
    renderer.CreateStaticText("Hello", 72);
    testWord = renderer.CreateSprite("Hello");
    testWord->SetX(640);
    testWord->SetY(500);

    for (int i = 0; i < 10; i++)
    {
        std::string str = std::to_string(i);
        renderer.CreateStaticText(str.c_str(), 48);
    }
    int prevX = 100;
    for (int i = 0; i < 10; ++i)
    {
        std::string str = std::to_string(i);
        Sprite* newSprite = renderer.CreateSprite(str.c_str());
        if (newSprite) // Check if sprite creation was successful
        {
            m_pNumberElements[i] = newSprite; // Store the new sprite in the vector
            m_pNumberElements[i]->SetX(prevX);
            m_pNumberElements[i]->SetY(300);

            prevX += 50;
        }
        else
        {
            
        }
    }

    return true;
}

void UiHandler::Process(float deltaTime)
{
    for (Sprite* sprite : m_pNumberElements)
    {
        if (sprite) // Ensure the sprite is not nullptr before processing
        {
            sprite->Process(deltaTime);
        }
    }
    testWord->Process(deltaTime);
}

void UiHandler::Draw(Renderer& renderer)
{
    for (Sprite* sprite : m_pNumberElements)
    {
        if (sprite) // Ensure the sprite is not nullptr before drawing
        {
            sprite->Draw(renderer);
        }
    }
    testWord->Draw(renderer);
}
