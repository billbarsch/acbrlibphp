#include <phpcpp.h>
#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
//#include "Acbrlibphp.h"
#include <memory>
#include "ACBrNFe.h"

void teste1()
{
    std::shared_ptr<ACBrNFe> nfe = std::make_shared<ACBrNFe>("/home/billbarsch/Desktop/testecpp/acbrlib.ini",""); 
    Php::out << nfe->nome() + " " + nfe->versao() << "<br>" << std::endl;
    //cout << nfe->nome() + " " + nfe->versao() << std::endl;
}
/*
void teste1()
{
    Acbrlibphp AcbrlibClass;

	string sucesso;
	string erro;
	string versao;
	
    versao = AcbrlibClass.NFE_Versao();
	sucesso = AcbrlibClass.status;
    erro = AcbrlibClass.error;
    //versao = "laaaa";
    //versao = error.c_str();
    Php::out << "Sucesso:" << sucesso << "<br>" << std::endl;
    Php::out << "Erro:" << erro << "<br>" << std::endl;
    Php::out << "Versao:" << versao << "<br>" << std::endl;

	//AcbrlibClass.NFE_ConfigGravarValor("NFe", "TimeOut", "7700");
}
*/

/*
extern "C" typedef void (*hello_t)( const char* text );

void teste()
{
    void* lib = dlopen("./libhello.so", RTLD_LAZY);
    hello_t hello = (hello_t)dlsym( lib, "hello" );

    hello("World!");

    //Php::out << "terminou!" << std::endl;
    //dlclose(lib);
}
*/

void teste2()
{
    putenv("DISPLAY=:0");
	void* lib = dlopen("/usr/local/lib/libacbrnfe64.so", RTLD_LAZY);
    dlclose(lib);

    //NFE_Versao_t NFE_Versao_h = (NFE_Versao_t)dlsym( lib, "NFE_Versao" );

	//int bufferlen = BUFFER_LEN;
	//char text[BUFFER_LEN];
	//NFE_Versao_h(&text, &bufferlen);

/*
	int bufferlen = BUFFER_LEN;
	char text[BUFFER_LEN];

    void* lib = dlopen("/usr/local/lib/libacbrnfe64.so", RTLD_LAZY);
    NFE_Versao_t NFE_Versao = (NFE_Versao_t)dlsym( lib, "NFE_Versao");

    //NFE_Versao(&text,&bufferlen);
    //Php::out << "erro" << std::endl;
    //Php::out << text << std::endl;

    dlclose(lib);
    */

    Php::out << "teste2 ok" << std::endl;
}

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("acbrlibphp", "1.0");
        
        extension.add<teste1>("Acbrlibphp\\teste1");
        extension.add<teste2>("Acbrlibphp\\teste2");

        // return the extension
        return extension;
    }
}
