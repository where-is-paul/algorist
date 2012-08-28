name = 10249
np++ = /cygdrive/c/Program\ Files\ \(x86\)/Notepad++/notepad++
all:
	g++ -lm -lcrypt -O2 -o $(name) $(name).cpp
	./$(name) < $(name).in
init:
	cp template.cpp $(name).cpp
	touch $(name).in
	$(np++) $(name).cpp $(name).in
clean:
	rm $(name).exe*
pack:
	mkdir -p "$(name)"
	mv $(name).* $(name)