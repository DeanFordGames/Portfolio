#include "Component.h"

#include <memory>
#include<rend/rend.h>

namespace myengine
{
	struct Texture;
	/**
	* Component for rendering a triangle  
	*/
	struct TriangleRenderer : Component
	{
		/**
		* TriangleRenderer initializes the shaders and mesh
		*/
		TriangleRenderer();
		/**
		* setTexture to set the required texture resource 
		*/
		void setTexture(std::shared_ptr<Texture> _texture);

	private:
		rend::Mesh m_mesh; ///< rend mesh required for triangle
		rend::Shader m_shader; ///< basic shaders required to render
		std::shared_ptr<Texture> m_texture; ///< pointer to texture resource

		/**
		* onDisplay called each frame to update triangle
		*/
		void onDisplay();
	};

}