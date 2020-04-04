#ifndef CHATSIMULATOR_USER_H_
#define CHATSIMULATOR_USER_H_

#include <cstdint>
#include <memory>

#include <QObject>
#include <QString>
#include "chat_view.h"

namespace ChatSimulator {

class User : public QObject {
  Q_OBJECT

 public:
  explicit User(const std::int64_t id, const QString& name,
                QObject* parent = Q_NULLPTR);
  void OpenWindow();
  const QString& GetUsername() const;
  const std::int64_t GetUserId() const;

 signals:
  // ����������� ��������� message ������������ � ��������������� user_id �� ������
  void SendMessageSignal(const std::int64_t user_id, const QString& message);
  // ����������� ��������� message ������������ � ��������������� user_id
  // � ������ username ������������ ������ ������� chat_view_
  void AppendMessageSignal(const std::int64_t user_id, const QString& username,
                           const QString& message);

 public slots:
  // ��������� ��������� message �� ������� chat_view_
  void SendMessageSlot(const QString& message);
  // ���������� ��������� message ������������ � ��������������� user_id
  // � ������ username �� �������
  void AppendMessageSlot(const std::int64_t user_id, const QString& username,
                         const QString& message);

 private:
  const std::int64_t user_id_;
  const QString username_;
  const std::unique_ptr<ChatView> chat_view_;
};

}  // namespace ChatSimulator

#endif  // CHATSIMULATOR_USER_H_
