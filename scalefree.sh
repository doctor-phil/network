#!/bin/bash

if [ "$1" != "" ]; then
    ./scalefree $1
else
    ./scalefree
fi

Rscript plotgraph.r
xdg-open Rplots.pdf
