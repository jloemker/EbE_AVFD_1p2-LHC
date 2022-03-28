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
cd superMC
rm data/*
cd src
rm data/*
cd ..
mv parameters_operation2.dat parameters.dat
./superMC.e "nev=$HydroNumber" "bmin=$bmin" "bmax=$bmax" "Npmin=$Npmin" "Npmax=$Npmax" "cutdSdy_lowerBound=$Smin" "cutdSdy_upperBound=$Smax" "ecm=$BeamEnergy" "Aproj=$AProjTarg" "Atarg=$AProjTarg" "Zproj=$ZProjTarg" "Ztarg=$ZProjTarg"
mv parameters_operation3.dat parameters.dat
./superMC.e "nev=$HydroNumber" "bmin=$bmin" "bmax=$bmax" "Npmin=$Npmin" "Npmax=$Npmax" "cutdSdy_lowerBound=$Smin" "cutdSdy_upperBound=$Smax" "ecm=$BeamEnergy" "Aproj=$AProjTarg" "Atarg=$AProjTarg" "Zproj=$ZProjTarg" "Ztarg=$ZProjTarg"
cd ..
cp ./superMC/data/*.dat ./data/ 
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
	mv ./movie/Evolution.dat ./VISHNUmovie_evolution.dat
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
	cp ./AVFD/VISHNUmovie_evolution.dat ./Result/event-$i/
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
# now @ job-x/ preparing EM field evolution script
	cp ./EbEIC/superMC/data/spectator_density_A_fromSd_order_2_block.dat ./Heavy-ion_EM_fields/results/spectator_density_A_fromSd_order_2.dat
	cp ./EbEIC/superMC/data/spectator_density_B_fromSd_order_2_block.dat ./Heavy-ion_EM_fields/results/spectator_density_B_fromSd_order_2.dat
	cp ./EbEIC/superMC/data/nuclear_thickness_TA_fromSd_order_2_block.dat ./Heavy-ion_EM_fields/results/nuclear_thickness_TA_fromSd_order_2.dat
	cp ./EbEIC/superMC/data/nuclear_thickness_TB_fromSd_order_2_block.dat ./Heavy-ion_EM_fields/results/nuclear_thickness_TB_fromSd_order_2.dat
	cp ./Result/event-$i/*.dat ./Heavy-ion_EM_fields/results/	
	# loop over all possible modes !
	cd Heavy-ion_EM_fields
	eval $(alienv printenv VO_ALICE@AliPhysics::vAN-20211124_ROOT6-1)
	export PATH=/cvmfs/alice.cern.ch/el6-x86_64/Packages/AliPhysics/vAN-20211124_ROOT6-1/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/treelite/8498081-16/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/RooUnfold/V02-00-01-alice5-38/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/AliRoot/v5-09-57g_ROOT6-1/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/JAliEn-ROOT/0.6.3-6/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/xjalienfs/1.2.8-10/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/Vc/1.4.1-32/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/GEANT4_VMC/v5-0-p5-33/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/GEANT4/v10.5.1-27/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/GEANT3/v3-5-34/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/fastjet/v3.2.1_1.024-alice3-109/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/cgal/4.6.3-82/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/boost/v1.74.0-16/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/DPMJET/v3.0.5-alice5-14/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/ROOT/v6-20-08-alice1-9/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/XRootD/v4.12.5-10/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/libxml2/v2.9.3-32/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/OpenSSL/v1.0.2o-32/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/GSL/v1.16-53/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/lzma/v5.2.3-23/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/Python-modules/1.0-105/share/python-modules/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/Python/v3.6.10-56/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/sqlite/v3.15.0-20/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/libpng/v1.6.34-66/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/FreeType/v2.10.1-27/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/AliEn-Runtime/v2-19-le-110/bin:/cvmfs/alice.cern.ch/el6-x86_64/Packages/GCC-Toolchain/v7.3.0-alice2-13/bin::/cvmfs/alice.cern.ch/bin:/usr/lib64/qt-3.3/bin:/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin
	./EM_fields.e
	cd ..
	cp ./Heavy-ion_EM_fields/results/surface_with_drifting_velocity.dat ./Result/event-$i/
	cp ./Heavy-ion_EM_fields/results/check_lrf_EMfields.dat ./Result/event-$i/
	cp ./Heavy-ion_EM_fields/results/check_lrf_velocity.dat ./Result/event-$i/
	# Note: could be that decdt.dat and surface.dat change in EM calculation!
	#cp ./Heavy-ion_EM_fields/results/*.dat ./Result/event-$i/
done

