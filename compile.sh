#! /bin/bash

cd AVFD_Node

#SuperMC -- MCGlauber Generator
(cp EbEIC/parameters_operation*.dat EbEIC/superMC/)
(rm EbEIC/superMC.e)
(cd EbEIC/superMC; make distclean; make)
if [ ! -f EbEIC/superMC/superMC.e ]; then echo "ERROR!!! Failed to compile superMC"; exit; fi

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

#EMField - distclean is in makefile !
echo "eval $(alienv printenv VO_ALICE@AliPhysics::vAN-20211124_ROOT6-1)"
export PATH=/cvmfs/alice.cern.ch/el6-x86_64/Packages/AliPhysics/vAN-20211124_ROOT6-1/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/treelite/8498081-16/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/RooUnfold/V02-00-01-alice5-38/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/AliRoot/v5-09-57g_ROOT6-1/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/JAliEn-ROOT/0.6.3-6/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/xjalienfs/1.2.8-10/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/Vc/1.4.1-32/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/GEANT4_VMC/v5-0-p5-33/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/GEANT4/v10.5.1-27/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/GEANT3/v3-5-34/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/fastjet/v3.2.1_1.024-alice3-109/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/cgal/4.6.3-82/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/boost/v1.74.0-16/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/DPMJET/v3.0.5-alice5-14/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/ROOT/v6-20-08-alice1-9/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/XRootD/v4.12.5-10/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/libxml2/v2.9.3-32/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/OpenSSL/v1.0.2o-32/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/GSL/v1.16-53/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/lzma/v5.2.3-23/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/Python-modules/1.0-105/share/python-modules/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/Python/v3.6.10-56/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/sqlite/v3.15.0-20/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/libpng/v1.6.34-66/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/FreeType/v2.10.1-27/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/AliEn-Runtime/v2-19-le-110/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/GCC-Toolchain/v7.3.0-alice2-13/bin::/cvmfs/alice.cern.ch/bin:/usr/lib64/qt-3.3/bin:/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin
(cd Heavy-ion_EM_fields; make distclean; make)
if [ ! -f Heavy-ion_EM_fields/EM_fields.e ]; then echo "ERROR!!! Failed to compile EMFields"; exit; fi


