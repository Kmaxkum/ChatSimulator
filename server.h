#ifndef CHATSIMULATOR_SERVER_H_
#define CHATSIMULATOR_SERVER_H_

#include <cstdint>
#include <memory>

#include <QWidget>
#include <QtCore>

#include "server_window.h"
#include "users_storage.h"

namespace ChatSimulator {

class Server : public QObject {
  Q_OBJECT

 public:
  explicit Server(QObject* parent = Q_NULLPTR);

 signals:
  // ����������� ��������� message ������������ � ��������������� user_id
  // � ������ username ������������ ������
  void AppendMessageSignal(const std::int64_t user_id, const QString& username,
                           const QString& message);

 public slots:
  // ��������� ��������� message �� ������������ � ��������������� user_id
  void SendMessageSlot(const std::int64_t user_id, const QString& message);
  // ������� ���� ���� ������������ � ��������������� user_id
  void OpenUserWindow(const int64_t user_id);
  // ���������� �������� ������������ � ������ username
  const std::int64_t AddUser(const QString& username);
  // �������� ������������ � ��������������� user_id
  // � ���������������� �������� QLIstWidget
  void DeleteUser(const int64_t user_id,
                  QListWidgetItem* const item = Q_NULLPTR);

 private:
  // ��������� ��� �������� ��������� � ����������� �� �����������
  struct Message {
    const std::int64_t user_id;
    const QString user_name;
    const QString message;
    Message(const std::int64_t user_id, const QString user_name,
            const QString message)
        : user_id(std::move(user_id)),
          user_name(std::move(user_name)),
          message(std::move(message)) {}
  };

  UsersStorage users_;
  std::list<Message> messages_;
  const std::unique_ptr<ServerWindow> main_window_;
};

}  // namespace ChatSimulator

#endif  // CHATSIMULATOR_SERVER_H_