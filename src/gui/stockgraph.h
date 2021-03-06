#ifndef STOCKGRAPH_H
#define STOCKGRAPH_H

#include <QTimer>
#include <QWidget>
#include "components/stock.h"
#include <QVariant>
#include "library/qcustomplot.h"
#include "components/stock.h"

namespace Ui {
class StockGraph;
}

class StockGraph : public QWidget {
  Q_OBJECT

 public:
  explicit StockGraph(QWidget *parent = nullptr);
  ~StockGraph();
  void clearData();
  void plot();
  void initLineChart();
  void initCandleStick();
  virtual void setStock(Stock *other_stock) = 0;
  virtual void updateData(bool firstTime) = 0;
  virtual void initTimeRange() = 0;
  virtual void setCandlestickBinSize() = 0;

 protected slots:
  virtual void realtimeDataSlot() = 0;
  void mouse_press(QMouseEvent *event);

 protected:
  Stock *stock;
  Ui::StockGraph *ui;
  QCPGraph *lineChart;
  QCPFinancial *candleStick;
  QVector<double> timestamp, open, high, low, close;
  QTimer dataTimer;
  QCPItemTracer *tracer;
  QCPItemText *textLabel;
};

#define StockGraph_iid "com.acme.StockGraph"

Q_DECLARE_INTERFACE(StockGraph, StockGraph_iid)

#endif // STOCKGRAPH_H
