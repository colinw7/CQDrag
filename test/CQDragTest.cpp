#include <CQDragTest.h>
#include <CQDrag.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QTimer>

#include <iostream>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQDragTest *test = new CQDragTest;

  test->show();

  test->test();

  return app.exec();
}

CQDragTest::
CQDragTest()
{
  QHBoxLayout *layout = new QHBoxLayout(this);

  drag1_ = new CQDrag;
  drag2_ = new CQDrag;

  drag1_->setFixedSize(100, 100);
  drag2_->setFixedSize(100, 100);

  layout->addWidget(drag1_);
  layout->addWidget(drag2_);
}

void
CQDragTest::
test()
{
  QPoint pos1( 2,  2);
  QPoint pos2(20, 20);

  QMouseEvent pressEvent  (QEvent::MouseButtonPress  , pos1, Qt::LeftButton,
                           Qt::LeftButton, Qt::NoModifier);
  QMouseEvent motionEvent (QEvent::MouseMove         , pos2, Qt::LeftButton,
                           Qt::LeftButton, Qt::NoModifier);

  cancelDrag_ = new CQDragCancel(drag1_, pos2);

  connect(drag1_, SIGNAL(dragStart()), cancelDrag_, SLOT(cancelDragStart()));
  connect(drag1_, SIGNAL(dragEnd  ()), cancelDrag_, SLOT(cancelDragEnd  ()));

  QApplication::sendEvent(drag1_, &pressEvent );
  QApplication::sendEvent(drag1_, &motionEvent);

  QApplication::processEvents(QEventLoop::AllEvents);
}

//----

void
CQDragCancel::
cancelDragStart()
{
  std::cerr << "drag start" << std::endl;

  timer_ = new QTimer;

  connect(timer_, SIGNAL(timeout()), this, SLOT(cancelDrag()));

  timer_->start(250);
}

void
CQDragCancel::
cancelDragEnd()
{
  std::cerr << "drag end" << std::endl;

  delete timer_;

  exit(0);
}

void
CQDragCancel::
cancelDrag()
{
  QMouseEvent releaseEvent(QEvent::MouseButtonRelease, pos_, Qt::LeftButton,
                           Qt::LeftButton, Qt::NoModifier);

  QApplication::sendEvent(w_, &releaseEvent);
  QApplication::processEvents(QEventLoop::AllEvents);
}
