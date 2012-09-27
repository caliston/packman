#!/bin/sh
cd ../tbx && \
../../../../gccsdk412/env/ro-make clean &&\
../../../../gccsdk412/env/ro-make -j8 &&\
cd ../LibPkg/\!LibPkg && \
../../../../../gccsdk412/env/ro-make clean &&\
../../../../../gccsdk412/env/ro-make -j8 &&\
cd ../../packman/ &&\
../../../../gccsdk412/env/ro-make clean &&\
../../../../gccsdk412/env/ro-make -j8 &&\
../../../../gccsdk412/env/ro-make -f RiscPkg/Rules &&\
cp RiscPkg/PackMan_0* ../packages/autobuilder_packages/Admin/ &&\
cp RiscPkg/PackMan_0.7-4.zip /home/atm26/public_html/ephemeral/packman07.zip && \
pushd ../packages && \
./build-website &&\
 ./build-index &&\
popd
#rsync -av autobuilder_website/ tmarkettos@packages.riscosopen.org:/var/www/packages/
scp RiscPkg/PackMan_0.7-4.zip tmarkettos@packages.riscosopen.org:gccsdk412/autobuilder/autobuilder_packages/Admin/
ssh tmarkettos@packages.riscosopen.org "cd gccsdk412/autobuilder; ./build-website; mv autobuilder_website/pkg/autobuilt autobuilder_website/pkg/raspberrypi-system; rsync -av autobuilder_website/ /var/www/packages/"


 
