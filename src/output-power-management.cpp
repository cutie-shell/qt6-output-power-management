#include "output-power-management_p.h"

OutputPowerManagerV1::OutputPowerManagerV1()
	: d_ptr(new OutputPowerManagerV1Private(this)) {}

bool OutputPowerManagerV1::mode() {
	Q_D(OutputPowerManagerV1);
	return d->m_mode;
}

void OutputPowerManagerV1::setMode(bool mode) {
	Q_D(OutputPowerManagerV1);
	if (d->m_mode == mode) return;
	d->m_mode = mode;
	if (d->m_power)
		d->m_power->set_mode(mode);
}

OutputPowerManagerV1Private::OutputPowerManagerV1Private(
	OutputPowerManagerV1 *q
	) : QWaylandClientExtensionTemplate(1),
		q_ptr(q) {
	connect(this, &QWaylandClientExtension::activeChanged, 
		this, &OutputPowerManagerV1Private::onActiveChanged);
}

void OutputPowerManagerV1Private::setMode(bool mode) {
	Q_Q(OutputPowerManagerV1);
	if (m_mode == mode) return;
	m_mode = mode;
	m_old_mode = mode;
	emit q->modeChanged(m_mode);
}

void OutputPowerManagerV1Private::resetMode() {
	Q_Q(OutputPowerManagerV1);
	if (m_mode == m_old_mode) return;
	m_mode = m_old_mode;
	emit q->modeChanged(m_mode);
}

void OutputPowerManagerV1Private::onActiveChanged() {
	if (!isActive()) return;
	m_power = new OutputPowerV1(this, 
		get_output_power(static_cast<QtWaylandClient::QWaylandScreen*>(
			qApp->screens().first()->handle())->output()));
}

OutputPowerV1::OutputPowerV1(
	OutputPowerManagerV1Private *manager,
	struct ::zwlr_output_power_v1 *object
) : QWaylandClientExtensionTemplate(1),
	QtWayland::zwlr_output_power_v1(object),
	m_manager(manager) {}

void OutputPowerV1::zwlr_output_power_v1_mode(uint32_t mode) {
	m_manager->setMode(mode);
}
void OutputPowerV1::zwlr_output_power_v1_failed() {
	m_manager->resetMode();
}