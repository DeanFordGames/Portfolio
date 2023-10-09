#include "Resource.h"

#include <memory>
#include <AL/al.h>

namespace myengine
{
	struct SoundSource;
	/**
	* Resource provides the Audio resource to resources 
	*/
	struct Audio : Resource
	{
		/**
		* onLoad loads the sound file
		*/
		void onLoad();

	private:
		friend struct SoundSource;

		 ALuint m_id; ///< Id for the loaded sound file
	};
}