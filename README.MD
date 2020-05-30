# AcbrLibPHP

## Script automatico de compilacao e instalacao

`wget -O install.sh https://raw.githubusercontent.com/billbarsch/acbrlibphp/master/install.sh`

`sudo chmod +x install.sh`

`sudo ./install.sh`


## Instalar dependencias:

`sudo apt install git -y`

`sudo apt install php-dev -y`

`sudo apt install libxml2 -y`

`sudo apt install openssl -y`

`sudo apt install libxmlsec1-openssl -y`

`sudo apt install libxslt-dev -y`

`sudo apt install libgtk2.0-0 -y`

`sudo apt install libcanberra-gtk-module -y`

`sudo apt install apache2 -y`

`sudo apt install php libapache2-mod-php -y`

`sudo apt install xvfb -y`


## Este projeto requer a instalacao do [PHP-CPP](http://www.php-cpp.com/) 

`git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git`

`cd PHP-CPP`

`make`

`sudo make install`


## Criar links simbolicos das libs dependentes

sera necessario descobrir o local onde estao as dependencias 
localize uma delas para saber em qual pasta estao os arquivos

`find /usr -name "libxml2.so*"`

a biblioteca abaixo libacbrnfe64.so deve ser adquirida com o pessoal do projeto [ACBR](https://projetoacbr.com.br/acbrlib/) ou voce pode [compila-la](https://www.youtube.com/watch?v=XJvMr3b6rNo&feature=emb_title) como e mostrado nesse video.

para fins de teste estou disponibilizando uma versao do arquivo temporariamente no [dropbox](https://www.dropbox.com/s/51jrad0bm9rp627/libacbrnfe64.so?dl=0)

`sudo wget -O libacbrnfe64.so https://www.dropbox.com/s/51jrad0bm9rp627/libacbrnfe64.so?dl=1` 
(para baixar a biblioteca)

`sudo cp libacbrnfe64.so /usr/lib/x86_64-linux-gnu` 
(para copiar a biblioteca para a pasta do sistema)

`sudo ln -s /usr/lib/x86_64-linux-gnu/libxmlsec1.so.1 /usr/lib/x86_64-linux-gnu/libxmlsec1.so`

`sudo ln -s /usr/lib/x86_64-linux-gnu/libxmlsec1-openssl.so.1 /usr/lib/x86_64-linux-gnu/libxmlsec1-openssl.so`

`sudo ln -s /usr/lib/x86_64-linux-gnu/libxslt.so.1 /usr/lib/x86_64-linux-gnu/libxslt.so`

`sudo ln -s /usr/lib/x86_64-linux-gnu/libxml2.so.2 /usr/lib/x86_64-linux-gnu/libxml.so`

`sudo ln -s /usr/lib/x86_64-linux-gnu/libexslt.so.0 /usr/lib/x86_64-linux-gnu/libexslt.so`

`sudo ln -s /usr/lib/x86_64-linux-gnu/libssl.so.1.0.0 /usr/lib/x86_64-linux-gnu/libssl.so`

`sudo ln -s /usr/lib/x86_64-linux-gnu/libcrypto.so.1.0.0 /usr/lib/x86_64-linux-gnu/libcrypto.so`


## Instalacao da extensao para o php (este projeto):

`git clone https://github.com/billbarsch/acbrlibphp.git`

`cd acbrlibphp`

`sudo make tudo`


# Ajustes

## Ativar modo grafico

### Caso esteja executando em SERVIDOR:

`Xvfb :99 &`

### Caso esteja executando em DESKTOP:

`xhost +` 


# Util

## Local do log de erros do apache:

`cat /var/log/apache2/error.log`
