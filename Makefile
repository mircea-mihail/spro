# Inspired by https://github.com/Costinteo/shellsec/blob/main/Makefile

INSTALL_DIR = /usr/local/bin
SHELL = /usr/bin/env sh

all:
	@echo Run \'make compile\' to compile spro.
	@echo
	@echo Run \'make install\' to install spro.
	@echo Run \'make uninstall\' to uninstall spro.
	@echo
	@echo For custom installation directory, use \'make INSTALL_DIR=...\'.
	@echo Current installation directory is \'$(INSTALL_DIR)\'.

compile:
	g++ main.cpp fileWriting.cpp generalUtility.cpp options.cpp printing.cpp -o spro

install:
	mkdir ~/.spro
	@echo Making directory $(INSTALL_DIR)...
	@mkdir -p $(INSTALL_DIR)
	@echo Copying files to it...
	@cp spro $(INSTALL_DIR)/
	@echo Making script executable...
	@chmod 755 $(INSTALL_DIR)/spro
	@echo creating .spro directory in your home directory...

uninstall:
	@echo Deleting spro...
	@rm $(shell command -v spro)
