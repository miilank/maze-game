# MazeGame

MazeGame je konzolna C++ igra u kojoj igrač upravlja robotom kroz generisani lavirint i pokušava da dođe do izlaza koristeći specijalne efekte.

Projekat je rađen u CLion-u i koristi CMake kao build sistem.

Program se prvo builda (Debug ili Release), nakon čega CLion generiše odgovarajući build direktorijum
(`cmake-build-debug/` ili `cmake-build-release/`).

Za pokretanje programa potrebno je pozicionirati se u `app` folder unutar build direktorijuma, npr.: `cd cmake-build-debug/app`

Program se pokreće iz terminala i zahtijeva argumente:

`./MazeGame <rows> <cols> <numOfItems>`

Primjer:

`./MazeGame 25 40 20`

Ako se program pokrene bez argumenata, ispisuje se poruka:

`Exception:<program> <rows> <cols> <numOfItems>`

Kontrole u igri:
w – gore  
s – dolje  
a – lijevo  
d – desno  
q – izlaz
