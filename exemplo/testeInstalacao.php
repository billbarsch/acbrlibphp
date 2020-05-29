<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

//Inicia componente Acbr
$acbrlibphp = new AcbrLibPhp("/usr/lib/x86_64-linux-gnu/","/var/www/html/acbrlib.ini",""); //esta pasta requer permissoes de escrita para o usuario www-data do php
$acbrlibphp->NFE_ConfigGravarValor("Principal", "LogPath", "/var/www/html/"); //esta pasta requer permissoes de escrita para o usuario www-data do php
$acbrlibphp->NFE_ConfigGravarValor("Principal", "LogNivel", "4"); //4 - Paranoico;

$acbrlibphp->NFE_Versao();
