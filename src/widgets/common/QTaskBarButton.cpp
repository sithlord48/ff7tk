//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <QTaskBarButton.h>

#ifdef QTASKBAR_WIN
QTaskBarButton::QTaskBarButton(QObject *parent)
    : QObject(parent)
    , pITask(0)
    , _minimum(0)
    , _maximum(100)
    ,_value(0)
    , _state(Invisible)
{
    QWidget *mainWindow = qobject_cast<QWidget*>(parent);
    if(mainWindow)
        _winId = mainWindow->window()->winId();
    else
        _winId = qApp->topLevelWidgets().first()->winId();

    CoInitialize(nullptr);
    HRESULT hRes = CoCreateInstance(CLSID_TaskbarList,
                                    nullptr, CLSCTX_INPROC_SERVER,
                                    IID_ITaskbarList3, reinterpret_cast<LPVOID*>(&pITask));
    if (FAILED(hRes)) {
        pITask = 0;
        CoUninitialize();
        return;
    }
    pITask->HrInit();
}

QTaskBarButton::~QTaskBarButton()
{
    if (pITask) {
        pITask->Release();
        pITask = nullptr;
        CoUninitialize();
    }
}

void QTaskBarButton::setOverlayIcon(const QImage &image, const QString &text)
{
    if (!pITask)
        return;

    if (image.isNull()) {
        pITask->SetOverlayIcon(HWND(_winId), nullptr, nullptr);
    } else {
        const HICON icon = image.toHICON();
        pITask->SetOverlayIcon(HWND(_winId), icon, reinterpret_cast<wchar_t *>(const_cast<ushort *>(text.utf16())));
        DestroyIcon(icon);
    }
}

void QTaskBarButton::setState(State state)
{
    if (!pITask)
        return;

    TBPFLAG flag;
    switch (state) {
    case Invisible:		flag = TBPF_NOPROGRESS;
        break;
    case Indeterminate:	flag = TBPF_INDETERMINATE;
        break;
    case Paused:		flag = TBPF_PAUSED;
        break;
    case Error:			flag = TBPF_ERROR;
        break;
    default:			flag = TBPF_NORMAL;
        break;
    }

    if (S_OK == pITask->SetProgressState(HWND(_winId), flag))
        _state = state;
}

void QTaskBarButton::setValue(int value)
{
    if (!pITask)
        return;

    int completed = value - _minimum, total = _maximum - _minimum;
    if (completed < 0 || total <= 0)
        return;

    if (S_OK == pITask->SetProgressValue(HWND(_winId), completed, total)) {
        _value = value;
        Q_EMIT valueChanged(value);
    }
}

#elif !defined(QTASKBAR_APPLE)

QTaskBarButton::QTaskBarButton(QObject *parent)
    : QObject(parent)
    , _minimum(0)
    , _maximum(100)
    , _value(0)
    , _state(Invisible)
{
}

QTaskBarButton::~QTaskBarButton() {}

void QTaskBarButton::setOverlayIcon(const QImage &image, const QString &text)
{
    Q_UNUSED(image)
    Q_UNUSED(text)
}

void QTaskBarButton::setState(State state)
{
    Q_UNUSED(state)
}

void QTaskBarButton::setValue(int value)
{
    Q_UNUSED(value)
}

#endif

int QTaskBarButton::maximum() const
{
    return _maximum;
}

int QTaskBarButton::minimum() const
{
    return _minimum;
}

QTaskBarButton::State QTaskBarButton::state() const
{
    return _state;
}

int QTaskBarButton::value() const
{
    return _value;
}

void QTaskBarButton::reset()
{
    setState(Normal);
    setValue(0);
}

void QTaskBarButton::setMaximum(int maximum)
{
    _maximum = maximum;
}

void QTaskBarButton::setMinimum(int minimum)
{
    _minimum = minimum;
}

void QTaskBarButton::setRange(int minimum, int maximum)
{
    setMinimum(minimum);
    setMaximum(maximum);
}
