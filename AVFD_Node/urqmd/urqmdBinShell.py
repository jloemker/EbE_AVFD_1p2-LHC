#! /usr/bin/env python2

from sys import argv
from os import unlink, rename, path, makedirs
from shutil import rmtree
from subprocess import call
import UrqmdOutputFormatter
#Shuzhe added more imported functions

resFolder = "./results"
tmpFile = "./results/tmp.dat"
tmpFileSp = "./results/particle_distribution_final/%d.dat"
tmpFileSpFO = "./results/particle_distribution_at_FO/%d.dat"

if len(argv) < 3:
    print("Usage: shell.py urqmd_output_file urqmd_input_file")
    exit(-1)

# format urqmd output file
if UrqmdOutputFormatter.formatUrqmdOutputFile(argv[1], tmpFile):
    makedirs("./results/particle_distribution_final")
    # Shuzhe added Spliter
    UrQMDCounter = UrqmdOutputFormatter.SplitTMPFile( tmpFile, tmpFileSp )

# format urqmd input file
if UrqmdOutputFormatter.formatUrqmdInputFile(argv[2], tmpFile):
    makedirs("./results/particle_distribution_at_FO")
    # Shuzhe added Spliter
    UrQMDCounter = UrqmdOutputFormatter.SplitTMPFile( tmpFile, tmpFileSpFO )
