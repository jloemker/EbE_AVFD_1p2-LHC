// ShuzheShi: Turn on for Distribution_Test.

#define RU_SLY4_SPH
/*
	DISTRIBUTION_TEST:
		PB_WS0: Pb, Woods-Saxon, Spheric
		PB_SLY4_SPH: Pb, Sly4, Spheric
		PB_IUFSU_SPH: Pb, IU-FSU, Spheric
		PB_TAMUFSU_SPH: Pb, TAMU-FSU, Spheric

		AU_WS0: Au, Woods-Saxon, Spheric
		AU_WS1: Au, Woods-Saxon, Deformed
		AU_SLY4_SPH: Au, Sly4, Spheric
		AU_IUFSU_SPH: Au, IU-FSU, Spheric
		AU_TAMUFSU_SPH: Au, TAMU-FSU, Spheric

		RU_WS0: Ru, Woods-Saxon, Spheric
		RU_WS1: Ru, Woods-Saxon-1, Deformed
		RU_WS1: Ru, Woods-Saxon-2, Deformed
		RU_SLY4_SPH: Ru, Sly4, Spheric
		RU_IUFSU_SPH: Ru, IU-FSU, Spheric
		RU_TAMUFSU_SPH: Ru, TAMU-FSU, Spheric

		ZR_WS0: Zr, Woods-Saxon, Spheric
		ZR_WS1: Zr, Woods-Saxon-1, Deformed
		ZR_WS1: Zr, Woods-Saxon-2, Deformed
		ZR_SLY4_SPH: Zr, Sly4, Spheric
		ZR_IUFSU_SPH: Zr, IU-FSU, Spheric
		ZR_TAMUFSU_SPH: Zr, TAMU-FSU, Spheric
	DT_DEFORM:
		0: Spheric
		1: Deformed
	DT_WS:
		0: Use new defined distribution
		1: Use Woods-Saxon
*/
// ============== Pb =============== \\
// Pb Woods-Saxon Spheric
#ifdef PB_WS0
	#define DISTRIBUTION_TEST "Pb_WS_Spheric"
	#define DT_NUCLEON_NUMBER 208
	#define DT_PROTON_NUMBER 82
	#define DT_DEFORM 0
	#define DT_WS 1
	#define DT_R 6.3
	#define DT_a 6.2
	#define DT_beta2 0.0
	#define DT_beta4 0.0
