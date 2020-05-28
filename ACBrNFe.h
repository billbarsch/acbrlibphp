#include <cstdint>
#include <string>
#include "ACBrNFeDinamico.h"

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

#if _WIN32 || _WIN64
#define ISWINDOWS
#elif __GNUC__
#define ISUNIX
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

#if defined(ISWINDOWS)
#include <windows.h>
#endif

#define BUFFER_LEN 256

class ACBrNFe{
private:
#if defined(ISWINDOWS)
	HMODULE nHandler;
#else
	void* nHandler;
#endif

	std::string trim(std::string& buffer) const;
	void check_result(int ret) const;
	std::string process_result(std::string buffer, int buffer_len);

public:
	ACBrNFe(std::string eArqConfig, std::string e_chave_crypt);
	ACBrNFe() : ACBrNFe("", "") {}
	~ACBrNFe();

	std::string _NFE_Nome();
	std::string _NFE_Versao();
	std::int32_t _NFE_ConfigGravarValor(std::string eSessao, std::string eChave, std::string sValor);
	std::int32_t _NFE_CarregarXML(std::string eArquivoOuXML);
	std::int32_t _NFE_Assinar();
	std::int32_t _NFE_Validar();
	std::string _NFE_ObterXml(std::int32_t AIndex);
	
};