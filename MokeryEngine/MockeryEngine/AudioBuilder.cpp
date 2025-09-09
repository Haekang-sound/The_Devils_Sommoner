#include "pch.h"
#include "AudioBuilder.h"
#include "ResourceCreator.h"
#include "../KestrelSoundLibrary/KestrelSoundLibrary.h"

AudioBuilder::AudioBuilder()
	: m_audio(nullptr), m_soundEngine(nullptr)
{

}

AudioBuilder::~AudioBuilder()
{

}

void AudioBuilder::Initialize(ResourceCreator* creator)
{
	m_soundEngine = creator->m_soundCreator;
}


void AudioBuilder::CreateType(std::string fileName)
{
	m_audio = new Audio();

	std::string type = ".wav";
	std::string filepath = fileName + type;
	m_soundEngine->LoadSound(filepath);
	m_audio->m_data = m_soundEngine->GetSound(filepath);
}

void AudioBuilder::SetType(IResource* resource)
{
	resource->SetResource(m_audio);
}