#endif
// Pb Sly4 Spheric
#ifdef PB_SLY4_SPH
	#define DISTRIBUTION_TEST "Pb_SLy4_Spheric"
	#define DT_NUCLEON_NUMBER 208
	#define DT_PROTON_NUMBER 82
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 6.8683
	#define DT_DF_n_a 0.522672
	#define DT_DF_n_rho 0.790667
	#define DT_DF_n_c1 -0.0628995
	#define DT_DF_n_c2 -2.84259
	#define DT_DF_n_c3  0.214192
	#define DT_DF_n_c4 -0.933466
	#define DT_DF_n_c5  3.51047
	#define DT_DF_n_c6 -3.03628
	#define DT_DF_n_c7  1.28744
	#define DT_DF_n_c8 -0.317615
	#define DT_DF_n_c9  0.0479752
	#define DT_DF_n_c10 -0.00438652
	#define DT_DF_n_c11  0.00022345
	#define DT_DF_n_c12 -0.00000487497

	#define DT_DF_p_R 7.06336
	#define DT_DF_p_a 0.408799
	#define DT_DF_p_rho 0.465727
	#define DT_DF_p_c1 0.444462
	#define DT_DF_p_c2 -0.627055
	#define DT_DF_p_c3  0.643246
	#define DT_DF_p_c4 -0.932607
	#define DT_DF_p_c5  1.03056
	#define DT_DF_p_c6 -0.626497
	#define DT_DF_p_c7  0.222407
	#define DT_DF_p_c8 -0.0487027
	#define DT_DF_p_c9  0.00668645
	#define DT_DF_p_c10 -0.000561338
	#define DT_DF_p_c11  0.000026357
	#define DT_DF_p_c12 -0.000000530364 

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif
// Pb IU-FSU Spheric
#ifdef PB_IUFSU_SPH
	#define DISTRIBUTION_TEST "Pb_IU-FSU_Spheric"
	#define DT_NUCLEON_NUMBER 208
	#define DT_PROTON_NUMBER 82
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 6.74261
	#define DT_DF_n_a 0.552423
	#define DT_DF_n_rho 0.846073
	#define DT_DF_n_c1 0.00863332
	#define DT_DF_n_c2 -0.411721
	#define DT_DF_n_c3  30.1225
	#define DT_DF_n_c4 -42.2378
	#define DT_DF_n_c5  23.0921
	#define DT_DF_n_c6 -5.36219
	#define DT_DF_n_c7 -0.0472267
	#define DT_DF_n_c8  0.326157
	#define DT_DF_n_c9 -0.0812916
	#define DT_DF_n_c10  0.00966412
	#define DT_DF_n_c11 -0.000585705
	#define DT_DF_n_c12  0.0000145341

	#define DT_DF_p_R 6.94026
	#define DT_DF_p_a 0.420006
	#define DT_DF_p_rho 0.553989
	#define DT_DF_p_c1 0.356332
	#define DT_DF_p_c2 -0.474743
	#define DT_DF_p_c3  0.633899
	#define DT_DF_p_c4 -0.903792
	#define DT_DF_p_c5  0.813363
	#define DT_DF_p_c6 -0.402678
	#define DT_DF_p_c7  0.114031
	#define DT_DF_p_c8 -0.0185832
	#define DT_DF_p_c9  0.00159921
	#define DT_DF_p_c10 -0.0000441001
	#define DT_DF_p_c11 -0.00000280322
	#define DT_DF_p_c12  0.000000170771

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif
// Pb TAMU-FSU Spheric
#ifdef PB_TAMUFSU_SPH
	#define DISTRIBUTION_TEST "Pb_TAMU-FSU_Spheric"
	#define DT_NUCLEON_NUMBER 208
	#define DT_PROTON_NUMBER 82
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 6.96202
	#define DT_DF_n_a 0.584114
	#define DT_DF_n_rho 0.848917
	#define DT_DF_n_c1 0.0260988
	#define DT_DF_n_c2 -1.00559
	#define DT_DF_n_c3  9.56635
	#define DT_DF_n_c4 -13.6142
	#define DT_DF_n_c5  8.72544
	#define DT_DF_n_c6 -3.11816
	#define DT_DF_n_c7  0.663515
	#define DT_DF_n_c8 -0.0825124
	#define DT_DF_n_c9  0.00506673
	#define DT_DF_n_c10 -0.00000419306
	#define DT_DF_n_c11 -0.000016945
	#define DT_DF_n_c12  0.000000658788

	#define DT_DF_p_R 6.98617
	#define DT_DF_p_a 0.422769
	#define DT_DF_p_rho 0.541164
	#define DT_DF_p_c1 0.369123
	#define DT_DF_p_c2 -0.44595
	#define DT_DF_p_c3  0.594533
	#define DT_DF_p_c4 -0.855537
	#define DT_DF_p_c5  0.774691
	#define DT_DF_p_c6 -0.38681
	#define DT_DF_p_c7  0.111267
	#define DT_DF_p_c8 -0.0187005
	#define DT_DF_p_c9  0.00173246
	#define DT_DF_p_c10 -0.0000670348
	#define DT_DF_p_c11 -0.00000106187
	#define DT_DF_p_c12  0.00000011951 

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif

// ============== Au =============== \\
// Au Woods-Saxon Spheric
#ifdef AU_WS0
	#define DISTRIBUTION_TEST "Au_WS_Spheric"
	#define DT_NUCLEON_NUMBER 197
	#define DT_PROTON_NUMBER 79
	#define DT_DEFORM 0
	#define DT_WS 1
	#define DT_R 6.42
	#define DT_a 0.45
	#define DT_beta2 0.0
	#define DT_beta4 0.0
#endif
// Au Woods-Saxon Deformed
#ifdef AU_WS1
	#define DISTRIBUTION_TEST "Au_WS_Deformed"
	#define DT_NUCLEON_NUMBER 197
	#define DT_PROTON_NUMBER 79
	#define DT_DEFORM 1
	#define DT_WS 1
	#define DT_R 6.42
	#define DT_a 0.45
	#define DT_beta2 -0.13
	#define DT_beta4 -0.03
