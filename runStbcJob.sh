#!/bin/bash
source /cvmfs/alice.cern.ch/etc/login.sh
#eval $(alienv printenv VO_ALICE@AliPhysics::vAN-20210927-1)
cd ${TMPDIR}
echo ${TMPDIR}
export INPUT_FILES_DIR=/data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround/job-${PBS_ARRAYID}
#export INPUT_FILES_DIR=/data/alice/jlomker/EbE_AVFD_1p2-LHC/testplayground/PlayGround/job-${PBS_ARRAYID}
#export Output=/data/alice/jlomker/EbE_AVFD_1p2-LHC/testplayground/PlayGround/job-${PBS_ARRAYID}/Result/event-1

export Output=/data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround/job-${PBS_ARRAYID}/Result/event-1

export LOG_FILES_DIR=/data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround/job-${PBS_ARRAYID}/logs

outputdir=/dcache/alice/jlomker/sim/tau_init0.9/BField0.2/Centrality30_40/job-${PBS_ARRAYID}/Result/event-1

#Go to the directory
cd ${INPUT_FILES_DIR}
pwd
ls

##run the simulation
echo "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
bash run.sh
#if [ ! -d particle_distribution_final ]; then
#        echo "Failed, trying again"
#        source run.sh
#fi
#if [ ! -d particle_distribution_final ]; then
#        echo "Failed yet again. Second time's the charm"
#        source run.sh
#fi
#if [ ! -d particle_distribution_final ]; then
#        echo "Failed yet again. Third time's the charm"
#        source run.sh
#fi
#if [ ! -d particle_distribution_final ]; then
#        echo "Forget it. Clean tree output up, this is bogus, sorry"
#        rm */*.dat
#fi
echo "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"

#Create the output directory
mkdir -p ${outputdir}

#Move the logs + the output to dcache
mv ${LOG_FILES_DIR}/* ${outputdir}/
mv ${Output}/* ${outputdir}/


echo "Anything left?"
ls
echo "Done! Enjoy!"
