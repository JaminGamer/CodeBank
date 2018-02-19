#ifndef __Box2DDebugDraw_H__
#define __Box2DDebugDraw_H__

class ShaderProgram;
struct b2Vec2;
struct b2Transform;
class MyMatrix;

class Box2DDebugDraw : public b2Draw
{
protected:
    ShaderProgram* m_pShaderProgram;
	MyMatrix* m_pMatView;
	MyMatrix* m_pMatProj;

    bool m_DisplayOnXZ;

public:
    Box2DDebugDraw(ShaderProgram* pShaderProgram, MyMatrix* pMatView, MyMatrix* pMatProj);
    ~Box2DDebugDraw();

    virtual void Draw(const b2Vec2* vertices, int32 vertexCount, const b2Color& color, unsigned char alpha, int primitivetype);
    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color); // CCW order.
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color); // CCW order.
    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    virtual void DrawTransform(const b2Transform& xf);

    void SetViewProjMatrices(MyMatrix* pMatView, MyMatrix* pMatProj);
    void SetDisplayOnXZ(bool value) { m_DisplayOnXZ = value; }
};

#endif //__Box2DDebugDraw_H__
