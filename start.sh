#!/bin/bash
Xvfb :99 &
#/usr/sbin/apache2 -D FOREGROUND &
service apache2 start 
sleep infinity
#/bin/bash