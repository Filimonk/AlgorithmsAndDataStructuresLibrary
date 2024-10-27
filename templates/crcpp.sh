#!/bin/bash

# добавить проверку на 1 аргумент, позже можно сделать команду с флагами (диапозон, размножение, помощь; не создавать cpp файл, если уже существует файл с таким названием, заисключением случаев с наличием флага силы -f; отбрасывать расширение .cpp)
mkdir -p buildCpp
cp ~/.local/templates/MakefileCpp ./buildCpp/MakefileCpp_$1
sed -i s/place_to_insert_name/$1/ ./buildCpp/MakefileCpp_$1
cp ~/.local/templates/programTemplateCpp.cpp ./$1.cpp