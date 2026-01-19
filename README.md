# MazeGame

MazeGame je konzolna C++ igra u kojoj igrač upravlja robotom kroz generisani lavirint i pokušava da dođe do izlaza koristeći različite specijalne efekte.

Projekat je razvijen u CLion-u i koristi CMake kao build sistem, a testiran je na Linux operativnom sistemu.

Program se najprije builda (Debug ili Release), nakon čega CLion automatski generiše odgovarajući build direktorijum (`cmake-build-debug/` ili `cmake-build-release/`).

Za pokretanje programa potrebno je pozicionirati se u `app` direktorijum unutar build foldera, na primjer:

`cd cmake-build-debug/app`

Nakon uspješnog buildovanja, u `app` direktorijumu se generiše izvršna datoteka `MazeGame`. Program se zatim pokreće iz terminala i zahtijeva sljedeće argumente:

`./MazeGame <rows> <cols> <numOfItems>`

Primjer pokretanja:

`./MazeGame 25 40 20`

Ako se program pokrene bez odgovarajućih argumenata, ispisuje se poruka:

`Exception: <program> <rows> <cols> <numOfItems>`

## Kontrole

- `w` – kretanje gore
- `s` – kretanje dolje
- `a` – kretanje lijevo
- `d` – kretanje desno
- `q` – izlaz iz igre
