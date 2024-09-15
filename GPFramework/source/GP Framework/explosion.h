#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include <vector>
#include <string>

#include "animatedentity.h"

class Renderer;
class Sprite;

class Explosion : AnimatedEntity
{
public:
    Explosion();
    virtual ~Explosion();

    virtual bool Initialise(Renderer& renderer);
    virtual void Process(float deltaTime);
    virtual void Draw(Renderer& renderer);

    void SetAlive(bool alive);

    void SetThePosition(float x, float y);

private:
    Explosion(const Explosion& uiHandler);
    Explosion& operator=(const Explosion& uiHandler);

protected:
    bool m_bIsExploding;
};

#endif // !_EXPLOSION_H
