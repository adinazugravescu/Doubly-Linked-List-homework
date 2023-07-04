# Doubly-Linked-List-homework
Implementarea temei este facuta cu ajutorul a 2 fisiere sursa(un fisier header si unul 
in care este main-ul) si un Makefile folosit pentru compilarea surselor,crearea executabilului ,
rularea si stegrerea acestuia.

Fisierul header -tema1.h- contine definirea structurilor (pentru banda, a unei liste dublu 
inlantuite la care retinem in List santinela si "degetul" aka nodul curent , pentru stiva 
-TStack si pentru coada -TQueue), dar si a mai multor functii:
->functiile care vor implementa operatiile din cerinta(UPDATE,QUERY,UNDO/DO,EXECUTE);
->functii pentru prelucrarea TAD-urilor (pentru lista dublu inlantuita avem o functie de creare
a unui nod din lista ,una pentru initializarea acestui tip particular de liste si una pentru 
dezalocarea memoriei; pentru stiva avem functie de initializare,de verificare stiva goala,de 
introducere a unui nou element,de eliminare din stiva si de dezalocare a memoriei ;pentru coada
avem functie de initializare si eliberare a unui nod,de initializare a cozii si de verificare
daca este goala,de adaugare si de eliminare,respectiv de gasire a primei valori si de eliberare
a memoriei);

In mtema1.c , banda va fi reprezentata de variabila List,stiva pentru operatiile UNDO de stackU
si cea pentru REDO de stackR,iar coada pentru EXECUTE de variabila queue.Citind din fisierul 
"tema1.in", avem prima data nr de operatii in variabila n,urmand ca apoi sa citim intr-o variabila
inputCharacters fiecare rand ce contine o comanda,pe baza careia se vor efectua mai multe operatii
benzii: daca comanda nu este de tip execute , tratam 2 cazuri : cazul in care este de tip UPDATE
si o vom adauga in 'queue', si cazul in care se va executa pe loc,ce implica 2 variante -QUERY
si UNDO/REDO;QUERY rezulta in apelarea functiilor show si show_current , iar UNDO si REDO in 
umplerea si golirea stivelor cu adresele ultimului nod curent,conform cerintei.Daca comanda este
de tip execute,atunci luam pe rand operatiile de tip UPDATE,apeland functiile implementate pentru
acestea in tema1.h.La final,dezalocam lista si inchidem fisierele de intrare si iesire.

-= TEMA 1 SDA =-

README: 5/5
Coding style: 15/15
test1.in: 5/5
  Valgrind test.in: 1/1
test2.in: 5/5
  Valgrind test.in: 1/1
test3.in: 1/1
  Valgrind test.in: 1/1
test4.in: 1/1
  Valgrind test.in: 1/1
test5.in: 1/1
  Valgrind test.in: 1/1
test6.in: 1/1
  Valgrind test.in: 1/1
test7.in: 1/1
  Valgrind test.in: 1/1
test8.in: 2/2
  Valgrind test.in: 1/1
test9.in: 2/2
  Valgrind test.in: 1/1
test10.in: 2/2
  Valgrind test.in: 1/1
test11.in: 2/2
  Valgrind test.in: 1/1
test12.in: 2/2
  Valgrind test.in: 1/1
test13.in: 2/2
  Valgrind test.in: 1/1
test14.in: 2/2
  Valgrind test.in: 1/1
test15.in: 2/2
  Valgrind test.in: 1/1
test16.in: 2/2
  Valgrind test.in: 1/1
test17.in: 3/3
  Valgrind test.in: 1/1
test18.in: 3/3
  Valgrind test.in: 1/1
test19.in: 3/3
  Valgrind test.in: 1/1
test20.in: 3/3
  Valgrind test.in: 1/1
test21.in: 3.5/3.5
  Valgrind test.in: 1/1
test22.in: 3.5/3.5
  Valgrind test.in: 1/1
test23.in: 3.5/3.5
  Valgrind test.in: 1/1
test24.in: 3.5/3.5
  Valgrind test.in: 1/1
test25.in: 3.5/3.5
  Valgrind test.in: 1/1
test26.in: 3.5/3.5
  Valgrind test.in: 1/1
test27.in: 3.5/3.5
  Valgrind test.in: 1/1
test28.in: 3.5/3.5
  Valgrind test.in: 1/1
test29.in: 3.5/3.5
  Valgrind test.in: 1/1
test30.in: 3.5/3.5
  Valgrind test.in: 1/1

Total: 100.0/100
Valgrind: 20/20
