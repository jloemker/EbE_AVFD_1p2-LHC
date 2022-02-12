#! /bin/bash

cd AVFD_Node

#SuperMC -- MCGlauber Generator
(cd EbEIC/superMC; make distclean; make; mv superMC.e ../)
if [ ! -f EbEIC/superMC.e ]; then echo "ERROR!!! Failed to compile superMC"; exit; fi

#AVFDInitialCondition -- To Generate I.C. for AVFD Components
(cd EbEIC/AVFDInitial; make clean; make; mv AVFD-IC ../)
if [ ! -f EbEIC/AVFD-IC ]; then echo "ERROR!!! Failed to compile AVFD-IC"; exit; fi

#VISH
(cd VISHNew; make clean; make)
if [ ! -f VISHNew/VISHNew.e ]; then echo "ERROR!!! Failed to compile VISHNew"; exit; fi

#AVFDTransport
(cd AVFDTransport; make distclean; make)
if [ ! -f AVFDTransport/AVFD_Transport ]; then echo "ERROR!!! Failed to compile AVFDTransport"; exit; fi

#iSS
(cd iSS_LCC; make distclean; make)
if [ ! -f iSS_LCC/iSS.e ]; then echo "ERROR!!! Failed to compile iSS_LCC"; exit; fi

#osc2u -- Format Converter from OSCAR to UrQMD
(cd iSS_LCC/osc2u; make distclean; make; mv osc2u.e ../)
if [ ! -f iSS_LCC/osc2u.e ]; then echo "ERROR!!! Failed to compile osc2u"; exit; fi

#urqmd
(cd urqmd; make distclean; make)
if [ ! -f urqmd/urqmd.e ]; then echo "ERROR!!! Failed to compile urqmd"; exit; fi