#ifndef CHATSIMULATOR_SERVERWINDOW_H_
#define CHATSIMULATOR_SERVERWINDOW_H_

#include <cstdint>
#include <memory>

#include <QString>
#include <QtWidgets>
#include "ui_server_window.h"

namespace ChatSimulator {

class Server;

class ServerWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit ServerWindow(const Server *const server,
                        QWidget *parent = Q_NULLPTR);
 signals:
  // ����������� ������� �� ���������� ������������ � ��������������� user_id
  void AddUser(const QString &username);
  // ����������� ������� �� �������� ������������ � ��������������� user_id
  // � ���������������� �������� QLIstWidget
  void DeleteUser(const std::int64_t user_id, QListWidgetItem *const item);
  // ����������� ������� �� �������� ���� ����
  // ������������ � ���������������� user_id
  void OpenUserWindow(const std::int64_t user_id);

 public slots:
  // ��������� ��������� message ������������ � ��������������� user_id
  // � ������ username �� �������, � ��� ���������� �� �����
  void AppendMessageSlot(const std::int64_t user_id, const QString &username,
                         const QString &message);
  // ���������� � ������ ������������� ������������
  // � ��������������� user_id � ������ username
  void UpdateUsersListView(const std::int64_t user_id, const QString &username);

 private slots:
  void on_addUser_clicked();
  void on_deleteUser_clicked();
  void on_usersListWidget_itemDoubleClicked(QListWidgetItem *item);

 private:
  std::int64_t ItemGetUserId(QListWidgetItem *item);

  std::unique_ptr<Ui::ServerWindowClass> ui_;
};

}  // namespace ChatSimulator

#endif  // CHATSIMULATOR_SERVERWINDOW_H_