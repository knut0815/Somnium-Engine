#include "Camera.h"

namespace Somnium
{
	namespace Graphics
	{
		Camera::Camera(Maths::Matrix4 projection, Maths::Vector3 position, Maths::Vector3 orientation):
			m_Projection(projection), m_Position(position), m_Orientation(orientation)
		{
			updateView();
		}

		void Camera::move(Maths::Vector3 displacement) 
		{
			m_Position -= displacement; //We're not moving the camera Forward/Backward, we're moving the whole scene Backward/Forward, so have to negate the displacement
			m_View *= Maths::Matrix4::translation(-displacement);
		}

		void Camera::updateView() 
		{
			m_View = Maths::Matrix4::rotationX(m_Orientation.x) *
				Maths::Matrix4::rotationY(m_Orientation.y) *
				Maths::Matrix4::rotationZ(m_Orientation.z) *
				Maths::Matrix4::translation(m_Position); //TODO: Include orientation here
		}
	}
}	