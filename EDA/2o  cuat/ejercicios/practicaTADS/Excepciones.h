/*
 * Excepciones.h
 *
 *  Created on: 06/03/2014
 *      Author: isabel
 */

#ifndef EXCEPCIONES_H_
#define EXCEPCIONES_H_

#include <iostream>
#include <string>
#include <cassert>
#include <cstddef>
using namespace std;

class ExcepcionTAD {
	public :
    ExcepcionTAD ( ) {}
    ExcepcionTAD(const std :: string &msg) : _msg(msg) {}
    const std :: string msg() const { return _msg; }
    friend ostream &operator<< (std::ostream &out, const ExcepcionTAD &e){
        out << e._msg; return out; }
	protected :
    string _msg;
};



#endif /* EXCEPCIONES_H_ */
