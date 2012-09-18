#!/bin/sh
cd ../LibPkg/\!LibPkg && \
../../../../../gccsdk412/env/ro-make clean &&\
../../../../../gccsdk412/env/ro-make -j8 &&\
cd ../../packman/ &&\
../../../../gccsdk412/env/ro-make clean &&\
../../../../gccsdk412/env/ro-make -j8 &&\
../../../../gccsdk412/env/ro-make -f RiscPkg/Rules &&\
cp RiscPkg/PackMan_0* ../packages/autobuilder_packages/Admin/ &&\
cp RiscPkg/PackMan_0.7-1.zip /home/atm26/public_html/ephemeral/packman07.zip && \
cd ../packages && \
./build-website &&\
 ./build-index &&\
rsync -av autobuilder_website/ tmarkettos@packages.riscosopen.org:/var/www/packages/

 
