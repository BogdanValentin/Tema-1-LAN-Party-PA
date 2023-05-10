# Tema 1: LAN Party
## Cuprins
* [Descriere](#descriere)
* [Obiective](#obiective)
* [Instalare & Utilizare](#instalare--utilizare)
* [Cerințe](#cerințe)
* [Dificultăți întâmpinate](#dificultăți-întâmpinate)
* [Lucruri interesante descoperite pe parcurs](#lucruri-interesante-descoperite-pe-parcurs)
* [Licență](#licență)

## Descriere
Facultatea de Automatică și Calculatoare prin LSAC organizează în fiecare semestru un LAN Party la care participă toți studenții care vor să își testeze abilitățile la un anumit joc. Se dorește realizarea unei soluții software(program executabil) ce poate automatiza acest proces.   

## Obiective
* Înțelegerea conceptului de funcționare și implementare a unor structuri de date(precum liste, stive, cozi, arbori binari de căutare)
* Operarea cu aceste structuri de date
* Implementarea unei funcționalități practice folosind aceste concepte

## Instalare & Utilizare
1. Clonați repozitoriul
```bash
git clone https://github.com/BogdanValentin/Tema-1-LAN-Party-PA.git
```
2. Compilați proiectul
```bash
make
```
3. Rulați proiectul
```bash
./lanParty c.in d.in r.out
```

## Cerințe
1. Se va crea o listă cu informațiile din fișierul d.in(lista se va forma prin adaugarea elementelor la inceput O(1)).
2. Se vor elimina din lista anterior creată, echipele cu cel mai mic punctaj de echipă (informațiile despre modul de calcul al acestui punctaj se găsesc în cadrul secțiunii Detalii Tehnice astfel incat in lista sa ramana n echipe (unde n maxim si n este putere a lui 2)). În cazul în care mai multe echipe au acelasi scor se elimina prima echipă gasita in lista. Dupa fiecare eliminare se va relua parcurgerea listei de la cap.
3. Se vor implementa structurile de date necesare pentru a se efectua meciurile:
    - Se va crea o coadă în care se vor pune meciurile dintre echipe.
    - Echipele vor forma meciuri în ordinea în care se află în lista de la punctul anterior, primele două echipe vor forma primul meci (și așa mai departe).
    - Se vor crea două stive - una pentru învinși și una pentru câștigători - ce vor conține echipele ce au pierdut, respectiv, au câștigat meciul anterior.
    - Se vor introduce în stivă echipele în funcție de rezultatul obținut și se va adauga un punct la punctajul de echipă al echipelor ce au câștigat.
    - In cazul unui meci in care ambele echipe au acelasi punctaj, se va alege prima echipa adaugata in meciul disputat.
    - Se vor șterge echipele ce se găsesc în stiva de învinși. (la finalul fiecărei etape; ex: dintr-o runda cu 8 echipe, stergerea se face dupa ce au fost eliminate toate echipele. In acest caz, dupa ce au fost eliminate 4 dintre echipe, se vor sterge. In runda urmatoare, pe acest exemplu, se vor adauga 2 echipe in stiva de invinsi, dupa care o sa fie eliberata din nou - stiva de invinsi -.)
    - Din stiva de câștigători se vor extrage echipele și se va umple din nou coada de meciuri formându-se meciuri cu echipele consecutive (prima echipă scoasă din stivă va juca cu a doua echipa scoasă din stivă primul meci).
    - Se vor repeta pașii enumerați pana la aflarea echipelor de pe primele 8 locuri, care vor fi salvate intr-o alta lista, dupa aflarea acestora se vor continua meciurile pana la aflarea echipei castigatoare.
4. Se va realiza un clasament al ultimelor 8 echipe (salvate la subpunctul anterior) sub forma unui BST(Binary Search Tree). Acesta va fi ordonat după punctajul pe echipă și i se va afișa conținutul în ordine descrescătoare(in cazul in care doua echipe au acelasi punctaj se vor ordona in functie de nume, descrescator).
5. Se va realiza un arbore de tip AVL cu ultimele 8 echipe (salvate la subpunctul 3, dar sortate ca la subpunctul 4) si se vor afisa echipele de pe nivelul 2 al arborelui.

## Dificultăți întâmpinate
- Pentru realizarea temei am folosit WSL și am întâmpinat dificultăți în momentul citirii datelor din fișiere, deoarece acestea erau în format Windows (CRLF), iar eu lucrând în WSL mă așteptam la formatul Linux (LF). Pentru a rezolva această problemă, am citit toată linia și am eliminat ultimele caractere, fie ele '\r' sau '\n'.
- Unele teste conțineau trailing whitespace, așa că a trebuit să tratez cazul acesta.
- Memory leaks. Am folosit valgrind pentru a identifica memory leaks-urile.
- Setarea debugger-ului in VSCode

## Lucruri interesante descoperite pe parcurs
- Cum sa fac un makefile
- Nu poti inchide un fisier ce nu s-a putut deschide
- Nu poti deschide acelasi fisier daca acesta nu a fost mai intai inchis

## Licență
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
  