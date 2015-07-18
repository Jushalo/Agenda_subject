#include "AgendaService.h"

AgendaService::AgendaService() {
  startAgenda();
}
AgendaService::~AgendaService() {
  quitAgenda();
}
bool AgendaService::userLogIn(std::string userName, std::string password) {
  std::function<bool(const User&)> filter;
  filter = [userName, password](const User& user) {
    if (userName == user.getName()) {
      if (password == user.getPassword()) {
	return true;
      } else {
	return false;
      }
    } else {
      return false;
    }
  };
  std::list<User> nameList = storage_ -> queryUser(filter);
  if (nameList.size()) {
    return true;
  } else {
    return false;
  }
}
bool AgendaService::userRegister(std::string userName, std::string password,
                  std::string email, std::string phone) {
  std::function<bool(const User&)> filter;
  filter = [userName](const User& user) {
    if (userName == user.getName()) {
      return true;
    } else {
      return false;
    }
  };
  std::list<User> nameList = storage_ -> queryUser(filter);
  if (nameList.size()) {
    return false;
  } else {
    storage_ -> createUser(User(userName, password, email, phone));
    return true;
  }
}
// Important logical
bool AgendaService::deleteUser(std::string userName, std::string password) {
  std::function<bool(const User&)> filter;
  filter = [userName, password](const User& user) {
    if (userName == user.getName()) {
      if (password == user.getPassword()) {
	return true;
      } else {
	return false;
      }
    } else {
      return false;
    }
  };
  if (!storage_ -> deleteUser(filter)) {
    return false;
  } else {
    std::function<bool(const Meeting&)> filter2;
    filter2 = [userName](const Meeting& meeting) {
      if (meeting.getSponsor() == userName) {
	return true;
      } else if (meeting.getParticipator() == userName) {
	return true;
      } else {
	return false;
      }
    };
    storage_ -> deleteMeeting(filter2);
    return true;
  }
}
std::list<User> AgendaService::listAllUsers(void) {
  std::function<bool(const User&)> filter;
  filter = [](const User& user) {return true;};
  std::list<User> nameList = storage_ -> queryUser(filter);
  return nameList;
}
// important logical
bool AgendaService::createMeeting(std::string userName, std::string title,
                   std::string participator,
		   std::string startDate, std::string endDate) {
  Date startDateIns = Date::stringToDate(startDate),
    endDateIns = Date::stringToDate(endDate);
  std::list<User> userList = listAllUsers();  // is the users valid
  std::list<User>::iterator iter = userList.begin();
  bool userExist, parExist;
  userExist = false;
  parExist = false;
  for (; iter != userList.end(); iter++) {
    if (iter -> getName() == userName) userExist = true;
    if (iter -> getName() == participator) parExist = true;
  }
  if (!(userExist && parExist)) return false;
  std::list<Meeting> meetingTitleSame;  // is the title same
  std::function<bool(const Meeting&)> titleJudge;
  titleJudge = [title](const Meeting& meeting) {
    if (meeting.getTitle() == title) {
      return true;
    } else {
      return false;
    }
  };
  meetingTitleSame = storage_ -> queryMeeting(titleJudge);
  if (meetingTitleSame.size()) return false;
  if (endDateIns <= startDateIns) return false;  // is the time valid
  if (!(Date::isValid(endDateIns) && Date::isValid(startDateIns))) return false;
  std::function<bool(const Meeting&)> filter;  // is the time over lap
  filter = [userName, participator, startDateIns, endDateIns](const Meeting& meeting) {
    if (meeting.getEndDate() <= startDateIns ||
	meeting.getStartDate() >= endDateIns) {  // when time is not over lap
      return false;
    } else {  // time over lap
      if (meeting.getSponsor() == userName ||
	  meeting.getParticipator() == participator ||
	  meeting.getSponsor() == participator ||
	  meeting.getParticipator() == userName) {  // when the persons are in
	return true;
      } else {
	return false;
      }
    }
  };
  std::list<Meeting> meetingList = storage_ -> queryMeeting(filter);
  if (meetingList.size()) {
    return false;
  } else {
    Meeting tem(userName, participator, startDateIns, endDateIns, title);
    storage_ -> createMeeting(tem);
    return true;
  }
}
std::list<Meeting> AgendaService::meetingQuery(std::string userName,
					       std::string title) {
  std::function<bool(const Meeting&)> filter;
  filter = [userName, title](const Meeting& meeting) {
    if (meeting.getTitle() == title) {
      if (meeting.getSponsor() == userName) {
	return true;
      } else if (meeting.getParticipator() == userName) {
	return true;
      } else {
	return false;
      }
    } else {
      return false;
    }
  };
  std::list<Meeting> meetingList;
  meetingList = storage_ -> queryMeeting(filter);
  return meetingList;
}
std::list<Meeting> AgendaService::meetingQuery(std::string userName,
					       std::string startDate,
				               std::string endDate) {
  Date startDateIns = Date::stringToDate(startDate);
  Date endDateIns = Date::stringToDate(endDate);
  std::function<bool(const Meeting&)> filter;
  filter = [userName, startDateIns, endDateIns](const Meeting& meeting) {
    if (meeting.getEndDate() <= startDateIns ||
	meeting.getStartDate() >= endDateIns) {  // when time is not over lap
      return false;
    } else {  // time over lap
      if (meeting.getSponsor() == userName ||
	  meeting.getParticipator() == userName) {  // when the persons are in
	return true;
      } else {
	return false;
      }
    }
  };
  std::list<Meeting> meetingList = storage_ -> queryMeeting(filter);
  meetingList = storage_ -> queryMeeting(filter);
  return meetingList;
}
std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
  std::function<bool(const Meeting&)> filter;
  filter = [userName](const Meeting& meeting) {
    if (meeting.getSponsor() == userName) {
      return true;
    } else if (meeting.getParticipator() == userName) {
      return true;
    } else {
      return false;
    }
  };
  std::list<Meeting> meetingList;
  meetingList = storage_ -> queryMeeting(filter);
  return meetingList;
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
  std::function<bool(const Meeting&)> filter;
  filter = [userName](const Meeting& meeting) {
    if (meeting.getSponsor() == userName) {
      return true;
    } else {
      return false;
    }
  };
  std::list<Meeting> meetingList;
  meetingList = storage_ -> queryMeeting(filter);
  return meetingList;
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(
					std::string userName) {
  std::function<bool(const Meeting&)> filter;
  filter = [userName](const Meeting& meeting) {
    if (meeting.getParticipator() == userName) {
      return true;
    } else {
      return false;
    }
  };
  std::list<Meeting> meetingList;
  meetingList = storage_ -> queryMeeting(filter);
  return meetingList;
}
bool AgendaService::deleteMeeting(std::string userName, std::string title) {
  std::function<bool(const Meeting&)> filter;
  filter = [userName, title](const Meeting& meeting) {
    if (meeting.getTitle() == title) {
      if (meeting.getSponsor() == userName) {
	return true;
      } else if (meeting.getParticipator() == userName) {
	return true;
      } else {
	return false;
      }
    } else {
      return false;
    }
  };
  if (storage_ -> deleteMeeting(filter)) {
    return true;
  } else {
    return false;
  }
}
bool AgendaService::deleteAllMeetings(std::string userName) {
  std::function<bool(const Meeting&)> filter;
  filter = [userName](const Meeting& meeting) {
    if (meeting.getSponsor() == userName ||
	meeting.getParticipator() == userName) {
      return true;
    } else {
      return false;
    }
  };
  if (storage_ -> deleteMeeting(filter)) {
    return true;
  } else {
    return false;
  }
}
void AgendaService::startAgenda(void) {
  storage_ = Storage::getInstance();
}
void AgendaService::quitAgenda(void) {
  storage_ -> sync();
}
