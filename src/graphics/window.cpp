#include "window.h"
#include <iostream>

namespace sparky {
	namespace graphics {

		void window_resize(GLFWwindow *window, int width, int height);

		Window::Window(const char *name, int width, int height)
		{
			m_Name = name;
			m_Width = width;
			m_Height = height;
			if (!init())
				glfwTerminate();

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_Keys[i] = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}


		bool Window::init()
		{

			if (!glfwInit())
				return false;

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);

			if (!m_Window)
			{
				std::cout << "Failed to initialize GLFW " << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			
			if (glewInit() != GLEW_OK) 
			{
				std::cout << "Could not initialize GLEW" << std::endl;
			}

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

			return true;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;

			return m_Keys[keycode];
			
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_BUTTONS)
				return false;

			return m_MouseButtons[button];
		}

		void Window::getMousePosition(double & x, double & y) const
		{
			x = mx;
			y = my;
		}

		void Window::update()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		void window_resize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
		}
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
		{
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}

	}
}