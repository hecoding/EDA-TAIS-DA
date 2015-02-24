#ifndef EXCEPCION_TAD
#define EXCEPCION_TAD
#include <string>

class ExcepcionTAD {
private:
	std::string _causa;

public:
	ExcepcionTAD( std::string causa ) : _causa( causa ) {}

	std::string getCausa() {
		return _causa;
	}
};

#endif 