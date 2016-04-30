TEST="$(echo $1 | grep \\.)"

if [ -z $1 ]; then
	echo -e "usage ./make.sh filename"
	exit;
fi

if [ $TEST ]; then
	echo -e "Leave out .c/.cpp"
	exit;
fi

TEST=$1.cpp
if [ -f $TEST ]; then
	g++ -fopenmp $1.cpp -o $1.o
else
	gcc -fopenmp $1.c -o  $1.o
fi
