gcc -o compare_gal_files/comp compare_gal_files/compare_gal_files.c -lm -Ofast
gcc -o ./galsim ./galsim.c -lm

echo running test
echo N = 10 -----------------
./galsim 10 ./input_data/ellipse_N_00010.gal 200 0.00001 0

echo compparing results with reference
./compare_gal_files/comp 10 ./ref_output_data/ellipse_N_00010_after200steps.gal ./result.gal

echo N = 100 -----------------
./galsim 100 ./input_data/ellipse_N_00100.gal 200 0.00001 0

echo compparing results with reference
./compare_gal_files/comp 100 ./ref_output_data/ellipse_N_00100_after200steps.gal ./result.gal


echo N = 500 -----------------
./galsim 500 ./input_data/ellipse_N_00500.gal 200 0.00001 0

echo compparing results with reference
./compare_gal_files/comp 500 ./ref_output_data/ellipse_N_00500_after200steps.gal ./result.gal

echo N = 2000 -----------------
./galsim 2000 ./input_data/ellipse_N_02000.gal 200 0.00001 0

echo compparing results with reference
./compare_gal_files/comp 2000 ./ref_output_data/ellipse_N_02000_after200steps.gal ./result.gal

echo N = 3000 -----------------
./galsim 3000 ./input_data/ellipse_N_03000.gal 100 0.00001 0

echo compparing results with reference
./compare_gal_files/comp 3000 ./ref_output_data/ellipse_N_03000_after100steps.gal ./result.gal