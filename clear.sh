#! /bin/bash

cd AVFD_Node

#SuperMC -- MCGlauber Generator
(cd EbEIC/superMC; make distclean)

#AVFDInitialCondition -- To Generate I.C. for AVFD Components
(cd EbEIC/AVFDInitial; make clean)

#VISH
(cd VISHNew; make clean)

#AVFDTransport
(cd AVFDTransport; make distclean)

#iSS
(cd iSS_LCC; make distclean)

#osc2u -- Format Converter from OSCAR to UrQMD
(cd iSS_LCC/osc2u; make distclean)

#urqmd
(cd urqmd; make distclean)