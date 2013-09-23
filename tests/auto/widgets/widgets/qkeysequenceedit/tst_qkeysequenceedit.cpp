/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the test suite of the Qt Toolkit.
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


#include <QtTest/QtTest>

#include <QKeySequenceEdit>

Q_DECLARE_METATYPE(Qt::Key)
Q_DECLARE_METATYPE(Qt::KeyboardModifiers)

class tst_QKeySequenceEdit : public QObject
{
    Q_OBJECT

private slots:
    void testSetters();
    void testKeys_data();
    void testKeys();
};

void tst_QKeySequenceEdit::testSetters()
{
    QKeySequenceEdit edit;
    QSignalSpy spy(&edit, SIGNAL(keySequenceChanged(QKeySequence)));
    QCOMPARE(edit.keySequence(), QKeySequence());

    edit.setKeySequence(QKeySequence::New);
    QCOMPARE(edit.keySequence(), QKeySequence(QKeySequence::New));

    edit.clear();
    QCOMPARE(edit.keySequence(), QKeySequence());

    QCOMPARE(spy.count(), 2);
}

void tst_QKeySequenceEdit::testKeys_data()
{
    QTest::addColumn<Qt::Key>("key");
    QTest::addColumn<Qt::KeyboardModifiers>("modifiers");
    QTest::addColumn<QKeySequence>("keySequence");

    QTest::newRow("1") << Qt::Key_N << Qt::KeyboardModifiers(Qt::ControlModifier) << QKeySequence("Ctrl+N");
    QTest::newRow("2") << Qt::Key_N << Qt::KeyboardModifiers(Qt::AltModifier) << QKeySequence("Alt+N");
    QTest::newRow("3") << Qt::Key_N << Qt::KeyboardModifiers(Qt::ShiftModifier) << QKeySequence("Shift+N");
    QTest::newRow("4") << Qt::Key_N << Qt::KeyboardModifiers(Qt::ControlModifier  | Qt::ShiftModifier) << QKeySequence("Ctrl+Shift+N");
}

void tst_QKeySequenceEdit::testKeys()
{
    QFETCH(Qt::Key, key);
    QFETCH(Qt::KeyboardModifiers, modifiers);
    QFETCH(QKeySequence, keySequence);
    QKeySequenceEdit edit;

    QSignalSpy spy(&edit, SIGNAL(editingFinished()));
    QTest::keyPress(&edit, key, modifiers);
    QTest::keyRelease(&edit, key, modifiers);

    QCOMPARE(spy.count(), 0);
    QCOMPARE(edit.keySequence(), keySequence);
    QTRY_COMPARE(spy.count(), 1);
}

QTEST_MAIN(tst_QKeySequenceEdit)
#include "tst_qkeysequenceedit.moc"