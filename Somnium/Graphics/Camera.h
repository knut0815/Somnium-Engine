#pragma once

#define ENABLE_DEBUG_CAMERA true

#include "../Maths/Maths.h"
#include "UI/UIObject.h"
#include "UI/UIText.h"
#include "UI/UIImage.h"
#include <vector>

namespace Somnium
{
	namespace Graphics
	{
		class Camera
		{
		/* Methods */
		public:
			Camera(const float fieldOfView, const float aspectRatio, const float near = 0.1f, const float far = 0.1f, const bool orthographic = false, Maths::Vector3 position = Maths::Vector3(), Maths::Vector3 orientation = Maths::Vector3());
			~Camera() {};

			const Maths::Matrix4& getView() const { return m_View; };
			const Maths::Matrix4& getProjection() const { return m_Projection; }
			const float& getFOV() const { return m_FieldOfView; }
			const Maths::Vector3& getPosition() const { return m_Position; };
			const Maths::Vector3& getOrientation() const { return m_Orientation; };

			void lookAt();
			void setOrientation(Maths::Vector3 &orientation) { m_Orientation = orientation; };
			void setOrientation(const float &pitchAngle, float const &yawAngle, const float &rollAngle = 0) { m_Orientation = Maths::Vector3(pitchAngle, yawAngle, rollAngle); }
			void offsetOrientation(const float &pitchAngle, float const &yawAngle, const float &rollAngle = 0) { m_Orientation += Maths::Vector3(pitchAngle, yawAngle, rollAngle) * m_Sensitivity; updateView(); }
			void setFOV(const float fov);
			void setPitch(float const &angle);
			void setYaw(float const &angle);
			void setRoll(float const &angle);
			void setPosition();

			void offsetFOV(const float offset) { setFOV(m_FieldOfView + offset); }

			void move(Maths::Vector3 displacement);
			
			/* UI Controls */

			void drawUIText() {};
			void drawUIGraphic() {};
			void updateUI();
			void clearUI() {};

		private:
			void updateView();
			void updateProjection();
			inline void initialiseUI();
			Maths::Vector3 forward();
			Maths::Vector3 right();

		/* Variables */
		public:

		private:
			Maths::Matrix4 m_Projection;
			Maths::Vector3 m_Position;
			Maths::Vector3 m_Orientation;

			float m_Sensitivity = 0.05f;

			float m_FieldOfView = 45.f, m_Near = 0.1f, m_Far = 100.f;
			float m_AspectRatio;
			bool m_Orthographic = false;

			Maths::Matrix4 m_View; //The finalized representation of the camera's viewpoint

			std::vector<UI::UIObject*> m_UIObjects;

#if ENABLE_DEBUG_CAMERA
			UI::UIText m_UICameraPosition;
			UI::UIText m_UICameraOrientation;
			UI::UIText m_UIFieldOfView;
#endif
		};
	}
}