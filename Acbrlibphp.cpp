#include "Acbrlibphp.h"

Acbrlibphp::Acbrlibphp()
{
	putenv("DISPLAY=:0");
	lib = dlopen("/usr/local/lib/libacbrnfe64.so", RTLD_LAZY);
	if (!lib) { 
		status = "erro";
		error = dlerror();
	}else{
		status = "sucesso";
		NFE_Versao_h = (NFE_Versao_t)dlsym( lib, "NFE_Versao" );
		NFE_ConfigGravarValor_h = (NFE_ConfigGravarValor_t)dlsym( lib, "NFE_ConfigGravarValor" );
	}
}

/*Acbrlibphp::~Acbrlibphp()
{
	dlclose(lib);
}
*/

string Acbrlibphp::Teste()
{
	return error;
}

string Acbrlibphp::NFE_Versao()
{
	int bufferlen = BUFFER_LEN;
	char text[BUFFER_LEN];
	NFE_Versao_h(&text, &bufferlen);
	//printf ("Bufferlen: %d\n", bufferlen);
	//std::cout << text << std::endl;
	//char* retorno = new char;
	//retorno = text;
	string retorno = text;
	return retorno;
}//NFE_Versao

void Acbrlibphp::NFE_ConfigGravarValor(const char* sessao, const char* chave, const char* value )
{
    NFE_ConfigGravarValor_h(sessao, chave, value);
}