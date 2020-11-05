#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Notice.h"
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_ButtonPublish_clicked();

  void on_ListNotes_itemClicked(QListWidgetItem *item);

  void on_ListNotes_itemDoubleClicked(QListWidgetItem *item);

  void on_ListArchive_itemClicked(QListWidgetItem *item);

  void on_ListArchive_itemDoubleClicked(QListWidgetItem *item);

  void on_ButtonCommit_clicked();

  void on_EnterFilter_textChanged(const QString &arg1);

private:
  Ui::MainWindow *ui;
  std::vector<Notice> notes;
  std::vector<Notice> archive;
  int number_of_nonamed = 0;
  QString filter;

  void ShowTable();
  void ShowArchive();
};
#endif // MAINWINDOW_H
