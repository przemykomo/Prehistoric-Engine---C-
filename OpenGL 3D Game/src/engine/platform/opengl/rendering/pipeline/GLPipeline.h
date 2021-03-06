#ifndef GL_PIPELINE_H
#define GL_PIPELINE_H

#include <glew.h>

#include "engine/prehistoric/common/rendering/pipeline/Pipeline.h"
#include "engine/prehistoric/common/framework/Window.h"

class GLPipeline : public Pipeline
{
public:
	GLPipeline(Shader* shader);
	virtual ~GLPipeline() {}

	void CreatePipeline(Window* window, MeshVBO* vbo) override;

	void BindPipeline() override;
	void UnbindPipeline() const override;

	void DestroyPipeline() override;
private:

};

#endif