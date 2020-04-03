#ifndef CHATSIMULATOR_CHATVIEW_H_
#define CHATSIMULATOR_CHATVIEW_H_

#include <cstdint>

#include <QWidget>
#include "ui_chat_view.h"

namespace ChatSimulator {

class User;

class ChatView : public QWidget {
  Q_OBJECT

 public:
  explicit ChatView(const User* const user, QWidget* parent = Q_NULLPTR);

 signals:
  // Отправление сообщения message подключенным слотам
  void SendMessageSignal(const QString& message);

 public slots:
  // Получение сообщения message пользователя с идентификатором user_id
  // и именем username, и его добавление на форму
  void AppendMessageSlot(const std::int64_t user_id, const QString& username,
                         const QString& message);

 private slots:
  void on_sendMessage_clicked();

 private:
  std::unique_ptr<Ui::ChatView> ui_;
};

}  // namespace ChatSimulator

#endif  // CHATSIMULATOR_CHATVIEW_H_