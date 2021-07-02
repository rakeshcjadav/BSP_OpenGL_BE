#include "Utils.h"

std::string Utils::GetMediaPath()
{
    return getenv("MEDIA_PATH");
}

string Utils::GetTexturePath()
{
    return GetMediaPath().append("textures/");
}

string Utils::GetShaderPath()
{
    return GetMediaPath().append("shaders/");
}