#include "Resource.h"
#include <rend/rend.h>

#include <memory>

namespace myengine
{
	struct TriangleRenderer;
	struct ModelRenderer;

	/**
	* Resource used for all the texture resources
	*/
	struct Texture : Resource
	{
		void onLoad();

	private:
		friend struct TriangleRenderer;
		friend struct ModelRenderer;

		std::shared_ptr<rend::Texture> m_texture; ///< pointer to the loaded rend texture 
	};
}