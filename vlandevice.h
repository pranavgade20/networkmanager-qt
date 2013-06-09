/*
    Copyright 2013 Jan Grulich <jgrulich@redhat.com>

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

#ifndef NMQT_VLAN_DEVICE_H
#define NMQT_VLAN_DEVICE_H

#include "device.h"
#include "NetworkManagerQt-export.h"

namespace NetworkManager {

class VlanDevicePrivate;

class NETWORKMANAGERQT_EXPORT VlanDevice : public Device
{
Q_OBJECT
Q_DECLARE_PRIVATE(VlanDevice)
Q_PROPERTY(bool carrier READ carrier NOTIFY carrierChanged)
Q_PROPERTY(QString hwAddress READ hwAddress NOTIFY hwAddressChanged)
Q_PROPERTY(uint vlanId READ vlanId NOTIFY vlanIdChanged)

public:
    typedef QSharedPointer<VlanDevice> Ptr;
    typedef QList<Ptr> List;

    explicit VlanDevice(const QString& path, QObject* parent = 0);
    virtual ~VlanDevice();

    virtual Type type() const;
    bool carrier() const;
    QString hwAddress() const;
    uint vlanId() const;

Q_SIGNALS:
    void carrierChanged(bool plugged);
    void hwAddressChanged(const QString & address);
    void vlanIdChanged(uint id);

protected:
    /**
     * When subclassing make sure to call the parent class method
     * if the property was not useful to your new class
     */
    virtual void propertyChanged(const QString &property, const QVariant &value);
};

}

#endif
