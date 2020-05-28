<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

//funcao para achar chave da nota na resposta recebida
function recursiveFind(array $haystack, $needle)
{
    $iterator  = new RecursiveArrayIterator($haystack);
    $recursive = new RecursiveIteratorIterator(
        $iterator,
        RecursiveIteratorIterator::SELF_FIRST
    );
    foreach ($recursive as $key => $value) {
        if ($key === $needle) {
            return $value;
        }
    }
}

//Inicia componente Acbr
$acbrlibphp = new AcbrLibPhp("/usr/lib/x86_64-linux-gnu/","/var/www/html/acbrlib.ini",""); //esta pasta requer permissoes de escrita para o usuario www-data do php
$acbrlibphp->NFE_ConfigGravarValor("Principal", "LogPath", "/var/www/html/"); //esta pasta requer permissoes de escrita para o usuario www-data do php
$acbrlibphp->NFE_ConfigGravarValor("NFe", "PathSalvar", "/var/www/html/"); //
$acbrlibphp->NFE_ConfigGravarValor("NFe", "PathNFe", "/var/www/html/"); //
$acbrlibphp->NFE_ConfigGravarValor("NFe", "PathInu", "/var/www/html/"); //
$acbrlibphp->NFE_ConfigGravarValor("NFe", "PathEvento", "/var/www/html/"); //
$acbrlibphp->NFE_ConfigGravarValor("NFe", "PathSchemas", "/home/billbarsch/Desktop/acbrlibphp/Schemas/NFe");

$acbrlibphp->NFE_ConfigGravarValor("DFe", "ArquivoPFX", "/var/www/html/39678831569137928.pfx");
$acbrlibphp->NFE_ConfigGravarValor("DFe", "Senha", "23101981");
$acbrlibphp->NFE_ConfigGravarValor("DFe", "UF", "TO");
$acbrlibphp->NFE_ConfigGravarValor("Principal", "TipoResposta", "2"); //2 - json
$acbrlibphp->NFE_ConfigGravarValor("Principal", "LogNivel", "4"); //4 - Paranoico;

$acbrlibphp->NFE_ConfigGravarValor("DFe", "SSLCryptLib", "1"); //1 = cryOpenSSL
$acbrlibphp->NFE_ConfigGravarValor("DFe", "SSLHttpLib", "3"); //3 = httpOpenSSL
$acbrlibphp->NFE_ConfigGravarValor("DFe", "SSLXmlSignLib", "4"); //4 = xsLibXml2
$acbrlibphp->NFE_ConfigGravarValor("NFe", "SalvarGer", "0"); //nao
$acbrlibphp->NFE_ConfigGravarValor("NFe", "ExibirErroSchema", "0"); //nao
$acbrlibphp->NFE_ConfigGravarValor("NFe", "Ambiente", "1"); // 0-producao | 1-homologacao
$acbrlibphp->NFE_ConfigGravarValor("NFe", "SSLType", "5"); // 5 - LT_TLSv1_2

$acbrlibphp->NFE_ConfigGravarValor("DANFE", "MostraPreview", "0"); // 0 - nao
$acbrlibphp->NFE_ConfigGravarValor("DANFE", "MostraStatus", "0"); // 0 - nao
$acbrlibphp->NFE_ConfigGravarValor("DANFE", "MostraSetup", "0"); // 0 - nao
$acbrlibphp->NFE_ConfigGravarValor("DANFE", "PathPDF", "/var/www/html/"); //esta pasta requer permissoes de escrita para o usuario www-data do php

$acbrlibphp->NFE_LimparLista();

$xml = file_get_contents('/var/www/html/xml.xml');
$acbrlibphp->NFE_CarregarXML($xml);

$acbrlibphp->NFE_Assinar();

$acbrlibphp->NFE_Validar();

echo "<br>Antes de emitir:<br>"; 
echo '<textarea cols="130" rows="40">';
echo $acbrlibphp->NFE_ObterXml(0);
echo '</textarea>';

echo "<br>Resultado do envio:<br>"; 
echo '<textarea cols="130" rows="40">';
$resultadoEnvio = $acbrlibphp->NFE_Enviar(1,False,True,false);
echo $resultadoEnvio;
echo '</textarea>';

echo "<br>Depois de Emitir:<br>";
echo '<textarea cols="130" rows="40">';
echo $acbrlibphp->NFE_ObterXml(0);
echo '</textarea>';

echo $acbrlibphp->NFE_ImprimirPDF();

$arrayResultado = json_decode($resultadoEnvio,true);

if(!empty($arrayResultado["Envio"]["CStat"]))
if($arrayResultado["Envio"]["CStat"]==100){//autorizada
    //pega chave da nota
    $chave = recursiveFind($arrayResultado,"chDFe");
    $arquivoPdf = file_get_contents('/var/www/html/'.$chave.'-nfe.pdf');

    //mostra pdf da nota na tela
    ?>
    <object data="data:application/pdf;base64,<?php echo base64_encode($arquivoPdf); ?>" type="application/pdf" width="100%" height="800px"></object>
    <?php
}//if autorizada
