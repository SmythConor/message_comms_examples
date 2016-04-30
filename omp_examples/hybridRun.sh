if [ -z $1 ]; then
	echo -e "usage ./run.sh file"
	exit;
fi

TEST="$(echo $1 | grep \\.)"
if [ $TEST ]; then
	echo -e "Leave out .o/.exe"
	exit;
fi

./$1.o
