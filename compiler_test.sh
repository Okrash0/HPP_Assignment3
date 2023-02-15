gcc -o ./galsim ./galsim.c -lm

rm times.txt
touch times.txt

echo "------------" >> times.txt
echo "No compiler optimization" >> times.txt
time ./galsim 1000 ./input_data/ellipse_N_01000.gal 200 0.00001 0 >> times.txt

echo "------------" >> times.txt
gcc -o ./galsim ./galsim.c -lm -O3
echo "Compiler optimization O3" >> times.txt
time ./galsim 1000 ./input_data/ellipse_N_01000.gal 200 0.00001 0 >> times.txt

echo "------------" >> times.txt
gcc -o ./galsim ./galsim.c -lm -O2
echo "Compiler optimization O2" >> times.txt
time ./galsim 1000 ./input_data/ellipse_N_01000.gal 200 0.00001 0 >> times.txt
 
echo "------------" >> times.txt
gcc -o ./galsim ./galsim.c -lm -O1
echo "Compiler optimization O1" >> times.txt
time ./galsim 1000 ./input_data/ellipse_N_01000.gal 200 0.00001 0 >> times.txt

echo "------------" >> times.txt
gcc -o ./galsim ./galsim.c -lm -Ofast
echo "Compiler optimization fast" >> times.txt
time ./galsim 1000 ./input_data/ellipse_N_01000.gal 200 0.00001 0 >> times.txt

echo "------------" >> times.txt
gcc -o ./galsim ./galsim.c -lm -march=native -Ofast
echo "Compiler optimization Ofast and march=native" >> times.txt
time ./galsim 1000 ./input_data/ellipse_N_01000.gal 200 0.00001 0 >> times.txt

echo "------------" >> times.txt
gcc -o ./galsim ./galsim.c -lm -march=native -O3
echo "Compiler optimization O3 and march=native" >> times.txt
time ./galsim 1000 ./input_data/ellipse_N_01000.gal 200 0.00001 0 >> times.txt