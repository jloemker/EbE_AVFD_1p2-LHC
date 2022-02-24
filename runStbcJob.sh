#!/bin/bash
source /cvmfs/alice.cern.ch/etc/login.sh
#eval $(alienv printenv VO_ALICE@AliPhysics::vAN-20210927-1)
cd ${TMPDIR}
echo ${TMPDIR}
export INPUT_FILES_DIR=/data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround/job-${PBS_ARRAYID}
export LOG_FILES_DIR=/data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround/job-${PBS_ARRAYID}/logs

outputdir=/dcache/alice/jlomker/sim/BField0.8/5.02TeV/Centrality20_30/job-${PBS_ARRAYID}

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
mv ${INPUT_FILES_DIR}/* ${outputdir}/


echo "Anything left?"
ls
echo "Done! Enjoy!"
