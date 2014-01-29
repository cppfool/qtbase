/****************************************************************************
**
** Copyright (C) 2014 John Layt <jlayt@kde.org>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWINDOWSPRINTDEVICE_H
#define QWINDOWSPRINTDEVICE_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of internal files.  This header file may change from version to version
// without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qfeatures.h> // Some feature dependencies might define QT_NO_PRINTER
#ifndef QT_NO_PRINTER

#include <qpa/qplatformprintdevice.h>

#include <QtCore/qt_windows.h>

QT_BEGIN_NAMESPACE

class QWindowsPrintDevice : public QPlatformPrintDevice
{
public:
    QWindowsPrintDevice();
    explicit QWindowsPrintDevice(const QString &id);
    QWindowsPrintDevice(const QWindowsPrintDevice &other);
    virtual ~QWindowsPrintDevice();

    QWindowsPrintDevice &operator=(const QWindowsPrintDevice &other);

    QWindowsPrintDevice *clone();

    bool operator==(const QWindowsPrintDevice &other) const;

    bool isValid() const Q_DECL_OVERRIDE;
    bool isDefault() const Q_DECL_OVERRIDE;

    QPrint::DeviceState state() const Q_DECL_OVERRIDE;

    QPageSize defaultPageSize() const Q_DECL_OVERRIDE;

    QMarginsF printableMargins(const QPageSize &pageSize, QPageLayout::Orientation orientation,
                               int resolution) const Q_DECL_OVERRIDE;

    int defaultResolution() const Q_DECL_OVERRIDE;

    QPrint::InputSlot defaultInputSlot() const Q_DECL_OVERRIDE;

    QPrint::DuplexMode defaultDuplexMode() const Q_DECL_OVERRIDE;

    QPrint::ColorMode defaultColorMode() const Q_DECL_OVERRIDE;

    static QStringList availablePrintDeviceIds();
    static QString defaultPrintDeviceId();

protected:
    void loadPageSizes() const Q_DECL_OVERRIDE;
    void loadResolutions() const Q_DECL_OVERRIDE;
    void loadInputSlots() const Q_DECL_OVERRIDE;
    void loadOutputBins() const Q_DECL_OVERRIDE;
    void loadDuplexModes() const Q_DECL_OVERRIDE;
    void loadColorModes() const Q_DECL_OVERRIDE;

private:
    HANDLE m_hPrinter;
};

QT_END_NAMESPACE

#endif // QT_NO_PRINTER
#endif // QWINDOWSPRINTDEVICE_H