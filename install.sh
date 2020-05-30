#!/bin/bash
apt update
apt install git -y
apt install php-dev -y
apt install libxml2 -y
apt install openssl -y
apt install libxmlsec1-openssl -y
apt install libxslt-dev -y
apt install libgtk2.0-0 -y
apt install libcanberra-gtk-module -y
apt install apache2 -y
apt install php libapache2-mod-php -y
apt install xvfb -y
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
make
make install
cd ..
wget -O libacbrnfe64.so https://www.dropbox.com/s/51jrad0bm9rp627/libacbrnfe64.so?dl=1
cp libacbrnfe64.so /usr/lib/x86_64-linux-gnu
ln -s /usr/lib/x86_64-linux-gnu/libxmlsec1.so.1 /usr/lib/x86_64-linux-gnu/libxmlsec1.so
ln -s /usr/lib/x86_64-linux-gnu/libxmlsec1-openssl.so.1 /usr/lib/x86_64-linux-gnu/libxmlsec1-openssl.so
ln -s /usr/lib/x86_64-linux-gnu/libxslt.so.1 /usr/lib/x86_64-linux-gnu/libxslt.so
ln -s /usr/lib/x86_64-linux-gnu/libxml2.so.2 /usr/lib/x86_64-linux-gnu/libxml.so
ln -s /usr/lib/x86_64-linux-gnu/libexslt.so.0 /usr/lib/x86_64-linux-gnu/libexslt.so
ln -s /usr/lib/x86_64-linux-gnu/libssl.so.1.0.0 /usr/lib/x86_64-linux-gnu/libssl.so
ln -s /usr/lib/x86_64-linux-gnu/libcrypto.so.1.0.0 /usr/lib/x86_64-linux-gnu/libcrypto.so
git clone https://github.com/billbarsch/acbrlibphp.git
cd acbrlibphp
sudo make tudo
cp ./exemplo/teste.php /var/www/html
chown -R www-data:www-data /var/www/html
cd ..
Xvfb :99 &