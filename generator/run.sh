g++ gen1.cpp -o gen1
g++ gen2.cpp -o gen2
./gen1 data1.txt
./gen2 data2.txt
python draw.py data1.txt plot1.png
python draw.py data2.txt plot2.png