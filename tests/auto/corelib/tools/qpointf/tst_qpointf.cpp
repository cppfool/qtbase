/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QtTest>

#include <qdebug.h>
#include <qpoint.h>

class tst_QPointF : public QObject
{
    Q_OBJECT

public:
    tst_QPointF();

private slots:
    void isNull();

    void manhattanLength_data();
    void manhattanLength();

    void getSet_data();
    void getSet();

    void rx();
    void ry();

    void operator_add_data();
    void operator_add();

    void operator_subtract_data();
    void operator_subtract();

    void operator_multiply_data();
    void operator_multiply();

    void operator_divide_data();
    void operator_divide();
    void division();

    void operator_unary_minus_data();
    void operator_unary_minus();

    void operator_eq_data();
    void operator_eq();

    void toPoint_data();
    void toPoint();

#ifndef QT_NO_DATASTREAM
    void stream_data();
    void stream();
#endif

private:
    const qreal QREAL_MIN;
    const qreal QREAL_MAX;
};

tst_QPointF::tst_QPointF()
: QREAL_MIN(std::numeric_limits<qreal>::min()),
QREAL_MAX(std::numeric_limits<qreal>::max())
{
}

void tst_QPointF::isNull()
{
    QPointF point(0, 0);
    QVERIFY(point.isNull());
    ++point.rx();
    QVERIFY(!point.isNull());
    point.rx() -= 2;
    QVERIFY(!point.isNull());
}

void tst_QPointF::manhattanLength_data()
{
    QTest::addColumn<QPointF>("point");
    QTest::addColumn<qreal>("expected");

    QTest::newRow("(0, 0)") << QPointF(0, 0) << qreal(0);
    QTest::newRow("(10, 0)") << QPointF(10, 0) << qreal(10);
    QTest::newRow("(0, 10)") << QPointF(0, 10) << qreal(10);
    QTest::newRow("(10, 20)") << QPointF(10, 20) << qreal(30);
    QTest::newRow("(10.1, 20.2)") << QPointF(10.1, 20.2) << qreal(30.3);
    QTest::newRow("(-10.1, -20.2)") << QPointF(-10.1, -20.2) << qreal(30.3);
}

void tst_QPointF::manhattanLength()
{
    QFETCH(QPointF, point);
    QFETCH(qreal, expected);

    QCOMPARE(point.manhattanLength(), expected);
}

void tst_QPointF::getSet_data()
{
    QTest::addColumn<qreal>("r");

    QTest::newRow("0") << qreal(0);
    QTest::newRow("-1") << qreal(-1);
    QTest::newRow("1") << qreal(1);
    QTest::newRow("QREAL_MAX") << qreal(QREAL_MAX);
    QTest::newRow("QREAL_MIN") << qreal(QREAL_MIN);
}

void tst_QPointF::getSet()
{
    QFETCH(qreal, r);

    QPointF point;
    point.setX(r);
    QCOMPARE(point.x(), r);

    point.setY(r);
    QCOMPARE(point.y(), r);
}

void tst_QPointF::rx()
{
    const QPointF originalPoint(-1, 0);
    QPointF point(originalPoint);
    ++point.rx();
    QCOMPARE(point.x(), originalPoint.x() + 1);
}

void tst_QPointF::ry()
{
    const QPointF originalPoint(0, -1);
    QPointF point(originalPoint);
    ++point.ry();
    QCOMPARE(point.y(), originalPoint.y() + 1);
}

void tst_QPointF::operator_add_data()
{
    QTest::addColumn<QPointF>("point1");
    QTest::addColumn<QPointF>("point2");
    QTest::addColumn<QPointF>("expected");

    QTest::newRow("(0, 0) + (0, 0)") << QPointF(0, 0) << QPointF(0, 0) << QPointF(0, 0);
    QTest::newRow("(0, 9) + (1, 0)") << QPointF(0, 9) << QPointF(1, 0) << QPointF(1, 9);
    QTest::newRow("(QREAL_MIN, 0) + (1, 0)") << QPointF(QREAL_MIN, 0) << QPointF(1, 0) << QPointF(QREAL_MIN + 1, 0);
    QTest::newRow("(QREAL_MAX, 0) + (-1, 0)") << QPointF(QREAL_MAX, 0) << QPointF(-1, 0) << QPointF(QREAL_MAX - 1, 0);
}

