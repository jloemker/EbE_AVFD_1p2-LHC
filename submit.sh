iGroup=1
while [ $iGroup -le 1000 ] 
do 
    outdir=/data/alice/jlomker/EbE_AVFD_1p2-LHC/PlayGround/job-${iGroup}
    if [ ! -d ${outdir} ]
    then
	mkdir -p ${outdir}
	mkdir -p ${outdir}/logs/
    fi
    cp runStbcJob.sh ${outdir}
    cd ${outdir}
    qsub -o ${outdir}/logOut -e ${outdir}/logErr -q generic -t ${iGroup} runStbcJob.sh
    cd -
    let iGroup++
done



