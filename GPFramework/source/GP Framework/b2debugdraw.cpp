#include "b2debugdraw.h"

#include "glew.h"

void 
DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    glColor4f(color.r, color.g, color.b, color.a); // Set the color for the polygon
    glBegin(GL_TRIANGLE_FAN); // Use GL_TRIANGLE_FAN to create a filled polygon

    for (int32 i = 0; i < vertexCount; ++i) {
        glVertex2f(vertices[i].x, vertices[i].y); // Use input vertices for drawing
    }

    glEnd(); // End the drawing
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color) {
    // Begin setting up your rendering context
    glBegin(GL_LINE_LOOP); // Use GL_LINE_LOOP for polygon outline

    // Set the color for drawing
    glColor3f(color.r, color.g, color.b);

    for (int i = 0; i < vertexCount; ++i) {
        // Transform the vertex coordinates to your rendering system
        // Ensure you are using the correct coordinate system
        glVertex2f(vertices[i].x, vertices[i].y); // Adjust based on your coordinate scaling
    }

    glEnd();
}
void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {}
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
void DebugDraw::DrawTransform(const b2Transform& xf) {}
void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color) {}