void tst_QPointF::operator_add()
{
    QFETCH(QPointF, point1);
    QFETCH(QPointF, point2);
    QFETCH(QPointF, expected);

    QCOMPARE(point1 + point2, expected);
    point1 += point2;
    QCOMPARE(point1, expected);
}

void tst_QPointF::operator_subtract_data()
{
    QTest::addColumn<QPointF>("point1");
    QTest::addColumn<QPointF>("point2");
    QTest::addColumn<QPointF>("expected");

    QTest::newRow("(0, 0) - (0, 0)") << QPointF(0, 0) << QPointF(0, 0) << QPointF(0, 0);
    QTest::newRow("(0, 9) - (1, 0)") << QPointF(0, 9) << QPointF(1, 0) << QPointF(-1, 9);
    QTest::newRow("(QREAL_MAX, 0) - (1, 0)") << QPointF(QREAL_MAX, 0) << QPointF(1, 0) << QPointF(QREAL_MAX - 1, 0);
    QTest::newRow("(QREAL_MIN, 0) - (-1, 0)") << QPointF(QREAL_MIN, 0) << QPointF(-1, 0) << QPointF(QREAL_MIN - -1, 0);
}

void tst_QPointF::operator_subtract()
{
    QFETCH(QPointF, point1);
    QFETCH(QPointF, point2);
    QFETCH(QPointF, expected);

    QCOMPARE(point1 - point2, expected);
    point1 -= point2;
    QCOMPARE(point1, expected);
}

void tst_QPointF::operator_multiply_data()
{
    QTest::addColumn<QPointF>("point");
    QTest::addColumn<qreal>("factor");
    QTest::addColumn<QPointF>("expected");

    QTest::newRow("(0, 0) * 0.0") << QPointF(0, 0) << qreal(0) << QPointF(0, 0);
    QTest::newRow("(QREAL_MIN, 1) * 0.5") << QPointF(QREAL_MIN, 1) << qreal(0.5) << QPointF(QREAL_MIN * 0.5, 0.5);
    QTest::newRow("(QREAL_MAX, 2) * 0.5") << QPointF(QREAL_MAX, 2) << qreal(0.5) << QPointF(QREAL_MAX * 0.5, 1);
}

void tst_QPointF::operator_multiply()
{
    QFETCH(QPointF, point);
    QFETCH(qreal, factor);
    QFETCH(QPointF, expected);

    QCOMPARE(point * factor, expected);
    // Test with reversed argument version.
    QCOMPARE(factor * point, expected);
    point *= factor;
    QCOMPARE(point, expected);
}

void tst_QPointF::operator_divide_data()
{
    QTest::addColumn<QPointF>("point");
    QTest::addColumn<qreal>("divisor");
    QTest::addColumn<QPointF>("expected");

    QTest::newRow("(0, 0) / 1") << QPointF(0, 0) << qreal(1) << QPointF(0, 0);
    QTest::newRow("(0, 9) / 2") << QPointF(0, 9) << qreal(2) << QPointF(0, 4.5);
    QTest::newRow("(QREAL_MAX, 0) / 2") << QPointF(QREAL_MAX, 0) << qreal(2) << QPointF(QREAL_MAX / qreal(2), 0);
    QTest::newRow("(QREAL_MIN, 0) / -1.5") << QPointF(QREAL_MIN, 0) << qreal(-1.5) << QPointF(QREAL_MIN / qreal(-1.5), 0);
}

void tst_QPointF::operator_divide()
{
    QFETCH(QPointF, point);
    QFETCH(qreal, divisor);
    QFETCH(QPointF, expected);

    QCOMPARE(point / divisor, expected);
    point /= divisor;
    QCOMPARE(point, expected);
}

static inline qreal dot(const QPointF &a, const QPointF &b)
{
    return a.x() * b.x() + a.y() * b.y();
}

void tst_QPointF::division()
{
    {
        QPointF p(1e-14, 1e-14);
        p = p / sqrt(dot(p, p));
        qFuzzyCompare(dot(p, p), 1);
    }
    {
        QPointF p(1e-14, 1e-14);
        p /= sqrt(dot(p, p));
        qFuzzyCompare(dot(p, p), 1);
    }
}

