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
        std::string eArqConfig = params[0];
        std::string eChaveCrypt = params[1];
        nfe = std::make_shared<ACBrNFe>(eArqConfig,eChaveCrypt);
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
        //Php::out << nfe->_NFE_Nome() + " " + nfe->_NFE_Versao() << "<br>" << std::endl;
    }//NFE_ConfigGravarValor

};

//std::shared_ptr<ACBrNFe> nfe = std::make_shared<ACBrNFe>("/home/billbarsch/Desktop/acbrlibphp/acbrlib.ini","");
//Php::out << nfe->_NFE_Nome() + " " + nfe->_NFE_Versao() << "<br>" << std::endl;
//return "nada";

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

        AcbrLibPhp.method<&AcbrLibPhp::nomeVersao>("nomeVersao");

        // the Example class has one public property
        //example.property("property1", "xyz", Php::Public);

        // add the class to the extension
        myExtension.add(std::move(AcbrLibPhp));

        return myExtension;
    }
}
