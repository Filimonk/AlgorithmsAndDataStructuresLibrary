.PHONY: all install

all: install

install:
	mkdir -p ~/.local/bin
	# echo "PATH=\"$$HOME/.local/bin:$$PATH\"" | sudo tee -p /etc/environment > /dev/null
	# . /etc/environment
	cp ./templates/crcpp.sh ~/.local/bin/crcpp
	chmod +x ~/.local/bin/crcpp
	
	mkdir -p ~/.local/templates
	cp ./templates/MakefileCpp ~/.local/templates/MakefileCpp
	cp ./templates/programTemplateCpp.cpp ~/.local/templates/programTemplateCpp.cpp
	
	mkdir -p ~/RecentCpp

uninstall:
	rm -f ~/.local/bin/crcpp
	rm -f ~/.local/templates/MakefileCpp
	rm -f ~/.local/templates/programTemplateCpp.cpp
	
	rm -f -r ~/RecentCpp
