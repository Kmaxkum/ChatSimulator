#include "chat_view.h"

#include "user.h"

namespace ChatSimulator {

ChatView::ChatView(const User* const user, QWidget* parent)
    : QWidget(parent), ui_(new Ui::ChatView()) {
  ui_->setupUi(this);

  this->setWindowTitle(
      QString(u8"Username: %1 (user_id: %2)")
          .arg(user->GetUsername())
          .arg(QString::fromStdString(std::to_string(user->GetUserId()))));

  connect(user, &User::AppendMessageSignal, this, &ChatView::AppendMessageSlot);
  connect(this, &ChatView::SendMessageSignal, user, &User::SendMessageSlot);
}

void ChatView::AppendMessageSlot(const std::int64_t user_id,
                                 const QString& username,
                                 const QString& message) {
  ui_->chatBrowser->append(
      QString(u8"Username: %1 (user_id: %2)\nMessage: %3")
          .arg(username)
          .arg(QString::fromStdString(std::to_string(user_id)))
          .arg(message));
}

void ChatView::on_sendMessage_clicked() {
  const QString message = ui_->messageEdit->toPlainText();
  if (!message.isEmpty()) {
    emit SendMessageSignal(message);
  }
}

}  // namespace ChatSimulator
