#!/bin/bash
#------------------------------------------------------
# PALETA DE COLORES
#------------------------------------------------------
#setaf para color de letras/setab: color de fondo
	red=`tput setaf 1`;
	green=`tput setaf 2`;
	blue=`tput setaf 4`;
	bg_blue=`tput setab 4`;
	reset=`tput sgr0`;
	bold=`tput setaf bold`;
#------------------------------------------------------
# VARIABLES GLOBALES
#------------------------------------------------------
proyectoActual="/home/fedeatanasoff/Documentos/bash/tp";
proyectos="/home/fedeatanasoff/Documentos/bash/tp/repos.txt";

#------------------------------------------------------
# DISPLAY MENU
#------------------------------------------------------
imprimir_menu () {
       imprimir_encabezado "\t  S  U  P  E  R  -  M  E  N U ";
	
    echo -e "\t\t El proyecto actual es:";
    echo -e "\t\t $proyectoActual";
    
    echo -e "\t\t";
    echo -e "\t\t Opciones:";
    echo "";
    echo -e "\t\t\t a.  Ver estado del proyecto";
    echo -e "\t\t\t b.  Guardar cambios";
    echo -e "\t\t\t c.  Actualizar repositorio";    
    echo -e "\t\t\t d.  Buscar programa ";
    echo -e "\t\t\t e.  Buscar archivos";
    echo -e "\t\t\t f.  Buscar string en un archivo";    
    echo -e "\t\t\t q.  Salir";
    echo "";
    
}


 imprimir_opcion_b (){
	echo -e "\t\t";
	echo -e "\t\t Elija un comando a ejecutar:";
	echo "";
	echo -e "\t\t\t a. git add -A ";
	echo -e "\t\t\t b. git commit -m "mensaje" ";
    	echo -e "\t\t\t c. git push ";
	echo -e "\t\t\t q. Salir";
    	echo "";
    	echo -e "Escriba la opción y presione ENTER";
}


#------------------------------------------------------
# FUNCTIONES AUXILIARES
#------------------------------------------------------

imprimir_encabezado () {
    clear;
    #Se le agrega formato a la fecha que muestra
    #Se agrega variable $USER para ver que usuario está ejecutando
    echo -e "`date +"%d-%m-%Y %T" `\t\t\t\t\t USERNAME:$USER";
    echo "";
    #Se agregan colores a encabezado
    echo -e "\t\t ${bg_blue} ${red} ${bold}--------------------------------------\t${reset}";
    echo -e "\t\t ${bold}${bg_blue}${red}$1\t\t${reset}";
    echo -e "\t\t ${bg_blue}${red} ${bold} --------------------------------------\t${reset}";
    echo "";
}

esperar () {
    echo "";
    echo -e "Presione enter para continuar";
    read ENTER ;
}

malaEleccion () {
    echo -e "Selección Inválida ..." ;
}

decidir () {
	echo $1;
	while true; do
		echo "desea ejecutar? (s/n)";
    		read respuesta;
    		case $respuesta in
        		[Nn]* ) break;;
       			[Ss]* ) eval $1
				break;;
        		* ) echo "Por favor tipear S/s ó N/n.";;
    		esac
	done
}

agregarMensajeCommit () {
echo -e "\t Agregue descripcion/mensaje que llevara el commit";
read respuesta;
decidir "cd $proyectoActual; git commit -m $respuesta" ;
}

#------------------------------------------------------
# FUNCIONES del MENU
#------------------------------------------------------
a_funcion () {
    	imprimir_encabezado "\tOpción a.  Ver estado del proyecto";
    	decidir "cd $proyectoActual; git status";
}

b_funcion () {
       	imprimir_encabezado "\tOpción b.  Guardar cambios";
while true;
do	

    # muestra las opciones
    imprimir_opcion_b;
    read opB;
    
    case $opB in
        a|A) decidir  "cd $proyectoActual; git add -A";;
        b|B) agregarMensajeCommit;;
        c|C) decidir  "cd $proyectoActual; git push -u origin master";;
        q|Q) break;;
        *) malaEleccion;;
    esac
done
 
}

c_funcion () {
      	imprimir_encabezado "\tOpción c.  Actualizar repositorio";
	
	echo -e "Actualizar repositorio";
      	decidir "cd $proyectoActual; git pull";
}

d_funcion () {
           imprimir_encabezado "\tOpción d. Buscar si un programa esta instalado";
            read paquete
            if dpkg -l | grep -w $paquete; then
                echo "el programa $paquete se encuenta instalado"
            else
                echo "el programa $paquete no se encuentra instalado"
            fi
}

e_funcion () {
          imprimir_encabezado "\tOpción e. Buscar archivos por nombre y extension en un directorio especifico";
            echo "ingrese path"
            read path
            echo "ingresar extencion"
            read extencion 
            echo "ingrese nombre"
            read nombre

            if  find $path -name "*.$extencion" | grep -i $nombre > archivos.txt; then
                cat -b archivos.txt
            else
                echo "no se encontro el archivo con la busqueda deseada"
            fi    
}

f_funcion () {
    imprimir_encabezado "\tOpción d. Buscar string en un archivo";
        echo "ingrese el path del archivo"
        read path
        echo "ingresar string"
        read palabra 
        cat $path | grep -n $palabra >> salida.out 
        echo "-------" >> salida.out
        cat salida.out
}

#------------------------------------------------------
# LOGICA PRINCIPAL
#------------------------------------------------------
while  true
do
    # 1. mostrar el menu
    imprimir_menu;
    # 2. leer la opcion del usuario
    read opcion;
    
    case $opcion in
        a|A) a_funcion;;
        b|B) b_funcion;;
        c|C) c_funcion;;
        d|D) d_funcion;;
        e|E) e_funcion;;
        f|F) f_funcion;;
        q|Q) break;;
        *) malaEleccion;;
    esac
    esperar
done
 
