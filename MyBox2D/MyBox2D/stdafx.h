// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>



// TODO: reference additional headers your program requires here

#include <string>

#define GLEW_STATIC
#include "GL/glew.h"

// Graphics
#include "ShaderProgram.h"

// Library
#include "Box2D/Box2D.h"
// MyBox2D
#include "Box2DWorld.h"
#include "Box2DDebugDraw.h"
#include "Box2DContactListener.h"