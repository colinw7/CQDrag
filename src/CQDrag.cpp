#include <CQDrag.h>

#include <QApplication>
#include <QMimeData>
#include <QDrag>
#include <QDragMoveEvent>
#include <QPainter>

#include <drag.xpm>

CQDrag::
CQDrag(QWidget *parent) :
 QWidget(parent), pressed_(false), count_(0)
{
  setAcceptDrops(true);
}

void
CQDrag::
paintEvent(QPaintEvent *)
{
  QPainter p(this);

  p.setPen(QColor(0,0,0));

  p.drawText(rect(), QString("%1").arg(count_));
}

void
CQDrag::
mousePressEvent(QMouseEvent *event)
{
  pressPos_ = event->pos();
  pressed_  = true;

  QWidget::mousePressEvent(event);
}

void
CQDrag::
mouseMoveEvent(QMouseEvent *event)
{
  // set press point (if not already set)
  if (! pressed_) {
    pressPos_ = event->pos();
    pressed_  = true;
  }

  // Ignore if left button isn't pressed
  if (! (event->buttons() & Qt::LeftButton))
    return;

  // If the distance is too small then return
  if ((event->pos() - pressPos_).manhattanLength() < QApplication::startDragDistance())
    return;

  emit dragStart();

  // initiate drag
  QDrag *drag = new QDrag(this);

  drag->setPixmap(QPixmap(drag_data));

  QMimeData *mimeData = new QMimeData;

  mimeData->setData("action", "CQDrag");

  drag->setMimeData(mimeData);

  drag->exec();

  emit dragEnd();
}

void
CQDrag::
mouseReleaseEvent(QMouseEvent *)
{
  // reset pressed
  pressed_ = false;
}

void
CQDrag::
dragEnterEvent(QDragEnterEvent *event)
{
  if (! dragValid(event->mimeData())) {
    event->ignore();
    return;
  }

  event->acceptProposedAction();
}

void
CQDrag::
dragMoveEvent(QDragMoveEvent *event)
{
  if (! dragValid(event->mimeData())) {
    event->ignore();
    return;
  }

  event->acceptProposedAction();
}

void
CQDrag::
dropEvent(QDropEvent *event)
{
  if (! dragValid(event->mimeData())) {
    event->ignore();
    return;
  }

  ++count_;

  update();

  event->acceptProposedAction();
}

bool
CQDrag::
dragValid(const QMimeData *m) const
{
  // Only accept if it's our request
  QStringList formats = m->formats();

  if (! formats.contains("action") || m->data("action") != "CQDrag")
    return false;

  return true;
}
