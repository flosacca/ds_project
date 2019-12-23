#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "doc.h"

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
    void on_btnQuery_clicked();
	void on_btnSearch_clicked();

private:
	Ui::MainWindow* ui;
	Doc doc;
};

#endif // MAINWINDOW_H
