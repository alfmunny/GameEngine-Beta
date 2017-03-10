#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "../utils/fileutils.h"
#include "../maths/maths.h"
#include <iostream>

namespace sparky { namespace graphics {
	class Shader
	{
	private:
		GLuint m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void setUniform1f(const GLchar* name, const float value);
		void setUniform1i(const GLchar* name, const int value);
		void setUniform2f(const GLchar* name, const glm::vec2& vector);
		void setUniform3f(const GLchar* name, const glm::vec3& vector);
		void setUniform4f(const GLchar* name, const glm::vec4& vector);
		void setUniformMat4(const GLchar* name, const glm::mat4& matrix);

		void enable() const;
		void disable() const;
	private:
		GLuint load();
		GLint getUniformLocation(const GLchar* name);

	};
} }