#!/bin/bash

# echo -e "il y a $# parametres"

if [ $# -gt 1 ]
then
	echo -e "trop de parametres chef"
	exit ;
elif [ $# = 1 ]
then
	dir=$1
	# echo -e "dir is $dir"
else
	echo -e "Entre le nom du dossier stp:"
	read dir
	# echo "le dossier est: $dir"
fi

if [ ! -d $dir ]
then
	echo -e "$dir n'est pas un dossier..."
	exit ;
fi

if [ ! -e asm ]
then
	echo -e "l'executable asm n'est pas dans le dossier courant"
	exit ;
fi 

liste_fichiers=`ls $dir/*.s`

for fichier in $liste_fichiers
do
        ./asm $fichier
done

# echo -e "TA MERE LE VERRE DE TERRE"
