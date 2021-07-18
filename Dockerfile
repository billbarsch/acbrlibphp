FROM ubuntu:20.04 AS acbrlibphpdev

ENV DEBIAN_FRONTEND="noninteractive"

RUN apt-get update

RUN yes "2" | apt install -y \
    git \
    php-dev \
    libxml2 \
    openssl \
    libxmlsec1-openssl \
    libxslt-dev \
    libgtk2.0-0 \
    libcanberra-gtk-module \
    apache2 \
    php \
    libapache2-mod-php \
    xvfb

RUN apt install -y \
    wget

#RUN apt-get install -y \
#    mariadb-client \
#    zip \
#    curl \
#    sudo \
#    unzip \
#    zlib1g-dev \
#    libxpm-dev \
#    libxml2-dev \
#    libzip-dev \
#    libicu-dev \
#    libbz2-dev \
#    libpng-dev \
#    libjpeg-dev \
#    libwebp-dev \
#    libonig-dev \
#    libmcrypt-dev \
#    libreadline-dev \
#    libfreetype6-dev \
#    libcurl4-gnutls-dev \
#    g++ \
#    nano

## 2. apache configs + document root
#ENV APACHE_DOCUMENT_ROOT=/var/www/html/public
#RUN sed -ri -e 's!/var/www/html!${APACHE_DOCUMENT_ROOT}!g' /etc/apache2/sites-available/*.conf
#RUN sed -ri -e 's!/var/www/!${APACHE_DOCUMENT_ROOT}!g' /etc/apache2/apache2.conf /etc/apache2/conf-available/*.conf
## 3. mod_rewrite for URL rewrite and mod_headers for .htaccess extra headers like Access-Control-Allow-Origin-
#RUN a2enmod rewrite headers
## 4. start with base php config, then add extensions
#RUN mv "$PHP_INI_DIR/php.ini-development" "$PHP_INI_DIR/php.ini"
#RUN docker-php-ext-configure gd --enable-gd --with-freetype --with-jpeg --with-webp
#RUN docker-php-ext-install \
#    gd \
#    bz2 \
#    intl \
#    iconv \
#    bcmath \
#    opcache \
#    calendar \
#    mbstring \
#    curl \
#    soap \
#    xml \
#    mysqli \
#    pdo \
#    pdo_mysql \
#    zip

# 5. composer
#COPY --from=composer:latest /usr/bin/composer /usr/bin/composer

WORKDIR /home
RUN git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
WORKDIR /home/PHP-CPP
RUN make
RUN make install

WORKDIR /home
RUN wget -O libacbrnfe64.so https://www.dropbox.com/s/51jrad0bm9rp627/libacbrnfe64.so?dl=1
RUN mv libacbrnfe64.so /usr/lib/x86_64-linux-gnu

RUN ln -s /usr/lib/x86_64-linux-gnu/libxmlsec1.so.1 /usr/lib/x86_64-linux-gnu/libxmlsec1.so
RUN ln -s /usr/lib/x86_64-linux-gnu/libxmlsec1-openssl.so.1 /usr/lib/x86_64-linux-gnu/libxmlsec1-openssl.so
#RUN ln -s /usr/lib/x86_64-linux-gnu/libxslt.so.1 /usr/lib/x86_64-linux-gnu/libxslt.so
RUN ln -s /usr/lib/x86_64-linux-gnu/libxml2.so.2 /usr/lib/x86_64-linux-gnu/libxml.so
#RUN ln -s /usr/lib/x86_64-linux-gnu/libexslt.so.0 /usr/lib/x86_64-linux-gnu/libexslt.so
#RUN ln -s /usr/lib/x86_64-linux-gnu/libssl.so.1.0.0 /usr/lib/x86_64-linux-gnu/libssl.so
#RUN ln -s /usr/lib/x86_64-linux-gnu/libcrypto.so.1.0.0 /usr/lib/x86_64-linux-gnu/libcrypto.so

RUN git clone --progress https://github.com/billbarsch/acbrlibphp.git
WORKDIR /home/acbrlibphp
RUN make tudodocker

RUN cp /home/acbrlibphp/exemplo/teste.php /var/www/html
RUN chown -R www-data:www-data /var/www/html

#CMD ["Xvfb",":99","&"]
CMD [ "sleep", "infinity" ]