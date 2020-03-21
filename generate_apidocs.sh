#!/bin/sh
# vim: syntax=sh
doxygen doxygen/Doxyfile
cp doxygen/html/shutf8_8h.html docs/index.html
cp doxygen/html/shutf8_8h_source.html docs/
cp doxygen/html/*.png docs/
cp doxygen/html/*.css docs/

