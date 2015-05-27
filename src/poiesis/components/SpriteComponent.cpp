#include "poiesis/components/SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string filename, bool centered,
    float scale) :
    filename(filename), centered(centered), scale(scale)
{
}

std::string SpriteComponent::GetComponentClass()
{
    return "SpriteComponent";
}

std::string SpriteComponent::GetFilename()
{
    return filename;
}

void SpriteComponent::SetFilename(std::string filename)
{
    this->filename = filename;
}

bool SpriteComponent::GetCentered()
{
    return centered;
}

void SpriteComponent::SetCentered(bool centered)
{
    this->centered = centered;
}

float SpriteComponent::GetScale()
{
    return scale;
}

void SpriteComponent::SetScale(float scale)
{
    this->scale = scale;
}