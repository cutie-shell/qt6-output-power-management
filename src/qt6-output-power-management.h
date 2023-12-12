#pragma once

#include <QtWaylandClient/QtWaylandClient>
#include <QtQml/QQmlEngine>

class OutputPowerManagerV1Private;
class OutputPowerV1Private;
class OutputPowerV1;

class Q_WAYLANDCLIENT_EXPORT OutputPowerManagerV1 
	: public QObject {
	Q_OBJECT
	Q_DECLARE_PRIVATE(OutputPowerManagerV1)
	Q_PROPERTY(bool mode READ mode WRITE setMode NOTIFY modeChanged)
public:
	OutputPowerManagerV1();

	bool mode();
	void setMode(bool mode);

signals:
	void modeChanged();

private:
	OutputPowerManagerV1Private *d_ptr;
};