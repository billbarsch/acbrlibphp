## Instalacao da extensao:

`git clone https://github.com/billbarsch/acbrlibphp.git`

`cd acbrlibphp`

`sudo make tudo`


## Este projeto requer a instalacao do [PHP-CPP](http://www.php-cpp.com/) 

`sudo apt-get install php-dev`

`git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git`

`cd PHP-CPP`

`make`

`sudo make install`


# Ajustes

## Para conseguir ler a dll pela extensao:

executar no terminal: 

`xhost +` 

para liberar todos a se conectarem no x11


# Util

## Local do log de erros do apache:

`cat /var/log/apache2/error.log`
