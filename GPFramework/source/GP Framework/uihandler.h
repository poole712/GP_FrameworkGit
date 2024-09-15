#ifndef _UIHANDLER_H
#define _UIHANDLER_H

#include <vector>
#include <string>

class Renderer;
class Sprite;

class UiHandler
{
public:
    UiHandler();
    ~UiHandler();

    bool Initialise(Renderer& renderer);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);

private:
    UiHandler(const UiHandler& uiHandler);
    UiHandler& operator=(const UiHandler& uiHandler);

protected:

    std::vector<Sprite*> m_pNumberElements; // Use vector to manage sprites
    Sprite* testWord;
};

#endif // !_UIHANDLER_H
