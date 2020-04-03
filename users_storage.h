#ifndef CHATSIMULATOR_USERSSTORAGE_H_
#define CHATSIMULATOR_USERSSTORAGE_H_

#include <cstdint>
#include <forward_list>
#include <memory>
#include <unordered_map>

#include <QString>
#include "user.h"

namespace ChatSimulator {

class User;

class UsersStorage {
 public:
  // ���������� ������ ������������ � ������ username
  const std::int64_t AddUser(const QString& username);
  // �������� ������������ � ��������������� user_id
  void DeleteUser(const std::int64_t user_id);
  // ���������� ������ �� ��� ������������ � ��������������� user_id
  const QString& GetUsername(const std::int64_t user_id) const;
  // ���������� ������ �� ����� ��������� � ��������������� ������� �
  // ������������ � ��������������� user_id
  const std::unique_ptr<User>& GetUser(const std::int64_t user_id) const;

 private:
  using ConstItUser =
      std::unordered_map<std::int64_t, std::unique_ptr<User>>::const_iterator;
  // ���������� ��������� ��������� �������������
  const std::int64_t GetFreeUserId();
  // ��������� ��������� ������������ � ��������������� user_id � ���������
  ConstItUser CheckUserId(const std::int64_t user_id) const;

  std::forward_list<std::int64_t> free_id_;
  std::unordered_map<std::int64_t, std::unique_ptr<User>> users_;
};

}  // namespace ChatSimulator

#endif  // CHATSIMULATOR_USERSSTORAGE_H_