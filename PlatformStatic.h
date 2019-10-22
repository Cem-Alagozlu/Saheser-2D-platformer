#pragma once
#include "Platform.h"

class PlatformStatic : public Platform
{
public:
	PlatformStatic(const Point2f& position, const std::string& path, float angle, float scale, const std::string& pathVertices);

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

private:
	Texture m_Texture;
};
