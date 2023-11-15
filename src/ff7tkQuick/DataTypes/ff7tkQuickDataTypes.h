// SPDX-FileCopyrightText: 2023 Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <ff7tkquickdatatypes_export.h>
#include <QObject>
#include <QQmlEngine>

#include <ff7tkInfo>
#include <FF7Text>
#include <FF7Item>
#include <FF7Materia>

struct FF7TKQUICKDATATYPES_EXPORT Info
{
    Q_GADGET
    QML_SINGLETON
    QML_FOREIGN(ff7tkInfo)
    QML_NAMED_ELEMENT(FF7tkInfo)
};


struct FF7TKQUICKDATATYPES_EXPORT FF7TextSingleton
{
    Q_GADGET
    QML_SINGLETON
    QML_FOREIGN(FF7Text)
    QML_NAMED_ELEMENT(FF7Text)
    public:
        inline static FF7Text *s_singletonInstance = nullptr;
        static FF7Text* create(QQmlEngine *, QJSEngine*) {
            QQmlEngine::setObjectOwnership(FF7Text::get(), QQmlEngine::CppOwnership);
            return FF7Text::get();
        }
};

struct FF7TKQUICKDATATYPES_EXPORT FF7ItemSingleton
{
        Q_GADGET
        QML_SINGLETON
        QML_FOREIGN(FF7Item)
        QML_NAMED_ELEMENT(FF7Item)
    public:
        inline static FF7Item *s_singletonInstance = nullptr;
        static FF7Item* create(QQmlEngine *, QJSEngine*) {
            QQmlEngine::setObjectOwnership(FF7Item::get(), QQmlEngine::CppOwnership);
            return FF7Item::get();
        }
};

struct FF7TKQUICKDATATYPES_EXPORT FF7MateriaSingleton
{
        Q_GADGET
        QML_SINGLETON
        QML_FOREIGN(FF7Materia)
        QML_NAMED_ELEMENT(FF7Materia)
    public:
        inline static FF7Materia *s_singletonInstance = nullptr;
        static FF7Materia* create(QQmlEngine *, QJSEngine*) {
            QQmlEngine::setObjectOwnership(FF7Materia::get(), QQmlEngine::CppOwnership);
            return FF7Materia::get();
        }
};
