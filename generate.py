#! /usr/bin/env python
EbEAVFD_Parameters = {
    'Projectile/Target'         :   'Pb',
    'Beam Energy'               :   '5020',
    'Job Number'                :   '1000',
    'Hydro Events Per Job'      :   '1',
    'Hadronization Events'      :   '50',
    'Centrality'                :   '20-30%',
    'LCC Ratio'                 :   '0%'   ,
    'Axial Charge Ratio'        :   '0.0'   ,
    'Bfield Life Time'          :   '0.0'   ,
}
from os import path, getcwd, remove, makedirs
from shutil import move, copy, rmtree, copytree
import numpy as np

if path.isdir("./Result"):
    print "Please remove/backup Result Folder First!! Exiting..."
    exit(1)

#####################################################################
#       1. update parameters, determine centrality cut              #
#####################################################################
import EbE_AVFD_Parameters
WorkingDirectory = path.abspath('./PlayGround')
EbEAVFD_Parameters.update(EbE_AVFD_Parameters.EbEAVFD_Parameters)
JobNumber = EbEAVFD_Parameters['Job Number']
HydroEventNumber = EbEAVFD_Parameters['Hydro Events Per Job']
HadronizationEventNumber = EbEAVFD_Parameters['Hadronization Events']
CentralityClass = EbEAVFD_Parameters['Centrality'].split('%')[0]
PLCC = EbEAVFD_Parameters['LCC Ratio'].split('%')[0]
N5_over_s = EbEAVFD_Parameters['Axial Charge Ratio']
Tau_Bfield = EbEAVFD_Parameters['Bfield Life Time']
BeamEnergy = EbEAVFD_Parameters['Beam Energy']
ProjTarg = EbEAVFD_Parameters['Projectile/Target']
if ProjTarg == 'Au':
    a_proj_targ = 197
    z_proj_targ = 79
elif ProjTarg == 'Ru':
    a_proj_targ = 96
    z_proj_targ = 44
elif ProjTarg == 'Zr':
    a_proj_targ = 96
    z_proj_targ = 40
elif ProjTarg == 'Pb':
    a_proj_targ = 208
    z_proj_targ = 82
else:
    print 'Projectile/Target must be Au, Ru, Zr, or Pb! Exiting...'

CutFile = ('./AVFD_Node/ControlFiles/centralityCut_total_entropy_MCGlb%s%s%s.dat'
    %(ProjTarg,ProjTarg,BeamEnergy))

cnt_lower = float(CentralityClass.split('-')[0])
cnt_upper = float(CentralityClass.split('-')[1])

cnt_table = np.loadtxt(CutFile)

lower_idx = (cnt_table[:, 0].searchsorted(cnt_lower+1e-30))
upper_idx = (cnt_table[:, 0].searchsorted(cnt_upper))
s_max = (
    (cnt_table[lower_idx-1, 1] - cnt_table[lower_idx, 1])
    /(cnt_table[lower_idx-1, 0] - cnt_table[lower_idx, 0])
    *(cnt_lower - cnt_table[lower_idx-1, 0])
    + cnt_table[lower_idx-1, 1])
s_min = (
    (cnt_table[upper_idx-1, 1] - cnt_table[upper_idx, 1])
    /(cnt_table[upper_idx-1, 0] - cnt_table[upper_idx, 0])
    *(cnt_upper - cnt_table[upper_idx-1, 0])
    + cnt_table[upper_idx-1, 1])
npart_min = min(cnt_table[lower_idx-1:upper_idx+1, 2])
npart_max = max(cnt_table[lower_idx-1:upper_idx+1, 3])
b_min = min(cnt_table[lower_idx-1:upper_idx+1, 4])
b_max = max(cnt_table[lower_idx-1:upper_idx+1, 5])

print '='*63
print '-'*20,'E-by-E AVFD Generator','-'*20
print '-'*63
print ('|\t%s+%s @ sqrt(s_NN) = %s GeV' %(ProjTarg,ProjTarg,BeamEnergy))
print ('|\t %s (Job) x %s(Hydro) x %s (Hadronization) Events' 
    %(JobNumber, HydroEventNumber, HadronizationEventNumber))
print("|\tCentrality : %g - %g"
    % (cnt_lower, cnt_upper) + r" %")
print "|\tNpart: ", npart_min, '-', npart_max
print "|\tb: ", b_min, '-', b_max, ' fm'
print '|\tn5/s:', N5_over_s
print '|\ttau_B:', Tau_Bfield
print '|\tP_LCC:', PLCC, "%"
print '='*63

AVFDRAWFile = open('./AVFD_Node/ControlFiles/AVFD_Parameter_RAW.py','r')
AVFDFile = open('./AVFD_Node/ControlFiles/AVFD_Parameter.py','w+')
all_lines = AVFDRAWFile.readlines()
AVFDFile.seek(0)
AVFDFile.truncate()
for line in all_lines:
    line = line.replace('N5_OVER_S', N5_over_s)
    line = line.replace('Tau_BField', Tau_Bfield)
    AVFDFile.write(line)
AVFDRAWFile.close()
AVFDFile.close()

#####################################################################
#       2. prepare PlayGround -- Working Directory of AVFD          #
#####################################################################
if path.isdir("./PlayGround"):
    rmtree("./PlayGround")