#endif
// Au Sly4 Spheric
#ifdef AU_SLY4_SPH
	#define DISTRIBUTION_TEST "Au_SLy4_Spheric"
	#define DT_NUCLEON_NUMBER 197
	#define DT_PROTON_NUMBER 79
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 6.85004
	#define DT_DF_n_a 0.481062
	#define DT_DF_n_rho 0.756828
	#define DT_DF_n_c1 0.0414091
	#define DT_DF_n_c2 -4.37685
	#define DT_DF_n_c3  8.11705
	#define DT_DF_n_c4 -11.9578
	#define DT_DF_n_c5  10.5546
	#define DT_DF_n_c6 -5.24122
	#define DT_DF_n_c7  1.54356
	#define DT_DF_n_c8 -0.278654
	#define DT_DF_n_c9  0.0306843
	#define DT_DF_n_c10 -0.00194986
	#define DT_DF_n_c11  0.0000613418
	#define DT_DF_n_c12 -0.000000589046

	#define DT_DF_p_R 6.96199
	#define DT_DF_p_a 0.403725
	#define DT_DF_p_rho 0.568664
	#define DT_DF_p_c1 -0.121391
	#define DT_DF_p_c2 -1.21931
	#define DT_DF_p_c3  0.35277
	#define DT_DF_p_c4 -0.38209
	#define DT_DF_p_c5  0.190665
	#define DT_DF_p_c6  0.0767414
	#define DT_DF_p_c7 -0.0885523
	#define DT_DF_p_c8  0.0303034
	#define DT_DF_p_c9 -0.00532276
	#define DT_DF_p_c10  0.000519167
	#define DT_DF_p_c11 -0.0000267198
	#define DT_DF_p_c12  0.000000565729

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif
// Au IU-FSU Spheric
#ifdef AU_IUFSU_SPH
	#define DISTRIBUTION_TEST "Au_IU-FSU_Spheric"
	#define DT_NUCLEON_NUMBER 197
	#define DT_PROTON_NUMBER 79
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 6.72006
	#define DT_DF_n_a 0.506671
	#define DT_DF_n_rho 0.794407
	#define DT_DF_n_c1 0.100507
	#define DT_DF_n_c2 -3.08437
	#define DT_DF_n_c3  5.64473
	#define DT_DF_n_c4 -8.57617
	#define DT_DF_n_c5  7.95302
	#define DT_DF_n_c6 -4.22132
	#define DT_DF_n_c7  1.35181
	#define DT_DF_n_c8 -0.271155
	#define DT_DF_n_c9  0.0342764
	#define DT_DF_n_c10 -0.00264526
	#define DT_DF_n_c11  0.00011334
	#define DT_DF_n_c12 -0.00000205267

	#define DT_DF_p_R 6.80104
	#define DT_DF_p_a 0.424472
	#define DT_DF_p_rho 0.586547
	#define DT_DF_p_c1 0.32413
	#define DT_DF_p_c2 -0.727997
	#define DT_DF_p_c3  1.00252
	#define DT_DF_p_c4 -1.49099
	#define DT_DF_p_c5  1.4333
	#define DT_DF_p_c6 -0.763021
	#define DT_DF_p_c7  0.23671
	#define DT_DF_p_c8 -0.0442626
	#define DT_DF_p_c9  0.00493962
	#define DT_DF_p_c10 -0.00030573
	#define DT_DF_p_c11  0.00000837446
	#define DT_DF_p_c12 -0.0000000256736

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif
// Au TAMU-FSU Spheric
#ifdef AU_TAMUFSU_SPH
	#define DISTRIBUTION_TEST "Au_TAMU-FSU_Spheric"
	#define DT_NUCLEON_NUMBER 197
	#define DT_PROTON_NUMBER 79
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 6.92308
	#define DT_DF_n_a 0.53051
	#define DT_DF_n_rho 0.784658
	#define DT_DF_n_c1 0.126746
	#define DT_DF_n_c2 -2.23157
	#define DT_DF_n_c3  3.82648
	#define DT_DF_n_c4 -5.79515
	#define DT_DF_n_c5  5.40801
	#define DT_DF_n_c6 -2.88327
	#define DT_DF_n_c7  0.928586
	#define DT_DF_n_c8 -0.188036
	#define DT_DF_n_c9  0.0241365
	#define DT_DF_n_c10 -0.00190686
	#define DT_DF_n_c11  0.0000845745
	#define DT_DF_n_c12 -0.00000161054

	#define DT_DF_p_R 6.86502
	#define DT_DF_p_a 0.425077
	#define DT_DF_p_rho 0.564051
	#define DT_DF_p_c1 0.346664
	#define DT_DF_p_c2 -0.700279
	#define DT_DF_p_c3  0.936786
	#define DT_DF_p_c4 -1.3761
	#define DT_DF_p_c5  1.31094
	#define DT_DF_p_c6 -0.689717
	#define DT_DF_p_c7  0.21095
	#define DT_DF_p_c8 -0.0387598
	#define DT_DF_p_c9  0.00422296
	#define DT_DF_p_c10 -0.000251102
	#define DT_DF_p_c11  0.00000620804
	#define DT_DF_p_c12  0.00000000633282

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif

