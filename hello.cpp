#include <phpcpp.h>
#include <iostream>
//#include <cstdio>
extern "C" {

  void hello( const char* text ) {

    Php::out << "lalalalla!" << std::endl;
    Php::out << text << std::endl;

  }

}
