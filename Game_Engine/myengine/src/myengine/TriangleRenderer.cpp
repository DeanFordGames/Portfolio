#include "TriangleRenderer.h"
#include "Transform.h"
#include "Entity.h"
#include "Texture.h"

#include <iostream>

namespace myengine
{

	TriangleRenderer::TriangleRenderer() :
		m_shader("../data/shaders/basic.vert", "../data/shaders/basic.frag")
	{
		m_mesh.loadTriangle();
	}

	void TriangleRenderer::onDisplay()
	{
		//create renderer
		rend::Renderer r(640, 480);

		//gets transform for model matrix
		std::shared_ptr<Transform> t = getEntity()->getComponent<Transform>();

		//sets all values for rendering then renders
		r.model(t->getModelMatrix());
		r.view(getCamera()->getViewMatrix());
		r.shader(&m_shader);
		r.mesh(&m_mesh);
		r.texture(m_texture->m_texture.get());

		r.render();
	}

	void TriangleRenderer::setTexture(std::shared_ptr<Texture> _texture)
	{
		m_texture = _texture;
	}

}