#pragma once
class Flag
{
public:
	Flag(const Point2f& pos);

	void Draw() const;
	void Update(float elapsedSec);
	bool CollisionFlag(Rectf& actorShape);

private:
	Point2f m_Pos{};
	Rectf m_FlagRect{};

	bool m_IsFlagTouched{};

	std::unique_ptr<Texture> m_FlagTexture;
	Sprite m_FlagSprite;
};

