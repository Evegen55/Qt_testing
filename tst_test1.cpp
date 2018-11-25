#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class test1 : public QObject
{
    Q_OBJECT

public:
    test1();
    ~test1();



private slots:
    void initTestCase();
    void cleanupTestCase();
    void toUpperSimple();
    void toUpper();
    void toUpper_data();

};

test1::test1()
{

}

test1::~test1()
{

}

void test1::initTestCase()
{

}

void test1::cleanupTestCase()
{

}

void test1::toUpperSimple()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
    QCOMPARE(str.toUpper(), QString("HELLO"));

}
void test1::toUpper()
{

    QFETCH(QString, string);
    QFETCH(QString, result);

    QCOMPARE(string.toUpper(), result);
}

void test1::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("mixed")     << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";
}

QTEST_MAIN(test1)

#include "tst_test1.moc"
