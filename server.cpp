#include "server.h"

#include <QDebug>
#include "user.h"

namespace ChatSimulator {

Server::Server(QObject* parent)
    : QObject(parent), main_window_(new ServerWindow(this)) {
  main_window_->show();
}

const std::int64_t Server::AddUser(const QString& username) {
  const std::int64_t user_id{users_.AddUser(username)};
  User *user = users_.GetUser(user_id).get();

  connect(user, &User::SendMessageSignal, this, &Server::SendMessageSlot);
  connect(this, &Server::AppendMessageSignal, user, &User::AppendMessageSlot);

  main_window_->UpdateUsersListView(user_id, user->GetUsername());

  return user_id;
}

void Server::DeleteUser(const int64_t user_id, QListWidgetItem* const item) {
  User* user = Q_NULLPTR;

  try {
    user = users_.GetUser(user_id).get();
  } catch (QString e) {
    qDebug() << e.append(u8" - In Server::DeleteUser");
    return;
  }

  disconnect(user, &User::SendMessageSignal, this, &Server::SendMessageSlot);
  disconnect(this, &Server::AppendMessageSignal, user,
             &User::AppendMessageSlot);

  users_.DeleteUser(user_id);

  if (item) {
    delete item;
  }
}

void Server::OpenUserWindow(const std::int64_t user_id) {
  try {
    users_.GetUser(user_id).get()->OpenWindow();
  } catch (QString e) {
    qDebug() << e.append(u8" - In Server::OpenUserWindow");
  }
}

void Server::SendMessageSlot(const std::int64_t user_id,
                             const QString& message) {
  try {
    const QString& username = users_.GetUsername(user_id);
    messages_.emplace_back(user_id, username, message);
    emit AppendMessageSignal(user_id, username, message);
  } catch (QString e) {
    qDebug() << e.append(u8" - In Server::SendMessageSlot");
  }
}

}  // namespace ChatSimulator