// ============== Ru =============== \\
// Ru Woods-Saxon Spheric
#ifdef RU_WS0
	#define DISTRIBUTION_TEST "Ru_WS_Spheric"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 44
	#define DT_DEFORM 0
	#define DT_WS 1
	#define DT_R 5.09
	#define DT_a 0.46
	#define DT_beta2 0.0
	#define DT_beta4 0.0
#endif
// Ru Woods-Saxon Deformed: Scheme 1
#ifdef RU_WS1
	#define DISTRIBUTION_TEST "Ru_WS1_Deformed"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 44
	#define DT_DEFORM 1
	#define DT_WS 1
	#define DT_R 5.14
	#define DT_a 0.46
	#define DT_beta2 0.13
	#define DT_beta4 0.0
#endif
// Ru Woods-Saxon Deformed: Scheme 2
#ifdef RU_WS2
	#define DISTRIBUTION_TEST "Ru_WS2_Deformed"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 44
	#define DT_DEFORM 1
	#define DT_WS 1
	#define DT_R 5.13
	#define DT_a 0.45
	#define DT_beta2 0.03
	#define DT_beta4 0.009
#endif
// Ru SLy4 Spheric
#ifdef RU_SLY4_SPH
	#define DISTRIBUTION_TEST "Ru_SLy4_Spheric"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 44
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 5.35773
	#define DT_DF_n_a 0.455887
	#define DT_DF_n_rho 0.667865
	#define DT_DF_n_c1 0.13814
	#define DT_DF_n_c2  0.569791
	#define DT_DF_n_c3  0.7492
	#define DT_DF_n_c4 -1.89475
	#define DT_DF_n_c5  1.89262
	#define DT_DF_n_c6 -1.25197
	#define DT_DF_n_c7  0.568169
	#define DT_DF_n_c8 -0.17129
	#define DT_DF_n_c9  0.0332064
	#define DT_DF_n_c10 -0.00395517
	#define DT_DF_n_c11  0.000262826
	#define DT_DF_n_c12 -0.00000745301

	#define DT_DF_p_R 5.38667
	#define DT_DF_p_a 0.435498
	#define DT_DF_p_rho 0.627927
	#define DT_DF_p_c1 0.195016
	#define DT_DF_p_c2  0.31746
	#define DT_DF_p_c3  0.716574
	#define DT_DF_p_c4 -1.66303
	#define DT_DF_p_c5  1.66135
	#define DT_DF_p_c6 -1.08403
	#define DT_DF_p_c7  0.480795
	#define DT_DF_p_c8 -0.141715
	#define DT_DF_p_c9  0.0269533
	#define DT_DF_p_c10 -0.00316014
	#define DT_DF_p_c11  0.000207215
	#define DT_DF_p_c12 -0.00000580774

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif
// Ru IU-FSU Spheric
#ifdef RU_IUFSU_SPH
	#define DISTRIBUTION_TEST "Ru_IU-FSU_Spheric"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 44
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 5.23526
	#define DT_DF_n_a 0.45362
	#define DT_DF_n_rho 0.726381
	#define DT_DF_n_c1 0.00340614
	#define DT_DF_n_c2  55.1016
	#define DT_DF_n_c3  11.7735
	#define DT_DF_n_c4 -59.3516
	#define DT_DF_n_c5  55.5384
	#define DT_DF_n_c6 -43.4352
	#define DT_DF_n_c7  25.5185
	#define DT_DF_n_c8 -9.43538
	#define DT_DF_n_c9  2.10587
	#define DT_DF_n_c10 -0.276383
	#define DT_DF_n_c11  0.0196766
	#define DT_DF_n_c12 -0.000587025

	#define DT_DF_p_R 5.21905
	#define DT_DF_p_a 0.449941
	#define DT_DF_p_rho 0.700392
	#define DT_DF_p_c1 0.0255855
	#define DT_DF_p_c2  6.62007
	#define DT_DF_p_c3  3.74973
	#define DT_DF_p_c4 -11.8669
	#define DT_DF_p_c5  11.9061
	#define DT_DF_p_c6 -8.72592
	#define DT_DF_p_c7  4.53007
	#define DT_DF_p_c8 -1.52343
	#define DT_DF_p_c9  0.319492
	#define DT_DF_p_c10 -0.0402599
	#define DT_DF_p_c11  0.00278919
	#define DT_DF_p_c12 -0.0000816696

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif
// Ru TAMU-FSU Spheric
#ifdef RU_TAMUFSU_SPH
	#define DISTRIBUTION_TEST "Ru_TAMU-FSU_Spheric"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 44
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 5.33007
	#define DT_DF_n_a 0.461333
	#define DT_DF_n_rho 0.720852
	#define DT_DF_n_c1 0.00284618
	#define DT_DF_n_c2  64.9539
	#define DT_DF_n_c3 -0.90482
	#define DT_DF_n_c4 -37.2447
	#define DT_DF_n_c5  29.4578
	#define DT_DF_n_c6 -25.5332
	#define DT_DF_n_c7  17.8108
	#define DT_DF_n_c8 -7.24997
	#define DT_DF_n_c9  1.69594
	#define DT_DF_n_c10 -0.227486
	#define DT_DF_n_c11  0.016331
	#define DT_DF_n_c12 -0.000487491

	#define DT_DF_p_R 5.26958
	#define DT_DF_p_a 0.449612
	#define DT_DF_p_rho 0.690897
	#define DT_DF_p_c1 0.0344422
	#define DT_DF_p_c2  4.80992
	#define DT_DF_p_c3  2.91105
	#define DT_DF_p_c4 -8.96536
	#define DT_DF_p_c5  8.96583
	#define DT_DF_p_c6 -6.49224
	#define DT_DF_p_c7  3.32804
	#define DT_DF_p_c8 -1.10838
	#define DT_DF_p_c9  0.230657
	#define DT_DF_p_c10 -0.0288667
	#define DT_DF_p_c11  0.00198671
	#define DT_DF_p_c12 -0.0000577888

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif

