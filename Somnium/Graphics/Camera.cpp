#include "Camera.h"

#ifdef _WIN32
	#define SPRINTF sprintf_s
#else
	#define SPRINTF sprintf
#endif

namespace Somnium
{
	namespace Graphics
	{
		Camera::Camera(const float fieldOfView, const float aspectRatio, const float near, const float far, const bool orthographic, Maths::Vector3 position, Maths::Vector3 orientation):
			m_Position(position), m_Orientation(orientation), m_FieldOfView(fieldOfView), m_Near(near), m_Far(far), m_Orthographic(orthographic), m_AspectRatio(aspectRatio)
		{
#if ENABLE_DEBUG_CAMERA
			m_UIObjects.push_back(&m_UICameraPosition);
			m_UIObjects.push_back(&m_UICameraOrientation);
			m_UIObjects.push_back(&m_UIFieldOfView);
#endif
			updateProjection();
			updateView();
		}

		void Camera::setFOV(const float fov)
		{
			if (fov >= 1.f && fov <= 45.f) m_FieldOfView = fov;
			updateProjection();
		}

		void Camera::updateProjection()
		{
			if(m_Orthographic)
				m_Projection = Maths::Matrix4::orthographic(-m_AspectRatio / 2.0f, m_AspectRatio / 2.0f, -0.5f, 0.5f, m_Near, m_Far);
			else
				m_Projection = Maths::Matrix4::perspective(m_FieldOfView, m_AspectRatio, m_Near, m_Far);
			updateView();
		}

		void Camera::move(Maths::Vector3 displacement)
		{
			m_Position -= displacement; //We're not moving the camera Forward/Backward, we're moving the whole scene Backward/Forward, so have to negate the displacement
			m_View *= Maths::Matrix4::translation(-displacement);
		}

		void Camera::updateView()
		{
			m_View = Maths::Matrix4::translation(m_Position) * //TODO: Include orientation here
			Maths::Matrix4::rotationX(m_Orientation.x) *
				Maths::Matrix4::rotationY(m_Orientation.y) *
				Maths::Matrix4::rotationZ(m_Orientation.z);
		}

		void Camera::updateUI()
		{
#if ENABLE_DEBUG_CAMERA
			static char camPos[128], camRot[128], camFOV[128];
			SPRINTF(camPos, "CAMERA POSITION - X: %f, Y: %f Z: %f\r\n", -m_Position.x, -m_Position.y, m_Position.z);
			SPRINTF(camRot, "CAMERA ORIENTATION - Pitch: %f, Yaw: %f Roll: %f\r\n", m_Orientation.x, -m_Orientation.y, m_Orientation.z);
			SPRINTF(camFOV, "CAMERA FIELD OF VIEW - %d\r\n", m_FieldOfView);
			//printf("CURSOR POSITION - X: %d, Y: %d\r\n", mouseX, mouseY);
			//printf("CURSOR OFFSET - X: %d, Y: %d\r\n", xOffset, yOffset);

			m_UICameraPosition.setText(camPos);
			m_UICameraOrientation.setText(camRot);
			m_UIFieldOfView.setText(camFOV);
#endif
		}
	}
}
