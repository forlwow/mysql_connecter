#include "wd_sql_result.h"
#include "ui_wd_sql_result.h"

#include <QScrollBar>

wd_sql_result::wd_sql_result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wd_sql_result),

	font_size(12),
	edit_font("Menlo", font_size),

	line_count(1)
{
    ui->setupUi(this);
	ui->horizontalLayout->setAlignment(Qt::AlignTop);

	// 输入框设置
	ui->text_input->setFont(edit_font);
    connect(ui->text_input->document(), &QTextDocument::contentsChanged, this, text_content_adjust);
	min_height = font_size * 6;
	ui->text_input->setMinimumHeight(min_height);
	ui->text_input->setFixedHeight(min_height);

	// 行号设置
	ui->text_line_num->setReadOnly(true);
	ui->text_line_num->append("1");
	ui->text_line_num->setFont(edit_font);
	connect(this, editor_changed, this, line_num_content_adjust);
	line_num_content_adjust();

	
}

wd_sql_result::~wd_sql_result()
{
    delete ui;
}

void wd_sql_result::text_content_adjust(){
	//调整文字高度并设置
	QTextDocument *doc = ui->text_input->document();
	doc->adjustSize();
	//获得调整之后的Edit高度
	int height = doc->size().height();
	int width = doc->size().width();

	line_count = doc->lineCount();

	// 如果宽高小于最小宽高，设置为最小宽高
	if (height < min_height)
	{
		ui->text_input->setFixedHeight(min_height);
		emit editor_changed();
		return;
	}

	//重新设置Edit高度
	if (width > ui->text_input->width())
		ui->text_input->setFixedHeight(height + ui->text_input->horizontalScrollBar()->height());
	else
		ui->text_input->setFixedHeight(height + 5);
	emit editor_changed();
}

void wd_sql_result::line_num_content_adjust(){
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

