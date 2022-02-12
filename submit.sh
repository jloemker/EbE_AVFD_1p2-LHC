#PBS-q batch
#source /cvmfs/alice.cern.ch/etc/login.sh
iGroup=1
while [ $iGroup -le 10 ] 
do 
    outdir=/data/alice/jlomker/EbE_AVFD_1p2-LHC/Result/job-${iGroup}
    workdir=/data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround/job-${iGroup}
    if [ ! -d ${outdir} ]
    then
	mkdir -p ${outdir}
	mkdir -p ${outdir}/logs/
    fi
    cp /data/alice/jlomker/EbE_AVFD_1p2-LHC/runStbcJob.sh ${workdir}
    cd ${workdir}
    qsub -o ${outdir}/logs/logOut -e ${outdir}/logs/logErr -q generic -t ${iGroup} runStbcJob.sh
    cd -
    let iGroup++
done



