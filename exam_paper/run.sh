if [ -z $1 ]; then
	echo -e "usage ./run.sh noProcesors file"
	echo -e "missing number of processors"
	exit;
fi

if [ -z $2 ]; then
	if [ $2 -eq $2 2>/dev/null ]; then
		echo -e "usage ./run.sh noProcesors file"
		echo -e "missing number of processors"
	else
 		echo -e "missing file name"
	fi
	exit;
fi

TEST="$(echo $1 | grep \\.)"
if [ $TEST ]; then
	echo -e "Leave out .o/.exe"
	exit;
fi

mpirun -np $1 ./$2.o
