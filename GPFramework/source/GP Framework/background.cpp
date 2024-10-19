#include "background.h"

#include "renderer.h"
#include "sprite.h"

Background::Background(int speed)
    : m_sForeground1(nullptr), m_sForeground2(nullptr), m_sMiddleground1(nullptr), m_sMiddleground2(nullptr), m_sBackground1(nullptr), m_sBackground2(nullptr), m_fSpeed(speed)
{
}

Background::Background()
    : m_sForeground1(nullptr), m_sForeground2(nullptr), m_sMiddleground1(nullptr), m_sMiddleground2(nullptr), m_sBackground1(nullptr), m_sBackground2(nullptr), m_fSpeed(30)
{
}

Background::~Background()
{
    delete m_sForeground1;
    m_sForeground1 = 0;
    delete m_sForeground2;
    m_sForeground2 = 0;

    delete m_sMiddleground1;
    m_sMiddleground1 = 0;
    delete m_sMiddleground2;
    m_sMiddleground2 = 0;

    delete m_sBackground1;
    m_sBackground1 = 0;
    delete m_sBackground2;
    m_sBackground2 = 0;
}

bool Background::Initialise(Renderer& renderer)
{
    m_rRenderer = &renderer;

    m_iWidth = m_rRenderer->GetWidth();
    m_iHeight = m_rRenderer->GetHeight();

    CreateForeground();
    CreateMiddleground();
    CreateBackground();

    return true;
}

void Background::Process(float deltaTime)
{
    ProcessForeground(deltaTime);
    ProcessMiddleground(deltaTime);
    ProcessBackground(deltaTime);

}

void Background::Draw(Renderer& renderer)
{
    DrawBackground();
    DrawMiddleground();
    DrawForeground();
}

void Background::CreateForeground()
{
    m_sForeground1 = m_rRenderer->CreateSprite("sprites\\ForegroundBlur.png");
    m_sForeground2 = m_rRenderer->CreateSprite("sprites\\ForegroundBlur.png");

    m_sForeground1->SetY(m_iHeight / 2);
    m_sForeground2->SetY(m_iHeight / 2);

    m_sForeground1->SetX(0);
    m_sForeground2->SetX(m_iWidth);
}

void Background::CreateMiddleground()
{
    m_sMiddleground1 = m_rRenderer->CreateSprite("sprites\\MiddlegroundBlur.png");
    m_sMiddleground2 = m_rRenderer->CreateSprite("sprites\\MiddlegroundBlur.png");

    m_sMiddleground1->SetY(m_iHeight / 2);
    m_sMiddleground2->SetY(m_iHeight / 2);

    m_sMiddleground1->SetX(0);
    m_sMiddleground2->SetX(m_iWidth);
}

void Background::CreateBackground()
{
    m_sBackground1 = m_rRenderer->CreateSprite("sprites\\BackgroundBlur.png");
    m_sBackground2 = m_rRenderer->CreateSprite("sprites\\BackgroundBlur.png");

    m_sBackground1->SetY(m_iHeight / 2);
    m_sBackground2->SetY(m_iHeight / 2);

    m_sBackground1->SetX(0);
    m_sBackground2->SetX(m_iWidth);

}

void Background::ProcessForeground(float multiplier)
{
    m_sForeground1->SetX(m_sForeground1->GetX() - m_fSpeed * multiplier);
    m_sForeground2->SetX(m_sForeground2->GetX() - m_fSpeed * multiplier);

    if (m_sForeground1->GetX() <= (0 - m_iWidth / 2))
    {
        m_sForeground1->SetX(m_iWidth * 1.5);
    }
    if (m_sForeground2->GetX() <= (0 - m_iWidth / 2))
    {
        m_sForeground2->SetX(m_iWidth * 1.5);
    }
}

void Background::ProcessMiddleground(float multiplier)
{
    m_sMiddleground1->SetX(m_sMiddleground1->GetX() - m_fSpeed / 2 * multiplier);
    m_sMiddleground2->SetX(m_sMiddleground2->GetX() - m_fSpeed / 2 * multiplier);

    if (m_sMiddleground1->GetX() <= (0 - m_iWidth / 2))
    {
        m_sMiddleground1->SetX(m_iWidth * 1.5);
    }
    if (m_sMiddleground2->GetX() <= (0 - m_iWidth / 2))
    {
        m_sMiddleground2->SetX(m_iWidth * 1.5);
    }
}

void Background::ProcessBackground(float multiplier)
{
    m_sBackground1->SetX(m_sBackground1->GetX() - m_fSpeed / 2 / 2 * multiplier);
    m_sBackground2->SetX(m_sBackground2->GetX() - m_fSpeed / 2 / 2 * multiplier);

    if (m_sBackground1->GetX() <= (0 - m_iWidth / 2))
    {
        m_sBackground1->SetX(m_iWidth * 1.5);
    }
    if (m_sBackground2->GetX() <= (0 - m_iWidth / 2))
    {
        m_sBackground2->SetX(m_iWidth * 1.5);
    }
}

void Background::DrawForeground()
{
    m_sForeground1->Draw(*m_rRenderer);
    m_sForeground2->Draw(*m_rRenderer);
}

void Background::DrawMiddleground()
{
    m_sMiddleground1->Draw(*m_rRenderer);
    m_sMiddleground2->Draw(*m_rRenderer);
}

void Background::DrawBackground()
{
    m_sBackground1->Draw(*m_rRenderer);
    m_sBackground2->Draw(*m_rRenderer);
}
