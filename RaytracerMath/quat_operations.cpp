#include "pch.h"
#include "quat_operations.h"
#include "angles.h"
#include "vec_operations.h"
#include <cmath>
namespace math
{
	float norm(const quat& q)
	{
		float ss = q.s_ * q.s_;
		float vv = dot(q.v_, q.v_);
		return sqrtf(ss + vv);
	}

	void normalize(quat& q)
	{
		auto n = norm(q);
		auto inv_n = 1.0f / n;
		q.s_ *= inv_n;
		q.v_ *= inv_n;
	}

	quat normalized(const quat& q)
	{
		auto n = norm(q);
		auto inv_n = 1.0f / n;
		return quat(q.s_ * inv_n, q.v_ * inv_n);
	}

	void conjugate(quat& q)
	{
		q.v_ *= -1.0f;
	}

	quat conjugated(const quat& q)
	{
		return quat(q.s_, q.v_ * -1.0f);
	}

	void inverse(quat& q)
	{
		float n = norm(q);
		n *= n;
		float inv_n = 1.0f / n;
		conjugate(q);
		q *= inv_n;
	}

	quat inversed(quat& q)
	{
		float n = norm(q);
		n *= n;
		float inv_n = 1.0f / n;
		auto rv = conjugated(q);
		rv *= inv_n;
		return rv;
	}

	void to_unit_norm_deg(quat& q)
	{
		float angle = to_radians(q.s_);
		normalize(q.v_);
		q.s_ = std::cosf(angle * 0.5f);
		q.v_ = q.v_ * std::sinf(angle * 0.5f);
	}

	void to_unit_norm_rad(quat& q)
	{
		float angle = q.s_;
		normalize(q.v_);
		q.s_ = std::cosf(angle * 0.5f);
		q.v_ = q.v_ * std::sinf(angle * 0.5f);
	}
}