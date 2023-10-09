#include "ModelRenderer.h"
#include "Transform.h"
#include "Entity.h"
#include "Model.h"
#include "Texture.h"

#include <iostream>

namespace myengine
{
	ModelRenderer::ModelRenderer() :
		m_shader("../data/shaders/basic.vert", "../data/shaders/basic.frag")
	{
	}

	void ModelRenderer::onDisplay()
	{
		rend::ModelRenderer r(640, 640);
		//get transform for model matrix
		std::shared_ptr<Transform> t = getEntity()->getComponent<Transform>();
		//set all rendering values
		r.modelMatrix(t->getModelMatrix());
		r.view(getCamera()->getViewMatrix());
		glm::mat4 projection(1.0f);
		projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		r.projection(projection);
		r.shader(&m_shader);
		r.texture(m_texture->m_texture.get());
		r.model(m_model->m_model.get());

		r.depthTest(true);

		r.render();

	}

	void ModelRenderer::setModel(std::shared_ptr<Model> _model)
	{
		m_model = _model;
	}

	void ModelRenderer::setTexture(std::shared_ptr<Texture> _texture)
	{
		m_texture = _texture;
	}
}