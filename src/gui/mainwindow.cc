#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->query, &QLineEdit::returnPressed, this, &MainWindow::on_btnQuery_clicked);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_btnQuery_clicked() {
	ui->result->clear();
	auto ids = doc.recommend(ui->query->text().toStdString().data(), 5);
	if (ids.empty()) {
		ui->result->append("找不到电影");
	} else {
		ui->result->append("为你推荐：");
		for (int id: ids)
			ui->result->append(doc.title(id).data());
	}
}

void MainWindow::on_btnSearch_clicked() {
	ui->result->clear();
	auto ol = doc.search(ui->query->text().toStdString().data());
	map<List<int>>(ol, [&] (auto& a) { return a[2]; }).each([&] (int id) {
		ui->result->append(doc.title(id).data());
	});
	ui->result->verticalScrollBar()->triggerAction(QScrollBar::SliderToMinimum);
}
