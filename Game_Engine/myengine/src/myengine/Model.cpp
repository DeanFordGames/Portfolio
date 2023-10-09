#include "Model.h"

namespace myengine
{
	void Model::onLoad()
	{
		m_model = std::make_shared<rend::Model>(getPath().c_str());
	}
}