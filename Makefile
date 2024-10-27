.PHONY: all install

all:

install:
	mkdir -p ~/.local/bin
	# добавление в PATH НА ПОСТОЯННОЙ ОСНОВЕ
	cp ./templates/crcpp.sh ~/.local/bin/crcpp
	chmod +x ~/.local/bin/crcpp
	
	mkdir -p ~/.local/templates
	cp ./templates/MakefileCpp ~/.local/templates/MakefileCpp
	cp ./templates/programTemplateCpp.cpp ~/.local/templates/programTemplateCpp.cpp

uninstall:
	rm -f ~/.local/bin/crcpp
	rm -f ~/.local/templates/MakefileCpp
	rm -f ~/.local/templates/programTemplateCpp.cpp
