#pragma once

namespace edn
{
	class vec3;
	class mat3;

	class quat
	{
	public:
		quat();
		quat(float X, float Y, float Z, float W);
		quat(const vec3 &right, const vec3 &up, const vec3 &forward);
		quat(const mat3 &rotation);
		
		quat operator*(const quat &other) const;
		quat &operator*=(const quat &other);

		float operator[](unsigned int index) const;
		float &operator[](unsigned int index);

		void SetIdentity();
		void Conjugate();
		quat GetConjugate() const;
		void Normalize();
		quat GetNormalized() const;

		void Rotate(const vec3 &axis, float degrees);
		void Rotate(float X, float Y, float Z, float degrees);
		void RotateX(float degrees);
		void RotateY(float degrees);
		void RotateZ(float degrees);
		
		static float Dot(const quat &p0, const quat &p1);
		static quat Slerp(const quat &p0, const quat &p1, float percent);

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 1.0f;

	private:
	};
}