#include "../headers/tst_mainwindowtest.h"
#include "../headers/tst_mainwindowtest.h"

void MainWindowTest::testOpenFile_data() {
    QTest::addColumn<QString>("fileName");

    // Add test cases for opening different file types
    QTest::newRow("Open Text File") << "test.txt";
    QTest::newRow("Open SQL File") << "test.sql";
    QTest::newRow("Open XML File") << "test.xml";
    // Add more test cases as needed
}

void MainWindowTest::testOpenFile() {
    QFETCH(QString, fileName);

    MainWindow mainWindow;
    QVERIFY(mainWindow.isVisible());

    // Utilize the public method to load a file
    QVERIFY(mainWindow.loadFile(fileName));

    // Assert that the file is loaded correctly
    QCOMPARE(mainWindow.windowTitle(), QString("Expected Title")); // Replace "Expected Title" with the expected window title
    QCOMPARE(mainWindow.getFileExtension(), QString("Expected Extension")); // Replace "Expected Extension" with the expected file extension

    // Additional assertions
    QVERIFY(mainWindow.getCurrentFileName() == fileName); // Verify the current file name
    QVERIFY(mainWindow.getCurrentTabIndex() >= 0); // Verify the current tab index
    // Add more assertions as needed
}

void MainWindowTest::testRecentFileActions() {
    MainWindow mainWindow;
    QVERIFY(mainWindow.isVisible());

    // Simulate recent file actions
    for (int i = 0; i < MainWindow::MaxRecentFiles; ++i) {
        // Utilize the public method to trigger recent file actions
        QVERIFY(mainWindow.triggerRecentFileAction(i));

        // Add more assertions as needed
        QVERIFY(mainWindow.getCurrentFileName() == mainWindow.getRecentFileName(i)); // Verify the current file name matches the recent file name
    }
}

void MainWindowTest::testTabManagement() {
    MainWindow mainWindow;
    QVERIFY(mainWindow.isVisible());

    // Simulate opening and closing tabs
    QVERIFY(mainWindow.loadFile("test.txt"));
    QVERIFY(mainWindow.loadFile("test.sql"));
    QVERIFY(mainWindow.loadFile("test.xml"));

    // Test tab count after opening files
    QCOMPARE(mainWindow.getTabCount(), 3);

    // Close each tab and assert tab count
    for (int i = 0; i < mainWindow.getTabCount(); ++i) {
        mainWindow.closeCurrentTab();
        QCOMPARE(mainWindow.getTabCount(), 3 - (i + 1));
    }

    // Additional assertions
    QVERIFY(mainWindow.getTabCount() == 0); // Verify no tabs are left after closing
    QVERIFY(mainWindow.getCurrentTabIndex() == -1); // Verify no tab is selected after closing
    // Add more assertions as needed
}

void MainWindowTest::testZoom() {
    MainWindow mainWindow;
    QVERIFY(mainWindow.isVisible());

    // Utilize public methods to simulate key events for zooming
    QVERIFY(mainWindow.zoomIn());
    QVERIFY(mainWindow.zoomOut());

    // Assert zoom level changes
    QVERIFY(mainWindow.getCurrentTabZoomLevel() > 1.0); // Zoom level increased
    QVERIFY(mainWindow.getCurrentTabZoomLevel() < 1.0); // Zoom level decreased

    // Additional assertions
    QVERIFY(mainWindow.getCurrentTabZoomLevel() == 1.0); // Verify zoom level is reset
    // Add more assertions as needed
}

// Add more test cases here to cover additional functionalities and edge cases of MainWindow
// Ensure to use publicly accessible methods for testing
// Add more assertions as needed
