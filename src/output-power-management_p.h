#pragma once

#include <qt6-output-power-management.h>

#include <wayland-util.h>
#include <QtWaylandClient/QWaylandClientExtensionTemplate>
#include <QtWaylandClient/private/qwaylanddisplay_p.h>
#include <QtWaylandClient/private/qwaylandinputdevice_p.h>
#include <QtWaylandClient/private/qwaylandscreen_p.h>
#include "qwayland-wlr-output-power-management-unstable-v1.h"

class OutputPowerManagerV1Private
	: public QWaylandClientExtensionTemplate<OutputPowerManagerV1Private>
	, public QtWayland::zwlr_output_power_manager_v1 {
	Q_OBJECT
	Q_DECLARE_PUBLIC(OutputPowerManagerV1)
public:
	OutputPowerManagerV1Private(OutputPowerManagerV1 *q);
	void setMode(bool mode);
	void resetMode();

protected:
	OutputPowerV1 *m_power = nullptr;
	bool m_mode = true;
	bool m_old_mode;

private slots:
	void onActiveChanged();

private:
	OutputPowerManagerV1 *q_ptr;
};

class OutputPowerV1
	: public QWaylandClientExtensionTemplate<OutputPowerV1>
	, public QtWayland::zwlr_output_power_v1 {
	Q_OBJECT
public:
	OutputPowerV1(
		OutputPowerManagerV1Private *manager,
		struct ::zwlr_output_power_v1 *object);

protected:
	void zwlr_output_power_v1_mode(uint32_t mode) override;
	void zwlr_output_power_v1_failed() override;

private:
	OutputPowerManagerV1Private *m_manager;
};
