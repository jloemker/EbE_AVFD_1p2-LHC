#! /bin/bash
HydroNumber=KEYHYDRONUMBER
FONumber=KEYFONUMBER
PLCC=KEYPLCC
bmin=KEYBMIN
bmax=KEYBMAX
Npmin=KEYNPMIN
Npmax=KEYNPMAX
Smin=KEYSMIN
Smax=KEYSMAX
BeamEnergy=KEYBEAMENERGY
AProjTarg=KEYAPROJTARG
ZProjTarg=KEYZPROJTARG

cd KEYDIRECTORY
# Prepare IC for all
rm ./EbEIC/data/*
cd EbEIC
rm data/*
./superMC.e "nev=$HydroNumber" "bmin=$bmin" "bmax=$bmax" "Npmin=$Npmin" "Npmax=$Npmax" "cutdSdy_lowerBound=$Smin" "cutdSdy_upperBound=$Smax" "ecm=$BeamEnergy" "Aproj=$AProjTarg" "Atarg=$AProjTarg" "Zproj=$ZProjTarg" "Ztarg=$ZProjTarg"
./AVFD-IC "$HydroNumber" "$AProjTarg" "$ZProjTarg" "$BeamEnergy"
cd ..

for ((i=1; i<=$HydroNumber; i++)); do
	# Clear result folders
	rm ./AVFD/*.dat
	rm ./AVFD/Initial/*.dat
	rm ./AVFD/results/*.dat
	rm ./iSS_LCC/results/*
	rm ./iSS_LCC/OSCAR.DAT
	rm ./urqmd/OSCAR.input
	rm ./urqmd/particle_list.*
	rm ./urqmd/*.dat
	rm -r ./urqmd/results/*
# now @ job-x/
#	mkdir -p Result/event-$i/animation
	mkdir -p Result/event-$i
	exec 1>Result/event-$i/RunRecord.txt 2>Result/event-$i/ErrorRecord.txt
	mv ./EbEIC/data/sd_event_${i}_block.dat ./AVFD/Initial/InitialSd.dat
	mv ./EbEIC/data/EMField_event_$i.dat ./AVFD/EMField.dat
	cp ./AVFD/Initial/InitialSd.dat ./Result/event-$i/
	cp ./AVFD/EMField.dat ./Result/event-$i/
	cd AVFD
# now @ job-x/AVFD
	# Run VISHNU2+1 Hydro
	./VISHNew.e
	mv ./results/OSCAR2008H.dat ./
	mv ./results/surface.dat ./
	mv ./results/decdat2.dat ./
	# AVFD Component
	./AVFD_Transport
	cd ..
# now @ job-x/
	cp ./AVFD/surface.dat ./iSS_LCC/results/
	cp ./AVFD/decdat2.dat ./iSS_LCC/results/
	cp ./AVFD/surface_mu.dat ./iSS_LCC/results/
	cp ./AVFD/surface.dat ./Result/event-$i/
	cp ./AVFD/decdat2.dat ./Result/event-$i/
	cp ./AVFD/surface_mu.dat ./Result/event-$i/
	# FO_with iSS
	cd iSS_LCC
# now @ job-x/iSS_LCC
	./iSS.e number_of_repeated_sampling=$FONumber local_charge_conservation=$PLCC
	./osc2u.e < OSCAR.DAT
	cd ..
# now @ job-x/
	mv ./iSS_LCC/fort.14 ./urqmd/OSCAR.input
	cd urqmd
# now @ job-x/urqmd
	bash ./runqmd.sh
	python ./urqmdBinShell.py particle_list.dat OSCAR.input
	cd ..
# now @ job-x/
	mv urqmd/results/particle_distribution_final ./Result/event-$i/
	mv urqmd/results/particle_distribution_at_FO ./Result/event-$i/
done