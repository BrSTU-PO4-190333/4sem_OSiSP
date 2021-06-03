#! /bin/bash

function clear_line {
	echo ""
}

function menu {
	clear_line
	echo "Menu:"
	echo "1. Find file in directory"
	echo "2. Copy file to directory"
	echo "3. Exit"
	clear_line
}

function find_file_in_folder {
	echo "alpha"

	echo "find <path> -name <whatFind>"
	clear_line

	echo "path (the path to search in) ="
	read path
	clear_line

	echo "whatFind ="
	read whatFind
	clear_line

	echo "find $path -name $whatFind"
	find $path -name $whatFind
	clear_line
}

function copy_file_to_directory {
	echo "cp <path1> <path2>"
	clear_line

	echo "path1 (the path to the file, which you copy) ="
	read path1
	clear_line

	echo "path2 (the path to the folder, to which you want to copy) ="
	read path2
	clear_line

	echo "cp $path1 $path2"
	cp $path1 $path2
	clear_line

	echo "ls $path2"
	ls $path2
	clear_line
}

function main {
	clear
	while true
		do
			menu
			read choosenKey
			clear
			case $choosenKey in
				'1')
					find_file_in_folder
				;;
				'2')
					copy_file_to_directory
				;;
				'3')
					break
				;;
			esac # end case
	done # end while
}

main
exit 0
