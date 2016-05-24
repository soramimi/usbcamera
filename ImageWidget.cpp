#include "ImageWidget.h"

#include <QPainter>

ImageWidget::ImageWidget(QWidget *parent)
	: QWidget(parent)
{

}

void ImageWidget::setImage(const QImage &image)
{
	this->image = image;
	update();
}

void ImageWidget::paintEvent(QPaintEvent *)
{
	QPainter pr(this);
	pr.drawImage(0, 0, image);

}
