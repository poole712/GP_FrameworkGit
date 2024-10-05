#include "animatedentity.h"

#include "renderer.h"
#include "animatedsprite.h"
#include "inlinehelper.h"
#include "imgui/imgui.h"
#include "logmanager.h"
#include "entity.h"
#include "box2d/box2d.h"

#include <cassert>
#include <cstdlib>

AnimatedEntity::AnimatedEntity()
	: m_pASprite(nullptr), m_bAlive(true)
{

}

AnimatedEntity::~AnimatedEntity()
{
	delete m_pASprite;
	m_pASprite = 0;

	delete m_iInputSystem;
	m_iInputSystem = 0;
}

