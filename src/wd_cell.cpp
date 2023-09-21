#include "wd_cell.h"
#include "ui_wd_cell.h"
#include <QScrollBar>

wd_cell::wd_cell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wd_cell),

	font_size(12), edit_font("Menlo", font_size),
	line_count(1)
{
	Q_UNUSED(font_size);
	
    ui->setupUi(this);

	// 输入框设置
	ui->text_input->setFont(edit_font);
    connect(ui->text_input->document(), &QTextDocument::contentsChanged, this, &wd_cell::text_content_adjust);
	min_height = font_size * 6;
	ui->text_input->setMinimumHeight(min_height);
	ui->text_input->setFixedHeight(min_height);

	// 行号设置
	ui->text_line_num->setReadOnly(true);
	ui->text_line_num->append("1");
	ui->text_line_num->setFont(edit_font);
	ui->text_line_num->setAlignment(Qt::AlignRight);
	connect(this, &wd_cell::editor_changed, this, &wd_cell::line_num_content_adjust);
	line_num_content_adjust();
}

wd_cell::~wd_cell()
{
    delete ui;
}

void wd_cell::text_content_adjust(){
	//调整文字高度并设置
	QTextDocument *doc = ui->text_input->document();
	int old_height = ui->text_input->size().height();
	doc->adjustSize();
	//获得调整之后的Edit高度
	int height = doc->size().height();
	int width = doc->size().width();

	line_count = doc->lineCount();

	// 如果宽高小于最小宽高，设置为最小宽高
	if (height < min_height)
	{
		ui->text_input->setFixedHeight(min_height);
		emit editor_changed(0);
		return;
	}
	int addition = 5;
	//重新设置Edit高度
	if (width > ui->text_input->width()){
		// qDebug() << "first:" << old_height;
		// qDebug() << "second" << height + ui->text_input->horizontalScrollBar()->height();
		addition = ui->text_input->horizontalScrollBar()->height();
	}
	else{
		// qDebug() << "first" << old_height;
		// qDebug() << "second" << height + 5;
		addition = 5;
	}
	ui->text_input->setFixedHeight(height + addition);
	if (old_height != height + addition)
		emit editor_changed(height + addition - old_height);
}

void wd_cell::line_num_content_adjust(){
	int height = ui->text_input->height();
	ui->text_line_num->setFixedHeight(height);

	QTextDocument *doc = ui->text_line_num->document();
	while (doc->lineCount() < line_count){
		ui->text_line_num->append(QString::number(doc->lineCount() + 1));
	}

	QTextCursor storeCursorPos = ui->text_line_num->textCursor(); 
	while (doc->lineCount() > line_count){
		ui->text_line_num->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor); 
		ui->text_line_num->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor); 
		ui->text_line_num->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor); 
		ui->text_line_num->textCursor().removeSelectedText(); 
		ui->text_line_num->textCursor().deletePreviousChar(); 
		ui->text_line_num->setTextCursor(storeCursorPos); 
	}
}
