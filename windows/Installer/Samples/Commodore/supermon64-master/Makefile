all: supermon64.prg

.PHONY: clean cleanprg cleanmerge

clean: cleanprg cleanmerge cleanlst

cleanprg:
	rm *.prg
    
cleanlst:
	rm *.lst

cleanmerge:
	rm mergerelocate.exe
    
supermon64.prg: relocate.prg supermon64-8000.prg supermon64-C000.prg mergerelocate.exe
	./mergerelocate.exe relocate.prg supermon64-8000.prg supermon64-C000.prg supermon64.prg

supermon64-8000.prg: supermon64.asm
	./pasm64.exe supermon64.asm -o supermon64-8000.prg -d ORG '$$8000' -l supermon64-8000.lst -c64

supermon64-C000.prg: supermon64.asm
	./pasm64.exe supermon64.asm -o supermon64-C000.prg -d ORG '$$C000' -l supermon64-C000.lst -c64

relocate.prg: relocate.asm
	./pasm64.exe relocate.asm -o relocate.prg -c64

mergerelocate.exe: MergeRelocate.cpp
	gcc mergerelocate.cpp -o mergerelocate.exe -std=c++11 -lstdc++
