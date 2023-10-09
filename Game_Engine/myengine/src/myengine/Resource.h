#pragma once

#include <string>

namespace myengine
{
	struct Resources;

	struct Resource
	{
		/**
		* onLoad to be called by the different resources
		*/
		virtual void onLoad() = 0;

		std::string getPath() const { return m_path; };

	private:
		friend struct Resources;

		std::string m_path; ///< path to resource required

		/**
		* load used to call onLoad virtual function
		*/
		void load();
	};

}