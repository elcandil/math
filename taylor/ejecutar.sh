#!/bin/bash
# El array applications contiene las aplicaciones que quiero compilar y ejecutar
# Son aplicaciones con un unico fuente (extensión .c)
# Si cada aplicación tuviera varios fuentes
# Habria que proceder de otro modo.
echo "--------------------------------------"
echo "usage: ./ejecutar.sh [clang]          "
echo "--------------------------------------"


nargs=$#;
echo "--------------------------------------"
if [ $nargs -eq 0 ]
then
    echo "--> no arguments, using GCC"
    COMPILER=gcc
else 
    echo "--> trying the "$1" compiler"
    COMPILER=$1;
fi

################################################################################
# Aplicaciones de este directorio
################################################################################

applications=(lnx)

echo "--------------------------------------"
echo "--> Applications: "${applications[@]}
echo "--------------------------------------"

################################################################################
# Script para lanzar a ejecución (lanza las aplicaicones con parametros)
################################################################################

launch_script="./ejecutar-lnx.sh"

echo "--------------------------------------"
echo "--> Script experiments: "${launc_script}}
echo "--------------------------------------"

# compilamos primero los fuentes usando nuestro makefile 

echo "--------------------------------------"
for app in ${applications[@]}; do
    echo "--> Compiling "${app}" with "${COMPILER}" ..."
    make SRC=${app}.c CC=${COMPILER}
done
echo "--------------------------------------"
echo "--> Setting OpenMP environment: "
echo "--> OMP_NUM_THREADS=4"
export OMP_NUM_THREADS=4
echo "--------------------------------------"
echo "launching script = "${launch_script}
echo "--------------------------------------"

for app in ${applications[@]}; do
    echo "--> Trying "${app}
    ${launch_script} ./${app}.${COMPILER}
done
echo "--------------------------------------"

