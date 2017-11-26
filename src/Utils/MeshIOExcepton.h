#pragma once

#include <stdexcept>

class MeshIOException : public std::exception {
public:
	MeshIOException() noexcept;
	explicit MeshIOException(const std::string& what) noexcept;
	explicit MeshIOException(const char* what) noexcept;

	virtual const char* what() const noexcept;
private:
	std::string what_;
};