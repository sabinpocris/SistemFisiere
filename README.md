# Sistem de Fișiere

La baza temei sta implementarea arboriilor binari de cautare generali.
Ordinea dintre elemente se stabiliseste dupa o functie ce compara datele nodurilor.

Am plecat de la aceasta implementare si am definit tipurile:
  - `Folder` = structura care reprezinta un folder
  - `File` = structura care reprezinta un fisier
  - `FileStructure` = structura de baza, contine radacina si folderul in care lucram

Dupa parsare, apelez functiile specifice:
  - `touch()` = verific daca exista fiserul, in caz contrar il creez si il adaug in arbore  
  - `makeDirectory()` = verific daca exista directorul, in caz contrar il creez si il adaug in arbore 
  - `ls()` = printez continului arborilor de fisiere si subdirectoare din fisierul curent
  - `removeFile()` = daca exista, sterg nodul din arbore si il dezaloc
  - `removeDirectory()` = daca exista, sterg nodul din arbore si il dezaloc
  - `changeDirectory()` = daca exista folderul, modific FileStructure sa pointeze catre directorul cerut
  - `printWorkingDirectory()` = in mod recursiv, parcurg folderele pana la parinte, de unde incep sa printez calea
  - `find()` = verific in mod recursiv daca exista un folder sau un director cu numele cerut
  - `cleanRoot()` = dealoca memoria in mod recursiv a elementelor din arbore si noduri
