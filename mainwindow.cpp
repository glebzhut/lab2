#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

bool operator>(const Notice& n1, const Notice& n2)
{
  return n1.GetDate() > n2.GetDate();
}

bool operator<(const Notice& n1, const Notice& n2)
{
  return n1.GetDate() < n2.GetDate();
}

bool operator==(const Notice& n1, const Notice& n2)
{
  return n1.GetDate() == n2.GetDate();
}

bool SUBString(const QString& sub, const QString& line)
{
  if(sub.size()>line.size())
    return false;
  for(int i = 0; i < int(line.size()-sub.size()+1);i++)
    {
      bool res = true;
      for (int j = 0; j < int(sub.size()) && res;j++)
        if(sub[j] != line[i+j])
          res = false;
      if (res)
        return true;
    }
  return false;
}

void QuickSort(int first, int last, std::vector<Notice>& list)
	{
		Notice x = list[first];
		int i = first, j = last;
		do
		{
			while (list[i] > x)
				i++;
			while (list[j] < x)
				j--;
			if (i <= j)
			{
				if (i < j)
					std::swap(list[i], list[j]);
				i++;
				j--;
			}
		} while (i <= j);
		if (first < j)
			QuickSort(first, j, list);
		if (last > i)
			QuickSort(i, last, list);
	}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::ShowTable()
{
  ui->ListNotes->clear();
  if (notes.size())
    QuickSort(0,int(notes.size()-1),notes);
  for(int i = 0; i < int(notes.size()); i++)
    {
      if (filter.size())
        {
          if(SUBString(filter, notes[i].GetTag()))
            {
              QString new_note = "new note";
              new_note = "Name: "+ notes[i].GetName() + "; Tag: " + notes[i].GetTag() + "; Date: " + notes[i].GetDate();
              ui->ListNotes->addItem(new_note);
            }
        }
      else
        {
          QString new_note = "new note";
          new_note = "Name: "+ notes[i].GetName() + "; Tag: " + notes[i].GetTag() + "; Date: " + notes[i].GetDate();
          ui->ListNotes->addItem(new_note);
        }
    }
}

void MainWindow::ShowArchive()
{
  ui->ListArchive->clear();
  if(archive.size())
    QuickSort(0,int(archive.size()-1),archive);
  for(int i = int(archive.size())-1; i >= 0; i--)
    {
      if (filter.size())
        {
          if(SUBString(filter, archive[i].GetTag()))
            {
              QString new_note = "new note";
              new_note = "Name: "+ archive[i].GetName() + "; Tag: " + archive[i].GetTag() + "; Date: " + archive[i].GetDate();
              ui->ListArchive->addItem(new_note);
            }
        }
      else
        {
          QString new_note = "new note";
          new_note = "Name: "+ archive[i].GetName() + "; Tag: " + archive[i].GetTag() + "; Date: " + archive[i].GetDate();
          ui->ListArchive->addItem(new_note);
        }
    }
}

void MainWindow::on_ButtonPublish_clicked()
{
    QString name = "";
    QString text = "Nothing";
    QString tag = "Default tag";
    if(ui->EnterName->text().size())
      {
        name = ui->EnterName->text();
        ui->EnterName->clear();
      }
    else
      {
        name = QString::fromStdString(std::to_string(number_of_nonamed));
        number_of_nonamed++;
      }
    if(ui->EnterKey->text().size())
      {
        tag = ui->EnterKey->text();
        ui->EnterKey->clear();
      }
    if(ui->EnterNotice->toPlainText().size())
      {
        text = ui->EnterNotice->toPlainText();
        ui->EnterNotice->clear();
      }
    Notice note(text,tag,name);
    notes.push_back(note);
    ShowTable();
    ui->ActionText->setText("Added note");
    ui->ShownNote->clear();
}

void MainWindow::on_ListNotes_itemClicked(QListWidgetItem *item)
{
    ui->ShownNote->clear();
    for (int i = 0; i < int(notes.size());i++)
      if(("Name: "+ notes[i].GetName() + "; Tag: " + notes[i].GetTag() + "; Date: " + notes[i].GetDate()).toStdString()
         == item->text().toStdString())
        {
          ui->ShownNote->setText(notes[i].GetText());
          ui->EnterName->setText(notes[i].GetName());
          ui->EnterKey->setText(notes[i].GetTag() + ".1");
          break;
        }
    ui->ActionText->setText("Shown");
}

void MainWindow::on_ListNotes_itemDoubleClicked(QListWidgetItem *item)
{
  for(int i = 0; i < int(notes.size());i++)
    if(("Name: "+ notes[i].GetName() + "; Tag: " + notes[i].GetTag() + "; Date: " + notes[i].GetDate()).toStdString()
       == item->text().toStdString())
      {
        archive.push_back(notes[i]);
        notes.erase(notes.begin()+i);
        break;
      }
  ShowArchive();
  ShowTable();
  ui->ActionText->setText("Moved to archive");
}

void MainWindow::on_ListArchive_itemClicked(QListWidgetItem *item)
{
  for(int i = 0; i < int(archive.size());i++)
    if(("Name: "+ archive[i].GetName() + "; Tag: " + archive[i].GetTag() + "; Date: " + archive[i].GetDate()).toStdString()
       == item->text().toStdString())
      {
        ui->ShownNote->setText(archive[i].GetText());
        ui->EnterName->setText(archive[i].GetName());
        ui->EnterKey->setText(archive[i].GetTag() + ".1");
        break;
      }
  ui->ActionText->setText("Shown");
}

void MainWindow::on_ListArchive_itemDoubleClicked(QListWidgetItem *item)
{
  for(int i = 0; i < int(archive.size());i++)
    if(("Name: "+ archive[i].GetName() + "; Tag: " + archive[i].GetTag() + "; Date: " + archive[i].GetDate()).toStdString()
       == item->text().toStdString())
      {
        archive.erase(archive.begin()+i);
        break;
      }
  ShowArchive();
  ui->ActionText->setText("Delete");
}

void MainWindow::on_ButtonCommit_clicked()
{
  QString name = "";
  QString text = "Nothing";
  QString tag = "Default tag";
  if(ui->EnterName->text().size())
    {
      name = ui->EnterName->text();
      ui->EnterName->clear();
    }
  else
    {
      name = QString::fromStdString(std::to_string(number_of_nonamed));
      number_of_nonamed++;
    }
  if(ui->EnterKey->text().size())
    {
      tag = ui->EnterKey->text();
      ui->EnterKey->clear();
    }
  if(ui->ShownNote->toPlainText().size())
    {
      text = ui->ShownNote->toPlainText();
      ui->EnterNotice->clear();
    }
  Notice note(text,tag,name);
  notes.push_back(note);
  ShowTable();
  ui->ActionText->setText("Edited note");
  ui->ShownNote->clear();
}

void MainWindow::on_EnterFilter_textChanged(const QString &arg1)
{
  filter = arg1;
  ui->ActionText->setText("Filter changed: " + filter);
  ShowArchive();
  ShowTable();
}
