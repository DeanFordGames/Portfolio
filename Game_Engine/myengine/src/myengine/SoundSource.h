#include "Component.h"

#include <memory>
#include <AL/al.h>
#include <AL/alc.h>

namespace myengine
{
	struct Audio;

	/**
	* Component handles the sound for the Entity 
	*/
	struct SoundSource : Component
	{
		/**
		* SoundSource creates the source id
		*/
		SoundSource();
		/**
		* setAudio used to set the required audio resource
		*/
		void setAudio(std::shared_ptr<Audio> _audio);

	private:

		void onTick();

		ALuint sourceId; ///< Id for the current sound

	};

}