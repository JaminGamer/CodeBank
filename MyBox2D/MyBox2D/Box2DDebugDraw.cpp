#include "stdafx.h"

Box2DDebugDraw::Box2DDebugDraw(ShaderProgram* pShaderProgram, MyMatrix* pMatView, MyMatrix* pMatProj)
{
    m_pShaderProgram = pShaderProgram;
    m_pMatView = pMatView;
    m_pMatProj = pMatProj;

    m_DisplayOnXZ = true;
}

Box2DDebugDraw::~Box2DDebugDraw()
{
}

void Box2DDebugDraw::Draw(const b2Vec2* vertices, int32 vertexCount, const b2Color& color, unsigned char alpha, int primitivetype)
{
	GLuint programhandle = m_pShaderProgram->GetProgram();
	glUseProgram(programhandle);
    if( m_pMatView == 0 || m_pMatProj == 0 )
        return;

    // bind our vertex and index buffers.
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    // setup the position attribute.
    GLint aPos = glGetAttribLocation( m_pShaderProgram->GetProgram(), "Position" );
    assert( aPos != -1 );
    glVertexAttribPointer( aPos, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (void*)vertices );
    glEnableVertexAttribArray( aPos );

	// uniforms
	// world
	MyMatrix worldmat;
	worldmat.SetIdentity();
	if (m_DisplayOnXZ)
	{
		worldmat.Rotate(-90, 1, 0, 0);
	}

	m_pShaderProgram->SetUniformMat4("WorldMatrix", &worldmat);
	m_pShaderProgram->SetUniformMat4("ViewMatrix", m_pMatView);
	m_pShaderProgram->SetUniformMat4("ProjMatrix", m_pMatProj);

	Vector4 color4(color.r, color.g, color.b, alpha / 255.0f);
	m_pShaderProgram->SetUniformFloat4("ObjectColor", color4.x, color4.y, color4.z, color4.w);

    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );

    //glLineWidth( 1 );
    glDrawArrays( primitivetype, 0, vertexCount );

    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
}

void Box2DDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    Draw( vertices, vertexCount, color, 255, GL_LINE_LOOP );
}

void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    Draw( vertices, vertexCount, color, 128, GL_TRIANGLE_FAN );
    Draw( vertices, vertexCount, color, 255, GL_LINE_LOOP );
}

void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    static const int vertexCount = 24;
    float anglechange = 2.0f * PI / vertexCount;

    b2Vec2 vertices[vertexCount];
    for( int i=0; i<vertexCount; i++ )
    {
        vertices[i].x = center.x + cos( i*anglechange ) * radius;
        vertices[i].y = center.y + sin( i*anglechange ) * radius;
    }

    Draw( vertices, vertexCount, color, 128, GL_TRIANGLE_FAN );
}

void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    static const int vertexCount = 24;
    float anglechange = 2.0f * PI / vertexCount;

    b2Vec2 vertices[vertexCount];
    for( int i=0; i<vertexCount; i++ )
    {
        vertices[i].x = center.x + cos( i*anglechange ) * radius;
        vertices[i].y = center.y + sin( i*anglechange ) * radius;
    }

    Draw( vertices, vertexCount, color, 128, GL_TRIANGLE_FAN );
    Draw( vertices, vertexCount, color, 255, GL_LINE_LOOP );
}

void Box2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    b2Vec2 vertices[2] = { p1, p2 };

    Draw( vertices, 2, color, 255, GL_LINES );
}

void Box2DDebugDraw::DrawTransform(const b2Transform& xf)
{
    b2Vec2 vertices[2] = { xf.p };

    vertices[1] = xf.p + 0.5f * xf.q.GetXAxis();
    Draw( vertices, 2, b2Color( 1, 0, 0 ), 255, GL_LINES );

    vertices[1] = xf.p + 0.5f * xf.q.GetYAxis();
    Draw( vertices, 2, b2Color( 0, 1, 0 ), 255, GL_LINES );
}

void Box2DDebugDraw::SetViewProjMatrices(MyMatrix* pMatView, MyMatrix* pMatProj)
{
    m_pMatView = pMatView;
    m_pMatProj = pMatProj;
}
