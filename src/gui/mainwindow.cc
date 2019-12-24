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

const Str InfoItems[] = {
	"导演",
	"编剧",
	"主演",
	"类型",
	"制片国家/地区",
	"语言",
	"上映日期",
	"片长",
	"又名"
};

void MainWindow::on_btnQuery_clicked() {
	ui->result->clear();

	int id = doc.id(ui->query->text().toStdString().data());
	if (id == -1) {
		ui->result->append("数据库中不存在查询的电影");

	} else {
		auto info = doc.info(id);
		for (auto& item: InfoItems)
			ui->result->append((item + "：" + info[item]).data());
		ui->result->append("");

		ui->result->append("剧情简介：");
		ui->result->append(info["summary"].data());
		ui->result->append("");

		auto ids = doc.recommend(id, 5);
		ui->result->append("为你推荐：");
		for (int id: ids)
			ui->result->append(doc.title(id).data());
	}

	ui->result->verticalScrollBar()->triggerAction(QScrollBar::SliderToMinimum);
}

void MainWindow::on_btnSearch_clicked() {
	ui->result->clear();

	ui->result->append("搜索结果：");
	auto ol = doc.search(ui->query->text().toStdString().data());
	if (ol.empty()) {
		ui->result->append("没有找到相关电影");
	} else {
		map<List<int>>(ol, [&] (auto& a) { return a[2]; }).each([&] (int id) {
			ui->result->append(doc.title(id).data());
		});
	}

	ui->result->verticalScrollBar()->triggerAction(QScrollBar::SliderToMinimum);
}
