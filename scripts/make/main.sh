#!/bin/bash

compile_src() {
	echo -e "\033[1;33mCompiling src..."

	local files=$(ls ./src/*.cpp)
	local files_count=$(ls ./src/*.cpp | wc -l)

	mkdir -p ./objects/

	local i=0
        for file in $files; do
                i=$((i+1))
		echo -en "\033[1;0m * \033[1;31mCompiling: \033[1;0m$file..."
		echo -e "\033[1;32m [$i/$files_count]"

                g++ -c $file -o ./objects/$(basename $file .cpp).o -I./include/
        done
}

compile_libs() {
	echo -e "\033[1;33mCompiling libs..."

	local files=$(find ./src/eng/ -name "*.cpp")
	local files_count=$(find ./src/eng/ -name "*.cpp" | wc -l)

	mkdir -p ./objects/

	local i=0
        for file in $files; do
                i=$((i+1))
		echo -en "\033[1;0m * \033[1;31mCompiling: \033[1;0m$file..."
		echo -e "\033[1;32m [$i/$files_count]"

                g++ -c $file -o ./objects/eng_$(basename $file .cpp).o -Iinclude/
        done
}

link() {
        echo -e "\033[1;33mLinking..."
	
	g++ ./objects/*.o -o ./raytracer \
		-Wl,-rpath=./lib \
		-L./lib/ -lsfml-graphics -lsfml-window -lsfml-system
}

compile_shaders() {
	echo -e "\033[1;33mCompiling shaders..."
	python3 ./scripts/make/compile_shaders.py
}

clean_objects() {
        rm -rf ./objects
}

clean() {
	rm ./raytracer
}

build() {
	compile_src
	compile_libs
	compile_shaders

	link

	clean_objects
	
	echo -e "\033[1;0m"
}

run() {
	clear
	./raytracer
}

main() {
	for callback in "$@"; do $callback; done
}

main $@ 
