#include "server_window.h"

#include "server.h"

namespace ChatSimulator {

ServerWindow::ServerWindow(const Server *const server, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::ServerWindowClass()) {
  ui_->setupUi(this);

  this->setWindowTitle(u8"ChatSimulator");

  connect(server, &Server::AppendMessageSignal, this,
          &ServerWindow::AppendMessageSlot);
  connect(ui_->usersListWidget, &QListWidget::itemDoubleClicked, this,
          &ServerWindow::on_usersListWidget_itemDoubleClicked);
  connect(this, &ServerWindow::OpenUserWindow, server, &Server::OpenUserWindow);
  connect(this, &ServerWindow::DeleteUser, server, &Server::DeleteUser);
  connect(this, &ServerWindow::AddUser, server, &Server::AddUser);
}

std::int64_t ServerWindow::ItemGetUserId(QListWidgetItem *item) {
  return item->data(Qt::UserRole).value<std::int64_t>();
}

void ServerWindow::UpdateUsersListView(const std::int64_t user_id,
                                       const QString &username) {
  QListWidgetItem *item = new QListWidgetItem(ui_->usersListWidget);
  QVariant var(user_id);
  QString role = QString(u8"user_id: %1 (username: %2)")
                     .arg(QString::fromStdString(std::to_string(user_id)))
                     .arg(username);
  item->setData(Qt::DisplayRole, role);
  item->setData(Qt::UserRole, var);
}

void ServerWindow::on_addUser_clicked() {
  bool flag = false;
  QString name =
      QInputDialog::getText(this, QString(u8"Введите имя пользователя"),
                            QString(u8"Имя пользователя:"), QLineEdit::Normal,
                            QDir::home().dirName(), &flag);
  if (flag && !name.isEmpty()) {
    emit AddUser(name);
  }
}

void ServerWindow::on_deleteUser_clicked() {
  auto item = ui_->usersListWidget->currentItem();
  if (item != Q_NULLPTR) {
    const int64_t user_id = ItemGetUserId(item);
    emit DeleteUser(user_id, item);
  }
}

void ServerWindow::AppendMessageSlot(const std::int64_t user_id,
                                     const QString &username,
                                     const QString &message) {
  ui_->chatMessageListWidget->addItem(
      QString(u8"Username: %1 (user_id: %2)\nMessage: %3")
          .arg(username)
          .arg(QString::fromStdString(std::to_string(user_id)))
          .arg(message));
}

void ServerWindow::on_usersListWidget_itemDoubleClicked(QListWidgetItem *item) {
  emit OpenUserWindow(ItemGetUserId(item));
}

}  // namespace ChatSimulator