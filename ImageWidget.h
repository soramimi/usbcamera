#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>

class ImageWidget : public QWidget
{
	Q_OBJECT
private:
	QImage image;
public:
	explicit ImageWidget(QWidget *parent = 0);

	void setImage(QImage const &image);

	QImage getImage() const
	{
		return image;
	}

signals:

public slots:

	// QWidget interface
protected:
	void paintEvent(QPaintEvent *);
};

#endif // IMAGEWIDGET_H
