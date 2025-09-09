#pragma once

class AudioBuilder;
namespace FMOD
{
	class Sound;
}

class Audio
{
public:

	FMOD::Sound* m_data;
	static AudioBuilder* m_builder;
};

