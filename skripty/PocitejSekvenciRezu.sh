#!/bin/bash

#definice adresarove struktury
NazevSouboru="solution";
BinDir="../bin";
VstupDir="../vstupni_data";
VystupDir="../vystup_gnuplot";
Rez="X";

if [ ! -d $VystupDir ]; then
  echo "Vytavarim adresar $VystupDir";
  mkdir $VystupDir;
fi

for File in {4000..4100..100}
do
	for BodRezu in $(seq 0.01 0.01 0.02)
	do
		echo "Volam program ProvedRez pro $Rez=$BodRezu soubor $VstupDir/$NazevSouboru$File.plt ...";
		$BinDir/ProvedRez $VstupDir/$NazevSouboru$File.plt $Rez=$BodRezu $VystupDir/$NazevSouboru$File-$Rez-$BodRezu.dat;
		echo "Hotovo ...";
	done
done
