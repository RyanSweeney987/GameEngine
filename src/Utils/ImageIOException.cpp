#include "ImageIOException.h"

ImageIOException::ImageIOException() noexcept {
	what_ = "ImageIO exception has occured";
}

ImageIOException::ImageIOException(const std::string& what) noexcept {
	what_ = what;
}

ImageIOException::ImageIOException(const char* what) noexcept {
	what_ = what;
}

const char* ImageIOException::what() const noexcept {
	return what_.c_str();
}
