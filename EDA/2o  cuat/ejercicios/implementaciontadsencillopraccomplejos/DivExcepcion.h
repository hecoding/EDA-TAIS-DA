#pragma once
#include "ExcepcionTAD.h"
#include <string>

class DivExcepcion : public ExcepcionTAD {
public: DivExcepcion( std::string causa ) : ExcepcionTAD( causa) {}
};