#ifndef MATH_QUAT_OPERATIONS_H
#define MATH_QUAT_OPERATIONS_H

namespace math
{
	float norm(const quat& q);
	void normalize(quat& q);
	quat normalized(const quat& q);
	void conjugate(quat& q);
	quat conjugated(const quat& q);
	void inverse(quat& q);
	quat inversed(quat& q);
	void to_unit_norm_deg(quat& q);
	void to_unit_norm_rad(quat& q);
}

#endif // !MATH_QUAT_OPERATIONS_H