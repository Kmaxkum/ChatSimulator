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
  // Добавление нового пользователя с именем username
  const std::int64_t AddUser(const QString& username);
  // Удаление пользователя с идентификатором user_id
  void DeleteUser(const std::int64_t user_id);
  // Возвращает ссылку на имя пользователя с идентификатором user_id
  const QString& GetUsername(const std::int64_t user_id) const;
  // Возвращает ссылку на умный указатель с предоставлением доступа к
  // пользователю с идентификатором user_id
  const std::unique_ptr<User>& GetUser(const std::int64_t user_id) const;

 private:
  using ConstItUser =
      std::unordered_map<std::int64_t, std::unique_ptr<User>>::const_iterator;
  // Возвращает следующий свободный идентификатор
  const std::int64_t GetFreeUserId();
  // Проверяет наличение пользователя с идентификатором user_id в хранилище
  ConstItUser CheckUserId(const std::int64_t user_id) const;

  std::forward_list<std::int64_t> free_id_;
  std::unordered_map<std::int64_t, std::unique_ptr<User>> users_;
};

}  // namespace ChatSimulator

#endif  // CHATSIMULATOR_USERSSTORAGE_H_