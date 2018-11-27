/*
    Copyright Pranav Gade <pranavgade20@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "iptunnelsetting.h"
#include "iptunnelsetting_p.h"

#include <QDebug>

NetworkManager::IpTunnelSettingPrivate::IpTunnelSettingPrivate()
: name(NM_SETTING_IP_TUNNEL_SETTING_NAME)
, mode(IpTunnelSetting::DefaultMode)
, pathMtuDiscovery(true)
, encapsulationLimit(0)
, flags(0)
, flowLabel(0)
, tos(0)
, ttl(0)
{ }

NetworkManager::IpTunnelSetting::IpTunnelSetting()
: Setting(Setting::IpTunnel)
, d_ptr(new IpTunnelSettingPrivate())
{ }

NetworkManager::IpTunnelSetting::IpTunnelSetting(const Ptr &other)
: Setting(other)
, d_ptr(new IpTunnelSettingPrivate())
{
    setMode(other->mode());
    setPathMtuDiscovery(other->pathMtuDiscovery());
    setEncapsulationLimit(other->encapsulationLimit());
    setFlags(other->flags());
    setFlowLabel(other->flowLabel());
    setMtu(other->mtu());
    setTos(other->tos());
    setTtl(other->ttl());
    setInputKey(other->inputKey());
    setLocal(other->local());
    setOutputKey(other->outputKey());
    setParent(other->parent());
    setRemote(other->remote());
}

NetworkManager::IpTunnelSetting::~IpTunnelSetting()
{
    delete d_ptr;
}

QString NetworkManager::IpTunnelSetting::name() const
{
    Q_D(const IpTunnelSetting);

    return d->name;
}

void NetworkManager::IpTunnelSetting::setMode(NetworkManager::IpTunnelSetting::Mode mode)
{
    Q_D(IpTunnelSetting);

    d->mode = mode;
}

NetworkManager::IpTunnelSetting::Mode NetworkManager::IpTunnelSetting::mode() const
{
    Q_D(const IpTunnelSetting);

    return d->mode;
}

void NetworkManager::IpTunnelSetting::setPathMtuDiscovery(bool discovery)
{
    Q_D(IpTunnelSetting);

    d->pathMtuDiscovery = discovery;
}

bool NetworkManager::IpTunnelSetting::pathMtuDiscovery() const
{
    Q_D(const IpTunnelSetting);

    return d->pathMtuDiscovery;
}

void NetworkManager::IpTunnelSetting::setEncapsulationLimit(quint32 limit)
{
    Q_D(IpTunnelSetting);

    d->encapsulationLimit = limit;
}

quint32 NetworkManager::IpTunnelSetting::encapsulationLimit() const
{
    Q_D(const IpTunnelSetting);

    return d->encapsulationLimit;
}
void NetworkManager::IpTunnelSetting::setFlags(quint32 flags)
{
    Q_D(IpTunnelSetting);

    d->flags = flags;
}

quint32 NetworkManager::IpTunnelSetting::flags() const
{
    Q_D(const IpTunnelSetting);

    return d->flags;
}
void NetworkManager::IpTunnelSetting::setFlowLabel(quint32 label)
{
    Q_D(IpTunnelSetting);

    d->flowLabel = label;
}

quint32 NetworkManager::IpTunnelSetting::flowLabel() const
{
    Q_D(const IpTunnelSetting);

    return d->flowLabel;
}
void NetworkManager::IpTunnelSetting::setMtu(quint32 mtu)
{
    Q_D(IpTunnelSetting);

    d->mtu = mtu;
}

quint32 NetworkManager::IpTunnelSetting::mtu() const
{
    Q_D(const IpTunnelSetting);

    return d->mtu;
}
void NetworkManager::IpTunnelSetting::setTos(quint32 tos)
{
    Q_D(IpTunnelSetting);

    d->tos = tos;
}

quint32 NetworkManager::IpTunnelSetting::tos() const
{
    Q_D(const IpTunnelSetting);

    return d->tos;
}
void NetworkManager::IpTunnelSetting::setTtl(quint32 ttl)
{
    Q_D(IpTunnelSetting);

    d->ttl = ttl;
}

quint32 NetworkManager::IpTunnelSetting::ttl() const
{
    Q_D(const IpTunnelSetting);

    return d->ttl;
}
void NetworkManager::IpTunnelSetting::setInputKey(const QString& key)
{
    Q_D(IpTunnelSetting);

    d->inputKey = key;
}

QString NetworkManager::IpTunnelSetting::inputKey() const
{
    Q_D(const IpTunnelSetting);

    return d->inputKey;
}

void NetworkManager::IpTunnelSetting::setLocal(const QString& local)
{
    Q_D(IpTunnelSetting);

    d->local = local;
}

QString NetworkManager::IpTunnelSetting::local() const
{
    Q_D(const IpTunnelSetting);

    return d->local;
}

void NetworkManager::IpTunnelSetting::setParent(const QString& parent)
{
    Q_D(IpTunnelSetting);

    d->parent = parent;
}

QString NetworkManager::IpTunnelSetting::parent() const
{
    Q_D(const IpTunnelSetting);

    return d->parent;
}

void NetworkManager::IpTunnelSetting::setOutputKey(const QString& key)
{
    Q_D(IpTunnelSetting);

    d->outputKey = key;
}

QString NetworkManager::IpTunnelSetting::outputKey() const
{
    Q_D(const IpTunnelSetting);

    return d->outputKey;
}

void NetworkManager::IpTunnelSetting::setRemote(const QString& remote)
{
    Q_D(IpTunnelSetting);

    d->remote = remote;
}

QString NetworkManager::IpTunnelSetting::remote() const
{
    Q_D(const IpTunnelSetting);

    return d->remote;
}

void NetworkManager::IpTunnelSetting::fromMap(const QVariantMap &setting)
{
    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_MODE))) {
        setMode((Mode)setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_MODE)).toUInt());
    }

    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_PATH_MTU_DISCOVERY))) {
        setPathMtuDiscovery(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_PATH_MTU_DISCOVERY)).toBool());
    }

   if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_ENCAPSULATION_LIMIT))) {
        setEncapsulationLimit(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_ENCAPSULATION_LIMIT)).toUInt());
    }

    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_FLAGS))) {
        setFlags(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_FLAGS)).toUInt());
    }

    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_FLOW_LABEL))) {
        setFlowLabel(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_FLOW_LABEL)).toUInt());
    }

    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_MTU))) {
        setMtu(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_MTU)).toUInt());
    }

    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_TOS))) {
        setTos(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_TOS)).toUInt());
    }

    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_TTL))) {
        setTtl(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_TTL)).toUInt());
    }

    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_INPUT_KEY))) {
        setInputKey(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_INPUT_KEY)).toString());
    }

    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_LOCAL))) {
        setLocal(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_LOCAL)).toString());
    }

    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_PARENT))) {
        setParent(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_PARENT)).toString());
    }

    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_OUTPUT_KEY))) {
        setOutputKey(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_OUTPUT_KEY)).toString());
    }

    if (setting.contains(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_REMOTE))) {
        setRemote(setting.value(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_REMOTE)).toString());
    }
}

QVariantMap NetworkManager::IpTunnelSetting::toMap() const
{
    QVariantMap setting;

    setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_PATH_MTU_DISCOVERY), pathMtuDiscovery());

    if ((int)mode() > 0) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_MODE), (int)mode());
    }

    if (encapsulationLimit() > 0) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_ENCAPSULATION_LIMIT), encapsulationLimit());
    }

    if (flags() > 0) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_FLAGS), flags());
    }

    if (flowLabel() > 0) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_FLOW_LABEL), flowLabel());
    }

    if (mtu() > 0) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_MTU), mtu());
    }

    if (tos() > 0) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_TOS), tos());
    }

    if (ttl() > 0) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_TTL), ttl());
    }

    if (!inputKey().isEmpty()) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_INPUT_KEY), inputKey());
    }

    if (!local().isEmpty()) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_LOCAL), local());
    }

    if (!parent().isEmpty()) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_PARENT), parent());
    }

    if (!outputKey().isEmpty()) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_OUTPUT_KEY), outputKey());
    }

    if (!remote().isEmpty()) {
        setting.insert(QLatin1String(NMQT_SETTING_IP_TUNNEL_CONFIG_REMOTE), remote());
    }

    return setting;
}

QDebug NetworkManager::operator <<(QDebug dbg, const NetworkManager::IpTunnelSetting &setting)
{
    dbg.nospace() << "type: " << setting.typeAsString(setting.type()) << '\n';
    dbg.nospace() << "initialized: " << !setting.isNull() << '\n';

    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_MODE << ": " << setting.mode() << '\n';
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_PATH_MTU_DISCOVERY << ": " << setting.pathMtuDiscovery() << '\n';
////////////////////
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_ENCAPSULATION_LIMIT << ": " << setting.encapsulationLimit() << '\n';
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_FLAGS << ": " << setting.flags() << '\n';
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_FLOW_LABEL << ": " << setting.flowLabel() << '\n';
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_MTU << ": " << setting.mtu() << '\n';
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_TOS << ": " << setting.tos() << '\n';
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_TTL << ": " << setting.ttl() << '\n';
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_INPUT_KEY << ": " << setting.inputKey() << '\n';
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_LOCAL << ": " << setting.local() << '\n';
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_PARENT << ": " << setting.parent() << '\n';
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_OUTPUT_KEY << ": " << setting.outputKey() << '\n';
    dbg.nospace() << NMQT_SETTING_IP_TUNNEL_CONFIG_REMOTE << ": " << setting.remote() << '\n';

    return dbg.maybeSpace();
}
