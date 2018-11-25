#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include <QtWidgets>

class test1 : public QObject
{
    Q_OBJECT

public:
    test1();
    ~test1();

    //tests
private slots:
    void initTestCase();
    void cleanupTestCase();

    void toUpperSimple();
    void toUpper();
    void toUpper_data();

    void testGuiSimple();
    void testGui();
    void testGui_data();
    void simpleBenchmark();
    void multiple();
    void multiple_data();
};

test1::test1()
{

}

test1::~test1()
{

}

//tests implementation
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
//depends on toUpper()
void test1::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");
    //            set of           string      result
    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("mixed")     << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";
}

void test1::testGuiSimple()
{
    QLineEdit lineEdit;

    QTest::keyClicks(&lineEdit, "hello world");

    QCOMPARE(lineEdit.text(), QString("hello world"));

    QSKIP("skipping all");
}

void test1::testGui()
{
    QFETCH(QTestEventList, events);
    QFETCH(QString, expected);

    QLineEdit lineEdit;

    events.simulate(&lineEdit);

    QCOMPARE(lineEdit.text(), expected);
}

//depends on testGui()
void test1::testGui_data()
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("expected");

    QTestEventList list1;
    list1.addKeyClick('a');

    //set of                  events  expected
    QTest::newRow("chars") << list1 << "a";

    QTestEventList list2;
    list2.addKeyClick('a');
    list2.addKeyClick(Qt::Key_Backspace);
    QTest::newRow("there and back again") << list2 << "";
}

void test1::simpleBenchmark()
{
    QString str1 = QLatin1String("This is a test string");
    QString str2 = QLatin1String("This is a test string");

    QCOMPARE(str1.localeAwareCompare(str2), 0);

    QBENCHMARK {
        str1.localeAwareCompare(str2);
    }
}

void test1::multiple_data()
{
    QTest::addColumn<bool>("useLocaleCompare");
    QTest::newRow("locale aware compare") << true;
    QTest::newRow("standard compare") << false;
}

//Data functions are useful for creating benchmarks that compare multiple data inputs,
//for example locale aware compare against standard compare.
void test1::multiple()
{
    QFETCH(bool, useLocaleCompare);
    QString str1 = QLatin1String("This is a test string");
    QString str2 = QLatin1String("This is a test string");

    int result;
    if (useLocaleCompare) {
        QBENCHMARK {
            result = str1.localeAwareCompare(str2);
        }
    } else {
        QBENCHMARK {
            result = (str1 == str2);
        }
    }
    Q_UNUSED(result);
}


QTEST_MAIN(test1)

#include "tst_test1.moc"
