# Project Providence

##Wymagania funkcjonalne:

1. Dodanie/usunięcie usługi sieciowej do monitorowania
2. Monitorowanie wybranych usług http, ssh, ftp, smtp, pop3
3. Możliwość konfiguracji dowolnej częstotliwości monitorowania dla usuługi
4. Historia monitoringu zapisywana do pliku
5. Alert mailowy o nie działającej usłudze na dowolny adres
6. Możliwość ustawienia interwału wysyłania alertu


##Wymagania niefunkcjonalne:
1. Maszyna - specyfikacja
2. Os - Linux
3. Połączenie z siecią


##Przypadki użycia

###Przypadek 1: uruchomienie programu

1. Użytkownik uruchamia program, tworzone sš obiekty Beholder, Postmaster, Scribe
2. Program umożliwia użytkownikowi dodanie adresu i portu do obserwacji (usługi) oraz interwału w jakim będzie sprawdzana dostępnoć usługi
3. Użytkownik podaje dane wejciowe
4. Program tworzy obiekt zawierajšcy dane usługi
5. Program tworzy obiekt obsługujšcy wybrany protokół identyfikowany przez port
6. Program na bazie powyższych tworzy wštek, który nie jest aktywny przez okrelony czas
7. Po upływie interwału zestawiane jest polaczenie z usługš
8. Jeżeli usługa działa, wštek jest usypiany na okrelony czas i program powraca do punktu 7.
9. Jeli usługa nie działa, wštek komunikuje się z obiektami:

Postmaster - wysyłana jest wiadomoć na wskazany adres,
Scribe - zdarzenie logowane jest do pliku
Program wraca do punktu 7.



###Przypadek 2, program jest uruchomiony,  monitoruje wczeniej wprowadzone usługi

1. Użytkownik wydaje polecenie wypisania monitorowanych usług

2. Program wywietla identyfikatory (unikatowe w obrębie programu) i dane monitorowanych usług (adres ip, port, interwał, e-mail do powiadamiania)



###Przypadek 3, program jest uruchomiony, monitoruje wczeniej wprowadzone usługi, użytkownik zna identyfikatory monitorowanych usług
1. Program umożliwia użytkownikowi podanie identyfikatora monitorowanej usługi do zatrzymania
2. Użytkownik podaje identyfikator

3.  Program zatrzymuje monitorowanie usługi, wštek jest "joinowany"



Ramka danych dla protokołów TCP/IP

Datagram IP
	pakiet to datagram
	datagram jest podstawowš, samodzielnš jednostkš przesyłšna w sieci
	mogš być adresowane do pojedynczych/ wielu węzłów
	rozmiar w zależnoci od potrzeb, datagram może być podzielony na kilka mniejszych częci (fragmentacja)


