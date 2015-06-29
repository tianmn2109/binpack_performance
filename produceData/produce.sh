#!/bin/bash
confFiles=`ls conf`
if [ ! -d ../examples ]
then
	echo "Creating directory examples"
	mkdir ../examples
fi
cd ../examples
echo "Entry directory " $PWD
echo "Removing previous examples"
rm -rf *

for d in $confFiles
do
	echo "Making output directory " $d
	mkdir $d
done

cd ../produceData
echo "Entry directory " $PWD
	
echo "Entry ./random and execute make "
cd ./random && make && cd ..

for f in $confFiles
do
	PRODUCE_NUM=`cat ./conf/$f | cut -d " " -f 1`
	outDir=`cat ./conf/$f | cut -d " " -f 2`
	outMaxBins=`cat ./conf/$f | cut -d " " -f 3`
	outCapacity=`cat ./conf/$f | cut -d " " -f 4`
	outMinRange=`cat ./conf/$f | cut -d " " -f 5`
	outMaxRange=`cat ./conf/$f | cut -d " " -f 6`
	for ((i=1; i <= $PRODUCE_NUM; i ++))
	do
		outName=../examples/$outDir/$i.txt
		echo "Creating random data file $PWD/$outName"
		sleep 1
		./random/random $outName $outMaxBins $outCapacity $outMinRange $outMaxRange
	done
done

