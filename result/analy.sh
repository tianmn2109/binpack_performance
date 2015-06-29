#!/bin/bash
EXAMPLES_DIR=`ls ../examples`

AL_DIR=`ls -F ../algorithm | grep "/$"`

TARGET="result_analysis"

if [ -d $TARGET_DIR ]
then
	echo "Removing directory $PWD/$TARGET"
fi

echo "Making and entrying directory $PWD/$TARGET"
mkdir $TARGET
cd $TARGET

for dir in $EXAMPLES_DIR
do
	echo "Making result directory"
	mkdir $dir
done
echo "Leaving directory $PWD"
cd ..

echo "Start analy result"

for dir in $AL_DIR
do
	for d in $EXAMPLES_DIR
	do

		OP_DIR="$PWD/../algorithm/${dir/\//}/result/${d/\//}"
		cd $OP_DIR

		files=`ls -tr ../../../../examples/$d`
		echo "Creating file $PWD/packageSize "
		for f in $files
		do
			echo "cat $PWD/../../../../examples/${d/\//}/$f | cut -d " " -f 1 >> packageSize"
			cat $PWD/../../../../examples/${d/\//}/$f | cut -d " " -f 1 >> packageSize
		done

		echo "awk '{print '\$4' >> "$OP_DIR/binNum"; print '\$7' >> "$OP_DIR/fitness"; print '\$10' >> "$OP_DIR/time"}' $OP_DIR/result"
		awk '{print $4 >> "binNum"; print $7 >> "fitness"; print $10 >> "time"}' ./result
		cd -
	done
done

echo "Start collecting results"
for dir in $AL_DIR
do
	for d in $EXAMPLES_DIR
	do
		OP_DIR="$PWD/../algorithm/${dir/\//}/result/${d/\//}"
		echo "cp $OP_DIR/packageSize ./$TARGET/$d/packageSize"
		cp $OP_DIR/packageSize ./$TARGET/$d/packageSize
		echo "cp $OP_DIR/binNum ./$TARGET/$d/binNum_${dir/\//}"
		cp $OP_DIR/binNum ./$TARGET/$d/binNum_${dir/\//}
		echo "cp $OP_DIR/fitness ./$TARGET/$d/fitness_${dir/\//}"
		cp $OP_DIR/fitness ./$TARGET/$d/fitness_${dir/\//}
		echo "cp $OP_DIR/time ./$TARGET/$d/time_${dir/\//}"
		cp $OP_DIR/time ./$TARGET/$d/time_${dir/\//}
	done
done


echo "Analysis the collected files and creating the name.xls file"

DATA_DIR=`ls -F | grep "/$"`
cd $PWD/$DATA_DIR
echo "Entry directory " $PWD/DATA_DIR
RESULT_DIR=`ls -F | grep "/$"`

for d in $RESULT_DIR
do
        cd $d
        echo "Entry directory " $PWD/$d

        echo "Creating temp file .${d/\//}_binNum.tmp"
        T=`ls binNum* | tr '\n' ' '`
        TITLE="packageSize "$T
        echo $TITLE > .${d/\//}_binNum.tmp
        N=`ls binNum*`
        NUM="packageSize "$N
        echo $NUM | xargs paste >> .${d/\//}_binNum.tmp
        ../../produceXLS.py .${d/\//}_binNum.tmp binNum.xls

        echo "Creating temp file .${d/\//}_fitness.tmp"
        T=`ls fitness* | tr '\n' ' '`
        TITLE="packageSize "$T
        echo $TITLE > .${d/\//}_fitness.tmp
        F=`ls fitness*`
        FITNESS="packageSize "$F
        echo $FITNESS | xargs paste >> .${d/\//}_fitness.tmp
        ../../produceXLS.py .${d/\//}_fitness.tmp fitness.xls

        echo "Creating temp file .${d/\//}_time.tmp"
        T=`ls time* | tr '\n' ' '`
        TITLE="packageSize "$T
        echo $TITLE  > .${d/\//}_time.tmp
        TI=`ls time*`
        TIME="packageSize "$TI
        echo $TIME | xargs paste >> .${d/\//}_time.tmp
        ../../produceXLS.py .${d/\//}_time.tmp time.xls

        echo "Leaving directory " $PWD/$d
        cd ..
done

echo "Leaving directory " $PWD/$DATA_DIR
cd ..

