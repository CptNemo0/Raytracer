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
		constexpr auto eps = std::numeric_limits<float>::epsilon();
		return (v_ == other.v_) && (fabs(s_ - other.s_) < eps);
	}

	bool quat::operator!=(const quat& other)
	{
		constexpr auto eps = std::numeric_limits<float>::epsilon();
		const bool r = (v_ == other.v_) && (fabs(s_ - other.s_) < eps);
		return !r;
	}

	quat quat::operator*(const quat& other)
	{
		float scalar = s_ * other.s_ - dot(v_, other.v_);
		vec3 imaginary = (other.v_ * s_) + (v_ * other.s_) + cross(v_, other.v_);
		return quat(scalar, imaginary);
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