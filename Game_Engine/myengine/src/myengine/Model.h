#include "Resource.h"
#include <rend/rend.h>

#include <memory>

namespace myengine
{
	struct ModelRenderer;
	/**
	* Resource holds the resource for the model rendering
	*/
	struct Model : Resource
	{
		/**
		* onLoad loads the model needed
		*/
		void onLoad();

	private:
		friend struct ModelRenderer;

		std::shared_ptr<rend::Model> m_model; ///< holds a pointer to the loaded model
	};
}