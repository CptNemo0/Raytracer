#include "pch.h"
#include "quat.h"

namespace math
{
	quat::quat(const quat& q)
	{
		v_ = q.v_;
		s_ = q.s_;
	}

	quat& quat::operator=(const quat& other)
	{
		v_ = other.v_;
		s_ = other.s_;
		return *this;
	}

	quat quat::operator+(const quat& other)
	{
		return quat(s_ + other.s_, v_ + other.v_);
	}

	quat quat::operator-(const quat& other)
	{
		return quat(s_ - other.s_, v_ - other.v_);
	}

	void quat::operator+=(const quat& other)
	{
		s_ += other.s_;
		v_ += other.v_;
	}

	void quat::operator-=(const quat& other)
	{
		s_ -= other.s_;
		v_ -= other.v_;
	}

	bool quat::operator==(const quat& other)
	{
		return (v_ == other.v_) && (s_ == other.s_);
	}

	quat quat::operator*(const quat& other)
	{
		float s = s_ * other.s_ - dot(v_, other.v_);
		vec3  v = other.v_ * s_ + v_ * other.s_ + cross(v_, other.v_);
		return quat(s, v);
	}

	quat quat::operator*(const float other)
	{
		return quat(s_ * other, v_ * other);
	}

	void quat::operator*=(const quat& other)
	{
		float s = s_ * other.s_ - dot(v_, other.v_);
		vec3  v = other.v_ * s_ + v_ * other.s_ + cross(v_, other.v_);
		s_ = s;
		v_ = v;
	}

	void quat::operator*=(const float other)
	{
		s_ *= other;
		v_ *= other;
	}
}