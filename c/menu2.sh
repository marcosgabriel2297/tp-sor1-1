#!/bin/bash
#autor: fd_atanasoff
#fecha: 09/04/2018
#descripcion: menu en bash
#email: fede@fede.com

clear
while :
do
echo "  --------------------------------------"
echo "  ------------ Ejercicios C ------------"
echo "  --------------------------------------"
echo "1. Canto Maradooo"
echo "2. Canto hinchada"
echo "3. Mundial"
echo "4. salir"
echo "- seleccione una opcion -"
read opcion
echo

case $opcion in 
1) ./marado;;
2) ./canto;;
3) ./simulador;;
4) exit;;
*) echo "$opcion no es una opcion valida, intente nuevamente"
echo "presione una tecla para continuar"
read tecla;;
esac
done 
