#pragma once
#include "../Math/Vector2.h"
#include <vector>
#include <array>
#include <cassert>

namespace swaws {
	class InputSystem
	{
	public:
		InputSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		// KEYBOARD INPUT
		bool GetKeyDown(uint8_t key) { return m_keyboardState[key]; }
		bool GetPreviousKeyDown(uint8_t key) { return m_prevKeyboardState[key]; }
		bool GetKeyPressed(uint8_t key) { return !m_prevKeyboardState[key] && m_keyboardState[key]; }
		bool GetKeyReleased(uint8_t key) { return m_prevKeyboardState[key] && !m_keyboardState[key]; }

		// MOUSE INPUT
		bool GetMouseButtonDown(uint8_t button) { assert(button < 3);  return m_mouseButtonState[button]; }
		bool GetPreviousMouseButtonDown(uint8_t button) { assert(button < 3);  return m_prevMouseButtonState[button]; }
		bool GetMouseButtonPressed(uint8_t button) { assert(button < 3);  return !m_prevMouseButtonState[button] && m_mouseButtonState[button]; }
		bool GetMouseButtonReleased(uint8_t button) { assert(button < 3);  return m_prevMouseButtonState[button] && !m_mouseButtonState[button]; }

		const swaws::vector::vec2& GetMousePosition() { return m_mousePosition; }
		const swaws::vector::vec2& GetPreviousMousePosition() { return m_prevMousePosition; }


	private:
		std::vector<bool> m_keyboardState;
		std::vector<bool> m_prevKeyboardState;

		swaws::vector::vec2 m_mousePosition{ 0, 0 };
		swaws::vector::vec2 m_prevMousePosition{ 0, 0 };

		std::array<bool, 3> m_mouseButtonState{ false, false, false };
		std::array<bool, 3> m_prevMouseButtonState{ false, false, false };
	};


}