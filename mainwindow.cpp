#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() : m_text_editor(new QTextEdit)
{
    setCentralWidget(m_text_editor);
    CreateGUI();
}

void MainWindow::CreateGUI()
{
    QMenu *NewFile = menuBar()->addMenu("&File");
    QToolBar *toolbar = addToolBar("File");
    QIcon NewIcon = QIcon::fromTheme("document-new",QIcon(":/images/new.png"));
    QAction *NewFileAction = new QAction(NewIcon,"New",this);
    connect(NewFileAction,&QAction::triggered,this,&MainWindow::NewFileSlot);
    NewFile->addAction(NewFileAction);
    toolbar->addAction(NewFileAction);
    NewFile->addSeparator();
    toolbar->addSeparator();

    QIcon OpenFileIcon = QIcon::fromTheme("document-open",QIcon(":/images/open.png"));
    QAction *OpenFile = new QAction(OpenFileIcon,"Open",this);
    NewFile->addAction(OpenFile);
    toolbar->addAction(OpenFile);
    NewFile->addSeparator();
    toolbar->addSeparator();
    connect(OpenFile,&QAction::triggered,this,&MainWindow::OpenFileSlot);

    QIcon SaveFileIcon = QIcon::fromTheme("document-save",QIcon(":/images/save.png"));
    QAction *SaveFile = new QAction(SaveFileIcon,"Save",this);
    NewFile->addAction(SaveFile);
    toolbar->addAction(SaveFile);
    NewFile->addSeparator();
    toolbar->addSeparator();
    connect(SaveFile,&QAction::triggered,this,&MainWindow::SaveFileSlot);

    QIcon SaveAsFileIcon = QIcon::fromTheme("document-save",QIcon(":/images/save.png"));
    QAction *SaveAsFile = new QAction(SaveAsFileIcon,"SaveAs",this);
    NewFile->addAction(SaveAsFile);
    toolbar->addAction(SaveAsFile);
    NewFile->addSeparator();

    QMenu *Edit = menuBar()->addMenu("Edit");
    QIcon CopyFileIcon = QIcon::fromTheme("document-copy",QIcon(":/images/copy.png"));
    QAction *CopyFile = new QAction(CopyFileIcon,"Copy",this);
    Edit->addAction(CopyFile);
    toolbar->addAction(CopyFile);
    connect(CopyFile,&QAction::triggered,this,&MainWindow::CopyFileSlot);

    QIcon CutFileIcon = QIcon::fromTheme("document-cut",QIcon(":/images/cut.png"));
    QAction *CutFile = new QAction(CutFileIcon,"Cut",this);
    Edit->addAction(CutFile);
    toolbar->addAction(CutFile);
    connect(CutFile,&QAction::triggered,this,&MainWindow::CutFileSlot);

}

 void MainWindow :: CutFileSlot()
 {
    m_text_editor->cut();
 }

 void MainWindow:: CopyFileSlot()
 {
     m_text_editor->copy();
 }

 void MainWindow:: OpenFileSlot()
 {

     QString filename = QFileDialog::getOpenFileName(this, "Open File", "/", "*.txt");
     QFile file(filename);
     if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         return;
     }
     m_text_editor->setText(file.readAll());
 }

 void MainWindow:: SaveFileSlot()
 {
     QFileDialog *dialog = new QFileDialog(this);
     dialog->setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
     if(dialog->exec() != QDialog::Accepted)
         return;
     QFile file(dialog->selectedFiles().first());
     file.open(QIODevice::WriteOnly);
     QTextStream out(&file);
     out << m_text_editor->toPlainText();

 }

 void MainWindow::NewFileSlot()
 {
     if(m_text_editor->document()->isModified())
     {

       int ret =  QMessageBox::warning(this, "Warning!!", "Do you want to save the file?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);


       switch (ret) {
       case QMessageBox::Yes:
       {
           SaveFileSlot();
            m_text_editor->clear();
           break;
       }
       case QMessageBox::No:
           m_text_editor->clear();
           break;
       default:
           break;
       }
  }
     else
     {
         m_text_editor->clear();

     }
}
