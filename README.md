# ipv4_and_tcp_send

Projekt realizowany w ramach przedmiotu Programowanie w jezyku C cz.2

Zadanie projektowe
        Celem zadania projektowego jest stworzenie aplikacji pozwalającej na stworzenie i wysłanie dowolnego pakietu IP. 
        Przygotowanie do ćwiczeniach
        W ramach przygotowania do ćwiczenia należy zapoznać się z możliwościami programu sendip.
Realizacja ćwiczenia:
1. Każdy ze studentów realizuje projekt samodzielnie. Stos protokołów jakie ma obsługiwać program, dla każdego studenta, określa prowadzący zajęcia:
a) IPv4 + ICMP
b) IPv4 + TCP
c) IPv4 + UDP
d) IPv6 + ICMPv6
e) IPv6 + TCP
f) IPv6 + UDP
2. Program ma obsługiwać pobieranie parametrów z linii poleceń. Dostarczane parametry zależą od stosu protokołów określonego w punkcie 1.
3. Program musi również jako jeden z argumentów przyjmować interfejs za pomocą którego pakiet ma zostać wysłany.
4. Kolejnym argumentem programu ma być liczba pakietów do wysłania.
5. Dla każdego z obsługiwanych protokołów stworzyć bibliotekę pozwalającą na ustawienie poszczególnych pól (np. biblioteka do obsługi IPv4 powinna posiadać funkcję ustawiającą pole wersji, długość nagłówka itp.).
6. Biblioteki te mają być ładowane dynamicznie podczas działania programu.
7. Pola nie podane przez użytkownika powinny przyjmować domyślne wartości zgodne z RFC.
8. Po utworzeniu odpowiedniego pakietu, należy powielić go żądaną liczbę razy i załadować do listy wiązanej.
9. Pakiety z listy należy wysłać do wskazanego interfejsu.
 
Wymagania:
1. W programie należy wykorzystać wskaźniki na funkcje.
2. Historia prowadzenia i dokumentacja projektu powinna znajdować się na plataformie github.com (lub innej obsługującej system kontroli wersji git).
########################################################################################

Uruchomienie:  
Aby uruchomić program należy przejść do folderu
ipv4_and_tcp_send/main_program/Debug/      

następnie z konsoli systemowej wywołać program:    
sudo ./main_program [count packet] [count protocol: 0 ipv4 or 1 tcp]

Uwagi:  
Należy zmienić ścieżkę do bibliotek dynamicznych na własne.



