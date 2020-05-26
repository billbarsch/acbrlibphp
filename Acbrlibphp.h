#include <string>
#include <iostream>
#include <dlfcn.h>
#include <stdio.h>

using namespace std;

const int BUFFER_LEN = 256;
typedef int (*NFE_Versao_t)( char (*)[BUFFER_LEN], int * );
typedef int (*NFE_ConfigGravarValor_t)( const char* , const char* , const char* );

class Acbrlibphp
{
	public:
		Acbrlibphp(); //construct
		//~Acbrlibphp(); //construct

	    void* lib;
		string status;
		string error;

		string Teste();

		//funcoes acbrlib
		NFE_Versao_t NFE_Versao_h;
		string NFE_Versao();

		NFE_ConfigGravarValor_t NFE_ConfigGravarValor_h;
		void NFE_ConfigGravarValor(const char* sessao, const char* chave, const char* value );
};