# Backup Parameter Settings in Result Folder
makedirs("Result/parameters/");
copy("AVFD_Node/ControlFiles/AVFD_Parameter.py", "Result/parameters/")
copy("AVFD_Node/VISHNew/Vishydro.inp", "Result/parameters/")
copy("AVFD_Node/VISHNew/extraParas.inp", "Result/parameters/")
copy("AVFD_Node/iSS_LCC/iSS_parameters.dat", "Result/parameters/")
copy("AVFD_Node/urqmd/uqmd.burner", "Result/parameters/")
# Prepare PlayGround
makedirs("PlayGround/");
makedirs("PlayGround/SRC/AVFD/Initial");
makedirs("PlayGround/SRC/AVFD/results");
makedirs("PlayGround/SRC/iSS_LCC/results");
makedirs("PlayGround/SRC/urqmd/results");
makedirs("PlayGround/SRC/Result");
copytree("AVFD_Node/VISHNew/EOS", "PlayGround/SRC/AVFD/EOS")
copy("AVFD_Node/ControlFiles/AVFD_Parameter.py", "PlayGround/SRC/AVFD/")
# VISHydro + AVFD Transportation
copytree("AVFD_Node/EbEIC", "PlayGround/SRC/EbEIC")
copy("AVFD_Node/VISHNew/VISHNew.e", "PlayGround/SRC/AVFD/")
copy("AVFD_Node/VISHNew/Vishydro.inp", "PlayGround/SRC/AVFD/")
copy("AVFD_Node/VISHNew/extraParas.inp", "PlayGround/SRC/AVFD/")
copy("AVFD_Node/AVFDTransport/AVFD_Transport", "PlayGround/SRC/AVFD/")
# iSS w/ Local Charge Convervation
copytree("AVFD_Node/iSS_LCC/iSS_tables", "PlayGround/SRC/iSS_LCC/iSS_tables")
copy("AVFD_Node/iSS_LCC/iSS.e", "PlayGround/SRC/iSS_LCC/")
copy("AVFD_Node/iSS_LCC/osc2u.e", "PlayGround/SRC/iSS_LCC/")
copy("AVFD_Node/iSS_LCC/iSS_parameters.dat", "PlayGround/SRC/iSS_LCC/")
# UrQMD After-burner
copy("AVFD_Node/urqmd/uqmd.burner", "PlayGround/SRC/urqmd/")
copy("AVFD_Node/urqmd/urqmd.e", "PlayGround/SRC/urqmd/")
copy("AVFD_Node/urqmd/runqmd.sh", "PlayGround/SRC/urqmd/")
copy("AVFD_Node/urqmd/urqmdBinShell.py", "PlayGround/SRC/urqmd/")
copy("AVFD_Node/urqmd/UrqmdOutputFormatter.py", "PlayGround/SRC/urqmd/")

#####################################################################
#    3. prepare run.sh -- bash script to run single AVFD event      #
#####################################################################
comfile = open('./PlayGround/commands.txt','w+')
RUNRAWFile = open('./AVFD_Node/ControlFiles/run_RAW.sh','r')
all_lines = RUNRAWFile.readlines()
for i in range(1,int(JobNumber)+1):
    copytree("./PlayGround/SRC","./PlayGround/job-%d"%i)
    comfile.write("bash %s/job-%d/run.sh; mv %s/job-%d/Result /data/alice/jlomker/EbE_AVFD_1p2-LHC/Result/job-%d\n" 
        %(WorkingDirectory, i, WorkingDirectory, i, i))
    RUNFile = open('./PlayGround/job-%d/run.sh' %i,'w+')
    RUNFile.seek(0)
    RUNFile.truncate()
    for line in all_lines:
        line = line.replace('KEYDIRECTORY', '%s/job-%d' %(WorkingDirectory, i))
        line = line.replace('KEYHYDRONUMBER', HydroEventNumber)
        line = line.replace('KEYFONUMBER', HadronizationEventNumber)
        line = line.replace('KEYPLCC', PLCC)
        line = line.replace('KEYBMIN', '%g' %b_min)
        line = line.replace('KEYBMAX', '%g' %b_max)
        line = line.replace('KEYNPMIN','%g' %npart_min)
        line = line.replace('KEYNPMAX','%g' %npart_max)
        line = line.replace('KEYSMIN', '%g' %s_min)
        line = line.replace('KEYSMAX', '%g' %s_max)
        line = line.replace('KEYBEAMENERGY', '%s' %BeamEnergy)
        line = line.replace('KEYAPROJTARG', '%g' %a_proj_targ)
        line = line.replace('KEYZPROJTARG', '%g' %z_proj_targ)
        RUNFile.write(line)
    RUNFile.close()

#####################################################################
#   4. prepare qsub.pbs -- script to run AVFD events in parallel    #
#####################################################################
    open(path.join(WorkingDirectory, "qsub.pbs"), "w").write(
"""
#!/usr/bin/env bash
#PBS -k o
#PBS -q cpu
#PBS -N EbEAVFD
#PBS -l nodes=1:ppn=%d,walltime=100:00:00
#PBS -m abe
#PBS -j oe

aprun -n %d pcp %s/commands.txt
""" % (int(JobNumber)+1, int(JobNumber)+1, WorkingDirectory)
    )
RUNRAWFile.close()
comfile.close()
