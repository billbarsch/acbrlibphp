#!/bin/bash
Xvfb :99 &
service apache2 start &
sleep infinity
#/bin/bash