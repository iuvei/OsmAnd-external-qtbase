/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (info@qt.nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWINDOWSCLIPBOARD_H
#define QWINDOWSCLIPBOARD_H

#include "qwindowsinternalmimedata.h"

#include <QtGui/QPlatformClipboard>

QT_BEGIN_NAMESPACE

class QWindowsOleDataObject;

class QWindowsClipboardRetrievalMimeData : public QWindowsInternalMimeData {
public:

protected:
    virtual IDataObject *retrieveDataObject() const;
    virtual void releaseDataObject(IDataObject *) const;
};

class QWindowsClipboard : public QPlatformClipboard
{
public:
    QWindowsClipboard();
    ~QWindowsClipboard();
    void registerViewer(); // Call in initialization, when context is up.

    virtual QMimeData *mimeData(QClipboard::Mode mode = QClipboard::Clipboard);
    virtual void setMimeData(QMimeData *data, QClipboard::Mode mode = QClipboard::Clipboard);
    virtual bool supportsMode(QClipboard::Mode mode) const;
    virtual bool ownsMode(QClipboard::Mode mode) const;

    inline bool clipboardViewerWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT *result);

    static QWindowsClipboard *instance() { return m_instance; }

private:
    void clear();
    void releaseIData();
    inline void propagateClipboardMessage(UINT message, WPARAM wParam, LPARAM lParam) const;
    inline void unregisterViewer();
    inline bool ownsClipboard() const;

    static QWindowsClipboard *m_instance;

    QWindowsClipboardRetrievalMimeData m_retrievalData;
    QWindowsOleDataObject *m_data;
    HWND m_clipboardViewer;
    HWND m_nextClipboardViewer;
};

QT_END_NAMESPACE

#endif // QWINDOWSCLIPBOARD_H
