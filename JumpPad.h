#pragma once
class JumpPad
{
public:
	JumpPad(const Point2f& pos);

	void Draw() const;
	bool CollisionJumpPad(Rectf& actorShape) const;
	void SetIsJumping(bool isJumping);
	bool GetIsJumping();

private:
	Point2f m_Pos{};
	Rectf m_JumpPadRect{};
	bool m_IsJumping{};

	std::unique_ptr<Texture> m_JumpPadTexture;
};

