#include "Resource.h"

#include <memory>
#include <vector>
#include <string>

namespace myengine
{
	struct Resources
	{
		/**
		* load used to load the resources
		* \param _path the required path to resource
		* \return the required resource
		*/
		template <typename T>
		std::shared_ptr<T> load(const std::string& _path)
		{
			std::string p;
#ifdef _WIN32
			p += "../";
#endif
			p += _path;
			for (size_t i = 0; i < m_resources.size(); ++i)
			{
				if (m_resources.at(i)->getPath() == p)
				{
					return std::dynamic_pointer_cast<T>(m_resources.at(i));
				}
			}

			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->m_path = p;
			rtn->load();
			m_resources.push_back(rtn);

			return rtn;
		}

	private:

		std::vector<std::shared_ptr<Resource>> m_resources; ///< a vector of all loaded resources
	};
}