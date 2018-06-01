#pragma once
#include "../Maths/Maths.h"

namespace Somnium
{
	namespace Graphics
	{
		class Camera
		{
		/* Methods */
		public:
			Camera(Maths::Matrix4 projection, Maths::Vector3 position = Maths::Vector3(0, 0, 0), Maths::Vector3 orientation = Maths::Vector3(0, 0, 0));
			~Camera() {};

			const Maths::Matrix4& getView() const { return m_View; };
			const Maths::Matrix4& getProjection() const { return m_Projection;  }

			void lookAt();
			void setOrientation(Maths::Vector3 &orientation) { m_Orientation = orientation; };
			void setOrientation(const float &pitchAngle, float const &yawAngle, const float &rollAngle) { m_Orientation = Maths::Vector3(pitchAngle, yawAngle, rollAngle); };
			void setPitch(float const &angle);
			void setYaw(float const &angle);
			void setRoll(float const &angle);

			void setPosition();
			void move(Maths::Vector3 displacement);
			

		private:
			void updateView();
			Maths::Vector3 forward();
			Maths::Vector3 right();

		/* Variables */
		public:

		private:
			Maths::Matrix4 m_Projection;
			Maths::Vector3 m_Position;
			Maths::Vector3 m_Orientation;

			Maths::Matrix4 m_View; //The finalized representation of the camera's viewpoint
		};
	}
}