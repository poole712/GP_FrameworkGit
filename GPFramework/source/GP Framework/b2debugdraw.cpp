#include "b2debugdraw.h"

#include "glew.h"
#include "logmanager.h"

#include <iostream>
#include <stdlib.h>
#include <string>

void 
DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        LogManager::GetInstance().Log(("Open GL Error: " + std::to_string(error)).c_str());

    }
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color) {
    glColor3f(0.0f, 1.0f, 0.0f); // Set color to bright green
    glBegin(GL_LINE_LOOP);
    glVertex2f(-10.0f, -10.0f);
    glVertex2f(10.0f, -10.0f);
    glVertex2f(0.0f, 10.0f);
    glEnd();
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {}
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
void DebugDraw::DrawTransform(const b2Transform& xf) {}
void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color) {}