@echo off

gcc -o .\galsim.exe .\galsim.c -O3

echo running test
echo N = 10 -----------------
.\galsim.exe 10 .\input_data\ellipse_N_00010.gal 200 0.00001 0

echo compparing results with reference
.\compare_gal_files\comp.exe 10 .\ref_output_data\ellipse_N_00010_after200steps.gal .\result.gal

echo N = 100 -----------------
.\galsim.exe 100 .\input_data\ellipse_N_00100.gal 200 0.00001 0

echo compparing results with reference
.\compare_gal_files\comp.exe 100 .\ref_output_data\ellipse_N_00100_after200steps.gal .\result.gal


echo N = 500 -----------------
.\galsim.exe 500 .\input_data\ellipse_N_00500.gal 200 0.00001 0

echo compparing results with reference
.\compare_gal_files\comp.exe 500 .\ref_output_data\ellipse_N_00500_after200steps.gal .\result.gal