#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <memory>
#include "ACBrNFe.h"
#include <phpcpp.h>

class AcbrLibPhp : public Php::Base
{
private:
        std::shared_ptr<ACBrNFe> nfe;

public:
    /**
     *  c++ constructor
     */
    AcbrLibPhp() = default;

    /**
     *  c++ destructor
     */
    virtual ~AcbrLibPhp() = default;

    /**
     *  php "constructor"
     *  @param  params
     */
    void __construct(Php::Parameters &params)
    {
        // get self reference as Php::Value object
        Php::Value self(this);
        std::string ePathLib = params[0];
        std::string eArqConfig = params[1];
        std::string eChaveCrypt = params[2];
        nfe = std::make_shared<ACBrNFe>(ePathLib,eArqConfig,eChaveCrypt);
        // initialize a public property
        //self["property1"] = "xyz";
    }

    void nomeVersao()
    {
        // get self reference as Php::Value object
        Php::Value self(this);

        // overwrite the property
        //self["property1"] = "abc";

        Php::out << nfe->_NFE_Nome() + " " + nfe->_NFE_Versao() << "<br>" << std::endl;

    }

    void NFE_ConfigGravarValor(Php::Parameters &params)
    {
        // get self reference as Php::Value object
        Php::Value self(this);

        std::string eSessao = params[0];
        std::string eChave = params[1];
        std::string sValor = params[2];
        nfe->_NFE_ConfigGravarValor(eSessao,eChave,sValor);
    }//NFE_ConfigGravarValor

    void NFE_CarregarXML(Php::Parameters &params)
    {
        // get self reference as Php::Value object
        Php::Value self(this);

        std::string eArquivoOuXML = params[0];
        nfe->_NFE_CarregarXML(eArquivoOuXML);
    }//NFE_CarregarXML

    void NFE_Assinar()
    {
        Php::Value self(this);
        nfe->_NFE_Assinar();
    }//NFE_Assinar

    void NFE_LimparLista()
    {
        Php::Value self(this);
        nfe->_NFE_LimparLista();
    }//NFE_LimparLista

    void NFE_ImprimirPDF()
    {
        Php::Value self(this);
        nfe->_NFE_ImprimirPDF();
    }//NFE_ImprimirPDF


    void NFE_Validar()
    {
        // get self reference as Php::Value object
        Php::Value self(this);

        nfe->_NFE_Validar();
    }//NFE_Validar

    Php::Value NFE_ObterXml(Php::Parameters &params)
    {
        Php::Value self(this);
        std::int32_t AIndex = params[0];
        return nfe->_NFE_ObterXml(AIndex);
    }//NFE_ObterXml

    Php::Value NFE_Enviar(Php::Parameters &params)
    {
        Php::Value self(this);
        std::int32_t ALote = params[0];
        bool Imprimir = params[1];
        bool Sincrono = params[2];
        bool Zipado = params[3];
        return nfe->_NFE_Enviar(ALote, Imprimir,Sincrono,Zipado);
    }//NFE_Enviar

};

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
        static Php::Extension myExtension("acbrlibphp", "1.0");

        // description of the class so that PHP knows which methods are accessible
        Php::Class<AcbrLibPhp> AcbrLibPhp("AcbrLibPhp");

        // register the methods
        AcbrLibPhp.method<&AcbrLibPhp::__construct>("__construct", {
            Php::ByVal("eArqConfig", Php::Type::String),
            Php::ByVal("eChaveCrypt", Php::Type::String)
        });

        AcbrLibPhp.method<&AcbrLibPhp::NFE_ConfigGravarValor>("NFE_ConfigGravarValor", {
            Php::ByVal("eSessao", Php::Type::String),
            Php::ByVal("eChave", Php::Type::String),
            Php::ByVal("sValor", Php::Type::String)
        });

        AcbrLibPhp.method<&AcbrLibPhp::NFE_CarregarXML>("NFE_CarregarXML", {
            Php::ByVal("eArquivoOuXML", Php::Type::String)
        });

        AcbrLibPhp.method<&AcbrLibPhp::NFE_Assinar>("NFE_Assinar");

        AcbrLibPhp.method<&AcbrLibPhp::NFE_LimparLista>("NFE_LimparLista");

        AcbrLibPhp.method<&AcbrLibPhp::NFE_ImprimirPDF>("NFE_ImprimirPDF");

        AcbrLibPhp.method<&AcbrLibPhp::NFE_Validar>("NFE_Validar");

        AcbrLibPhp.method<&AcbrLibPhp::NFE_ObterXml>("NFE_ObterXml",{
            Php::ByVal("AIndex", Php::Type::Numeric)
        });

        AcbrLibPhp.method<&AcbrLibPhp::NFE_Enviar>("NFE_Enviar",{
            Php::ByVal("ALote", Php::Type::Numeric),
            Php::ByVal("Imprimir", Php::Type::Bool),
            Php::ByVal("Sincrono", Php::Type::Bool),
            Php::ByVal("Zipado", Php::Type::Bool)
        });

        AcbrLibPhp.method<&AcbrLibPhp::nomeVersao>("nomeVersao");

        // the Example class has one public property
        //example.property("property1", "xyz", Php::Public);

        // add the class to the extension
        myExtension.add(std::move(AcbrLibPhp));

        return myExtension;
    }
}
