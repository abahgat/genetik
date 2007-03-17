`echo $1 | grep .cpp > /dev/null` || OBJ_PREFIX=$1;

for src in $* 
do
	if `echo $src | grep .cpp > /dev/null` 
		then
			g++ -MM -MT $OBJ_PREFIX`echo $src | sed -e s/.cpp/.o/g` $src;
		fi
done
