#ifndef NOTICE_H
#define NOTICE_H

#endif // NOTICE_H
#include <QString>
#include <QDateTime>

class Notice
{
private:
  QString date;
  QString text;
  QString tag;
  QString name;

public:
  Notice(int number)
  {
    date = QDateTime::currentDateTime().toString("dd.MM.yyyy; hh:mm:ss");
    text = "New notice " + QString::fromStdString(std::to_string(number));
    name = QString::fromStdString(std::to_string(number));
    tag = "Default notice.";
  }

  Notice(const QString& new_text, const QString& new_tag, const QString& new_name)
  {
    text = new_text;
    tag = new_tag;
    name = new_name;
    date = QDateTime::currentDateTime().toString("dd.MM.yyyy; hh:mm:ss");
  }

  QString GetDate() const
  {
    return date;
  }

  QString GetName() const
  {
    return name;
  }

  QString GetText() const
  {
    return text;
  }

  void SetText(QString new_text)
  {
    text = new_text;
  }

  QString GetTag() const
  {
    return tag;
  }
};
