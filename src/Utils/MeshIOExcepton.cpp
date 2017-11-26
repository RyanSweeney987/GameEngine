#include "MeshIOExcepton.h"

MeshIOException::MeshIOException() noexcept {
	what_ = "ImageIO exception has occured";
}

MeshIOException::MeshIOException(const std::string& what) noexcept {
	what_ = what;
}

MeshIOException::MeshIOException(const char* what) noexcept {
	what_ = what;
}

const char* MeshIOException::what() const noexcept {
	return what_.c_str();
}
