#!/bin/bash
#source /data/alice/jlomker/EbE_AVFD_1p2-LHC/submit.sh
#source /cvmfs/alice.cern.ch/etc/login.sh
#eval $(alienv printenv VO_ALICE@AliPhysics::vAN-20210927-1)

export i=${PBS_ARRAYID}
INPUT_DIR=/data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround/job-$i
#create final results directory
mkdir -p /dcache/alice/jlomker/TestProduction/job-$i
#Go to the working directory
cd /data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround/job-$i
pwd
ls

##run the simulation
echo "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
source run.sh
if [ ! -d particle_distribution_final ]; then
        echo "Failed, trying again"
        source run.sh
fi
if [ ! -d particle_distribution_final ]; then
        echo "Failed yet again. Second time's the charm"
        source run.sh
fi
if [ ! -d particle_distribution_final ]; then
        echo "Failed yet again. Third time's the charm"
        source run.sh
fi
if [ ! -d particle_distribution_final ]; then
        echo "Forget it. Clean tree output up, this is bogus, sorry"
        rm */*.dat
fi
echo "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"

#cd /data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround
#Move the results to dcache
mv /data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround/job-$i/Result /dcache/alice/jlomker/TestProduction/job-$i

#mv /data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround/job-$i /dcache/alice/jlomker/TestProduction/job-$i

echo "Anything left?"
ls
echo "Done! Enjoy!"
