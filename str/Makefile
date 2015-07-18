test: Agenda.o AgendaService.o AgendaUI.o Date.o Meeting.o Storage.o User.o
	g++ Agenda.o AgendaService.o AgendaUI.o Date.o Meeting.o Storage.o User.o -o test -std=c++0x
Agenda.o: Agenda.cpp
	g++ Agenda.cpp -c -std=c++0x
AgendaService.o: AgendaService.o
	g++ AgendaService.cpp -c -std=c++0x
AgendaUI.o: AgendaUI.cpp
	g++ AgendaUI.cpp -c -std=c++0x
Date.o: Date.cpp
	g++ Date.cpp -c -std=c++0x
Meeting.o: Meeting.cpp
	g++ Meeting.cpp -c -std=c++0x
Storage.o: Storage.cpp
	g++ Storage.cpp -c -std=c++0x
User.o: User.cpp
	g++ User.cpp -c -std=c++0x
clean:
	rm *.o test *.csv
