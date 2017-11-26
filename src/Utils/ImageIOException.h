#pragma once

#include <stdexcept>

class ImageIOException : public std::exception {
public:
	ImageIOException() noexcept;
	explicit ImageIOException(const std::string& what) noexcept;
	explicit ImageIOException(const char* what) noexcept;

	virtual const char* what() const noexcept;
private:
	std::string what_;
};