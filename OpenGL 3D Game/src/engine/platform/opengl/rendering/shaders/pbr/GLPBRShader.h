#ifndef GL_PBR_SHADER_H
#define GL_PBR_SHADER_H

#include "engine/platform/opengl/rendering/shaders/GLShader.h"

#include <glew.h>

#include "engine/prehistoric/core/gameObject/GameObject.h"
#include "engine/prehistoric/core/movement/Camera.h"
#include "engine/prehistoric/component/renderer/Renderer.h"
#include "engine/prehistoric/core/model/material/Material.h"
#include "engine/platform/opengl/texture/GLTexture.h"

#include "engine/config/EngineConfig.h"

class GLPBRShader : public GLShader
{
public:
	GLPBRShader();
	virtual ~GLPBRShader() {}

	virtual void UpdateUniforms(GameObject* object, Camera* camera, std::vector<Light*> lights) const override;
};

#endif