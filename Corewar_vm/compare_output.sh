#!/bin/bash

if [ $# -gt 1 ]
then
	echo -e "trop de parametres chef"
	exit ;
elif [ $# = 1 ]
then
	file=$1
	# echo -e "file is $file"
else
	echo -e "Entre le nom du .cor stp:"
	read file
fi
	# echo -e "le champion est: $file"

if [ ! -e $file ]
then
	echo -e "le fichier $file n'existe pas"
	exit ;
fi

./corewar -v 31 $file > ret 
../source/corewar -v 31 $file > ../source/ret

diff=`diff ret ../source/ret`
if [ -z $diff]
then
	echo -e "Pas de difference. GG!"
else
	echo -e "$diff"
fi