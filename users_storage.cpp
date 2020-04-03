#include "users_storage.h"

namespace ChatSimulator {

UsersStorage::ConstItUser UsersStorage::CheckUserId(const std::int64_t user_id) const {
  auto it = users_.find(user_id);
  if (it != cend(users_)) {
    return it;
  }
  throw QString(u8"Invalid user id");
}

const std::int64_t UsersStorage::AddUser(const QString& username) {
  const std::int64_t user_id{GetFreeUserId()};
  std::unique_ptr<User> user(new User(user_id, username));
  users_[user_id] = std::move(user);
  return user_id;
}

void UsersStorage::DeleteUser(const std::int64_t user_id) {
  try {
    ConstItUser it = CheckUserId(user_id);
    free_id_.push_front(it->first);
    users_.erase(it);
  } catch (QString e) {
    throw e.append(u8" - In UsersStorage::DeleteUser");
  }
}

const QString& UsersStorage::GetUsername(const std::int64_t user_id) const {
  try {
    ConstItUser it = CheckUserId(user_id);
    return it->second->GetUsername();
  } catch (QString e) {
    throw e.append(u8" - In UsersStorage::GetUsername");
  }
}

const std::int64_t UsersStorage::GetFreeUserId() {
  std::int64_t user_id = users_.size();
  if (!free_id_.empty()) {
    user_id = free_id_.front();
    free_id_.pop_front();
  }
  return user_id;
}

const std::unique_ptr<User>& UsersStorage::GetUser(
    const std::int64_t user_id) const {
  try {
    ConstItUser it = CheckUserId(user_id);
    return it->second;
  } catch (QString e) {
    throw e.append(u8" - In UsersStorage::GetUser");
  }
}

}  // namespace ChatSimulator