void tst_QPointF::operator_unary_minus_data()
{
    QTest::addColumn<QPointF>("point");
    QTest::addColumn<QPointF>("expected");

    QTest::newRow("-(0, 0)") << QPointF(0, 0) << QPointF(0, 0);
    QTest::newRow("-(-1, 0)") << QPointF(-1, 0) << QPointF(1, 0);
    QTest::newRow("-(0, -1)") << QPointF(0, -1) << QPointF(0, 1);
    QTest::newRow("-(1.2345, 0)") << QPointF(1.2345, 0) << QPointF(-1.2345, 0);
    QTest::newRow("-(-QREAL_MAX, QREAL_MAX)")
        << QPointF(-QREAL_MAX, QREAL_MAX) << QPointF(QREAL_MAX, -QREAL_MAX);
}

void tst_QPointF::operator_unary_minus()
{
    QFETCH(QPointF, point);
    QFETCH(QPointF, expected);

    QCOMPARE(-point, expected);
}

void tst_QPointF::operator_eq_data()
{
    QTest::addColumn<QPointF>("point1");
    QTest::addColumn<QPointF>("point2");
    QTest::addColumn<bool>("expectEqual");

    QTest::newRow("(0, 0) == (0, 0)") << QPointF(0, 0) << QPointF(0, 0) << true;
    QTest::newRow("(-1, 0) == (-1, 0)") << QPointF(-1, 0) << QPointF(-1, 0) << true;
    QTest::newRow("(-1, 0) != (0, 0)") << QPointF(-1, 0) << QPointF(0, 0) << false;
    QTest::newRow("(-1, 0) != (0, -1)") << QPointF(-1, 0) << QPointF(0, -1) << false;
    QTest::newRow("(-1.125, 0.25) == (-1.125, 0.25)") << QPointF(-1.125, 0.25) << QPointF(-1.125, 0.25) << true;
    QTest::newRow("(QREAL_MIN, QREAL_MIN) == (QREAL_MIN, QREAL_MIN)")
        << QPointF(QREAL_MIN, QREAL_MIN) << QPointF(QREAL_MIN, QREAL_MIN) << true;
    QTest::newRow("(QREAL_MAX, QREAL_MAX) == (QREAL_MAX, QREAL_MAX)")
        << QPointF(QREAL_MAX, QREAL_MAX) << QPointF(QREAL_MAX, QREAL_MAX) << true;
}

void tst_QPointF::operator_eq()
{
    QFETCH(QPointF, point1);
    QFETCH(QPointF, point2);
    QFETCH(bool, expectEqual);

    bool equal = point1 == point2;
    QCOMPARE(equal, expectEqual);
    bool notEqual = point1 != point2;
    QCOMPARE(notEqual, !expectEqual);
}

void tst_QPointF::toPoint_data()
{
    QTest::addColumn<QPointF>("pointf");
    QTest::addColumn<QPoint>("expected");

    QTest::newRow("(0.0, 0.0) ==> (0, 0)") << QPointF(0, 0) << QPoint(0, 0);
    QTest::newRow("(0.5, 0.5) ==> (1, 1)") << QPointF(0.5, 0.5) << QPoint(1, 1);
    QTest::newRow("(-0.5, -0.5) ==> (0, 0)") << QPointF(-0.5, -0.5) << QPoint(0, 0);
}

void tst_QPointF::toPoint()
{
    QFETCH(QPointF, pointf);
    QFETCH(QPoint, expected);

    QCOMPARE(pointf.toPoint(), expected);
}

#ifndef QT_NO_DATASTREAM
void tst_QPointF::stream_data()
{
    QTest::addColumn<QPointF>("point");

    QTest::newRow("(0, 0.5)") << QPointF(0, 0.5);
    QTest::newRow("(-1, 1)") << QPointF(-1, 1);
    QTest::newRow("(1, -1)") << QPointF(1, -1);
    QTest::newRow("(INT_MIN, INT_MAX)") << QPointF(INT_MIN, INT_MAX);
}

void tst_QPointF::stream()
{
    QFETCH(QPointF, point);

    QBuffer tmp;
    QVERIFY(tmp.open(QBuffer::ReadWrite));
    QDataStream stream(&tmp);
    // Ensure that stream returned is the same stream we inserted into.
    QDataStream& insertionStreamRef(stream << point);
    QVERIFY(&insertionStreamRef == &stream);

    tmp.seek(0);
    QPointF pointFromStream;
    QDataStream& extractionStreamRef(stream >> pointFromStream);
    QVERIFY(&extractionStreamRef == &stream);
    QCOMPARE(pointFromStream, point);
}
#endif

QTEST_MAIN(tst_QPointF)
#include "tst_qpointf.moc"
