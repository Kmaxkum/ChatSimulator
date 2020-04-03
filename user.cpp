#include "user.h"

#include "chat_view.h"

namespace ChatSimulator {

User::User(const std::int64_t id, const QString& name, QObject* parent)
    : QObject(parent),
      user_id_(id),
      username_(name),
      chat_view_(new ChatView(this)) {
  OpenWindow();
}

void User::OpenWindow() { this->chat_view_->show(); }

const QString& User::GetUsername() const { return username_; }

const std::int64_t User::GetUserId() const { return user_id_; }

void User::SendMessageSlot(const QString& message) {
  emit SendMessageSignal(this->user_id_, message);
}

void User::AppendMessageSlot(const std::int64_t user_id,
                             const QString& username, const QString& message) {
  emit AppendMessageSignal(user_id, username, message);
}

}  // namespace ChatSimulator