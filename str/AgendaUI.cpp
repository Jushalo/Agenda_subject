#include "AgendaUI.h"
#include <iostream>
#include <iomanip>

AgendaUI::AgendaUI() {}
void AgendaUI::OperationLoop(void) {
  startAgenda();
  while(1) {
  std::string tem = getOperation();
  if (!executeOperation(tem)) break;
  }
}
void AgendaUI::startAgenda(void) {
  std::cout << "-----------------------Agenda--------------------------" << std::endl
	    << "Action :" << std::endl
	    << "l    - log in Agenda by user name and password" << std::endl
	    << "r    - register an Agenda account" << std::endl
	    << "q    - quit Agenda" << std::endl
	    << "-------------------------------------------------------" << std::endl;
}
std::string AgendaUI::getOperation() {
  std::string tem;
  if (userName_ == "") {
    std::cout << "Agenda : ~$ ";
    std::cin >> tem;
  } else {
    std::cout << "Agenda@" << userName_ << " : # ";
    std::cin >> tem;
  }
  return tem;
}
bool AgendaUI::executeOperation(std::string op) {
  if (op == "l") {
    userLogIn();
  } else if (op == "r") {
    userRegister();
  } else if (op == "q") {
    quitAgenda();
    return false;
  } else if (op == "o") {
    userLogOut();
  } else if (op == "dc") {
    deleteUser();
  } else if (op == "lu") {
    listAllUsers();
  } else if (op == "cm") {
    createMeeting();
  } else if (op == "la") {
    listAllMeetings();
  } else if (op == "las") {
    listAllSponsorMeetings();
  } else if (op == "lap") {
    listAllParticipateMeetings();
  } else if (op == "qm") {
    queryMeetingByTitle();
  } else if (op == "qt") {
    queryMeetingByTimeInterval();
  } else if (op == "dm") {
    deleteMeetingByTitle();
  } else if (op == "da") {
    deleteAllMeetings();
  } else {
    std::cout << "Please input the correct order again!" << std::endl;
  }
  return true;
}
void AgendaUI::userLogIn(void) {
  std::cout << std::endl << "[log in] [user name] [password]" << std::endl;
  std::string userName, password;
  std::cout << "[log in] ";
  std::cin >> userName >> password;
  if (agendaService_.userLogIn(userName, password)) {
    std::cout << "[log in] succeed!" << std::endl;
  std::cout << "-----------------------Agenda--------------------------" << std::endl
	    << "Action :" << std::endl
	    << "o   - log out Agenda" << std::endl
	    << "dc  - delete Agenda account" << std::endl
	    << "lu  - list all Agenda users" << std::endl
	    << "cm  - create a meeting" << std::endl
	    << "la  - list all meetings" << std::endl
	    << "las - list all sponsor meetings" << std::endl
	    << "lap - list all participate meetings" << std::endl
	    << "qm  - query meeting by title" << std::endl
	    << "qt  - query meeting by tiem interval" << std::endl
	    << "dm  - delete meeting bt title" << std::endl
	    << "da  - delete all meetings" << std::endl
	    << "-------------------------------------------------------" << std::endl;
  userName_ = userName;
  userPassword_ = password;
  } else {
    std::cout << "[error] log in fail!" << std::endl;
  }
}
void AgendaUI::userRegister(void) {
  std::cout << std::endl;
  std::cout << "[register] [user name] [password] [email] [phone]" << std::endl
	    << "[register] " ;
  std::string userName, password, email, phone;
  std::cin >> userName >> password >> email >> phone;
  if (agendaService_.userRegister(userName, password, email, phone)) {
    std::cout << "[register] succeed!" << std::endl << std::endl;
  } else {
    std::cout << "[error] resgistere fail! " << std::endl << std::endl;
  }
}
void AgendaUI::quitAgenda(void) {
  std::cout << "[quit Agenda] Thanks for using!" << std::endl << std::endl;
}
void AgendaUI::userLogOut(void) {
  std::cout << "[log out] succeed!" << std::endl;
  userName_ = "";
  userPassword_ = "";
  startAgenda();
}
void AgendaUI::deleteUser(void) {
  deleteAllMeetings();
  userName_ = "";
  userPassword_ = "";
  std::cout << "[delete user] succeed!" << std::endl << std::endl;
  startAgenda();
}
void AgendaUI::listAllUsers(void) {
  std::cout << std::endl;
  std::list<User> userList = agendaService_.listAllUsers();
  std::cout << "[list all users]" << std::endl;
  std::cout << "[userName] [email] [phone]" << std::endl;
  std::list<User>::iterator iter = userList.begin();
  for (; iter != userList.end(); iter++) {
    std::cout << iter -> getName() << " "
	 << iter -> getEmail() << " "
	 << iter -> getPhone() << std::endl;
  }
  std::cout << std::endl;
}
void AgendaUI::createMeeting(void) {
  std::cout << std::endl
	    << "[create meeting]" << std::endl << "[title] [participator] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << std::endl;
  std::string title, participator, startDate, endDate;
  std::cin >> title >> participator >> startDate >> endDate;
  if (agendaService_.createMeeting(userName_, title, participator, startDate, endDate)) {
    std::cout << "[create meeting] succeed!" << std::endl;
  } else {
    std::cout << "[error] fail!" << std::endl;
  }
}
void AgendaUI::listAllMeetings(void) {
  std::cout << std::endl << "[list all meeting]" << std::endl << std::endl
	    << "[sponsor] [participator] [start date] [end date] [title]" << std::endl;
  std::list<Meeting> meetingList = agendaService_.listAllMeetings(userName_);
  printMeetings(meetingList);
}
void AgendaUI::listAllSponsorMeetings(void) {
  std::cout << std::endl << "[list all sponsor meeting]" << std::endl << std::endl
	    << "[sponsor] [participator] [start date] [end date] [title]" << std::endl;
  std::list<Meeting> meetingList = agendaService_.listAllSponsorMeetings(userName_);
  printMeetings(meetingList);
}
void AgendaUI::listAllParticipateMeetings(void) {
  std::cout << std::endl << "[list all meeting]" << std::endl << std::endl
	    << "[sponsor] [participator] [start date] [end date] [title]" << std::endl;
  std::list<Meeting> meetingList = agendaService_.listAllParticipateMeetings(userName_);
  printMeetings(meetingList);
}
void AgendaUI::queryMeetingByTitle(void) {
  std::cout << std::endl << "[queay meetings] [title]" << std::endl
       << "[query meetings] ";
  std::string title;
  std::cin >> title;
  std::list<Meeting> meetingList;
  meetingList = agendaService_.meetingQuery(userName_, title);
  std::cout << std::endl << "[query meetings]" << std::endl
       << "[sponsor] [participator] [start date] [end date] [title]" << std::endl;
  printMeetings(meetingList);
}
void AgendaUI::queryMeetingByTimeInterval(void) {
  std::cout << std::endl << "[quuery meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << std::endl
	    << "[query meetings] ";
  std::string startTime, endTime;
  std::cin >> startTime >> endTime;
  std::cout << std::endl << "[query meetings]" << std::endl
       << "[sponsor] [participator] [start date] [end date] [title]" << std::endl;
  std::list<Meeting> meetingList;
  meetingList = agendaService_.meetingQuery(userName_, startTime, endTime);
  printMeetings(meetingList);
}
void AgendaUI::deleteMeetingByTitle(void) {
  std::cout << std::endl << "[delete meeting] [title]" << std::endl
	    << "[delete meeting] ";
  std::string title;
  std::cin >> title;
  if (agendaService_.deleteMeeting(userName_, title)) {
    std::cout << "[delete meeting by title] success!" << std::endl;
  } else {
    std::cout << "[error] delete meeting fail!" << std::endl;
  }
  std::cout << std::endl;
}
void AgendaUI::deleteAllMeetings(void) {
    if (agendaService_.deleteAllMeetings(userName_)) {
    std::cout << "[delete all meetings] succeed!" << std::endl;
  } else {
    std::cout << "[delete all meetings] fail!" << std::endl;
  }
    std::cout << std::endl;
}
void AgendaUI::printMeetings(std::list<Meeting> meetings) {
  std::list<Meeting>::iterator iter = meetings.begin();
  for (; iter != meetings.end(); iter++) {
    std::cout << iter -> getSponsor() << " "
	      << iter -> getParticipator() << " "
	      << Date::dateToString(iter -> getStartDate()) << " "
	      << Date::dateToString(iter -> getEndDate()) << " "
	      << iter -> getTitle() << std::endl;
  }
  std::cout << std::endl;
}
