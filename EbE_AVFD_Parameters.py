#! /usr/bin/env python
EbEAVFD_Parameters = {
	'Projectile/Target'			:	'Pb',
	'Beam Energy'               :   '5020',
	'Job Number'				:	'10',
	'Hydro Events Per Job'		:	'1',
	'Hadronization Events'		: 	'1',
	'Centrality'				:   '20-30%',
	'LCC Ratio'					:	'0.0%'	,
	'Axial Charge Ratio' 		:	'0.0'	,
    'Bfield Life Time'          :   '0.0'   ,
}

#'Projectile/Target'
#		Collision System, must be 'Au', 'Ru', 'Zr', or 'Pb'

#'Beam Energy' 
#		Collision energy \sqrt{s_{NN}}, in unit of GeV

#'Job Number' (e.g. '31')
#		Number of Jobs to be run in parallel

#'Hydro Events Per Job ' (e.g. '1000')
#		Number of hydro events in total

#'Hadronization Events' (e.g. '200')
#		Number of (oversampled) hadronization+UrQMD events per hydro event

#'Centrality Percentage' (e.g. '40-50%')
#		centrality class of the collision

#'LCC Ratio' (e.g. '33%')
#		ratio of LCC particles (particles sampled in pairs in the same FO cell)
#		could from '0%' (no LCC) to '100%' (fully LCC)

#'Axial Charge Ratio' (e.g. '0.1')
#		overall 'n5/s' faction to control chirality imbalance, hence CME strength
#		differs for different centrality range, recommend choices:
#		'0.0' (no CME), '0.05', '0.1', '0.2'

#'Bfield Life Time' (e.g. '0.6')
#		life time of magnetic field, in the unit of fm/c.
