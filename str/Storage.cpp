#include "Storage.h"
#include <fstream>
#include <memory.h>
#include <iostream>

User& stringToUser(std::string str) {
  User * newUser;
  newUser = new User();
  std::string::iterator iter = str.begin();
  std::string tem;
  for (iter++; *iter != '\"'; iter++) {  // set the name
    tem.push_back(*iter);
  }
  newUser -> setName(tem);
  tem = "";
  for (iter += 3; *iter != '\"'; iter++) {  // set the password
    tem.push_back(*iter);
  }
  newUser -> setPassword(tem);
  tem = "";
  for (iter += 3; *iter != '\"'; iter++) {  // set the email
    tem.push_back(*iter);
  }
  newUser -> setEmail(tem);
  tem = "";
  for (iter += 3; *iter != '\"'; iter++) {  // set the phone
    tem.push_back(*iter);
  }
  newUser -> setPhone(tem);
  return *newUser;
}

Meeting& stringToMeeting(std::string str) {
  Meeting * newMeeting = new Meeting();
  std::string::iterator iter = str.begin();
  std::string tem;
  for (iter++; *iter != '\"'; iter++) {  // set the sponsor
    tem.push_back(*iter);
  }
  newMeeting -> setSponsor(tem);
  tem = "";
  for (iter += 3; *iter != '\"'; iter++) {  // set the participator
    tem.push_back(*iter);
  }
  newMeeting -> setParticipator(tem);
  tem = "";
  for (iter += 3; *iter != '\"'; iter++) {  // set the startDate
    tem.push_back(*iter);
  }
  newMeeting -> setStartDate(Date::stringToDate(tem));
  tem = "";
  for (iter += 3; *iter != '\"'; iter++) {  // set the endDate
    tem.push_back(*iter);
  }
  newMeeting -> setEndDate(Date::stringToDate(tem));
  tem = "";
  for (iter += 3; *iter != '\"'; iter++) {  // set the title
    tem.push_back(*iter);
  }
  newMeeting -> setTitle(tem);
  return *newMeeting;
}

Storage* Storage::instance_ = NULL;
Storage::Storage() {
  readFromFile("./");
}
bool Storage::readFromFile(const char *fpath) {
  std::string userPath, meetingPath;
  userPath += fpath;
  userPath += "User.csv";
  meetingPath += fpath;
  meetingPath += "Meeting.csv";
  std::ifstream iFileUser;
  std::ifstream iFileMeeting;
  iFileUser.open(userPath.c_str());
  iFileMeeting.open(meetingPath.c_str());
  if (!iFileUser.is_open()) return false;
  if (!iFileMeeting.is_open()) return false;
  char buff[1024];
  std::string tem, line;
  while (iFileUser.good() && !iFileUser.eof()) {
    memset(buff, 0, 1024);
    iFileUser.getline(buff, 1024);
    line = buff;  // handle the data gotten form file
    if (line.size() > 3) {
      userList_.push_back(stringToUser(line));
    }
  }
  iFileUser.close();
  while (iFileMeeting.good() && !iFileMeeting.eof()) {
    memset(buff, 0, 1024);
    iFileMeeting.getline(buff, 1024);
    line = buff;
    if (line.size() > 3) {
      meetingList_.push_back(stringToMeeting(line));
    }
  }
  iFileMeeting.close();
  return true;
}
bool Storage::writeToFile(const char *fpath) {
  std::string userPath, meetingPath;
  userPath += fpath;
  userPath += "User.csv";
  meetingPath += fpath;
  meetingPath += "Meeting.csv";
  std::ofstream oFileUser(userPath.c_str());
  std::ofstream oFileMeeting(meetingPath.c_str());
  if (!oFileUser.is_open()) return false;
  if (!oFileMeeting.is_open()) return false;
  std::list<User>::iterator iter1 = userList_.begin();
  for (; iter1 != userList_.end(); iter1++) {
    oFileUser << "\"" << iter1 -> getName() << "\","
	      << "\"" << iter1 -> getPassword() << "\","
	      << "\"" << iter1 -> getEmail() << "\","
	      << "\"" << iter1 -> getPhone() << "\"" << std::endl;
  }
  oFileUser.close();
  std::list<Meeting>::iterator iter2 = meetingList_.begin();
  for (; iter2 != meetingList_.end(); iter2++) {
    oFileMeeting << "\"" << iter2 -> getSponsor() << "\","
	      << "\"" << iter2 -> getParticipator() << "\","
	      << "\"" << Date::dateToString(iter2 -> getStartDate()) << "\","
	      << "\"" << Date::dateToString(iter2 -> getEndDate()) << "\","
	      << "\"" << iter2 -> getTitle() << "\"" << std::endl;
  }
  oFileMeeting.close();
  return true;
}
Storage* Storage::getInstance(void) {
  if (instance_ != NULL) {
    return instance_;
  } else {
    Storage* tem = new Storage();
    return tem;
  }
}
Storage::~Storage() {}
void Storage::createUser(const User& addUser) {
  userList_.push_back(addUser);
}
std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
  std::list<User> listUser;
  std::list<User>::iterator iter = userList_.begin();
  for (; iter != userList_.end(); iter++) {
    if (filter(*iter)) listUser.push_back(*iter);
  }
  return listUser;
}
int Storage::updateUser(std::function<bool(const User&)> filter,
  std::function<void(User&)> switcher) {
  std::list<User>::iterator iter = userList_.begin();
  int num = 0;
  for (; iter != userList_.end(); iter++) {
    if (filter(*iter)) {
      num++;
      switcher(*iter);
    }
  }
  return num;
}
int Storage::deleteUser(std::function<bool(const User&)> filter) {
  std::list<User>::iterator iter = userList_.begin();
  int num = 0;
  for (; iter != userList_.end();) {
    if (filter(*iter)) {
      num++;
      iter = userList_.erase(iter);
    } else {
      iter++;
    }
  }
  return num;
}
void Storage::createMeeting(const Meeting& addMeeting) {
  meetingList_.push_back(addMeeting);
}
std::list<Meeting> Storage::queryMeeting(
  std::function<bool(const Meeting&)> filter) {
  std::list<Meeting> listMeeting;
  std::list<Meeting>::iterator iter = meetingList_.begin();
  for (; iter != meetingList_.end(); iter++) {
    if (filter(*iter)) listMeeting.push_back(*iter);
  }
  return listMeeting;
}
int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
  std::function<void(Meeting&)> switcher) {
  std::list<Meeting>::iterator iter = meetingList_.begin();
  int num = 0;
  for (; iter != meetingList_.end(); iter++) {
    if (filter(*iter)) {
      num++;
      switcher(*iter);
    }
  }
  return num;
}
int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
  std::list<Meeting>::iterator iter = meetingList_.begin();
  int num = 0;
  for (; iter != meetingList_.end();) {
    if (filter(*iter)) {
      num++;
      iter = meetingList_.erase(iter);
    } else {
      iter++;
    }
  }
  return num;
}
bool Storage::sync(void) {
  bool judge = writeToFile("./");
  return judge;
}
