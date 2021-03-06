#include "stockgraphonemonth.h"
#include "ui_stockgraph.h"
#include "helper/helper.h"

StockGraphOneMonth::StockGraphOneMonth(QWidget *parent) :
  StockGraph(parent) {
  initTimeRange();
  setCandlestickBinSize();
}

StockGraphOneMonth::~StockGraphOneMonth() {

}

void StockGraphOneMonth::setStock(Stock *other_stock) {
  stock = other_stock;
  clearData();
  lineChart->setData({}, {});
  candleStick->setData({}, {}, {}, {}, {});
  updateData(true);
}

void StockGraphOneMonth::updateData(bool firstTime = false) {
  stock->updateDataByDay();
  QJsonObject dataByDay = stock->getDataByDay();

  QVector<double> time, o, h, l, c;
  time = helper::convert_to_vector(dataByDay, "t");
  o = helper::convert_to_vector(dataByDay, "o");
  h = helper::convert_to_vector(dataByDay, "h");
  l = helper::convert_to_vector(dataByDay, "l");
  c = helper::convert_to_vector(dataByDay, "c");

  double now = QDateTime::currentDateTime().toTime_t();
  //2628288 is the number of seconds per month: Here we show a 1-month interval
  ui->plot->xAxis->setRange(now - 2628288, now);

  for (int i = 0; i < time.size(); i++) {
    if (time[i] >= now - 2628288 && time[i] <= now) {
      timestamp.append(time[i]);
      open.append(o[i]);
      high.append(h[i]);
      low.append(l[i]);
      close.append(c[i]);
      lineChart->addData(time[i], c[i]);
      candleStick->addData(time[i], o[i], h[i], l[i], c[i]);
    }
  }

  if (firstTime) {
    plot();
  }
}

void StockGraphOneMonth::initTimeRange() {
  QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
  dateTimeTicker->setDateTimeSpec(Qt::UTC);
  dateTimeTicker->setDateTimeFormat("dd/MM/yyyy");
  double now = QDateTime::currentDateTime().toTime_t();
  //2628288 is the number of seconds per month: Here we show a 1-month interval
  ui->plot->xAxis->setRange(now - 2628288, now);
  ui->plot->yAxis->setTickLabels(false);
  ui->plot->xAxis->ticker()->setTickCount(10);
  ui->plot->xAxis->setTicker(dateTimeTicker);
  ui->plot->xAxis->setTickLabelRotation(15);
  ui->plot->rescaleAxes();
  ui->plot->xAxis->scaleRange(1.025, ui->plot->xAxis->range().center());
  ui->plot->yAxis->scaleRange(1.1, ui->plot->yAxis->range().center());
}

void StockGraphOneMonth::setCandlestickBinSize() {
  candleStick->setWidth(3600 * 24 * 0.2);
}

void StockGraphOneMonth::realtimeDataSlot() {
//  if (stock == nullptr) {
//    return;
//  }

//  static QTime time(QTime::currentTime());
//  //calculate two new data points:
//  double key = time.elapsed() /
//               1000.0; // time elapsed since start of demo, in seconds
//  static double lastPointKey = -1e9;

//  if (key - lastPointKey >= 200) { // 200 seconds
//    updateData();
//    lastPointKey = key;
//  }
}
