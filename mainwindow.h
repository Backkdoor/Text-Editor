#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include<QWidget>
#include<QTextEdit>
#include<QToolBar>
#include<QPlainTextEdit>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

class MainWindow : public QMainWindow
{

    Q_OBJECT;
public:
    MainWindow();


private slots:
    void CutFileSlot();
    void CopyFileSlot();
    void OpenFileSlot();
    void SaveFileSlot();
    void NewFileSlot();


private:
    void CreateGUI();
    QTextEdit *m_text_editor;
public:
    static int saved;

};

#endif // MAINWINDOW_H