// ============== Zr =============== \\
// Zr Woods-Saxon Spheric
#ifdef ZR_WS0
	#define DISTRIBUTION_TEST "Zr_WS_Spheric"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 40
	#define DT_DEFORM 0
	#define DT_WS 1
	#define DT_R 5.09
	#define DT_a 0.46
	#define DT_beta2 0.0
	#define DT_beta4 0.0
#endif
// Zr Woods-Saxon Deformed: Scheme 1
#ifdef ZR_WS1
	#define DISTRIBUTION_TEST "Zr_WS1_Deformed"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 40
	#define DT_DEFORM 1
	#define DT_WS 1
	#define DT_R 5.07
	#define DT_a 0.48
	#define DT_beta2 0.06
	#define DT_beta4 0.0
#endif
// Zr Woods-Saxon Deformed: Scheme 2
#ifdef ZR_WS2
	#define DISTRIBUTION_TEST "Zr_WS2_Deformed"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 40
	#define DT_DEFORM 1
	#define DT_WS 1
	#define DT_R 5.05
	#define DT_a 0.45
	#define DT_beta2 0.18
	#define DT_beta4 0.01
#endif
// Zr Sly4 Spheric
#ifdef ZR_SLY4_SPH
	#define DISTRIBUTION_TEST "Zr_SLy4_Spheric"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 40
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 5.19252
	#define DT_DF_n_a 0.529498
	#define DT_DF_n_rho 0.776795
	#define DT_DF_n_c1 0.0266407
	#define DT_DF_n_c2  2.78571
	#define DT_DF_n_c3 -0.681842
	#define DT_DF_n_c4 -0.443065
	#define DT_DF_n_c5  1.04578
	#define DT_DF_n_c6 -1.20402
	#define DT_DF_n_c7  0.692266
	#define DT_DF_n_c8 -0.223048
	#define DT_DF_n_c9  0.0428623
	#define DT_DF_n_c10 -0.00492018
	#define DT_DF_n_c11  0.000313562
	#define DT_DF_n_c12 -0.00000858924

	#define DT_DF_p_R 5.3904
	#define DT_DF_p_a 0.427098
	#define DT_DF_p_rho 0.538417
	#define DT_DF_p_c1 0.283364
	#define DT_DF_p_c2  0.337709
	#define DT_DF_p_c3  0.358187
	#define DT_DF_p_c4 -0.933315
	#define DT_DF_p_c5  0.829241
	#define DT_DF_p_c6 -0.512454
	#define DT_DF_p_c7  0.235209
	#define DT_DF_p_c8 -0.0741526
	#define DT_DF_p_c9  0.0150594
	#define DT_DF_p_c10 -0.00186439
	#define DT_DF_p_c11  0.000127645
	#define DT_DF_p_c12 -0.00000370101

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif
// Zr IU-FSU Spheric
#ifdef ZR_IUFSU_SPH
	#define DISTRIBUTION_TEST "Zr_IU-FSU_Spheric"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 40
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 5.21199
	#define DT_DF_n_a 0.486511
	#define DT_DF_n_rho 0.808283
	#define DT_DF_n_c1 -0.0834127
	#define DT_DF_n_c2 -2.59847
	#define DT_DF_n_c3  1.36459
	#define DT_DF_n_c4 -1.05986
	#define DT_DF_n_c5  1.34122
	#define DT_DF_n_c6 -0.511832
	#define DT_DF_n_c7 -0.11161
	#define DT_DF_n_c8  0.136404
	#define DT_DF_n_c9 -0.0424733
	#define DT_DF_n_c10  0.00649937
	#define DT_DF_n_c11 -0.000503176
	#define DT_DF_n_c12  0.0000157812

	#define DT_DF_p_R 5.26697
	#define DT_DF_p_a 0.430761
	#define DT_DF_p_rho 0.620018
	#define DT_DF_p_c1 0.110104
	#define DT_DF_p_c2  1.40989
	#define DT_DF_p_c3  1.48257
	#define DT_DF_p_c4 -3.90539
	#define DT_DF_p_c5  3.91897
	#define DT_DF_p_c6 -2.72658
	#define DT_DF_p_c7  1.31827
	#define DT_DF_p_c8 -0.418126
	#define DT_DF_p_c9  0.084003
	#define DT_DF_p_c10 -0.0102555
	#define DT_DF_p_c11  0.000693479
	#define DT_DF_p_c12 -0.0000199156

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif
// Zr TAMU-FSU Spheric
#ifdef ZR_TAMUFSU_SPH
	#define DISTRIBUTION_TEST "Zr_TAMU-FSU_Spheric"
	#define DT_NUCLEON_NUMBER 96
	#define DT_PROTON_NUMBER 40
	#define DT_DEFORM 0
	#define DT_WS 0

	#define DT_DF_n_R 5.3531
	#define DT_DF_n_a 0.505707
	#define DT_DF_n_rho 0.812627
	#define DT_DF_n_c1 -0.0714293
	#define DT_DF_n_c2 -3.19296
	#define DT_DF_n_c3  2.82366
	#define DT_DF_n_c4 -3.68644
	#define DT_DF_n_c5  4.12487
	#define DT_DF_n_c6 -2.30637
	#define DT_DF_n_c7  0.636156
	#define DT_DF_n_c8 -0.0703709
	#define DT_DF_n_c9 -0.00480953
	#define DT_DF_n_c10  0.00216892
	#define DT_DF_n_c11 -0.000219225
	#define DT_DF_n_c12  0.00000771012

	#define DT_DF_p_R 5.3147
	#define DT_DF_p_a 0.433595
	#define DT_DF_p_rho 0.608277
	#define DT_DF_p_c1 0.120542
	#define DT_DF_p_c2  1.2554
	#define DT_DF_p_c3  1.46789
	#define DT_DF_p_c4 -3.77627
	#define DT_DF_p_c5  3.7925
	#define DT_DF_p_c6 -2.61017
	#define DT_DF_p_c7  1.2419
	#define DT_DF_p_c8 -0.388091
	#define DT_DF_p_c9  0.0769908
	#define DT_DF_p_c10 -0.00929684
	#define DT_DF_p_c11  0.000622422
	#define DT_DF_p_c12 -0.0000177077

	#define DT_DF_n_beta2 0.0
	#define DT_DF_n_beta4 0.0
	#define DT_DF_p_beta2 0.0
	#define DT_DF_p_beta4 0.0
#endif

// ======= Defaulted Option ======= \\
// Woods-Saxon Spheric
#ifdef DISTRIBUTION_TEST
#ifndef DT_DEFORM
	#define DT_DEFORM 0
#endif
#ifndef DT_WS
	#define DT_WS 1
#endif
#endif
/*
#ifdef 
	#define DT_R 
	#define DT_a 
	#define DT_beta2 
	#define DT_beta4 
#endif

*/
// ISOBAR_TEST:
//      11: SLy4_RU
//      12: SLy4_ZR
//      21: CH_RU
//      22: CH_ZR
//      81: WS_1_RU
//      82: WS_1_ZR
//      91: WS_2_RU
//      92: WS_2_ZR