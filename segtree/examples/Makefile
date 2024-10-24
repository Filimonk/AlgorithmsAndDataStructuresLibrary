PROGRAM_NAME = segtreeOfSum


CC = g++

GFLAGS = -Wall

START_STRING = \#ifndef DO_NOT_INCLUDE_SYS_LIBS
END_STRING = \#endif \/\/ DO_NOT_INCLUDE_SYS_LIBS

.PHONY: all send clean

all: ${PROGRAM_NAME} send
	@echo
	@echo 'Запуск программы'
	./${PROGRAM_NAME}

${PROGRAM_NAME}: ${PROGRAM_NAME}.cpp
	@echo 'Компиляция программы'
	$(CC) -I ~/AlgorithmsAndDataStructuresLibrary/*/include -o $@ $<

send: send_${PROGRAM_NAME}.cpp
	@echo
	@echo 'Обновление папки "RecentCpp" (добавление туда отправочного файла)'
	mkdir -p $(HOME)/RecentCpp
	rm -f -r $(HOME)/RecentCpp/*
	ln -f -s $(CURDIR)/$< $(HOME)/RecentCpp/$< #когда создам create-ор путь будет $(CURDIR)/../$< 

send_${PROGRAM_NAME}.cpp: ${PROGRAM_NAME}.cpp
	@echo
	@echo 'Частичный препроцессинг и раскритие библиотеки алгоритмов и структур данных'
	sed -n '/${START_STRING}/,/${END_STRING}/{//!p;}' $< > send_$<
	
	$(CC) $(GFLAGS) -E -I ~/AlgorithmsAndDataStructuresLibrary/*/include \
		               -D DO_NOT_INCLUDE_SYS_LIBS -o .send_$<.temp $<
	
	sed -i /^\#.*$$/d .send_$<.temp  # в будущем стоит либо усовершенствовать, либо заменить на самописный препроцессор
									 # т. к. это может привести к проблемам, когда в коде есть перенос (string) и 
									 # на новой строке начало - #
	
	cat .send_$<.temp >> send_$<
	rm .send_$<.temp

clean:
	rm -rf ${PROGRAM_NAME} send_${PROGRAM_NAME}.cpp

includes.d: ${PROGRAM_NAME}.cpp # это может понадобиться, когда я захочу писать самописный препроцессор
	$(CC) -MM -MF $@ -I ~/AlgorithmsAndDataStructuresLibrary/*/include $<

