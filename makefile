errflags = -Wall -Wextra -o2
linkedLibraries = -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lmingw32
dependencies = makefile main.cpp func.h
shareLinkedLibraries = SDL2_image.dll SDL2_ttf.dll SDL2.dll
ICSDL = -IC:\Users\david\Downloads\Code\SDL2\include
LCSDL = -LC:\Users\david\Downloads\Code\SDL2\lib

main: $(dependencies)
	g++ $(errflags) main.cpp -o TheMind $(ICSDL) $(LCSDL) $(linkedLibraries)
	./TheMind.exe
	python key.py

noKey: $(dependencies)
	g++ $(errflags) main.cpp -o TheMind $(ICSDL) $(LCSDL) $(linkedLibraries)
	./TheMind.exe

noRun: $(dependencies)
	g++ $(errflags) main.cpp -o TheMind $(ICSDL) $(LCSDL) $(linkedLibraries)

TheMind: $(dependencies)
	g++ $(errflags) -static main.cpp -o TheMind $(shareLinkedLibraries)
	powershell Remove-Item C:\Users\david\Downloads\Code\Exports\TheMind\TheMind.exe
	powershell move TheMind.exe C:\Users\david\Downloads\Code\Exports\TheMind
	powershell Remove-Item C:\Users\david\Downloads\Code\Exports\TheMindZip.zip
	powershell Compress-Archive C:\Users\david\Downloads\Code\Exports\TheMind C:\Users\david\Downloads\Code\Exports\TheMindZip.zip
	powershell make noRun
	python key.py