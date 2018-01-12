# Project Providence

## Wymagania funkcjonalne:

1. Dodanie usługi sieciowej do monitorowania, zatrzymanie monitorowania usługi.
2. Monitorowanie wybranych usług http (80, 8080), ssh (22), ftp (20,21), smtp (25), pop3 (110,995), możliwe monitorowanie usług na innych portach.
3. Możliwość konfiguracji dowolnej częstotliwości monitorowania dla usuługi.
4. Historia monitoringu zapisywana do pliku.
5. Alert mailowy o niedziałającej usłudze na dowolny adres.


## Wymagania niefunkcjonalne:
1. Komputer.
2. Os: Linux (Debian/Ubuntu i pochodne).
3. Połączenie z internetem.
4. Do kompilacji programu niezbędna jest instalacja pakietu libssl-dev (-lssl -lcrypto).

## Przypadki użycia

### Przypadek 1.: uruchomienie programu, załadowanie konfiguracji z pliku
1. Użytkownik przygotowuje plik z konfiguracją programu.
2. Program jest uruchamiany, jako parametr z linii poleceń podawany jest plik.
3. Program przetwarza plik, tworzy obiekty i rozpoczyna obserwację zadanych w pliku konfiguracyjnym usług.
4. Użytkownik ma możliwość dodawania kolejnych usług do obserwacji.

### Przypadek 2.: uruchomienie programu

1. Użytkownik uruchamia program, tworzone są obiekty Beholder, Scribe.
2. Program umożliwia użytkownikowi dodanie adresu i portu do obserwacji (usługi) oraz interwału, w jakim będzie sprawdzana dostępność usługi.
3. Użytkownik podaje dane wejściowe.
4. Program tworzy obiekt zawierający dane usługi.
5. Program tworzy obiekt obsługujący wybrany protokół identyfikowany przez port.
6. Program na bazie powyższych tworzy wątek, który nie jest aktywny przez określony czas.
7. Po upływie interwału zestawiane jest połączenie z usługą.
8. Jeżeli usługa działa, wątek jest usypiany na określony czas i program powraca do punktu 7 jako punkt 10.
9. Jeśli usługa nie działa, wątek komunikuje się z obiektem:
      * Scribe - zdarzenie logowane jest do pliku, wysyłane jest powiadomienie przez e-mail.
      * Program wraca do punktu 7.

### Przypadek 3.: program jest uruchomiony,  monitoruje wcześniej wprowadzone usługi

1. Użytkownik wydaje polecenie wypisania monitorowanych usług.
2. Program wyświetla identyfikatory (unikatowe w obrębie programu) i dane monitorowanych usług (adres ip, port, interwał, e-mail do powiadamiania).
3. Użytkownik ma możliwość wydawania kolejnych komend.

### Przypadek 4.: program jest uruchomiony, monitoruje wcześniej wprowadzone usługi, użytkownik zna identyfikatory monitorowanych usług
1. Program umożliwia użytkownikowi podanie identyfikatora monitorowanej usługi do zatrzymania.
2. Użytkownik podaje identyfikator.
3. Program zatrzymuje monitorowanie usługi, wątek jest zatrzymywany.

### Przypadek 5.: program jest uruchomiony
1. Użytkownik wydaje polecenie odpowiedzialne za wyświetlenie wewnętrznej pomocy.
2. Program wyświetla dostępne komendy.
3. Program przechodzi w stan oczekiwania na kolejne polecenia.

## Diagram sekwencji

![diagram sekwencji projek providence](https://github.com/duzypit/pprovidence/blob/master/docs/project_providence_seq_diag.png?raw=true)

## Ramka danych dla protokołów TCP/IP


Datagram TCP
![datagram TCP](https://github.com/duzypit/pprovidence/blob/master/docs/tcp_udp_headers.jpg?raw=true)

Połączenie klient - serwer
![klient - serwer](https://github.com/duzypit/pprovidence/blob/master/docs/TCP_IP_socket_diagram.png?raw=true)
