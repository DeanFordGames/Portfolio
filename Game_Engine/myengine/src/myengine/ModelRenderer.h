#include "Component.h"

#include <memory>
#include <rend/rend.h>
#include <string>

namespace myengine
{
	struct Model;
	struct Texture;
	/**
	* Component renders the model for the Entity
	*/
	struct ModelRenderer : Component
	{
		/**
		* ModelRenderer sets the shaders
		*/
		ModelRenderer();

		/**
		* setModel used to set the model resource required
		*/
		void setModel(std::shared_ptr<Model> _model);
		/**
		* setTexture used to set the texture resource required
		*/
		void setTexture(std::shared_ptr<Texture> _texture);

	private:
		rend::Shader m_shader; ///< basic shaders required for rendering
		std::shared_ptr<Model> m_model; ///< pointer to the model resource
		std::shared_ptr<Texture> m_texture; ///< pointer to the texture resource

		void onDisplay();
	};
}