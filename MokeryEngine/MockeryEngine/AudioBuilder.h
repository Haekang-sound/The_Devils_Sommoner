#pragma once
#include "IBuilder.h"
#include "Audio.h"

class KSL;

class AudioBuilder : public IBuilder
{

public:
	AudioBuilder();
	~AudioBuilder();

	void Initialize(ResourceCreator* creator) override;
	void CreateType(std::string fileName) override; 
	void SetType(IResource* resource) override;

private:
	Audio* m_audio{};
	KSL* m_soundEngine;

};