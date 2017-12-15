# Project Providence

## Wymagania funkcjonalne:

1. Dodanie/usunięcie usługi sieciowej do monitorowania
2. Monitorowanie wybranych usług http, ssh, ftp, smtp, pop3
3. Możliwość konfiguracji dowolnej częstotliwości monitorowania dla usuługi
4. Historia monitoringu zapisywana do pliku
5. Alert mailowy o nie działającej usłudze na dowolny adres
6. Możliwość ustawienia interwału wysyłania alertu


## Wymagania niefunkcjonalne:
1. Maszyna - specyfikacja
2. Os - Linux
3. Połączenie z siecią


## Przypadki użycia

### Przypadek 1: uruchomienie programu

1. Użytkownik uruchamia program, tworzone są obiekty Beholder, Postmaster, Scribe.
2. Program umożliwia użytkownikowi dodanie adresu i portu do obserwacji (usługi) oraz interwału w jakim będzie sprawdzana dostępność usługi
3. Użytkownik podaje dane wejściowe
4. Program tworzy obiekt zawierający dane usługi
5. Program tworzy obiekt obsługujący wybrany protokół identyfikowany przez port
6. Program na bazie powyższych tworzy wątek, który nie jest aktywny przez określony czas
7. Po upływie interwału zestawiane jest polaczenie z usługą
8. Jeżeli usługa działa, wątek jest usypiany na określony czas i program powraca do punktu 7.
9. Jeśli usługa nie działa, wštek komunikuje się z obiektami:
      * Postmaster - wysyłana jest wiadomość na wskazany adres,
      * Scribe - zdarzenie logowane jest do pliku
      * Program wraca do punktu 7.

### Przypadek 2, program jest uruchomiony,  monitoruje wcześniej wprowadzone usługi

1. Użytkownik wydaje polecenie wypisania monitorowanych usług
2. Program wyświetla identyfikatory (unikatowe w obrębie programu) i dane monitorowanych usług (adres ip, port, interwał, e-mail do powiadamiania)

### Przypadek 3, program jest uruchomiony, monitoruje wcześniej wprowadzone usługi, użytkownik zna identyfikatory monitorowanych usług
1. Program umożliwia użytkownikowi podanie identyfikatora monitorowanej usługi do zatrzymania
2. Użytkownik podaje identyfikator
3. Program zatrzymuje monitorowanie usługi, wątek jest "joinowany"

## Diagram sekwencji

![diagram sekwencji projek providence](https://github.com/duzypit/pprovidence/blob/master/docs/project_providence_seq_diag.png?raw=true)

## Ramka danych dla protokołów TCP/IP

Datagram TCP
![datagram TCP](https://github.com/duzypit/pprovidence/blob/master/docs/tcp_udp_headers.jpg?raw=true)

Połączenie klient - serwer
![klient - serwer](https://github.com/duzypit/pprovidence/blob/master/docs/TCP_IP_socket_diagram.png?raw=true)




