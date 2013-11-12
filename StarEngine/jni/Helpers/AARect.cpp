#include "AARect.h"
#include "../Graphics/ScaleSystem.h"

namespace star
{
	AARect::AARect():
		m_X(0),
		m_Y(0),
		m_Width(0),
		m_Height(0)
	{
	}

	AARect::AARect(int x, int y, int width, int height):
		m_X(x),
		m_Y(y),
		m_Width(width),
		m_Height(height)
	{
		ASSERT(m_Width >= 0, _T("Width can't be negative!"));
		ASSERT(m_Height >= 0, _T("Height can't be negative!"));
	}

	AARect::AARect(const vec2& location,const vec2& size)
	{
		m_X = static_cast<int>(location.x);
		m_Y = static_cast<int>(location.y);
		m_Width = static_cast<int>(size.x);
		m_Height = static_cast<int>(size.y);
	}

	AARect::~AARect()
	{

	}

	int AARect::GetLeft() const
	{
		return int(m_X * ScaleSystem::GetInstance()->GetScale());
	}

	int AARect::GetTop() const
	{
		return int(m_Y * ScaleSystem::GetInstance()->GetScale());
	}

	int AARect::GetRight() const
	{
		return int((m_X + m_Width) * ScaleSystem::GetInstance()->GetScale());
	}

	int AARect::GetBottom() const
	{
		return int((m_Y + m_Height) * ScaleSystem::GetInstance()->GetScale());
	}

	bool AARect::Equals(const AARect& rect) const
	{
		return m_X == rect.m_X &&
			m_Y == rect.m_Y &&
			m_Width == rect.m_Width &&
			m_Height == rect.m_Height;
	}

	bool AARect::Contains(int x, int y) const
	{
		float scale = ScaleSystem::GetInstance()->GetScale();
		return x >= m_X * scale && x < (m_X + m_Width) * scale &&
			y >= m_Y * scale && y < (m_Y + m_Height) * scale;
	}

	bool AARect::Contains(const vec2& pt) const
	{
		return Contains(int(pt.x), int(pt.y));
	}

	bool AARect::Contains(AARect& rect) const
	{
		//No need to apply scaling here, will be true in every resolution
		return (m_X <= rect.m_X) && (rect.GetRight() <= GetRight()) &&
				(m_Y <= rect.m_Y) && (rect.GetBottom() <= GetBottom());
	}

	bool AARect::Intersect(const AARect& rect)
	{
		return Intersect(*this, rect);
	}

	bool AARect::Intersect(const AARect& a, const AARect& b)
	{
		int right = min(a.GetRight(), b.GetRight());
		int bottom = min(a.GetBottom(), b.GetBottom());
		int left = max(a.GetLeft(), b.GetLeft());
		int top = max(a.GetTop(), b.GetTop());

		AARect c(
		left,
		top,
		right - left,
		bottom - top);

		return !(c.m_Width <= 0 || c.m_Height <= 0);
	}
}
